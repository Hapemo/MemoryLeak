/*!*****************************************************************************
\file GameStateManager.cpp
\author Jazz Teoh Yu Jue
\par DP email: j.teoh\@digipen.edu
\par Group: Memory Leak Studios
\date 24-09-2022
\brief
Manages the gamestate flow, control which game state is running or will be
running.
*******************************************************************************/
#include "GameStateManager.h"
#include "GameState.h"
#include "Helper.h"
#include "PerformanceVisualiser.h"
#include "ResourceManager.h"
#include "Graphics/RenderManager.h"
#include "Graphics/SpriteManager.h"
#include "Input.h"

const std::string GameStateManager::EXIT{ "Exit" };
const std::string GameStateManager::RESTART{ "Restart" };
GameStateManager::E_GSMSTATE GameStateManager::mGSMState{ GameStateManager::E_GSMSTATE::STARTING };

GameStateManager::GameStateManager() : mGameStates(), mCurrentGameState(nullptr), mNextGSPath("") {};

// Load the first game state.
void GameStateManager::Init() {
	LOG_CUSTOM_CREATE("SCENE");
	LOG_CUSTOM_CREATE("GAMESTATE");

	mGameStates.emplace_back(GameState());
	mCurrentGameState = &mGameStates.front();

	mCurrentGameState->Load(mNextGSPath);
	mCurrentGameState->Init();
	mGSMState = E_GSMSTATE::RUNNING;
}

void GameStateManager::Update() {
	mCurrentGameState->Update(); // Game logic
}

void GameStateManager::UpdateNextGSMState() {
	if (mGSMState == E_GSMSTATE::RUNNING) return; // No change in GS, ignore.

	mCurrentGameState->Exit();

	switch (mGSMState) {
	case E_GSMSTATE::EXIT:
		mCurrentGameState->Unload();
		return;
	case E_GSMSTATE::RESTART:
		mCurrentGameState->Init();
		break;
	case E_GSMSTATE::CHANGING:
		// Changing gamestate to some other gamestate.
		mCurrentGameState->Unload();
		mCurrentGameState->Load(mNextGSPath);
		mCurrentGameState->Init();
		break;
	}

	mGSMState = E_GSMSTATE::RUNNING;
}

void GameStateManager::ChangeGameState(std::string const& _path) {
	
	// Check if exit or restart;
	if (_path == EXIT)
		mGSMState = E_GSMSTATE::EXIT;
	else if (_path == RESTART)
		mGSMState = E_GSMSTATE::RESTART;
	else if (!ResourceManager::FileExist(_path)) {
		LOG_ERROR("Unable to change gamestate to: " + _path);
		return;
	} else {
		mNextGSPath = _path;
		mGSMState = E_GSMSTATE::CHANGING;
	}

}


void GameStateManager::Exit() {

}