/*!*****************************************************************************
\file DialogueScript.cpp
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 23-11-2022
\brief
The DialogueScript handles the dialogue functionalities such as proceeding to
the next line of dialogue and the zooming in of the camera during the dialogue
scene.
*******************************************************************************/

#include "DialogueScript.h"

REGISTER_SCRIPT(ScriptComponent, DialogueScript);

/*!*****************************************************************************
\brief
Function will run when the gamestate of the entity is activated.
*******************************************************************************/
void DialogueScript::Alive(Entity const& _e) {
	(void)_e;
}

/*!*****************************************************************************
\brief
Function will run on initialisation of the entity.
*******************************************************************************/
void DialogueScript::Init(Entity const& _e) {
	(void)_e;
	//LOG_INFO("Dialogue script starts works!!!");
	FUNC->LoadDialogs("Dialogue LittleGirl 0");
	FUNC->SetCurrentDialogueID(1);
	if (_e.HasComponent<Text>()) _e.GetComponent<Text>().text = FUNC->GetDialogue(FUNC->GetCurrentDialogueID());
	(FUNC->GetEntity("DialogueBox", "Level1")).Activate();
	currScn = &(FUNC->SelectScene("Level1"));
	currCamera = &FUNC->CurrentCamera();
	initialCamScale = FUNC->CurrentCamera().scale;
	currCamScale = initialCamScale; 
	targetCamScale = initialCamScale * 0.5f;
}

/*!*****************************************************************************
\brief
Function will run on every update while the entity is active.
*******************************************************************************/
void DialogueScript::Update(Entity const& _e) {
	currCamera->scale = currCamScale;
	if (currCamera->scale.x >= targetCamScale.x)
		currCamera->scale.x -= 500 * (float)FUNC->GetDeltaTime();
	currCamScale = currCamera->scale;
	if (FUNC->CheckKey(E_STATE::PRESS, M_BUTTON_L)) {
		if (_e.HasComponent<Text>()) {
			int currentId = FUNC->GetCurrentDialogueID();
			if (!FUNC->SetCurrentDialogueID(++currentId)) {
				_e.GetComponent<Text>().text = "";
				_e.Deactivate();
			} else {
				_e.GetComponent<Text>().text = FUNC->GetDialogue(currentId);
				FUNC->PlaySoundInChannel("BTNCLICK", (int)E_AUDIO_CHANNEL::FORCEPLAY);
			}
		}
	}

	if (FUNC->CheckKey(HOLD, LEFT_CONTROL) && FUNC->CheckKey(HOLD, LEFT_SHIFT) && FUNC->CheckKey(PRESS, N)) {
		_e.GetComponent<Text>().text = "";
		_e.Deactivate();
	}
}

/*!*****************************************************************************
\brief
Function will run on fixed delta time.
*******************************************************************************/
void DialogueScript::FixedUpdate(Entity const& _e) {
	(void)_e;
}

/*!*****************************************************************************
\brief
Function will run on exit or when the entity is destroyed.
*******************************************************************************/
void DialogueScript::Exit(Entity const& _e) {
	(void)_e;
	//LOG_INFO("Dialogue script end works!!!");
	(FUNC->GetEntity("DialogueBox", "Level1")).Deactivate();
}

/*!*****************************************************************************
\brief
Function will run when the gamestate of the entity exits.
*******************************************************************************/
void DialogueScript::Dead(Entity const& _e) {
	(void)_e;
}
