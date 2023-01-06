/*!*****************************************************************************
\file ScaleScript.cpp
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 24-10-2022
\brief
This file contains the function definitions of the class ScaleScript.
The ScaleScript class is an example to test the scripting component in the
engine.
*******************************************************************************/

#include "ScaleScript.h"

/*!*****************************************************************************
\brief
Function will run on initialisation of the entity.
*******************************************************************************/
void ScaleScript::StartScript(Entity const& gob) {
	(void)gob;
	LOG_INFO("ScaleScript starts works!!!");
}

/*!*****************************************************************************
\brief
Function will run on every update while the entity is active.
*******************************************************************************/
void ScaleScript::UpdateScript(Entity const& gob) {
	//LOG_INFO("ScaleScript updating works!!!");
	if (Input::CheckKey(E_STATE::HOLD, Y)) {
		gob.GetComponent<Transform>().scale += 2;
	}
	else if (Input::CheckKey(E_STATE::HOLD, U)) {
		gob.GetComponent<Transform>().scale -= 2;
	}
}

/*!*****************************************************************************
\brief
Function will run on exit or when the entity is destroyed.
*******************************************************************************/
void ScaleScript::EndScript(Entity const& gob) {
	(void)gob;
	LOG_INFO("ScaleScript end works!!!");
}

//REGISTER_SCRIPT(ScriptComponent, ScaleScript);
