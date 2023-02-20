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
		ALIVE = 0,
		INIT = 1,
		UPDATE = 2,
		EXIT = 3,
		DEAD = 4
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
	Activate logic system in application.
	*******************************************************************************/
	void Activate();

	/*!*****************************************************************************
	\brief
	Exit logic system in application.
	*******************************************************************************/
	void Close();

	/*!*****************************************************************************
	\brief
	Run the alive function for all active entities' scripts.
	*******************************************************************************/
	void Alive();

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
	Run the dead function for all active entities' scripts.
	*******************************************************************************/
	void Dead();

	/*!*****************************************************************************
	\brief
	Run the alive function for all entities' scripts given by the parameter.
	*******************************************************************************/
	void Alive(std::set<Entity> const& _entities);

	/*!*****************************************************************************
	\brief
	Run the initialisation function for all entities' scripts given by the parameter.
	*******************************************************************************/
	void Init(std::set<Entity> const& _entities);

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
	Run the dead function for all entities' scripts given by the parameter.
	*******************************************************************************/
	void Dead(std::set<Entity> const& _entities);

	/*!*****************************************************************************
	\brief
	Run the alive function for entity.
	*******************************************************************************/
	void Alive(Entity const& _e);

	/*!*****************************************************************************
	\brief
	Run the initialisation function for entity.
	*******************************************************************************/
	void Init(Entity const& _e);

	/*!*****************************************************************************
	\brief
	Run the update function for entity.
	*******************************************************************************/
	void Update(Entity const& _e);

	/*!*****************************************************************************
	\brief
	Run the exit function for entity.
	*******************************************************************************/
	void Exit(Entity const& _e);

	/*!*****************************************************************************
	\brief
	Run the dead function for entity.
	*******************************************************************************/
	void Dead(Entity const& _e);

	/*!*****************************************************************************
	\brief
	Run specified script for entity.
	*******************************************************************************/
	void RunScript(Entity const& _e, E_SCRIPTTYPE _type);

private:
		
};
