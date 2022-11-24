/*!*****************************************************************************
\file ExitGameButton.cpp
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 24-11-2022
\brief
This file contains the function definitions of the class ExitGameButton.
*******************************************************************************/

#include "ExitGameButton.h"

REGISTER_SCRIPT(ScriptComponent, ExitGameButton);

/*!*****************************************************************************
\brief
Function will run on initialisation of the entity.
*******************************************************************************/
void ExitGameButton::StartScript(Entity const& gob) {
	(void)gob;
	//LOG_INFO("How to Play button script starts works!!!");
}

/*!*****************************************************************************
\brief
Function will run on every update while the entity is active.
*******************************************************************************/
void ExitGameButton::UpdateScript(Entity const& gob) {
	if(gob.HasComponent<Button>())
		if (gob.GetComponent<Button>().activated)
			FUNC->GameStateExit();
}

/*!*****************************************************************************
\brief
Function will run on exit or when the entity is destroyed.
*******************************************************************************/
void ExitGameButton::EndScript(Entity const& gob) {
	(void)gob;
	//LOG_INFO("How to Play button script end works!!!");
}
