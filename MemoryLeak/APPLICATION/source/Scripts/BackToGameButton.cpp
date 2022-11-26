/*!*****************************************************************************
\file BackToGameButton.cpp
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 24-11-2022
\brief
This file contains the function definitions of the class BackToGameButton.
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
	if (gob.HasComponent<Button>() && gob.GetComponent<Button>().activated)
	{
		(FUNC->SelectScene("Settings")).Pause(true);
		(FUNC->SelectScene("How_To_Play")).Pause(true);
		(FUNC->SelectScene("Pause")).Pause(true);
		(FUNC->SelectScene("Level1")).Pause(false);
	}

	if (activate && FUNC->CheckKey(E_STATE::RELEASE, E_KEY::ESCAPE)) {
		activate = false;
		(FUNC->SelectScene("Settings")).Pause(true);
		(FUNC->SelectScene("How_To_Play")).Pause(true);
		(FUNC->SelectScene("Pause")).Pause(true);
		(FUNC->SelectScene("Level1")).Pause(false);
	}

	if (FUNC->CheckKey(E_STATE::NOTPRESS, E_KEY::ESCAPE)) activate = true;
}

/*!*****************************************************************************
\brief
Function will run on exit or when the entity is destroyed.
*******************************************************************************/
void BackToGameButton::EndScript(Entity const& gob) {
	(void)gob;
	//LOG_INFO("Back to Main Menu button script end works!!!");
}
