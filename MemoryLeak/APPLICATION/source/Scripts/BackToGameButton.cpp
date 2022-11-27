/*!*****************************************************************************
\file BackToGameButton.h
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 24-11-2022
\brief
The BackToGameButton script returns the scene to the gameplay on button press.
Press "ESC" to toggle the pause menu.
*******************************************************************************/

#include "BackToGameButton.h"

REGISTER_SCRIPT(ScriptComponent, BackToGameButton);

/*!*****************************************************************************
\brief
Function will run on initialisation of the entity.
*******************************************************************************/
void BackToGameButton::StartScript(Entity const& gob) {
	(void)gob;
	//LOG_INFO("Back to Main Menu button script starts works!!!");
}

/*!*****************************************************************************
\brief
Function will run on every update while the entity is active.
*******************************************************************************/
void BackToGameButton::UpdateScript(Entity const& gob) {
	static float x = gob.GetComponent<Transform>().scale.x;
	static float y = gob.GetComponent<Transform>().scale.y;
	if (gob.GetComponent<Button>().isHover) {
		if (gob.GetComponent<Transform>().scale.x < x + 15.f)
			++(gob.GetComponent<Transform>().scale.x);
		if (gob.GetComponent<Transform>().scale.y < y + 15.f)
			++(gob.GetComponent<Transform>().scale.y);
	}
	else {
		if (gob.GetComponent<Transform>().scale.x > x)
			--(gob.GetComponent<Transform>().scale.x);
		if (gob.GetComponent<Transform>().scale.y > y)
			--(gob.GetComponent<Transform>().scale.y);
	}

	if (gob.HasComponent<Button>() && gob.GetComponent<Button>().activated) {
		activate = false;
		(FUNC->SelectScene("Settings")).Pause(true);
		(FUNC->SelectScene("How_To_Play")).Pause(true);
		(FUNC->SelectScene("Pause")).Pause(true);
		(FUNC->SelectScene("Quit Confirmation")).Pause(true);
		(FUNC->SelectScene("Level1")).Pause(false);
		//FUNC->PlayAnySound("Button_Click_SFX", (int)E_AUDIO_CHANNEL::FORCEPLAY);
	}

	if (activate && FUNC->CheckKey(E_STATE::PRESS, E_KEY::ESCAPE)) {
		activate = false;
		(FUNC->SelectScene("Settings")).Pause(true);
		(FUNC->SelectScene("How_To_Play")).Pause(true);
		(FUNC->SelectScene("Pause")).Pause(true);
		(FUNC->SelectScene("Quit Confirmation")).Pause(true);
		(FUNC->SelectScene("Level1")).Pause(false);
		//FUNC->PlayAnySound("Button_Click_SFX", (int)E_AUDIO_CHANNEL::FORCEPLAY);
	}

	if (FUNC->CheckKey(E_STATE::RELEASE, E_KEY::ESCAPE)) activate = true;
}

/*!*****************************************************************************
\brief
Function will run on exit or when the entity is destroyed.
*******************************************************************************/
void BackToGameButton::EndScript(Entity const& gob) {
	(void)gob;
	//LOG_INFO("Back to Main Menu button script end works!!!");
}
