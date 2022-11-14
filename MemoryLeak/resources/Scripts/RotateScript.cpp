/*!*****************************************************************************
\file RotateScript.cpp
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 24-10-2022
\brief
This file contains the function definitions of the class RotateScript.
The RotateScript class is an example to test the scripting component in the
engine.
*******************************************************************************/

#include "RotateScript.h"

/*!*****************************************************************************
\brief
Function will run on initialisation of the entity.
*******************************************************************************/
void RotateScript::StartScript(Entity const& gob) {
	(void)gob;
	LOG_INFO("RotateScript starts works!!!");
}

/*!*****************************************************************************
\brief
Function will run on every update while the entity is active.
*******************************************************************************/
void RotateScript::UpdateScript(Entity const& gob) {
	//LOG_INFO("RotateScript updating works!!!");
	if (Input::CheckKey(E_STATE::HOLD, O)) {
		gob.GetComponent<Transform>().rotation += 0.05f;
	}
	else if (Input::CheckKey(E_STATE::HOLD, P)) {
		gob.GetComponent<Transform>().rotation -= 0.05f;
	}
}

/*!*****************************************************************************
\brief
Function will run on exit or when the entity is destroyed.
*******************************************************************************/
void RotateScript::EndScript(Entity const& gob) {
	(void)gob;
	LOG_INFO("RotateScript end works!!!");
}

//REGISTER_SCRIPT(ScriptComponent, RotateScript);
