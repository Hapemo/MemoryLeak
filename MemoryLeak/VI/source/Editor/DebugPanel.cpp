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
#include "DebugPanel.h"

void DebugPanel::Init()
{

}
void DebugPanel::Update()
{
	std::vector<std::pair<Logger::E_LOGLEVEL, std::string>> loggerStr = Logger::GetInstance()->GetLoggerStr();
	ImGui::Begin("Debug Logger");
	ImGui::BeginTabBar("DebugLogger ");
	if (ImGui::BeginTabItem("All Logs "))
	{
		for (auto str : loggerStr)
		{
			ImGui::Text(str.second.c_str());
		}
		ImGui::EndTabItem();
	}

	if (ImGui::BeginTabItem("Info Log "))
	{
		for (auto str : loggerStr)
		{
			if (str.first == Logger::E_LOGLEVEL::LOG_INFO)
				ImGui::Text(str.second.c_str());
		}
		ImGui::EndTabItem();
	}

	if (ImGui::BeginTabItem("Debug Log "))
	{

		for (auto str : loggerStr)
		{
			if (str.first == Logger::E_LOGLEVEL::LOG_DEBUG)
				ImGui::Text(str.second.c_str());
		}
		ImGui::EndTabItem();
	}

	if (ImGui::BeginTabItem("Warning Log "))
	{
		for (auto str : loggerStr)
		{
			if (str.first == Logger::E_LOGLEVEL::LOG_WARN)
				ImGui::Text(str.second.c_str());
		}
		ImGui::EndTabItem();
	}
	if (ImGui::BeginTabItem("Error Log "))
	{
		for (auto str : loggerStr)
		{
			if (str.first == Logger::E_LOGLEVEL::LOG_ERROR)
				ImGui::Text(str.second.c_str());
		}
		ImGui::EndTabItem();
	}
	if (ImGui::BeginTabItem("Custom Log "))
	{
		for (auto str : loggerStr)
		{
			if (str.first > Logger::E_LOGLEVEL::LOG_ASSERT)
				ImGui::Text(str.second.c_str());
		}
		ImGui::EndTabItem();
	}
	ImGui::Text("   ");
	ImGui::EndTabBar();
	ImGui::End();

}
void DebugPanel::Free()
{

}