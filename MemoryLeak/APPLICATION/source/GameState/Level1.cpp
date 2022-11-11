/*!*****************************************************************************
\file GameStatePhysics.cpp
\author Huang Wei Jhin
\par DP email: h.weijhin\@digipen.edu
\par Group: Memory Leak Studios
\date 05-11-2022
\brief
Game state for level 1
*******************************************************************************/
#include "Level1.h"
#include "Application.h"
#include "Input.h"


void Level1::Load() {
	serializationManager->LoadScene("Scene_Level1");
}

void Level1::Init() {
	for (Scene* scenePtr : mScenes)
		scenePtr->Init();
}

void Level1::Update() {
	for (Scene* scenePtr : mScenes)
		scenePtr->PrimaryUpdate();
	for (const Entity& e : mEntities)
	{
		if (e.GetComponent<General>().tag == TAG::PLAYER)
		{
			renderManager->GetGameCamera().SetPos(e.GetComponent<Transform>().translation);
			break;
		}
	}
}

void Level1::Draw() {
	renderManager->Render();
}

void Level1::Free() {
	for (auto& scenePtr : mScenes)
		scenePtr->Exit();
}

void Level1::Unload() {
	ECS::DestroyAllEntities();
}