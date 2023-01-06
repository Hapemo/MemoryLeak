#pragma once
/*!*****************************************************************************
\file WASDScript.h
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 24-10-2022
\brief
This file contains the function declarations of the class WASDScript.
The WASDScript class is an example to test the scripting component in the
engine.
*******************************************************************************/

#pragma once
#include "ECS_tools.h"
#include "ScriptComponent.h"
#include "ScriptManager.h"

class WASDScript : public ScriptComponent {
private:
	std::string name = "WASDScript";

public:
	WASDScript() = default;
	virtual ~WASDScript() = default;

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
