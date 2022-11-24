/*!*****************************************************************************
\file GameStateManager.h
\author Jazz Teoh Yu Jue
\par DP email: j.teoh\@digipen.edu
\par Group: Memory Leak Studios
\date 24-09-2022
\brief
Manages the gamestate flow, control which game state is running or will be 
running.
*******************************************************************************/
#pragma once
#include "pch.h"
#include "Singleton.h"
#include "GameState.h"

class GameStateManager : public Singleton<GameStateManager> {
public:
	GameStateManager();
	~GameStateManager() {};

	/*!*****************************************************************************
	\brief
	Initialise all the game states that will be ran and the starting game state
	*******************************************************************************/
	void Init();

	/*!*****************************************************************************
	\brief
	Main game update loop. Runs application's updates and current game state's 
	update. 
	*******************************************************************************/
	void Update();

	/*!*****************************************************************************
	\brief
	Unload all game states befor exiting the game. Should be called in application
	exit
	*******************************************************************************/
	void Unload();

	/*!*****************************************************************************
	\brief
	Controls the next gamestate to run with input keys. Should be called after
	current game state.
	*******************************************************************************/
	//static void GSControlPanel();

	enum class E_GSMSTATE {
		EXIT,
		RESTART,
		RUNNING,
		CHANGING,
		STARTING // Currently no use, just informative
	};

	static const std::string EXIT;
	static const std::string RESTART;
	static Scene mErrorScene;
	static const Entity mErrorEntity;
	static E_GSMSTATE mGSMState;
	GameState* mCurrentGameState; // During game, this shouldn't change at all. Editor mode can change this, depending on which game state is being changed.

	// This function is called by user, to change the next game state
	// User can use game state manager's defined string type EXIT and RESTART to change state.
	void ChangeGameState(std::string const& _path);
	void UpdateNextGSMState();
	Scene& SelectScene(std::string const& _name);
	Entity GetEntity(std::string const& _entityName, std::string const& _sceneName); // Get an entity from current gamestate.

	// Editor only functionalities
	void AddGameState(std::filesystem::path const& _path = std::filesystem::path());
	void RemoveGameState(GameState* = nullptr);
	void SetGameState(std::string const& _name);

	//void setgamestate();

	void SetNextGSPath(std::string const& _path) { mNextGSPath = _path; }

	std::vector<GameState> mGameStates{}; // Only 1 in game, multi gamestates allowed during editor mode
	std::map<std::string,std::vector<bool>> mGameStatesScenesPause; // One std::vector<bool> for each game state to keep record of their pause
	std::string mNextGSPath;

private:

	// Update the next game state at the end of game loop (Must be called the last)
};

