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
  //renderManager->SetClearColor({ 0,0,0,255 });

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
  //spriteManager->FreeTextures();
  //ResourceManager::GetInstance()->UnloadAllResources();
}





