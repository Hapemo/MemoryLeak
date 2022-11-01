/*!*****************************************************************************
\file GameState3.cpp
\author Jazz Teoh Yu Jue
\par DP email: j.teoh\@digipen.edu
\par Group: Memory Leak Studios
\date 24-09-2022
\brief
Game state for testing physics
*******************************************************************************/
#include "AIDemo.h"
#include "Application.h"

void AIDemo::Load() {
	//serializationManager->LoadScene("SceneJUX");
    LoadWithGUID(16665530225855236);
}

void AIDemo::Init() {
   
}

void AIDemo::Update() {

}

void AIDemo::Draw() {
    renderManager->Render();
}

void AIDemo::Free() {
    ECS::DestroyAllEntities();
}

void AIDemo::Unload() {
    
    renderManager->Clear();
}





