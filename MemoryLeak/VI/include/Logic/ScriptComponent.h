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
#include "Logger.h"
#include "InternalCalls.h"

class ScriptComponent {
private:
	std::string name = "Base";
public:
	/*!*****************************************************************************
	\brief
	Default constructor and destructor.
	*******************************************************************************/
	ScriptComponent() = default;
	virtual ~ScriptComponent() = default;

	/*!*****************************************************************************
	\brief
	Delete copy constructor.
	*******************************************************************************/
	ScriptComponent(const ScriptComponent&) = delete;
	const ScriptComponent& operator=(const ScriptComponent&) = delete;

	/*!*****************************************************************************
	\brief
	Start script to run on initialisation.
	*******************************************************************************/
	virtual void StartScript(Entity const& gob);

	/*!*****************************************************************************
	\brief
	Update script to run every update function call.
	*******************************************************************************/
	virtual void UpdateScript(Entity const& gob);

	/*!*****************************************************************************
	\brief
	End script to run when the entity gets destroyed/exit.
	*******************************************************************************/
	virtual void EndScript(Entity const& gob);

	/*!*****************************************************************************
	\brief
	Retrieve the name of the script.
	*******************************************************************************/
	inline std::string GetName() { return name; }

	/*!*****************************************************************************
	\brief
	Retrieve the script object.
	*******************************************************************************/
	inline ScriptComponent* GetScript() { return this; }
};
