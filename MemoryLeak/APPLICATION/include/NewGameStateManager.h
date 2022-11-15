/*!*****************************************************************************
\file NewGameStateManager.h
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

class NewGameState;

class NewGameStateManager : public Singleton<NewGameStateManager> {
public:
	NewGameStateManager();
	~NewGameStateManager() {};

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
	void Exit();

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
		STARTING
	};

	static const std::string EXIT;
	static const std::string RESTART;
	
	// This function is called by user, to change the next game state
	// User can use game state manager's defined string type EXIT and RESTART to change state.
	void ChangeGameState(std::string const& _path);

	// Editor only functionalities
	void AddGameState(std::string const& _path);
	void RemoveGameState(std::string const& _name);

private:
	std::vector<NewGameState> mGameStates; // Only 1 in game, multi gamestates allowed during editor mode
	NewGameState* mCurrentGameState; // During game, this shouldn't change at all. Editor mode can change this, depending on which game state is being changed.
	std::string mNextGSPath;
	static E_GSMSTATE mGSMState; 

	// Update the next game state at the end of game loop (Must be called the last)
	void UpdateNextGSMState();
};

