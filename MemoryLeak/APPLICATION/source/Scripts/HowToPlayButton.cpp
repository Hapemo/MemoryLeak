/*!*****************************************************************************
\file HowToPlayButton.cpp
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 24-11-2022
\brief
This file contains the function definitions of the class HowToPlayButton.
*******************************************************************************/

#include "HowToPlayButton.h"

REGISTER_SCRIPT(ScriptComponent, HowToPlayButton);

/*!*****************************************************************************
\brief
Function will run on initialisation of the entity.
*******************************************************************************/
void HowToPlayButton::StartScript(Entity const& gob) {
	(void)gob;
	//LOG_INFO("How to Play button script starts works!!!");
}

/*!*****************************************************************************
\brief
Function will run on every update while the entity is active.
*******************************************************************************/
void HowToPlayButton::UpdateScript(Entity const& gob) {
	if(gob.HasComponent<Button>())
		if (gob.GetComponent<Button>().activated) {
			LOG_INFO("How to Play button activated script works!!!");
			(FUNC->SelectScene("Menu_Main")).Pause(true);
			(FUNC->SelectScene("How_To_Play")).Pause(false);
		}
}

/*!*****************************************************************************
\brief
Function will run on exit or when the entity is destroyed.
*******************************************************************************/
void HowToPlayButton::EndScript(Entity const& gob) {
	(void)gob;
	//LOG_INFO("How to Play button script end works!!!");
}
