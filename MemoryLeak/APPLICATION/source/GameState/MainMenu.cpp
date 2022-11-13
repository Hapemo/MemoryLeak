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
#include "VertexFetcher.h"
#include <GameStateManager.h>


void MainMenu::Load() {
	//serializationManager->LoadScene("Scene_MainMenu");
}

void MainMenu::Init() {
	/*for (Scene* scenePtr : mScenes)
		scenePtr->Init();*/
}


void MainMenu::Update() {
	buttonManager->Update();
	//for (const Entity& e : mEntities)
	//{
	//	if (!e.HasComponent<Button>()) continue;
	//	if (e.GetComponent<General>().subtag == SUBTAG::PLAYER && e.GetComponent<Button>().activated)
	//	{
	//		GameStateManager::GetInstance()->NextGS(E_GS::Level1);
	//	}
	//	if (e.GetComponent<General>().subtag == SUBTAG::ENEMY && e.GetComponent<Button>().activated)
	//	{
	//		GameStateManager::GetInstance()->NextGS(E_GS::EXIT);
	//	}
	//}

	/*if (renderManager->GetRenderGameToScreen())
	{
		Math::Vec2 cursorPos = Math::Vec2(Input::CursorPos().x, -Input::CursorPos().y) +
			Math::Vec2(-Application::getWindowWidth() / 2.f, Application::getWindowHeight() / 2.f);
		for (const Entity& e : mEntities)
		{
			if (e.GetComponent<General>().tag != TAG::ENVIRONMENT)
				continue;
			if (!e.HasComponent<Text>())
				continue;
			std::vector<Math::Vec2> vertices = VertexFetcher::FetchVertices(e);
			if (Input::CheckKey(E_STATE::PRESS, E_KEY::M_BUTTON_L))
				if (cursorPos.x <= vertices[0].x && cursorPos.y <= vertices[0].y)
					if (cursorPos.x >= vertices[2].x && cursorPos.y >= vertices[2].y)
					{
						e.GetComponent<Text>().color = e.GetComponent<Text>().color.g == 255 ? 
							Color{0, 0, 0, 255}: Color{ 255, 255, 255, 255 };
						if (e.GetComponent<General>().subtag == SUBTAG::PLAYER)
						{
							GameStateManager::GetInstance()->NextGS(E_GS::Level1);
						}
						if (e.GetComponent<General>().subtag == SUBTAG::ENEMY)
						{
							GameStateManager::GetInstance()->NextGS(E_GS::EXIT);
						}
					}
		}
	}
	for (Scene* scenePtr : mScenes)
		scenePtr->PrimaryUpdate();*/
}

void MainMenu::Draw() {
	renderManager->Render();
}

void MainMenu::Free() {
	/*for (auto& scenePtr : mScenes)
		scenePtr->Exit();*/
}

void MainMenu::Unload() {
	renderManager->GetGizmo().Detach();
	ECS::DestroyAllEntities();
}