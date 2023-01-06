/*!*****************************************************************************
\file LogicSystem.cpp
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 24-10-2022
\brief
This file contains the function definitions of the class LogicSystem.
The LogicSystem class handles the C# scripting for the engine.
*******************************************************************************/

#include "LogicSystem.h"
#include "MonoManager.h"
#include "ScriptManager.h"

/*!*****************************************************************************
\brief
Run the initialisation function for all active entities' scripts.
*******************************************************************************/
void LogicSystem::Init() {
	LOG_DEBUG("Initialising LogicSystem.");
	//MonoManager::GetInstance()->InitMono();
	for (Entity const& e : mEntities) RunScript(e, E_SCRIPTTYPE::INIT);
	//GameStateManager::GetReference()->mcurrentGameState->mScenes[]
}

/*!*****************************************************************************
\brief
Run the update function for all active entities' scripts.
*******************************************************************************/
void LogicSystem::Update() {
	for (Entity const& e : mEntities) RunScript(e, E_SCRIPTTYPE::UPDATE);
}

/*!*****************************************************************************
\brief
Run the exit function for all active entities' scripts.
*******************************************************************************/
void LogicSystem::Exit() {
	LOG_DEBUG("Closing LogicSystem.");
	for (Entity const& e : mEntities) RunScript(e, E_SCRIPTTYPE::EXIT);
	//MonoManager::GetInstance()->CloseMono();
}

/*!*****************************************************************************
\brief
Run the initialisation function for all entities' scripts given by the parameter.
*******************************************************************************/
void LogicSystem::Init(std::set<Entity> const& _entities) {
	for (Entity const& e : _entities) RunScript(e, E_SCRIPTTYPE::INIT);
}

/*!*****************************************************************************
\brief
Run the update function for all entities' scripts given by the parameter.
*******************************************************************************/
void LogicSystem::Update(std::set<Entity> const& _entities) {
	for (Entity const& e : _entities) RunScript(e, E_SCRIPTTYPE::UPDATE);
}

/*!*****************************************************************************
\brief
Run the exit function for all entities' scripts given by the parameter.
*******************************************************************************/
void LogicSystem::Exit(std::set<Entity> const& _entities) {
	for (Entity const& e : _entities) RunScript(e, E_SCRIPTTYPE::EXIT);
}

/*!*****************************************************************************
\brief
Run specified script for entity.
*******************************************************************************/
void LogicSystem::RunScript(Entity const& _e, E_SCRIPTTYPE _type) {
	if (!_e.ShouldRun()) return;
	if (!_e.HasComponent<Script>()) return;

	std::string scriptName = _e.GetComponent<Script>().name;
	if (scriptName == "") {
		LOG_ERROR("Entity " + _e.GetComponent<General>().name + " component script name is empty!");
		return;
	}
	// Script is C++ script
	if (ScriptManager<ScriptComponent>::GetInstance()->GetScript(scriptName) != nullptr) {
		switch (_type) {
		case E_SCRIPTTYPE::INIT:
			LOG_INFO("Start Script for " + scriptName + " ran!");
			ScriptManager<ScriptComponent>::GetInstance()->GetScript(scriptName)->StartScript(_e);
			break;

		case E_SCRIPTTYPE::UPDATE:
			ScriptManager<ScriptComponent>::GetInstance()->GetScript(scriptName)->UpdateScript(_e);
			break;

		case E_SCRIPTTYPE::EXIT:
			LOG_INFO("Exit Script for " + scriptName + " ran!");
			ScriptManager<ScriptComponent>::GetInstance()->GetScript(scriptName)->EndScript(_e);
			break;

		default:
			LOG_WARN("Invalid script type passed in for " + scriptName + "!");
			break;
		}
		return;
	}

	/*
	// Script is C# script
	MonoManager::GetInstance()->RegisterMonoScript("BonVoyage", scriptName);
	if (MonoManager::GetInstance()->GetMonoComponent(scriptName) != nullptr) {
		switch (_type) {
		case E_SCRIPTTYPE::INIT:
			LOG_INFO("Start Script for " + scriptName + " ran!");
			MonoManager::GetInstance()->CallMethod(scriptName, "Init", 0);
			break;

		case E_SCRIPTTYPE::UPDATE:
			MonoManager::GetInstance()->CallMethod(scriptName, "Update", 0);
			break;

		case E_SCRIPTTYPE::EXIT:
			LOG_INFO("Exit Script for " + scriptName + " ran!");
			MonoManager::GetInstance()->CallMethod(scriptName, "Exit", 0);
			break;

		default:
			LOG_WARN("Invalid script type passed in for " + scriptName + "!");
			break;
		}
		return;
	}
	*/

	// Script doesnt exist
	LOG_ERROR("Script failed to attach or doesn't exist!");
}