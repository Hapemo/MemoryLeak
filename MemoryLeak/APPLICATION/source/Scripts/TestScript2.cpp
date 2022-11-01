/*!*****************************************************************************
\file TestScript2.cpp
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 24-10-2022
\brief
This file contains the function definitions of the class TestScript2.
The TestScript2 class is an example to test the scripting component in the
engine.
*******************************************************************************/

#include "TestScript2.h"

/*!*****************************************************************************
\brief
Function will run on initialisation of the entity.
*******************************************************************************/
void TestScript2::StartScript(Entity const& gob) {
	(void)gob;
	LOG_INFO("Test script2 starts works!!!");
}

/*!*****************************************************************************
\brief
Function will run on every update while the entity is active.
*******************************************************************************/
void TestScript2::UpdateScript(Entity const& gob) {
	//LOG_INFO("Test script updating works!!!");
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
void TestScript2::EndScript(Entity const& gob) {
	(void)gob;
	LOG_INFO("Test script2 end works!!!");
}
