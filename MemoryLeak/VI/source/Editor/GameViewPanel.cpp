/*!*****************************************************************************
/*!*****************************************************************************
\file GameViewPanel.cpp
\author Huang Wei Jhin
\par DP email: h.weijhin@digipen.edu
\par Group: Memory Leak Studios
\date 20-09-2022
\brief
This file contains function definations for a GameView Panel Editor system that displays the game scene
Entities and its Components.
*******************************************************************************/
#include "GameViewPanel.h"
#include <ECSManager.h>

void GameViewPanel::Init()
{
	viewportSize = { 0,0 };
	//camera = renderManager->GetGameCamera();
}
void GameViewPanel::Update()
{
	ImGui::Begin("Camera View");
	//Calcualting the aspect ratio 
	SetViewportAspectRatio();
	Math::Vec2 pos = { (ImGui::GetWindowWidth() / 2.f) - 110.f, 30.f };
	ImGui::SetCursorPos(ImVec2(pos.x, pos.y));
	//if (ImGui::Button("Reset", { 100,25 }))
		//serializationManager->LoadScene("SceneTmp");
	//ImGui::SameLine(0.f,20.f);
	if (ImGui::Button("Play", buttonSize))
	{
		isScenePaused = false;
	}
	ImGui::SameLine(0.f, 20.f);
	if (ImGui::Button("Pause", buttonSize))
	{
		isScenePaused = true;
	}

	CalculateMousePos(E_CAMERA_TYPE::GAME);
	if (ImGui::IsWindowHovered())
	{
		/*Math::Vec2 screenMousePos = Input::CursorPos() - Math::Vec2{ ImGui::GetWindowPos().x,ImGui::GetWindowPos().y } - pos - viewportSize / 2;
		Math::Vec2 worldMousePos = screenMousePos;
		worldMousePos.y = -worldMousePos.y;
		worldMousePos.x = worldMousePos.x / viewportSize.x * *mWindowWidth;
		worldMousePos.y = worldMousePos.y / viewportSize.y * *mWindowHeight;
		Math::Vec2 camMousePos = worldMousePos * renderManager->GetGameCamera().GetZoom() + renderManager->GetGameCamera().GetPos();*/
		/*const Math::Vec2 moveHorizontal{ 1, 0 };
		const Math::Vec2 moveVertical{ 0, 1 };
		const float zoom{ 0.1f };*/
		/*static Math::Vec2 camOffset{};
		static Math::Vec2 camPos{};
		static Math::Vec2 offset{};
		static int isSelected = 0;
		if (abs(screenMousePos.x) < viewportSize.x / 2 && abs(screenMousePos.y) < viewportSize.y / 2)*/
		
		if (IsMouseInScreen())
		{
			//Camera movement
			ArrowKeyMoveCam();
			MouseClickMoveCam();
			ScrollMoveCam();
			//if (Input::CheckKey(E_STATE::HOLD, E_KEY::UP))
			//{
			//	renderManager->GetGameCamera() += moveVertical;
			//}
			//if (Input::CheckKey(E_STATE::HOLD, E_KEY::DOWN))
			//{
			//	renderManager->GetGameCamera() -= moveVertical;
			//}
			//if (Input::CheckKey(E_STATE::HOLD, E_KEY::RIGHT))
			//{
			//	renderManager->GetGameCamera() += moveHorizontal;
			//}
			//if (Input::CheckKey(E_STATE::HOLD, E_KEY::LEFT))
			//{
			//	renderManager->GetGameCamera() -= moveHorizontal;
			//}
			//if (Input::CheckKey(E_STATE::PRESS, E_KEY::M_BUTTON_L) && !isSelected)
			//{
			//	camOffset = camMousePos;
			//}
			//if (Input::CheckKey(E_STATE::HOLD, E_KEY::M_BUTTON_L) && !isSelected)
			//{
			//	camPos = -(worldMousePos * renderManager->GetGameCamera().GetZoom() - camOffset);
			//	renderManager->GetGameCamera().SetPos(camPos);
			//}
			//if (Input::GetScroll() > 0.0) //scroll up   // zoon in
			//{
			//	renderManager->GetGameCamera() += worldMousePos * moveZoom;
			//	renderManager->GetGameCamera() *= -moveZoom;
			//	//renderManager->GetWorldCamera() -= -mousePos;
			//}
			//else if (Input::GetScroll() < 0.0)  //scroll down //zoom out
			//{
			//	renderManager->GetGameCamera() -= worldMousePos * moveZoom;
			//	renderManager->GetGameCamera() *= moveZoom;
			//	//renderManager->GetWorldCamera() += -mousePos;
			//}
		}

	}
	//GLuint frameBuffer = renderManager->GetGameFBO();
	fameBufferImage = (void*)(intptr_t)renderManager->GetGameFBO();
	ImGui::SetCursorPos(ImVec2(viewportPos.x, viewportPos.y));
	ImGui::Image(fameBufferImage, { viewportSize.x, viewportSize.y }, ImVec2(0, 1), ImVec2(1, 0));
	ImGui::End();
}
void GameViewPanel::Free()
{

}
void GameViewPanel::ArrowKeyMoveCam()
{
	if (Input::CheckKey(E_STATE::HOLD, E_KEY::UP))
	{
		renderManager->GetGameCamera() += moveVertical;
	}
	if (Input::CheckKey(E_STATE::HOLD, E_KEY::DOWN))
	{
		renderManager->GetGameCamera() -= moveVertical;
	}
	if (Input::CheckKey(E_STATE::HOLD, E_KEY::RIGHT))
	{
		renderManager->GetGameCamera() += moveHorizontal;
	}
	if (Input::CheckKey(E_STATE::HOLD, E_KEY::LEFT))
	{
		renderManager->GetGameCamera() -= moveHorizontal;
	}
}
void GameViewPanel::MouseClickMoveCam()
{
	if (Input::CheckKey(E_STATE::PRESS, E_KEY::M_BUTTON_L) && !isSelected)
	{
		camOffset = camMousePos;
	}
	if (Input::CheckKey(E_STATE::HOLD, E_KEY::M_BUTTON_L) && !isSelected)
	{
		camPos = -(worldMousePos * renderManager->GetGameCamera().GetZoom() - camOffset);
		renderManager->GetGameCamera().SetPos(camPos);
	}
}
void GameViewPanel::ScrollMoveCam()
{
	if (Input::GetScroll() > 0.0) //scroll up   // zoon in
	{

		renderManager->GetGameCamera() += worldMousePos * moveZoom;
		renderManager->GetGameCamera() *= -moveZoom;
		//renderManager->GetWorldCamera() -= -mousePos;
	}
	else if (Input::GetScroll() < 0.0)  //scroll down //zoom out
	{
		renderManager->GetGameCamera() -= worldMousePos * moveZoom;
		renderManager->GetGameCamera() *= moveZoom;
		//renderManager->GetWorldCamera() += -mousePos;
	}
}
