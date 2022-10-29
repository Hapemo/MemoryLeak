/*!*****************************************************************************
/*!*****************************************************************************
\file LevelEditor.cpp
\author Huang Wei Jhin
\par DP email: h.weijhin@digipen.edu
\par Group: Memory Leak Studios
\date 20-09-2022
\brief
This file contains function definations for a Level Editor system that modifies
Entities and its Components.
*******************************************************************************/
#include "GameViewPanel.h"
#include <ECSManager.h>

void GameViewPanel::Init()
{

}
void GameViewPanel::Update()
{
	ImGui::Begin("Camera View");
	Math::Vec2 viewportSize = { ImGui::GetWindowSize().x,ImGui::GetWindowSize().y };
	viewportSize.y -= 70;
	//Calcualting the aspect ratio 
	if (viewportSize.x / viewportSize.y > 16 / 9.0f) //wide screen
	{
		viewportSize.x = viewportSize.y / 9 * 16;
	}
	else if (viewportSize.x / viewportSize.y < 16 / 9.0f) // tall screen
	{
		viewportSize.y = viewportSize.x / 16 * 9;
	}
	Math::Vec2 pos = { (ImGui::GetWindowWidth() / 2.f) - 110.f, 30.f };
	ImGui::SetCursorPos(ImVec2(pos.x, pos.y));
	//if (ImGui::Button("Reset", { 100,25 }))
		//serializationManager->LoadScene("SceneTmp");
	//ImGui::SameLine(0.f,20.f);
	if (ImGui::Button("Play", { 100,25 }))
	{
		//serializationManager->SaveScene("SceneTmp");
		isPaused = false;
		//renderManager->GetGameCamera() += Math::Vec2(10.f, 10.f);
	}
	ImGui::SameLine(0.f, 20.f);
	if (ImGui::Button("Pause", { 100,25 }))
		isPaused = true;

	pos = { (ImGui::GetWindowWidth() - viewportSize.x) * 0.5f, 60.f };
	ImGui::SetCursorPos(ImVec2(pos.x, pos.y));
	//
	if (ImGui::IsWindowHovered())
	{
		Math::Vec2 ScreenMousePos = Input::CursorPos() - Math::Vec2{ ImGui::GetWindowPos().x,ImGui::GetWindowPos().y } - pos - viewportSize / 2;
		Math::Vec2 WorldMousePos = ScreenMousePos;
		WorldMousePos.y = -WorldMousePos.y;
		WorldMousePos.x = WorldMousePos.x / viewportSize.x * *mWindowWidth;
		WorldMousePos.y = WorldMousePos.y / viewportSize.y * *mWindowHeight;
		Math::Vec2 CamMousePos = WorldMousePos * renderManager->GetGameCamera().GetZoom() + renderManager->GetGameCamera().GetPos();
		const Math::Vec2 moveHorizontal{ 1, 0 };
		const Math::Vec2 moveVertical{ 0, 1 };
		const float zoom{ 0.1f };
		static Math::Vec2 camOffset{};
		static Math::Vec2 camPos{};
		static Math::Vec2 offset{};
		static int isSelected = 0;
		if (abs(ScreenMousePos.x) < viewportSize.x / 2 && abs(ScreenMousePos.y) < viewportSize.y / 2)
		{
			//Camera movement
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
			if (Input::CheckKey(E_STATE::PRESS, E_KEY::M_BUTTON_L) && !isSelected)
			{
				camOffset = CamMousePos;
			}
			if (Input::CheckKey(E_STATE::HOLD, E_KEY::M_BUTTON_L) && !isSelected)
			{
				camPos = -(WorldMousePos * renderManager->GetGameCamera().GetZoom() - camOffset);
				renderManager->GetGameCamera().SetPos(camPos);
			}
			if (Input::GetScroll() > 0.0) //scroll up   // zoon in
			{

				renderManager->GetGameCamera() += WorldMousePos * zoom;
				renderManager->GetGameCamera() *= -zoom;
				//renderManager->GetWorldCamera() -= -mousePos;
			}
			else if (Input::GetScroll() < 0.0)  //scroll down //zoom out
			{
				renderManager->GetGameCamera() -= WorldMousePos * zoom;
				renderManager->GetGameCamera() *= zoom;
				//renderManager->GetWorldCamera() += -mousePos;
			}
		}

	}
	GLuint frameBuffer = renderManager->GetGameFBO();
	ImTextureID fameBufferImage = (void*)(intptr_t)frameBuffer;
	ImGui::Image(fameBufferImage, { viewportSize.x, viewportSize.y }, ImVec2(0, 1), ImVec2(1, 0));
	ImGui::End();
}
void GameViewPanel::Free()
{

}