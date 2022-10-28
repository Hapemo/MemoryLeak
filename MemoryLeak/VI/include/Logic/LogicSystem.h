/*!*****************************************************************************
\file LogicSystem.h
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 24-10-2022
\brief
This file contains the function declarations of the class LogicSystem.
The LogicSystem class handles the C# scripting for the engine.
*******************************************************************************/

#pragma once

class ScriptManager;

#include "Singleton.h"
#include "ScriptComponent.h"
#include <string>
#include <vector>

class LogicSystem : public Singleton<LogicSystem>
{
public:
	/*!*****************************************************************************
	\brief
	Default constructor and destructor.
	*******************************************************************************/
	LogicSystem();
	~LogicSystem();

	/*!*****************************************************************************
	\brief
	Delete copy constructor.
	*******************************************************************************/
	LogicSystem(const LogicSystem&) = delete;
	const LogicSystem& operator=(const LogicSystem&) = delete;

	void Init();
	bool Update();
	void Exit();

	void AddBehaviour(std::string _key, ScriptManager* _behaviour);

private:
	// various behaviours (contains scripts)
	std::map<std::string, ScriptManager*> mBehaviours;

	// a behaviour-component contains the keys into "behaviours"
	std::map<std::string, ScriptComponent*> mBehaviourComponents;
};
