/*!*****************************************************************************
/*!*****************************************************************************
\file DialoguePanel.cpp
\author Huang Wei Jhin
\par DP email: h.weijhin@digipen.edu
\par Group: Memory Leak Studios
\date 20-10-2022
\brief
This file contains function definations for a Dialogue Panel Editor system that modifies
and view dialogues between a player and npc.
*******************************************************************************/
#include "DialoguePanel.h"
#include <ECSManager.h>

/*!*****************************************************************************
\brief
	Initializes the Dialogue Panel editor

\return
None.
*******************************************************************************/
void DialoguePanel::Init()
{
	//To be loaded from config file in the future...
	playerIcon = (void*)(intptr_t)spriteManager->GetTextureID("Textures\\Sprites\\mc.png");
	npcIcon = (void*)(intptr_t)spriteManager->GetTextureID("Textures\\Sprites\\girl.png");
	sendIcon = (void*)(intptr_t)spriteManager->GetTextureID("Textures\\Icons\\sendIcon.png");
	selectedID = 0;
	unselectedCol= ImVec4(ImColor(220, 30, 58));
	selectedCol= ImVec4(ImColor(0, 128, 0));
	npcCol= ImVec4(ImColor(0, 136, 204));
	backgroundCol=ImVec4(ImColor(50, 50, 50));
	//active = false;
}
/*!*****************************************************************************
\brief
	Updates the Dialogue Panel editor

\return
None.
*******************************************************************************/
void DialoguePanel::Update()
{
	if (!active)
		return;
	static int start{};
	if (start == 0)
	{
		start++;
		Init();
	}
	std::cout << "dddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd";
	ImGui::Begin("Dialog Editor");
	wrapsize = int(ImGui::GetWindowWidth() / 13);
	int id = 1;
	int id2 = 0;
	int prevID = 1;
	ImGui::SetCursorPosX(ImGui::GetWindowWidth() - sendbuttonSize.x-30);
	ImGui::PushStyleColor(ImGuiCol_Button, unselectedCol);
	if (ImGui::Button("X", sendbuttonSize))
	{
		active = false;
		ImGui::PopStyleColor();
		return;
	}
	ImGui::PopStyleColor();
	while (id)
	{
		if (dialogManager->GetDialogs().size() == 0)
		{
			active = false;
			break;
		}
		dialog = dialogManager->GetDialogue(id);
		if (id == 1 && dialog != dialogPrev) //reset selected if change dialogue
		{
			selectedID = 0;
			dialogPrev = dialog;
		}
		BreakString(dialog, wrapsize);

		if (dialogManager->GetSpeaker(id))// if right side convo (Player)
		{
			ImGui::NewLine();
			ImGui::SameLine(ImGui::GetWindowWidth() - 70);
			ImGui::ImageButton(playerIcon, iconSize, ImVec2(0, 1), ImVec2(1, 0));
			ImGui::SameLine(ImGui::GetWindowWidth() - 77 - (dialog.find("\n") != std::string::npos ? dialog.find("\n") : dialog.size()) * 7.4f);
			if (dialogManager->GetSelectedChoice(prevID))//2nd choice selected
				ImGui::PushStyleColor(ImGuiCol_Button, unselectedCol); //unselected
			else//1st
				ImGui::PushStyleColor(ImGuiCol_Button, selectedCol); //selected
		}
		else //left side (NPC)
		{
			ImGui::ImageButton(npcIcon, iconSize, ImVec2(0, 1), ImVec2(1, 0));
			ImGui::SameLine();
			ImGui::PushStyleColor(ImGuiCol_Button, npcCol); //passenger
		}
		ImGui::Button(dialog.c_str());
		ImGui::PopStyleColor();
		if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0))
		{//edit text for 1st choice
			selectedID = id;
			dialogEdit = dialogManager->GetDialogue(selectedID);
			for (size_t i = dialogEdit.size(); i < 500; i++)
			{
				dialogEdit += " ";
			}
			BreakString(dialogEdit, wrapsize);
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
					ImGui::PushStyleColor(ImGuiCol_Button, selectedCol); //selected
				else//1st
					ImGui::PushStyleColor(ImGuiCol_Button, unselectedCol); //unselected
			}
			else //left side (NPC)
			{
				ImGui::PushStyleColor(ImGuiCol_Button, npcCol);
			}
			ImGui::Button(dialog2.c_str());
			ImGui::PopStyleColor();
			if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0))
			{//edit text for 2nd choice
				selectedID = id2;
				dialogEdit = dialogManager->GetDialogue(selectedID);
				for (size_t i = dialogEdit.size(); i < 500; i++)
				{
					dialogEdit += " ";
				}
				BreakString(dialogEdit, wrapsize);
			}
			else if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(0))
			{//change selected to 2nd choice
				dialogManager->SetSelectedChoice(prevID, 1);
			}
		}
		//Get new ID for next loop
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
		ImGui::PushStyleColor(ImGuiCol_ChildBg, backgroundCol);
		ImGui::SetCursorPos(ImVec2(10, ImGui::GetWindowHeight() - 120 + ImGui::GetScrollY()));
		ImGui::BeginChild(" ", ImVec2(ImGui::GetWindowWidth() - 20, 100), true);
		ImGui::InputTextMultiline(" ", const_cast<char*>(dialogEdit.c_str()), 1000,
			ImVec2(ImGui::GetWindowWidth() - 100, 80));
		ImGui::SameLine();
		if (ImGui::ImageButton(sendIcon, sendbuttonSize, ImVec2(0, 1), ImVec2(1, 0)))
		{
			dialogManager->EditDialogue(selectedID, formatString(dialogEdit));
			selectedID = 0;
		}
		ImGui::EndChild();
		ImGui::PopStyleColor();
	}

	ImGui::End();
}
/*!*****************************************************************************
\brief
	Free the Dialogue Panel editor

\return
None.
*******************************************************************************/
void DialoguePanel::Free()
{

}
/*!*****************************************************************************
\brief
	This function removes duplicate white spaces and new line characters in a string
\param _str
	string to be formated
\return
	formated string
*******************************************************************************/
std::string DialoguePanel::formatString(std::string _str)
{
	std::string editedStr;
	std::string word;
	std::istringstream ss(_str);

	while (ss >> word) {
		if (!editedStr.empty()) {
			editedStr += ' ';
		}
		editedStr += word;
	}
	return editedStr;
}
/*!*****************************************************************************
\brief
	This function breaks a string by adding a string or character at specific intervals
	for text wraping
\param _str
	string to be formated
\param _offset
	minimun off set to break at
\param _breakAt
	character to break at 
	default = ' ' 
\param _breakWith
	string to break _str with
	default = "\n"
\return
	formated string
*******************************************************************************/
std::string& DialoguePanel::BreakString(std::string& _str, int _offset, char _breakAt, std::string _breakWith)
{
	int offset = 0;
	while (_str.size() > _offset)
	{
		if (_str[_offset] == _breakAt)
		{
			_str.replace(_offset, 1, _breakWith);
			_offset += 50;
		}
		else
		{
			offset = (int)_str.find(_breakWith, _offset);
			_offset += offset;
		}
	}
	return _str;
}