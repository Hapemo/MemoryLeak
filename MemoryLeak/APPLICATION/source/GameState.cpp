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
// Nothing for now

void GameState::LoadWithGUID(ResourceManager::GUID const& _guid) {
  LOG_CUSTOM("GAMESTATE", "Loading GameState " + std::to_string(_guid));
  GameStateData gamestateData = ResourceManager::GetInstance()->LoadGameState(_guid);
  //mEntities = gamestateData.mEntities;
  mGuid = _guid;
  // Scenes are currently loaded here, but in future, it will be done via resource manager.
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

// This should be called when unloading from the editor. 
// Save all scenes it has and save all it's entities.
void GameState::SaveGameState() {
  // Get gamestate data
  GameStateData gsData{};
  for (auto scenePtr : mScenes)
    gsData.mGUIDs.push_back(scenePtr->mGuid);

  // Open output file to save in
  std::string filePath{ ResourceManager::GetInstance()->GetFilePath(mGuid)};
  if (filePath.size() < 1) { // When there is no existing gamestate file, create one. NOTE: Once created, user is expected to change this save file's name.
    filePath = ResourceManager::GetInstance()->FileTypePath(ResourceManager::E_RESOURCETYPE::gamestateEntities).string() + "NewGameState.json";
  }
  std::ofstream outFile{ filePath };
  if (!outFile.is_open()) {
    LOG_WARN("Unable to save gamestate file: " + filePath);
    return;
  }

  // Save the gamestate data into output file using serialisation manager
  // DeserialiseGameStateData(gsData, outFile);
}

void GameState::CreateScene(std::string const& _name) {
  Scene* scene = new Scene(_name);
  
  mScenes.push_back(scene);
}

void GameState::PrimaryLoad() {
  Load();
  editorManager->Init();
  logicSystem->Init();
}

void GameState::PrimaryUnload() {
  Unload();
  UnloadWithGUID();
  renderManager->Clear();
  renderManager->ResetCameras();
  if (Coordinator::GetInstance()->GetEntityCount() != 0)
    LOG_ERROR("There remains " + std::to_string(Coordinator::GetInstance()->GetEntityCount()) + " after Unloading GameState " + std::to_string(mGuid));
  // Put in gamestate init later
}
