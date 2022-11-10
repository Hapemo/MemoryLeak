/*!*****************************************************************************
\file GameState.cpp
\author Jazz Teoh Yu Jue
\par DP email: j.teoh\@digipen.edu
\par Group: Memory Leak Studios
\date 24-09-2022
\brief
Game state base class, contains Load, Init, Update, Draw, Free and Unload
functions.

For Milestone 2:
Added load and unload of game state using resourceManager
Added encapsulation of scenes in game state

How to make a gamestate?

1. Make a class for your gamestate, inherited from class GameState
2. Declare and define all the virtual functions
3. In GameStateManager.h > class enum GS, make a new enum for your game state
4. In GameStateManager's Init(), make a new line "GS_list.insert(GS_pair(<GS>,
	 new <GameState>));" where <GS> is your game state's enum and <GameState> is
	 your game state class
*******************************************************************************/
#include "GameState.h"
#include "Scene.h"
#include "Serialization.h"
#include "ScriptManager.h"
#include "ScriptComponent.h"
// Nothing for now

void GameState::LoadWithGUID(ResourceManager::GUID const& _guid) {
  LOG_CUSTOM("GAMESTATE", "Loading GameState " + std::to_string(_guid));
  GameStateData gamestateData = ResourceManager::GetInstance()->LoadGameState(_guid);
  mEntities = gamestateData.mEntities;
  mGuid = _guid;
  for (ResourceManager::GUID const& guid : gamestateData.mGUIDs) {
    Scene* scene = new Scene(guid);
    scene->Load(guid);
    mScenes.push_back(scene);
  }
}

void GameState::UnloadWithGUID() {
  LOG_CUSTOM("GAMESTATE", "Unloading GameState " + std::to_string(mGuid));
  if (mGuid == 0) {
    LOG_ERROR("Current game state unloaded without guid\n");
    return;
  }

  for (Scene* scene : mScenes) {
    scene->Unload();
    delete scene;
  }
  mScenes.clear();
  ResourceManager::GetInstance()->UnloadGameState(mGuid);
  mEntities.clear();
}

void GameState::CreateScene() {
  Scene* scene = new Scene;
  
  mScenes.push_back(scene);
}

void GameState::PrimaryLoad() {
  Load();
  editorManager->Init();
}

void GameState::PrimaryUnload() {
  Unload();
  UnloadWithGUID();
  renderManager->Clear();
  renderManager->ResetCameras();
  if (Coordinator::GetInstance()->GetEntityCount() != 0)
    LOG_ERROR("There remains " + std::to_string(Coordinator::GetInstance()->GetEntityCount()) + " after Unloading GameState " + std::to_string(mGuid));
  ECS::DestroyAllEntities();
  // Put in gamestate init later
}
