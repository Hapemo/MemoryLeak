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

	mGameStatesScenesPause.insert({ mCurrentGameState->mName, std::vector<bool>() }); // FOR EDITOR

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

Scene& GameStateManager::SelectScene(std::string const& _name) {
	for (auto& scene : mCurrentGameState->mScenes)
		if (scene.mName == _name) return scene;

	static Scene errScene("Error");
	LOG_ERROR("Unable to select scene: " + _name);
	return errScene;
}

void GameStateManager::ChangeGameState(std::string const& _name) {
	LOG_CUSTOM("GAMESTATEMANAGER", "Set gamestate to change to: " + _name);
	std::string path{ ResourceManager::GetInstance()->FileTypePath(ResourceManager::E_RESOURCETYPE::gamestateEntities).string() + _name + ".json" };
	// Check if exit or restart;
	if (_name == EXIT)
		mGSMState = E_GSMSTATE::EXIT;
	else if (_name == RESTART)
		mGSMState = E_GSMSTATE::RESTART;
	else if (!ResourceManager::FileExist(path)) {
		LOG_ERROR("Unable to change gamestate to: " + _name);
		return;
	} else {
		mNextGSPath = path;
		mGSMState = E_GSMSTATE::CHANGING;
	}
}

void GameStateManager::AddGameState(std::filesystem::path const& _path) {
	std::string currName{ mCurrentGameState->mName };

	mGameStates.push_back(GameState());
	
	for (auto& gs : mGameStates) 
		if (gs.mName == currName) 
			mCurrentGameState = &gs; // This line is required because push_back changes arrangement of gamestates, messing up where mCurrentGameState is pointing at.
	
	if (_path.string().size() == 0) {
		static int newGSCount = 1;
		mGameStates.back().mName = "New GameState " + std::to_string(newGSCount++);  //cannot have same GS name
		LOG_CUSTOM("GAMESTATEMANAGER", "Add NEW gamestate");
	} else {
		mGameStates.back().Load(_path);
		LOG_CUSTOM("GAMESTATEMANAGER", "Add gamestate: " + _path.string());
	}

	// FOR EDITOR
	std::vector<bool> pausedList{};
	for (Scene& scene : mGameStates.back().mScenes)
		pausedList.push_back(scene.mIsPause);

	mGameStatesScenesPause.insert({ mGameStates.back().mName, pausedList }); // FOR EDITOR
	//SetGameState(_path.stem().string());  //Call set game state to chnage is paused of entites
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
		// Find the game state
		if (it->mName == _gameState->mName) {
			// Do necessary unloading 
			it->Exit();
			it->Unload();
			mGameStatesScenesPause.erase(mGameStatesScenesPause.find(it->mName)); // FOR EDITOR
			std::string currName{ mCurrentGameState->mName };
			// Erase selected gs from pool
			if (mCurrentGameState == &*it) {
				if (mGameStates.empty())
					mCurrentGameState = nullptr;
				else mCurrentGameState = &mGameStates.front();
			}
			mGameStates.erase(it);
			//if (!mGameStates.size()) {
			//	LOG_CUSTOM("GAMESTATEMANAGER", "No more gamestate exists after removing this gamestate: " + _gameState->mName);
			//	mCurrentGameState = nullptr;
			//}
			//for (auto& gs : mGameStates) if (gs.mName == currName) mCurrentGameState = &gs; // This line is required because removing gamestates from vector changes arrangement of gamestates, 
																																											// messing up where mCurrentGameState is pointing at.
			LOG_CUSTOM("GAMESTATEMANAGER", "Removed gamestate: " + _gameState->mName);

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

			// save curr gamestate scene pause, and pause all the scenes
			std::vector<bool>& currPauseList = mGameStatesScenesPause[mCurrentGameState->mName];
			currPauseList.clear();
			currPauseList.resize(mCurrentGameState->mScenes.size());
			for (size_t i{}; i < mCurrentGameState->mScenes.size(); ++i) {
				currPauseList[i] = mCurrentGameState->mScenes[i].mIsPause;
				mCurrentGameState->mScenes[i].Pause(true);
			}

			// load next gamestate scene pause, and unload all the saved pause status to the scenes
			mCurrentGameState = &gs;
			std::vector<bool>& nextPauseList = mGameStatesScenesPause[mCurrentGameState->mName];
			for (size_t i{}; i < mCurrentGameState->mScenes.size(); ++i) {
				mCurrentGameState->mScenes[i].Pause(nextPauseList[i]);
			}
			nextPauseList.clear();

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