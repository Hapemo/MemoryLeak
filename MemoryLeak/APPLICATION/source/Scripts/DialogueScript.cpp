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
	if (gob.HasComponent<Text>()) gob.GetComponent<Text>().text = FUNC->GetDialogue(FUNC->GetCurrentDialogueID());
	(FUNC->GetEntity("DialogueBox", "Level1")).Activate();
	Scene& scn = (FUNC->SelectScene("Level1"));
	initialCamScale = scn.mCamera.scale;
	targetCamScale = initialCamScale * 0.5f;
}

/*!*****************************************************************************
\brief
Function will run on every update while the entity is active.
*******************************************************************************/
void DialogueScript::UpdateScript(Entity const& gob) {
	Scene& scn = (FUNC->SelectScene("Level1"));

	if (scn.mCamera.scale.x >= targetCamScale.x)
	{
		scn.mCamera.scale.x -= 500 * (float)FPSManager::dt;
	}
	if (FUNC->CheckKey(E_STATE::PRESS, M_BUTTON_L)) {
		if (gob.HasComponent<Text>()) {
			int currentId = FUNC->GetCurrentDialogueID();
			if (!FUNC->SetCurrentDialogueID(++currentId)) {
				gob.GetComponent<Text>().text = "";
				gob.Deactivate();
			} else {
				gob.GetComponent<Text>().text = FUNC->GetDialogue(currentId);
			}
		}
	}
}

/*!*****************************************************************************
\brief
Function will run on exit or when the entity is destroyed.
*******************************************************************************/
void DialogueScript::EndScript(Entity const& gob) {
	(void)gob;
	FUNC->SelectScene("Level1").mCamera.scale = initialCamScale;
	//LOG_INFO("Dialogue script end works!!!");
	(FUNC->GetEntity("DialogueBox", "Level1")).Deactivate();
}
