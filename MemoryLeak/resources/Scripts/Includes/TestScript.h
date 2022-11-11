/*!*****************************************************************************
\file TestScript.h
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 02-11-2022
\brief
This file contains the function declarations of the class TestScript.
The TestScript class is an example to test the scripting component in the
engine.
*******************************************************************************/

#pragma once
#include "ECS_tools.h"
#include "Input.h"
#include "ScriptManager.h"
#include "ScriptComponent.h"

class TestScript : public ScriptComponent {
private:
	std::string name = "TestScript";

public:
	TestScript() = default;
	virtual ~TestScript() = default;

	/*!*****************************************************************************
	\brief
	Function will run on initialisation of the entity.
	*******************************************************************************/
	void StartScript(Entity const& gob) override;

	/*!*****************************************************************************
	\brief
	Function will run on every update while the entity is active.
	*******************************************************************************/
	void UpdateScript(Entity const& gob) override;

	/*!*****************************************************************************
	\brief
	Function will run on exit or when the entity is destroyed.
	*******************************************************************************/
	void EndScript(Entity const& gob) override;
};
