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

/*!*****************************************************************************
\brief
Function will run on initialisation of the entity.
*******************************************************************************/
void DialogueScript::StartScript(Entity const& gob) {
	(void)gob;
	LOG_INFO("Test script starts works!!!");
}

/*!*****************************************************************************
\brief
Function will run on every update while the entity is active.
*******************************************************************************/
void DialogueScript::UpdateScript(Entity const& gob) {
	(void)gob;
	static int counter{};
	if (++counter > 1000) {
		LOG_INFO("Test script updating works!!!");
		//std::cout << InternalCalls::GetInstance()->GetWorldMousePos().y << " " << InternalCalls::GetInstance()->GetWorldMousePos().x << "\n";
		counter = 0;
	}
}

/*!*****************************************************************************
\brief
Function will run on exit or when the entity is destroyed.
*******************************************************************************/
void DialogueScript::EndScript(Entity const& gob) {
	(void)gob;
	LOG_INFO("Test script end works!!!");
}
