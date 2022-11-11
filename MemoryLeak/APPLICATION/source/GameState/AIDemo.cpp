/*!*****************************************************************************
\file AIDemo.cpp
\author Huang Wei Jhin
\par DP email: h.weijhin\@digipen.edu
\par Group: Memory Leak Studios
\date 24-09-2022
\brief
Game state for testing AI
*******************************************************************************/
#include "AIDemo.h"
#include "Application.h"

void AIDemo::Load() {
	serializationManager->LoadScene("Scene_AIDemo");
}

void AIDemo::Init() {
    for (Scene* scenePtr : mScenes)
        scenePtr->Init();
}

void AIDemo::Update() {
    for (Scene* scenePtr : mScenes)
        scenePtr->PrimaryUpdate();
}

void AIDemo::Draw() {
    renderManager->Render();
}

void AIDemo::Free() {
    for (auto& scenePtr : mScenes)
        scenePtr->Exit();
}

void AIDemo::Unload() {
    ECS::DestroyAllEntities();
    
}





