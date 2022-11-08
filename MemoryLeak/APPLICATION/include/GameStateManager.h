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

class GameState;
// Game state ID
enum class E_GS {
	INVALID,
	MainMenu,
	Level1,
	PHYSICS,
	ScriptingDemo,
	Lighting,
	ParallaxSprite,
	AIDemo,
	END_OF_LIST,
	RESTART,
	EXIT
};
E_GS& operator++(E_GS& _gs);
E_GS& operator--(E_GS& _gs);

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
	void Exit();

	/*!*****************************************************************************
	\brief
	Point the game state function pointer to current game state's function
	*******************************************************************************/
	void SetNewGameState();

	/*!*****************************************************************************
	\brief
	Set the next game state

	\param E_GS
	- Game State to set next game state to
	*******************************************************************************/
	void NextGS(E_GS);

	//------------------------------------------------------------------------------
	// Getters
	//------------------------------------------------------------------------------
	E_GS GetNextGS() { return mNextGS; }
	E_GS GetCurrGS() { return mCurrGS; }
	E_GS GetPrevGS() { return mPrevGS; }
	void SetStartingGS(E_GS _gs) { mStartingGS = _gs; }

	/*!*****************************************************************************
	\brief
	Controls the next gamestate to run with input keys. Should be called after
	current game state.
	*******************************************************************************/
	static void GSControlPanel();

private:
	using FP = void (*)(void);
	using GS_pair = std::pair<E_GS, GameState*>;

	std::map<E_GS, GameState*> GS_List;
	E_GS mCurrGS, mPrevGS, mNextGS, mStartingGS;
	GameState* mCurrGameState;
	static E_GS mCurrentState;
};


