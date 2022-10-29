/*!*****************************************************************************
\file GameState.cpp
\author Jazz Teoh Yu Jue
\par DP email: j.teoh\@digipen.edu
\par Group: Memory Leak Studios
\date 24-09-2022
\brief
Game state base class, contains Load, Init, Update, Draw, Free and Unload
functions.

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
// Nothing for now

void GameState::LoadWithGUID(ResourceManager::GUID const& _guid) {
  LOG_CUSTOM("GAMESTATE", "Loading GameState " + std::to_string(_guid));
  GameStateData gamestateData = ResourceManager::GetInstance()->LoadGameState(_guid);
  mEntities = gamestateData.mEntities;
  mGuid = _guid;
  for (ResourceManager::GUID const& guid : gamestateData.mGUIDs) {
    LOG_CUSTOM("SCENE", "Loading Scene " + std::to_string(guid));
    Scene* scene = new Scene(guid);
    mScenes.push_back(scene);
    SceneData sceneData = ResourceManager::GetInstance()->LoadScene(guid);
    scene->mEntities = sceneData.mEntities;
    scene->pause = sceneData.isActive;
  }
}

void GameState::UnloadWithGUID() {
  LOG_CUSTOM("GAMESTATE", "Unloading GameState " + std::to_string(mGuid));
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
