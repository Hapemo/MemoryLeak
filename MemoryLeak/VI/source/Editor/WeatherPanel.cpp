/*!*****************************************************************************
/*!*****************************************************************************
\file WeatherPanel.cpp
\author Huang Wei Jhin
\par DP email: h.weijhin@digipen.edu
\par Group: Memory Leak Studios
\date 30-10-2022
\brief
This file contains function declarations for a WeatherPanel Editor system that modifies
and Weather tile map
*******************************************************************************/
#include "WeatherPanel.h"
#include <ECSManager.h>

/*!*****************************************************************************
\brief
	Initializes the Weather Panel editor

\return
None.
*******************************************************************************/
void WeatherPanel::Init()
{
	aiManager->weatherAIinit();
	viewportSize = { 0,0 };
	isWeatherPaused = true;
}
/*!*****************************************************************************
\brief
	Updates the Weather Panel editor

\return
None.
*******************************************************************************/
void WeatherPanel::Update()
{
	/*if (!active)
		return;*/
	

	ImGui::Begin("Weather Editor");
	SetViewportAspectRatio();
	Math::Vec2 pos = { (ImGui::GetWindowWidth() / 2.f) - 110.f, 30.f };
	ImGui::SetCursorPos(ImVec2(pos.x, pos.y));
	if (isWeatherPaused)
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(200, 0, 0)));
	else
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(0, 150, 0)));
	if (ImGui::Button("Play", buttonSize))
	{
		isWeatherPaused = false;
	}
	ImGui::PopStyleColor();

	if (isWeatherPaused)
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(0, 150, 0)));
	else
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(200, 0, 0)));
	ImGui::SameLine(0.f, 20.f);
	if (ImGui::Button("Pause", buttonSize))
	{
		isWeatherPaused = true;
	}
	ImGui::PopStyleColor();
	for (int h = 0; h < mapHeight; h++)
	{
		for (int w = 0; w < mapWidth; w++)
		{
			if (aiManager->weatherMap[w][h] == SUNNUY)
			{
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(255, 153, 51)));
				ImGui::Button("S", weatherIocnSize);
				ImGui::PopStyleColor();
			}
			else if (aiManager->weatherMap[w][h] == FOG)
			{
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(102, 204, 0)));
				ImGui::Button("F", weatherIocnSize);
				ImGui::PopStyleColor();
			}
			else if (aiManager->weatherMap[w][h] == RAIN)
			{
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(0, 76, 153)));
				ImGui::Button("R", weatherIocnSize);
				ImGui::PopStyleColor();
			}
			else if (aiManager->weatherMap[w][h] == WINDY)
			{
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(0, 200, 200)));
				ImGui::Button("W", weatherIocnSize);
				ImGui::PopStyleColor();
			}
			ImGui::SameLine(0.0f,2.f);
		}
		ImGui::NewLine();
	}
	
	if (!isWeatherPaused)
	{
		aiManager->weatherAIupdate();
	}
	ImGui::End();
}
/*!*****************************************************************************
\brief
	Free the Weather Panel editor

\return
None.
*******************************************************************************/
void WeatherPanel::Free()
{

}
