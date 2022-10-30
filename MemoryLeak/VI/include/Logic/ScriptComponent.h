/*!*****************************************************************************
\file ScriptComponent.h
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 24-10-2022
\brief
This file contains the function declarations of the class ScriptComponent.
The ScriptComponent class is the base class for the scripting component in the
engine.
*******************************************************************************/

#pragma once
#include "ECS_items.h"

class ScriptComponent
{
public:
	/*!*****************************************************************************
	\brief
	Default constructor and destructor.
	*******************************************************************************/
	ScriptComponent() {}
	~ScriptComponent() {}

	/*!*****************************************************************************
	\brief
	Delete copy constructor.
	*******************************************************************************/
	ScriptComponent(const ScriptComponent&) = delete;
	const ScriptComponent& operator=(const ScriptComponent&) = delete;

	virtual void StartScript(Entity* gob) {
		(void)gob;
		LOG_INFO("Base script starts works!!!");
	}

	virtual void UpdateScript(Entity* gob) {
		(void)gob;
		LOG_INFO("Base script updating works!!!");
	}

	virtual void EndScript(Entity* gob) {
		(void)gob;
		LOG_INFO("Base script end works!!!");
	}
};

