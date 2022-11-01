/*!*****************************************************************************
/*!*****************************************************************************
\file WeatherPanel.cpp
\author Huang Wei Jhin
\par DP email: h.weijhin@digipen.edu
\par Group: Memory Leak Studios
\date 20-10-2022
\brief
This file contains function definations for a AnimationPanel Editor system that modifies
and Animation 
*******************************************************************************/
#include "WeatherPanel.h"
#include <ECSManager.h>

/*!*****************************************************************************
\brief
	Initializes the Dialogue Panel editor

\return
None.
*******************************************************************************/
void WeatherPanel::Init()
{
	aiManager->weatherAIinit();
	viewportSize = { 0,0 };
}
/*!*****************************************************************************
\brief
	Updates the Dialogue Panel editor

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
	//if (ImGui::Button("Reset", { 100,25 }))
		//serializationManager->LoadScene("SceneTmp");
	//ImGui::SameLine(0.f,20.f);
	if (ImGui::Button("Play", buttonSize))
	{
		isWeatherPaused = false;
	}
	ImGui::SameLine(0.f, 20.f);
	if (ImGui::Button("Pause", buttonSize))
	{
		isWeatherPaused = true;
	}
	for (int h = 0; h < mapHeight; h++)
	{
		for (int w = 0; w < mapWidth; w++)
		{
			if (aiManager->weatherMap[w][h] == SUNNUY)
			{
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(255, 0, 0)));
				ImGui::Button("S", weatherIocnSize);
				ImGui::PopStyleColor();
			}
			else if (aiManager->weatherMap[w][h] == FOG)
			{
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(0, 0, 255)));
				ImGui::Button("F", weatherIocnSize);
				ImGui::PopStyleColor();
			}
			else if (aiManager->weatherMap[w][h] == RAIN)
			{
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(255, 0, 255)));
				ImGui::Button("R", weatherIocnSize);
				ImGui::PopStyleColor();
			}
			else if (aiManager->weatherMap[w][h] == WINDY)
			{
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(0, 255, 0)));
				ImGui::Button("W", weatherIocnSize);
				ImGui::PopStyleColor();
			}
			ImGui::SameLine(0.0f,2.f);
		}
		ImGui::NewLine();
	}
	
	if (isWeatherPaused)
	{
		aiManager->weatherAIupdate();
	}
	ImGui::End();
}
/*!*****************************************************************************
\brief
	Free the Dialogue Panel editor

\return
None.
*******************************************************************************/
void WeatherPanel::Free()
{

}
