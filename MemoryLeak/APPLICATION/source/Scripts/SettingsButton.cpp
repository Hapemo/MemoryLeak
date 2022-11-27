/*!*****************************************************************************
\file SettingsButton.cpp
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 24-11-2022
\brief
The SettingsButton script activates the "Settings" scene on button press.
*******************************************************************************/

#include "SettingsButton.h"

REGISTER_SCRIPT(ScriptComponent, SettingsButton);

/*!*****************************************************************************
\brief
Function will run on initialisation of the entity.
*******************************************************************************/
void SettingsButton::StartScript(Entity const& gob) {
	(void)gob;
	//LOG_INFO("How to Play button script starts works!!!");
}

/*!*****************************************************************************
\brief
Function will run on every update while the entity is active.
*******************************************************************************/
void SettingsButton::UpdateScript(Entity const& gob) {
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

	if (gob.HasComponent<Button>()) {
		if (gob.GetComponent<Button>().isHover)
		if (gob.GetComponent<Button>().activated) {
			(FUNC->SelectScene("Menu_Main")).Pause(true);
			(FUNC->SelectScene("Settings")).Pause(false);
			//FUNC->PlayAnySound("Button_Click_SFX", (int)E_AUDIO_CHANNEL::FORCEPLAY);
		}
	}
}

/*!*****************************************************************************
\brief
Function will run on exit or when the entity is destroyed.
*******************************************************************************/
void SettingsButton::EndScript(Entity const& gob) {
	(void)gob;
	//LOG_INFO("How to Play button script end works!!!");
}
