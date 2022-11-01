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
#include "ECS_tools.h"
#include "ScriptManager.h"

class LogicSystem : public System
{
public:
	/*!*****************************************************************************
	\brief
	Default constructor and destructor.
	*******************************************************************************/
	LogicSystem() = default;
	~LogicSystem() = default;

	/*!*****************************************************************************
	\brief
	Delete copy constructor.
	*******************************************************************************/
	LogicSystem(const LogicSystem&) = delete;
	const LogicSystem& operator=(const LogicSystem&) = delete;

	/*!*****************************************************************************
	\brief
	Run the initialisation function for all active entities' scripts.
	*******************************************************************************/
	void Init();

	/*!*****************************************************************************
	\brief
	Run the update function for all active entities' scripts.
	*******************************************************************************/
	void Update();

	/*!*****************************************************************************
	\brief
	Run the exit function for all active entities' scripts.
	*******************************************************************************/
	void Exit();
};
