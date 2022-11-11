/*!*****************************************************************************
\file GameStatePhysics.cpp
\author Jazz Teoh Yu Jue
\par DP email: j.teoh\@digipen.edu
\par Group: Memory Leak Studios
\date 01-11-2022
\brief
Game state for testing physics
*******************************************************************************/
#include "GameStatePhysics.h"
#include "Application.h"
#include "Input.h"
#include "TestScript.h"

void GameStatePhysics::Load() {
	serializationManager->LoadScene("SceneJPhysics");
}

void GameStatePhysics::Init() {
	for (Scene* scenePtr : mScenes)
		scenePtr->Init();
}

void GameStatePhysics::Update() {
	for (Scene* scenePtr : mScenes)
		scenePtr->PrimaryUpdate();
}

void GameStatePhysics::Draw() {
	renderManager->Render();
}

void GameStatePhysics::Free() {
	for (auto& scenePtr : mScenes)
		scenePtr->Exit();
}

void GameStatePhysics::Unload() {
	ECS::DestroyAllEntities();
}