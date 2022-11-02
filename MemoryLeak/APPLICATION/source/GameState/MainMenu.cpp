/*!*****************************************************************************
\file GameStatePhysics.cpp
\author Huang Wei Jhin
\par DP email: h.weijhin\@digipen.edu
\par Group: Memory Leak Studios
\date 05-11-2022
\brief
Game state for main menu
*******************************************************************************/
#include "MainMenu.h"
#include "Application.h"
#include "Input.h"


void MainMenu::Load() {
	//serializationManager->LoadScene("Scene_MainMenu");
	LoadWithGUID(16672089683329284);
}

void MainMenu::Init() {
	for (Scene* scenePtr : mScenes)
		scenePtr->Init();
}

void MainMenu::Update() {
	for (Scene* scenePtr : mScenes)
		scenePtr->PrimaryUpdate();
}

void MainMenu::Draw() {
	renderManager->Render();
}

void MainMenu::Free() {
	for (auto& scenePtr : mScenes)
		scenePtr->Exit();
}

void MainMenu::Unload() {
}