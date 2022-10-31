/*!*****************************************************************************
\file ViewportPanel.cpp
\author Huang Wei Jhin
\par DP email: h.weijhin@digipen.edu
\par Group: Memory Leak Studios
\date 20-10-2022
\brief
This file contains function definations for a Viewport Panel Editor system that displays the scene
*******************************************************************************/
#include "ViewportPanel.h"
#include <ECSManager.h>
int ViewportPanel::isSelected = 0;
/*!*****************************************************************************
\brief
	This function set the view port to 16:9 aspect ratio regardless of window size

\return
None.
*******************************************************************************/
void ViewportPanel::SetViewportAspectRatio()
{
	viewportSize = { ImGui::GetWindowSize().x,ImGui::GetWindowSize().y - 70 };
	if (viewportSize.x / viewportSize.y > 16 / 9.0f) //wide screen
	{
		viewportSize.x = viewportSize.y / 9 * 16;
	}
	else if (viewportSize.x / viewportSize.y < 16 / 9.0f) // tall screen
	{
		viewportSize.y = viewportSize.x / 16 * 9;
	}
}
void ViewportPanel::CalculateMousePos(E_CAMERA_TYPE _type)
{
	//to use matrix from graphics in the future
	
	viewportPos = { (ImGui::GetWindowWidth() - viewportSize.x) * 0.5f, buttonSize.y +35.f };
	screenMousePos = Input::CursorPos() - Math::Vec2{ ImGui::GetWindowPos().x,ImGui::GetWindowPos().y } - viewportPos - viewportSize / 2;
	worldMousePos = screenMousePos;
	worldMousePos.y = -worldMousePos.y;
	worldMousePos.x = worldMousePos.x / viewportSize.x * *mWindowWidth;
	worldMousePos.y = worldMousePos.y / viewportSize.y * *mWindowHeight;
	if(_type == E_CAMERA_TYPE::GAME)
		camMousePos = worldMousePos * renderManager->GetGameCamera().GetZoom() + renderManager->GetGameCamera().GetPos();
	else if (_type == E_CAMERA_TYPE::WORLD)
		camMousePos = worldMousePos * renderManager->GetWorldCamera().GetZoom() + renderManager->GetWorldCamera().GetPos();
}
bool ViewportPanel::IsMouseInScreen()
{
	return (abs(screenMousePos.x) < viewportSize.x / 2 && abs(screenMousePos.y) < viewportSize.y / 2);
	
}

