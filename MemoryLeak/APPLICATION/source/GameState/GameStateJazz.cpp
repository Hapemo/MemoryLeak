/*!*****************************************************************************
\file GameStateJazz.cpp
\author Jazz Teoh Yu Jue
\par DP email: j.teoh\@digipen.edu
\par Group: Memory Leak Studios
\date 24-09-2022
\brief
Game state for testing physics
*******************************************************************************/
#include "GameStateJazz.h"
#include "Application.h"
#include "Input.h"

void LoadGameStateFile() { // This should be called in ResourceManager
  // File format shall be a json file. First line is a list of GUID
  // Second line and there after shall be entity data

  // Read in saved data 
  // Store all scene GUID in a member container in GameState
  // Load in all entity data into ECS
}

void LoadSceneFiles() {
  // Loop through all scene GUID in GameState
  // Load each scene file (This should be done in resource manager)
  // Add pointer to those scenes to current GameState
}

void GameStateJazz::Load() {
  //ResourceManager::GetInstance()->LoadAllResources();

  // Load gamestate's saved data in json (It should contain GUID of gamestateEntities and scenes)
  // Then append the information from ResourceManager to game state
  //LoadGameStateFile();
  //GameStateData gamestateData = ResourceManager<>
  // Load in each scenes

  //for (size_t index = 0; index < GET_RESOURCES().size(); ++index)
  //  spriteManager->InitializeTexture(GET_TEXTURE_DATA(index));
  renderManager->SetVectorLengthModifier(5.f);
  renderManager->SetDebug(true);

  LoadWithGUID(16667121456447749);
}

void GameStateJazz::Init() {
  for (Scene* scenePtr : mScenes)
    scenePtr->Init();
  //serializationManager->LoadSceneData(16665530225854980);
  //serializationManager->LoadScene("SceneJPhysics");
}

void GameStateJazz::Update() {
  for (Scene* scenePtr : mScenes)
    scenePtr->PrimaryUpdate();
}

void GameStateJazz::Draw() {
  renderManager->Render();
  //renderManager->RenderDebug();
}

void GameStateJazz::Free() {
  for (auto& scenePtr : mScenes)
    scenePtr->Exit();
}

void GameStateJazz::Unload() {
  renderManager->Clear();
  UnloadWithGUID();
  //spriteManager->FreeTextures();
  //ResourceManager::GetInstance()->UnloadAllResources();
}





