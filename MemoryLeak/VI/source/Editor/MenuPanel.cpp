/*!*****************************************************************************
\file MenuPanel.cpp
\author Huang Wei Jhin
\par DP email: h.weijhin@digipen.edu
\par Group: Memory Leak Studios
\date 20-10-2022
\brief
	This class encapsulates the functions for the Level Editor Main menu
*******************************************************************************/
#include "MenuPanel.h"
#include <ECSManager.h>

/*!*****************************************************************************
\brief
	Initializes the Menu Panel editor

\return
None.
*******************************************************************************/
void MenuPanel::Init()
{
	
}
/*!*****************************************************************************
\brief
	Updates the Menu Panel editor

\return
None.
*******************************************************************************/
void MenuPanel::Update()
{
	static char filenameS_Scene[30] = "";
	static char filenameO_Scene[30] = "";
	static char filenameS_Dialog[30] = "";
	static char filenameO_Dialog[30] = "";
	if (ImGui::BeginMainMenuBar())
	{
		if (Input::CheckKey(E_STATE::HOLD, E_KEY::LEFT_CONTROL) && Input::CheckKey(E_STATE::PRESS, E_KEY::Z))//relocate
		{
			Undo();
		}
		if (Input::CheckKey(E_STATE::HOLD, E_KEY::LEFT_CONTROL) && Input::CheckKey(E_STATE::PRESS, E_KEY::Y))//relocate
		{
			Redo();
		}
		if (ImGui::BeginMenu("File"))
		{
			ImGui::MenuItem("(menu)", NULL, false, false);
			ImGui::MenuItem("Open Scene File", NULL, false, false);
			ImGui::PushID(1);
			ImGui::InputText(".json", filenameO_Scene, 30);
			ImGui::PopID();
			if (ImGui::MenuItem("Open Scene", "Ctrl+O"))
			{
				//serializationManager->LoadScene(filenameO_Scene);
				// REMOVEME remove 1
				if (filenameO_Scene[0] == 'S' && filenameO_Scene[1] == 'c' && filenameO_Scene[3] == 'n')
					serializationManager->LoadScene(filenameO_Scene);
				else
					serializationManager->LoadScene(filenameO_Scene, 1);
			}
			ImGui::Separator();
			ImGui::MenuItem("Open Scene File", NULL, false, false);
			ImGui::PushID(2);
			ImGui::InputText(".json", filenameS_Scene, 30);
			ImGui::PopID();
			if (ImGui::MenuItem("Save Scene As", "Ctrl+S"))
			{
				serializationManager->SaveScene(filenameS_Scene);
			}
			ImGui::Separator();
			if (ImGui::MenuItem("Clear Scene"))
			{
				ECS::DestroyAllEntities();
				SceneReset();
			}
			ImGui::Separator();
			ImGui::MenuItem("Open Dialogue File", NULL, false, false);
			ImGui::PushID(3);
			ImGui::InputText(".json", filenameO_Dialog, 20);
			ImGui::PopID();
			if (ImGui::MenuItem("Open Dialog", "Ctrl+D"))
			{
				serializationManager->LoadDialogs(filenameO_Dialog);
				SetPannelIsActive(E_PANELID::DIALOGUE, true);
			}
			ImGui::Separator();
			ImGui::MenuItem("Save Dialogue File As", NULL, false, false);
			ImGui::PushID(4);
			ImGui::InputText(".json", filenameS_Dialog, 20);
			ImGui::PopID();
			if (ImGui::MenuItem("Save Dialog As", "Ctrl+F"))
			{
				serializationManager->SaveDialogs(filenameS_Dialog);
			}
			ImGui::Separator();
			if (ImGui::MenuItem("Print Dialogs"))
			{
				dialogManager->PrintDialogs();
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Cut", "CTRL+X")) {}
			if (ImGui::MenuItem("Copy", "CTRL+C")) {}
			if (ImGui::MenuItem("Paste", "CTRL+V")) {}
			ImGui::Separator();
			if (ImGui::MenuItem("Undo", "CTRL+Z"))
			{
				Undo();
			}
			if (ImGui::MenuItem("Redo", "CTRL+Y"))
			{
				Redo();
			}
			ImGui::EndMenu();

		}
		if (ImGui::BeginMenu("Options"))
		{
			if (ImGui::BeginMenu("Change Theme"))
			{
				if(ImGui::MenuItem("Dark"))
					ImGui::StyleColorsDark();
				if (ImGui::MenuItem("Light"))
					ImGui::StyleColorsLight();
				if (ImGui::MenuItem("Classic"))
					ImGui::StyleColorsClassic();
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Change Song Lol :)"))
			{
				for (std::string song : audioManager->GetSongs())
				{
					if (ImGui::MenuItem(song.c_str()))
						audioManager->PlayBGSound(song, 10);
				}
				ImGui::EndMenu();
			}
			if (!GetPannelIsActive(E_PANELID::DEBUG) && ImGui::MenuItem("Show Debug Info"))
			{
				//debugPanel.setIsActive(true);
				SetPannelIsActive(E_PANELID::DEBUG, true);
			}
			if (GetPannelIsActive(E_PANELID::DEBUG) && ImGui::MenuItem("Hide Debug Info"))
			{
				//debugPanel.setIsActive(false);
				SetPannelIsActive(E_PANELID::DEBUG, false);
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}
/*!*****************************************************************************
\brief
	Free the Menu Panel editor

\return
None.
*******************************************************************************/
void MenuPanel::Free()
{
}