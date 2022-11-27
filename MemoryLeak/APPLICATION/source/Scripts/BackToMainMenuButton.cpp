/*!*****************************************************************************
\file BackToMainMenuButton.h
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 24-11-2022
\brief
The BackToMainMenuButton script returns the scene to the main menu on button press.
*******************************************************************************/

#include "BackToMainMenuButton.h"

REGISTER_SCRIPT(ScriptComponent, BackToMainMenuButton);

/*!*****************************************************************************
\brief
Function will run on initialisation of the entity.
*******************************************************************************/
void BackToMainMenuButton::StartScript(Entity const& gob) {
	(void)gob;
	//LOG_INFO("Back to Main Menu button script starts works!!!");
}

/*!*****************************************************************************
\brief
Function will run on every update while the entity is active.
*******************************************************************************/
void BackToMainMenuButton::UpdateScript(Entity const& gob) {
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
	if(gob.HasComponent<Button>())
		if (gob.GetComponent<Button>().activated) {
			(FUNC->SelectScene("Settings")).Pause(true);
			(FUNC->SelectScene("How_To_Play")).Pause(true);
			(FUNC->SelectScene("Quit Confirmation")).Pause(true);
			(FUNC->SelectScene("Menu_Main")).Pause(false);
			(FUNC->SelectScene("Pause")).Pause(false);
			FUNC->PlayAnySound("Button_Click_SFX", (int)E_AUDIO_CHANNEL::FORCEPLAY);
		}
}

/*!*****************************************************************************
\brief
Function will run on exit or when the entity is destroyed.
*******************************************************************************/
void BackToMainMenuButton::EndScript(Entity const& gob) {
	(void)gob;
	//LOG_INFO("Back to Main Menu button script end works!!!");
}
