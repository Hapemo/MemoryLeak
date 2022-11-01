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
}

void AIDemo::Unload() {
    
}





