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
#include "ScriptComponent.h"

class LogicSystem : public System
{
public:
	enum class E_SCRIPTTYPE {
		INIT = 1,
		UPDATE = 2,
		EXIT = 3,
	};

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

	/*!*****************************************************************************
	\brief
	Run the initialisation function for all entities' scripts given by the parameter.
	*******************************************************************************/
	void Init(std::set<Entity> const & _entities);

	/*!*****************************************************************************
	\brief
	Run the update function for all entities' scripts given by the parameter.
	*******************************************************************************/
	void Update(std::set<Entity> const& _entities);

	/*!*****************************************************************************
	\brief
	Run the exit function for all entities' scripts given by the parameter.
	*******************************************************************************/
	void Exit(std::set<Entity> const& _entities);

	/*!*****************************************************************************
	\brief
	Run specified script for entity.
	*******************************************************************************/
	void RunScript(Entity const& _e, E_SCRIPTTYPE _type);

private:
	double mAccumulatedDT{ 0.0 };					
	const double mFixedDT{ 1.0 / 60.0 };			
	const double mAccumulatedDTCap{ 1.0 };			
};
