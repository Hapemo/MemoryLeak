/*!*****************************************************************************
\file GameStatePhysics.cpp
\author Huang Wei Jhin
\par DP email: h.weijhin\@digipen.edu
\par Group: Memory Leak Studios
\date 01-11-2022
\brief
Game state for level 1
*******************************************************************************/
#include "Level1.h"
#include "Application.h"
#include "Input.h"
#include "TestScript.h"

void Level1::Load() {
	LoadWithGUID(16669349234147588);
}

void Level1::Init() {
	for (Scene* scenePtr : mScenes)
		scenePtr->Init();
}

void Level1::Update() {
	for (Scene* scenePtr : mScenes)
		scenePtr->PrimaryUpdate();
}

void Level1::Draw() {
	for (Scene* scenePtr : mScenes)
		scenePtr->PrimaryUpdate();
	renderManager->Render();
}

void Level1::Free() {
	for (auto& scenePtr : mScenes)
		scenePtr->Exit();
	ECS::DestroyAllEntities();
}

void Level1::Unload() {
	renderManager->Clear();
}