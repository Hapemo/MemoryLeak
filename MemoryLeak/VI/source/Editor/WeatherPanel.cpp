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
	std::srand(std::time(nullptr));
	aiManager->weatherAIinit();
	viewportSize = { 0,0 };
	isWeatherPaused = true;
	sunIcon = (void*)(intptr_t)spriteManager->GetTextureID("Textures\\Icons\\sunIcon.png");
	rainIcon = (void*)(intptr_t)spriteManager->GetTextureID("Textures\\Icons\\rainIcon.png");
	fogIcon = (void*)(intptr_t)spriteManager->GetTextureID("Textures\\Icons\\fogIcon.png");
	windIcon = (void*)(intptr_t)spriteManager->GetTextureID("Textures\\Icons\\windIcon.png");
	rainwindfogIcon = (void*)(intptr_t)spriteManager->GetTextureID("Textures\\Icons\\rainwindfogIcon.png");
	rainwindIcon = (void*)(intptr_t)spriteManager->GetTextureID("Textures\\Icons\\rainwindIcon.png");
	windfogIcon = (void*)(intptr_t)spriteManager->GetTextureID("Textures\\Icons\\windfogIcon.png");
	rainfogIcon = (void*)(intptr_t)spriteManager->GetTextureID("Textures\\Icons\\rainfogIcon.png");
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
	for (int w = 0; w < aiManager->getWeatherMap().size(); w++)
	{
		for (int h = 0; h < aiManager->getWeatherMap()[w].size(); h++)
		{
			if ((aiManager->getWeatherMap()[w][h] ) == SUNNUY) 
			{
				//ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(255, 203, 81)));
				//ImGui::Button("S", weatherIocnSize);
				//ImGui::Image(sunIcon, weatherIocnSize, ImVec2(0, 1), ImVec2(1, 0));
				//ImGui::PopStyleColor();
				selectedIcon = sunIcon;
			}
			else if ((aiManager->getWeatherMap()[w][h]) == ALL)
			{
				//ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(255, 203, 81)));
				//ImGui::Button("S", weatherIocnSize);
				//ImGui::Image(sunIcon, weatherIocnSize, ImVec2(0, 1), ImVec2(1, 0));
				//ImGui::PopStyleColor();
				selectedIcon = rainwindfogIcon;
			}
			else
			{
				if ((aiManager->getWeatherMap()[w][h] &= RAIN) )
				{
					//ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(0, 76, 153)));
					//ImGui::Button("R", weatherIocnSize);
					//ImGui::Image(rainIcon, weatherIocnSize, ImVec2(0, 1), ImVec2(1, 0));
					//ImGui::PopStyleColor();
					selectedIcon = rainIcon;
					if ((aiManager->getWeatherMap()[w][h] &= FOG) )
					{
						selectedIcon = rainfogIcon;
					}
					else if ((aiManager->getWeatherMap()[w][h] &= WINDY) )
					{
						selectedIcon = rainwindIcon;
					}

				}
				else if ((aiManager->getWeatherMap()[w][h] &= WINDY) )
				{
					//ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(0, 200, 200)));
					//ImGui::Button("W", weatherIocnSize);
					//ImGui::Image(windIcon, weatherIocnSize, ImVec2(0, 1), ImVec2(1, 0));
					//ImGui::PopStyleColor();
					selectedIcon = windIcon;
					if ((aiManager->getWeatherMap()[w][h] &= RAIN) )
					{
						selectedIcon = rainwindIcon;
					}
					else if ((aiManager->getWeatherMap()[w][h] &= FOG) )
					{
						selectedIcon = windfogIcon;
					}
				}
				else if ((aiManager->getWeatherMap()[w][h] &= FOG) )
				{
					//ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(102, 204, 0)));
					//ImGui::Button("F", weatherIocnSize);
					//ImGui::Image(fogIcon, weatherIocnSize, ImVec2(0, 1), ImVec2(1, 0));
					//ImGui::PopStyleColor();
					selectedIcon = fogIcon;
					if ((aiManager->getWeatherMap()[w][h] &= RAIN) )
					{
						selectedIcon = rainfogIcon;
					}
					else if ((aiManager->getWeatherMap()[w][h] &= WINDY) )
					{
						selectedIcon = windfogIcon;
					}
				}
				else
					selectedIcon = rainwindfogIcon;
			}
			ImGui::Image(selectedIcon, weatherIocnSize, ImVec2(0, 1), ImVec2(1, 0));
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
