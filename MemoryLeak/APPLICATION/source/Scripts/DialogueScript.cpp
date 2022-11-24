/*!*****************************************************************************
\file DialogueScript.cpp
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 02-11-2022
\brief
This file contains the function definitions of the class DialogueScript.
*******************************************************************************/

#include "DialogueScript.h"

REGISTER_SCRIPT(ScriptComponent, DialogueScript);

/*!*****************************************************************************
\brief
Function will run on initialisation of the entity.
*******************************************************************************/
void DialogueScript::StartScript(Entity const& gob) {
	(void)gob;
	LOG_INFO("Dialogue script starts works!!!");
	FUNC->LoadDialogs("Dialogue LittleGirl 0");
	FUNC->SetCurrentDialogueID(1);
}

/*!*****************************************************************************
\brief
Function will run on every update while the entity is active.
*******************************************************************************/
void DialogueScript::UpdateScript(Entity const& gob) {
	if (FUNC->CheckKey(E_STATE::PRESS, M_BUTTON_L)) {
		int currentId = FUNC->GetCurrentDialogueID();
		if (gob.HasComponent<Text>()) {
			gob.GetComponent<Text>().text = FUNC->GetDialogue(currentId);
			if (!FUNC->SetCurrentDialogueID(++currentId)) gob.GetComponent<Text>().text = "";
		}
	}
}

/*!*****************************************************************************
\brief
Function will run on exit or when the entity is destroyed.
*******************************************************************************/
void DialogueScript::EndScript(Entity const& gob) {
	(void)gob;
	LOG_INFO("Dialogue script end works!!!");
}
