/*!*****************************************************************************
\file ScriptComponent.cpp
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 24-10-2022
\brief
This file contains the function definitions of the class ScriptComponent.
The ScriptComponent class is the base class for the scripting component in the
engine.
*******************************************************************************/

#include "ScriptComponent.h"

/*!*****************************************************************************
\brief
Start script to run on initialisation.
*******************************************************************************/
void ScriptComponent::StartScript(Entity const& gob) {
	(void)gob;
	LOG_INFO("Base script starts works!!!");
}

/*!*****************************************************************************
\brief
Update script to run every update function call.
*******************************************************************************/
void ScriptComponent::UpdateScript(Entity const& gob) {
	(void)gob;
	//LOG_INFO("Base script updating works!!!");
}

/*!*****************************************************************************
\brief
End script to run when the entity gets destroyed/exit.
*******************************************************************************/
void ScriptComponent::EndScript(Entity const& gob) {
	(void)gob;
	LOG_INFO("Base script end works!!!");
}