/*!*****************************************************************************
\file PauseButton.h
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 27-11-2022
\brief
The PauseButton script pauses the game on button press.
*******************************************************************************/

#include "PauseButton.h"

REGISTER_SCRIPT(ScriptComponent, PauseButton);

/*!*****************************************************************************
\brief
Function will run on initialisation of the entity.
*******************************************************************************/
void PauseButton::StartScript(Entity const& gob) {
	(void)gob;
	//LOG_INFO("Back to Main Menu button script starts works!!!");
}

/*!*****************************************************************************
\brief
Function will run on every update while the entity is active.
*******************************************************************************/
void PauseButton::UpdateScript(Entity const& gob) {
	if (gob.HasComponent<Button>()) {
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
		if (gob.GetComponent<Button>().activated) {
			Scene& menuScene{ FUNC->SelectScene("Menu_Main") };
			if (menuScene.mName != "Error") { // If it's at main menu
				(FUNC->SelectScene("Quit Confirmation")).Pause(true);
				menuScene.Pause(false);
				//FUNC->PlayAnySound("Button_Click_SFX", (int)E_AUDIO_CHANNEL::FORCEPLAY);
			} else { // if it's game pause
				(FUNC->SelectScene("Settings")).Pause(true);
				(FUNC->SelectScene("How_To_Play")).Pause(true);
				(FUNC->SelectScene("Level1")).Pause(true);
				(FUNC->SelectScene("Quit Confirmation")).Pause(true);
				(FUNC->SelectScene("Pause")).Pause(false);
				//FUNC->PlayAnySound("Button_Click_SFX", (int)E_AUDIO_CHANNEL::FORCEPLAY);
			}
		}
	}
}

/*!*****************************************************************************
\brief
Function will run on exit or when the entity is destroyed.
*******************************************************************************/
void PauseButton::EndScript(Entity const& gob) {
	(void)gob;
	//LOG_INFO("Back to Main Menu button script end works!!!");
}
