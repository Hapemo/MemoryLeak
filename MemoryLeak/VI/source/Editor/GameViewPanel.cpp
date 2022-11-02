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
/*!*****************************************************************************
\brief
	Initializes the GameViewPanel editor

\return
None.
*******************************************************************************/
void GameViewPanel::Init()
{
	viewportSize = { 0,0 };
	//camera = renderManager->GetGameCamera();
}
/*!*****************************************************************************
\brief
	Update the GameViewPanel editor

\return
None.
*******************************************************************************/
void GameViewPanel::Update()
{
	ImGui::Begin("Game View");
	//Calcualting the aspect ratio 
	SetViewportAspectRatio();
	Math::Vec2 pos = { (ImGui::GetWindowWidth() / 2.f) - 110.f, 30.f };
	ImGui::SetCursorPos(ImVec2(pos.x, pos.y));
	//if (ImGui::Button("Reset", { 100,25 }))
		//serializationManager->LoadScene("SceneTmp");
	//ImGui::SameLine(0.f,20.f);
	if (isScenePaused)
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(200, 0, 0)));
	else
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(0, 150, 0)));
	if (ImGui::Button("Play", buttonSize))
	{
		isScenePaused = false;
	}
	ImGui::PopStyleColor();

	if (isScenePaused)
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(0, 150, 0)));
	else
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(200, 0, 0)));
	ImGui::SameLine(0.f, 20.f);
	if (ImGui::Button("Pause", buttonSize))
	{
		isScenePaused = true;
	}
	ImGui::PopStyleColor();
	CalculateMousePos(E_CAMERA_TYPE::GAME);
	if (ImGui::IsWindowHovered())
	{
		if (IsMouseInScreen())
		{
			//Camera movement
			ArrowKeyMoveCam();
			ScrollMoveCam();
			if (isScenePaused)
				MouseClickMoveCam();
			else
			{
				if (Input::CheckKey(E_STATE::PRESS, E_KEY::M_BUTTON_L))
				{
					ButtonClick();
				}
			}
		}
	}
	fameBufferImage = (void*)(intptr_t)renderManager->GetGameFBO();
	ImGui::SetCursorPos(ImVec2(viewportPos.x, viewportPos.y));
	ImGui::Image(fameBufferImage, { viewportSize.x, viewportSize.y }, ImVec2(0, 1), ImVec2(1, 0));
	ImGui::End();
}
/*!*****************************************************************************
\brief
	Free the GameViewPanel editor

\return
None.
*******************************************************************************/
void GameViewPanel::Free()
{

}
/*!*****************************************************************************
\brief
	This Function Moves the camera based on arrow key input

\return
None.
*******************************************************************************/
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
/*!*****************************************************************************
\brief
	This Function Moves the camera based on mouse input

\return
None.
*******************************************************************************/
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
/*!*****************************************************************************
\brief
	This Function Zoom the camera based on mouse input

\return
None.
*******************************************************************************/
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
void GameViewPanel::ButtonClick()
{
	int layer = 0;
	for (const Entity& ee : *myEntities)
	{
		if (ee.GetComponent<General>().tag == TAG::ENVIRONMENT)
		{
			if (ee.HasComponent<Transform>() && ee.HasComponent<Sprite>()&& ee.HasComponent<Text>()) //button
			{
				Math::Vec2 scale = ee.GetComponent<Transform>().scale;
				Math::Vec2 translation = ee.GetComponent<Transform>().translation;
				Math::Vec2 distance = camMousePos - translation;
				if (abs(distance.x) < abs(scale.x) / 2 && abs(distance.y) < abs(scale.y) / 2)
				{
					LOG_INFO(ee.GetComponent<General>().name + "Clicked");
					if (ee.GetComponent<Sprite>().layer >= layer)
					{
						if ( ee.GetComponent<Text>().color.g == (GLubyte)0)
							ee.GetComponent<Text>().color = Color(255,255,255,255);
						else
							ee.GetComponent<Text>().color = Color(0, 0, 0, 255);
						layer = ee.GetComponent<Sprite>().layer;
						if (ee.GetComponent<General>().tag == TAG::PLAYER)
						{
							//GameStateManager::GetInstance()->NextGS(E_GS::Level1);
						}
					}
				}
				else if (ee.GetComponent<Sprite>().color.r == (GLubyte)0 && ee.GetComponent<Sprite>().color.g == (GLubyte)0 && ee.GetComponent<Sprite>().color.b == (GLubyte)0)
				{
					ee.GetComponent<Sprite>().color = Color(255, 255, 255, 255);
				}
			}
		}
	}
}
