/*!*****************************************************************************
\file WASDScript.cpp
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 24-10-2022
\brief
This file contains the function definitions of the class WASDScript.
The WASDScript class is an example to test the scripting component in the
engine.
*******************************************************************************/

#include "WASDScript.h"

REGISTER_SCRIPT(ScriptComponent, RotateScript);

/*!*****************************************************************************
\brief
Function will run on initialisation of the entity.
*******************************************************************************/
void WASDScript::StartScript(Entity const& gob) {
	(void)gob;
	LOG_INFO("WASDScript starts works!!!");
}

/*!*****************************************************************************
\brief
Function will run on every update while the entity is active.
*******************************************************************************/
void WASDScript::UpdateScript(Entity const& gob) {
	//LOG_INFO("RotateScript updating works!!!");
	if (FUNC->CheckKey(E_STATE::HOLD, W)) {
		gob.GetComponent<Transform>().translation.y += 1.f;
	}
	else if (FUNC->CheckKey(E_STATE::HOLD, A)) {
		gob.GetComponent<Transform>().translation.x -= 1.f;
	}
	else if (FUNC->CheckKey(E_STATE::HOLD, S)) {
		gob.GetComponent<Transform>().translation.y -= 1.f;
	}
	else if (FUNC->CheckKey(E_STATE::HOLD, D)) {
		gob.GetComponent<Transform>().translation.x += 1.f;
	}
}

/*!*****************************************************************************
\brief
Function will run on exit or when the entity is destroyed.
*******************************************************************************/
void WASDScript::EndScript(Entity const& gob) {
	(void)gob;
	LOG_INFO("WASDScript end works!!!");
}
