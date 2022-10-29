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
#include "DialoguePanel.h"
#include <ECSManager.h>

void DialoguePanel::Init()
{

}
void DialoguePanel::Update()
{
	GLuint player_texture = spriteManager->GetTextureID("Textures\\Sprites\\mc.png");
	ImTextureID playerIcon = (void*)(intptr_t)player_texture;
	GLuint passenger_texture = spriteManager->GetTextureID("Textures\\Sprites\\girl.png");
	ImTextureID passengerIcon = (void*)(intptr_t)passenger_texture;
	GLuint send_texture = spriteManager->GetTextureID("Textures\\Icons\\sendIcon.png");
	ImTextureID sendIcon = (void*)(intptr_t)send_texture;
	ImGui::Begin("Dialog Editor");
	int id = 1;
	int id2 = 0;
	int prevID = 1;
	static int selectedID = 0;
	std::string dialog{};
	std::string dialog2{};
	static std::string editDialog{};
	int wrapsize = int(ImGui::GetWindowWidth() / 13);
	ImVec2 iconSize = ImVec2(40, 40);
	//ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(100, 0, 0))); ImGui::PopStyleColor();
	while (id)
	{
		if (dialogManager->GetDialogs().size() == 0)
			break;
		dialog = dialogManager->GetDialogue(id);
		BreakString(dialog, wrapsize);

		if (dialogManager->GetSpeaker(id))// if right side convo (Player)
		{
			ImGui::NewLine();
			ImGui::SameLine(ImGui::GetWindowWidth() - 70);
			ImGui::ImageButton(playerIcon, iconSize, ImVec2(0, 1), ImVec2(1, 0));
			ImGui::SameLine(ImGui::GetWindowWidth() - 77 - (dialog.find("\n") != std::string::npos ? dialog.find("\n") : dialog.size()) * 7.4f);
			if (dialogManager->GetSelectedChoice(prevID))//2nd choice selected
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(220, 30, 58))); //unselected
			else//1st
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(0, 128, 0))); //selected
		}
		else //left side (NPC)
		{
			//ImGui::Button("passenger", ImVec2(40,40));
			ImGui::ImageButton(passengerIcon, iconSize, ImVec2(0, 1), ImVec2(1, 0));
			ImGui::SameLine();
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(0, 136, 204))); //passenger
		}
		ImGui::Button(dialog.c_str());
		ImGui::PopStyleColor();
		if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0))
		{//edit text for 1st choice
			selectedID = id;
			editDialog = dialogManager->GetDialogue(selectedID);
			for (size_t i = editDialog.size(); i < 500; i++)
			{
				editDialog += " ";
			}
			BreakString(editDialog, wrapsize);
		}
		else if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(0))
		{//change selected to 1st choice
			dialogManager->SetSelectedChoice(prevID, 0);
		}
		if (id2) //if have 2nd choice
		{
			dialog2 = dialogManager->GetDialogue(id2);
			BreakString(dialog2, wrapsize);
			if (dialogManager->GetSpeaker(id2))
			{
				ImGui::NewLine();
				ImGui::SameLine(ImGui::GetWindowWidth() - 70);
				ImGui::ImageButton(playerIcon, iconSize, ImVec2(0, 1), ImVec2(1, 0));
				ImGui::SameLine(ImGui::GetWindowWidth() - 77 - (dialog2.find("\n") != std::string::npos ? dialog2.find("\n") : dialog2.size()) * 7.4f);
				if (dialogManager->GetSelectedChoice(prevID))//2nd choice selected
					ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(0, 128, 0))); //selected
				else//1st
					ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(220, 30, 58))); //unselected
			}
			else //left side (NPC)
			{
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(0, 136, 204)));
			}
			ImGui::Button(dialog2.c_str());
			ImGui::PopStyleColor();
			if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0))
			{//edit text for 2nd choice
				selectedID = id2;
				editDialog = dialogManager->GetDialogue(selectedID);
				for (size_t i = editDialog.size(); i < 500; i++)
				{
					editDialog += " ";
				}
				BreakString(editDialog, wrapsize);
			}
			else if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(0))
			{//change selected to 2nd choice
				dialogManager->SetSelectedChoice(prevID, 1);
			}
		}
		//Get new ID for net loop
		if (dialogManager->GetSelectedChoice(prevID))//2nd
			prevID = id2;
		else//1st
			prevID = id;
		id = dialogManager->GetNext(prevID);
		id2 = dialogManager->GetNext2(prevID);


		ImGui::NewLine();
	}
	ImGui::Separator();
	//LOG_INFO(std::to_string(ImGui::GetScrollY()));

	if (selectedID)
	{
		ImGui::Button(" ", ImVec2(1, 150));
		ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(ImColor(50, 50, 50)));
		ImGui::SetCursorPos(ImVec2(10, ImGui::GetWindowHeight() - 120 + ImGui::GetScrollY()));
		ImGui::BeginChild("yeet", ImVec2(ImGui::GetWindowWidth() - 20, 100), true);
		ImGui::InputTextMultiline(" ", const_cast<char*>(editDialog.c_str()), 1000,
			ImVec2(ImGui::GetWindowWidth() - 100, 80));
		ImGui::SameLine();
		if (ImGui::ImageButton(sendIcon, ImVec2(50, 50), ImVec2(0, 1), ImVec2(1, 0)))
		{
			std::string editedDialog;
			std::string word;
			std::istringstream ss(editDialog);

			while (ss >> word) {
				if (!editedDialog.empty()) {
					editedDialog += ' ';
				}
				editedDialog += word;
			}
			dialogManager->EditDialogue(selectedID, editedDialog);
		}
		ImGui::EndChild();
		ImGui::PopStyleColor();
	}

	ImGui::End();
}
void DialoguePanel::Free()
{

}
std::string& DialoguePanel::BreakString(std::string& _str, int _offset)
{
	int offset = 0;
	while (_str.size() > _offset)
	{
		if (_str[_offset] == ' ')
		{
			_str.replace(_offset, 1, "\n");
			_offset += 50;
		}
		else
		{
			offset = (int)_str.find("\n", _offset);
			_offset += offset;
		}
	}
	return _str;
}