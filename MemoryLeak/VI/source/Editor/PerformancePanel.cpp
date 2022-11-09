/*!*****************************************************************************
/*!*****************************************************************************
\file PerformancePanel.cpp
\author Huang Wei Jhin
\par DP email: h.weijhin@digipen.edu
\par Group: Memory Leak Studios
\date 20-10-2022
\brief
This file contains function definations for a Performance Panel Editor system that displays Performance infomation 
*******************************************************************************/
#include "PerformancePanel.h"
#include <ECSManager.h>
/*!*****************************************************************************
\brief
	Initializes the Performance Panel editor

\return
None.
*******************************************************************************/
void PerformancePanel::Init()
{
	
	count = 8;
	for (int i = 0; i < count; i++)
	{
		std::deque<float> list{ 0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f };
		system.push_back(list);
	}
}
/*!*****************************************************************************
\brief
	Updates the Performance Panel editor

\return
None.
*******************************************************************************/
void PerformancePanel::Update()
{
	static bool start = true;
	if (start)
	{
		
	}
	start = false;
	ImGui::Begin("Performance");
	ImGui::BeginTabBar("Performance Visualizer ");
	
	if (ImGui::BeginTabItem("Overall"))
	{
		static float arr[8];
		performance = PerformanceVisualiser::GetInstance()->GetPerformanceVec();
		for (int i = 0; i < performance.size(); i++)
		{
			arr[i] = (float)performance[i].second;
			system[i].push_front((float)performance[i].second);
			
		}
		ImGui::PlotHistogram("Performance", arr, IM_ARRAYSIZE(arr), 0, NULL, 0.0f, 100.0f, ImVec2(0, 80.0f));

		static float editor[8];
		static float graphics[8];
		for (int i = 0; i < 8; i++)
		{
			editor[i] = system[0][i];
			graphics[i] = system[1][i];
		}
		ImGui::PlotLines("Editor ", editor, IM_ARRAYSIZE(editor), 0, "%", 0.f, 100.f, ImVec2(200, 80));
		ImGui::PlotLines("graphics ", graphics, IM_ARRAYSIZE(graphics), 0, "%", 0.f, 10.f, ImVec2(200, 80));
		
	
	}
	ImGui::EndTabBar();
	ImGui::End();

}
/*!*****************************************************************************
\brief
	Free the Performance Panel editor

\return
None.
*******************************************************************************/
void PerformancePanel::Free()
{

}