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
//#include "MScriptComponent.h"
#include "ScriptManager.h"

LogicSystem::LogicSystem() {
	//monoComponent = new MScriptComponent;
	//LOG_DEBUG("Creating new MScriptComponent.");
}

LogicSystem::~LogicSystem() {
	//delete monoComponent;
	//LOG_DEBUG("Deleting new MScriptComponent.");
}

/*!*****************************************************************************
\brief
Run the initialisation function for all active entities' scripts.
*******************************************************************************/
void LogicSystem::Init() {
	LOG_DEBUG("LOGICSYSYEM INIT.");
	for (Entity const& e : mEntities) {
		if (e.ShouldRun()) {
			if (e.GetComponent<Script>().name != "") {
				if (ScriptManager<ScriptComponent>::GetInstance()->GetScript(e.GetComponent<Script>().name) != nullptr) {
					ScriptManager<ScriptComponent>::GetInstance()->GetScript(e.GetComponent<Script>().name)->StartScript(e);
					//if (monoComponent == nullptr) LOG_ERROR("Mono Script Component doesn't exist!"); else ((MScriptComponent*)monoComponent)->StartScript(e);
				}
				else LOG_ERROR("Start Script failed to attach!");
			}
			else LOG_ERROR("Component script name is empty!");
		}
	}
	//GameStateManager::GetReference()->mcurrentGameState->mScenes[]
}

/*!*****************************************************************************
\brief
Run the update function for all active entities' scripts.
*******************************************************************************/
void LogicSystem::Update() {
	//LOG_DEBUG("LOGICSYSYEM UPDATE.");
	for (Entity const& e : mEntities) {
		if (e.ShouldRun() && e.HasComponent<Script>()) {
			if (e.GetComponent<Script>().name != "") {
				if (ScriptManager<ScriptComponent>::GetInstance()->GetScript(e.GetComponent<Script>().name) != nullptr) {
					ScriptManager<ScriptComponent>::GetInstance()->GetScript(e.GetComponent<Script>().name)->UpdateScript(e);
					//if (monoComponent == nullptr) LOG_ERROR("Mono Script Component doesn't exist!"); else ((MScriptComponent*)monoComponent)->UpdateScript(e);
				}
				else LOG_ERROR("Update Script failed to attach!");
			}
			else LOG_ERROR("Component script name is empty!");
		}
	}
}

/*!*****************************************************************************
\brief
Run the exit function for all active entities' scripts.
*******************************************************************************/
void LogicSystem::Exit() {
	LOG_DEBUG("LOGICSYSYEM EXITING.");
	for (Entity const& e : mEntities) {
		if (e.ShouldRun() && e.HasComponent<Script>()) {
			if (e.GetComponent<Script>().name != "") {
				if (ScriptManager<ScriptComponent>::GetInstance()->GetScript(e.GetComponent<Script>().name) != nullptr) {
					ScriptManager<ScriptComponent>::GetInstance()->GetScript(e.GetComponent<Script>().name)->EndScript(e);
					//if (monoComponent == nullptr) LOG_ERROR("Mono Script Component doesn't exist!"); else ((MScriptComponent*)monoComponent)->EndScript(e);
				}
				else LOG_ERROR("Exit Script failed to attach!");
			}
			else LOG_ERROR("Component script name is empty!");
		}
	}
}

/*!*****************************************************************************
\brief
Run the initialisation function for all entities' scripts given by the parameter.
*******************************************************************************/
void LogicSystem::Init(std::set<Entity> const& _entities) {
	for (Entity const& e : _entities) {
		if (e.GetComponent<Script>().name != "") {
			if (ScriptManager<ScriptComponent>::GetInstance()->GetScript(e.GetComponent<Script>().name) != nullptr) {
				ScriptManager<ScriptComponent>::GetInstance()->GetScript(e.GetComponent<Script>().name)->StartScript(e);
				//if (monoComponent == nullptr) LOG_ERROR("Mono Script Component doesn't exist!"); else ((MScriptComponent*)monoComponent)->StartScript(e);
			}
			else LOG_ERROR("Init Script failed to attach!");
		}
		else LOG_ERROR("Component script name is empty!");
	}
}

/*!*****************************************************************************
\brief
Run the update function for all entities' scripts given by the parameter.
*******************************************************************************/
void LogicSystem::Update(std::set<Entity> const& _entities) {
	for (Entity const& e : _entities) {
		if (e.HasComponent<Script>()) {
			if (e.GetComponent<Script>().name != "") {
				if (ScriptManager<ScriptComponent>::GetInstance()->GetScript(e.GetComponent<Script>().name) != nullptr) {
					ScriptManager<ScriptComponent>::GetInstance()->GetScript(e.GetComponent<Script>().name)->UpdateScript(e);
					//if (monoComponent == nullptr) LOG_ERROR("Mono Script Component doesn't exist!"); else ((MScriptComponent*)monoComponent)->UpdateScript(e);
				}
				else LOG_ERROR("Update Script failed to attach!");
			}
			else LOG_ERROR("Component script name is empty!");
		}
	}
}

/*!*****************************************************************************
\brief
Run the exit function for all entities' scripts given by the parameter.
*******************************************************************************/
void LogicSystem::Exit(std::set<Entity> const& _entities) {
	for (Entity const& e : _entities) {
		if (e.HasComponent<Script>()) {
			if (e.GetComponent<Script>().name != "") {
				if (ScriptManager<ScriptComponent>::GetInstance()->GetScript(e.GetComponent<Script>().name) != nullptr) {
					ScriptManager<ScriptComponent>::GetInstance()->GetScript(e.GetComponent<Script>().name)->EndScript(e);
					//if (monoComponent == nullptr) LOG_ERROR("Mono Script Component doesn't exist!"); else ((MScriptComponent*)monoComponent)->EndScript(e);
				}
				else LOG_ERROR("Exit Script failed to attach!");
			}
			else LOG_ERROR("Component script name is empty!");
		}
	}
}
