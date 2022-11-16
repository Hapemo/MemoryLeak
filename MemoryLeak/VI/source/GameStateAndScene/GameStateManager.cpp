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
	LOG_CUSTOM_CREATE("GAMESTATEMANAGER");

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
	LOG_CUSTOM("GAMESTATEMANAGER", "Set gamestate to change to: " + _path);
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

void GameStateManager::AddGameState(std::filesystem::path const& _path) {
	LOG_CUSTOM("GAMESTATEMANAGER", "Add gamestate: " + _path.string());
	mGameStates.emplace_back(GameState());
	
	if (_path.string().size() < 0)
		mGameStates.back().mName = "New GameState";
	else
		mGameStates.back().Load(_path);

	SetGameState(_path.stem().string());  //Call set game state to chnage is paused of entites
	//mCurrentGameState = &mGameStates.back();
}

void GameStateManager::RemoveGameState(GameState* _gameState) {
	if (!_gameState) {
		_gameState = mCurrentGameState;
		if (!_gameState) {
			LOG_WARN("There is no existing gamestate to be removed");
			return;
		}
	}

	for (auto it = mGameStates.begin(); it != mGameStates.end(); ++it) {
		if (it->mName == _gameState->mName) {
			it->Exit();
			it->Unload();
			mGameStates.erase(it);
			LOG_CUSTOM("GAMESTATEMANAGER", "Removed gamestate: " + _gameState->mName);
			if (mCurrentGameState = &*it) {
				if (mGameStates.empty())
					mCurrentGameState = nullptr;
				else mCurrentGameState = &mGameStates.front();
			}
			return;
		}
	}
	LOG_WARN("Unable to find gamestate to remove: " + _gameState->mName);
}

void GameStateManager::SetGameState(std::string const& _name) {
	for (auto& gs : mGameStates) {
		if (gs.mName == _name) {
			//for (auto& scene : mCurrentGameState->mScenes)  //set pause true for prevoius scene (dont chane scene.mIsPause as it stores the original value)
			//	for (auto& e : scene.mEntities)
			//		e.GetComponent<General>().isPaused = true;
			//
			//for (auto& scene : gs.mScenes)  //set pause false for current scene iif scene not paused
			//	for (auto& e : scene.mEntities)
			//		e.GetComponent<General>().isPaused = scene.mIsPause;

			mCurrentGameState = &gs;
			LOG_CUSTOM("GAMESTATEMANAGER", "Set gamestate to: " + _name);
			return;
		}
	}
	LOG_WARN("Unable to find gamestate to set to: " + _name);
}

void GameStateManager::Unload() {
	LOG_CUSTOM("GAMESTATEMANAGER", "Unload GameStateManager");
	for (auto& gameState : mGameStates) {
		gameState.Exit();
		gameState.Unload();
	}
	mCurrentGameState = nullptr;
	mNextGSPath = "";
}