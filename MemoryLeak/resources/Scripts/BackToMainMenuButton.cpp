/*!*****************************************************************************
\file TestScript.cpp
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 02-11-2022
\brief
This file contains the function definitions of the class TestScript.
The TestScript class is an example to test the scripting component in the
engine.
*******************************************************************************/

#include "TestScript.h"

/*!*****************************************************************************
\brief
Function will run on initialisation of the entity.
*******************************************************************************/
void TestScript::StartScript(Entity const& gob) {
	(void)gob;
	LOG_INFO("Test script starts works!!!");
}

/*!*****************************************************************************
\brief
Function will run on every update while the entity is active.
*******************************************************************************/
void TestScript::UpdateScript(Entity const& gob) {
	(void)gob;
	LOG_INFO("Test script updating works!!!");
}

/*!*****************************************************************************
\brief
Function will run on exit or when the entity is destroyed.
*******************************************************************************/
void TestScript::EndScript(Entity const& gob) {
	(void)gob;
	LOG_INFO("Test script end works!!!");
}

//REGISTER_SCRIPT(ScriptComponent, TestScript);
