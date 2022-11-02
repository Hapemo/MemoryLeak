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
#include "ScriptManager.h"

/*!*****************************************************************************
\brief
Run the initialisation function for all active entities' scripts.
*******************************************************************************/
void LogicSystem::Init() {
	ScriptManager<ScriptComponent>::GetInstance()->PrintRegisteredScripts();
	for (Entity const& e : mEntities) {
		e.GetComponent<Script>().script = ScriptManager<ScriptComponent>::GetInstance()->GetScript(e.GetComponent<Script>().name);
		LOG_WARN(e.GetComponent<Script>().name.c_str());
	}

	LOG_DEBUG("LOGICSYSYEM INIT.");
	for (Entity const& e : mEntities) {
		if (e.ShouldRun()) {
			if (e.GetComponent<Script>().script != nullptr)
				e.GetComponent<Script>().script->StartScript(e);
			else
				LOG_ERROR("start: Script failed to attach!!!");
		}
	}
}

/*!*****************************************************************************
\brief
Run the update function for all active entities' scripts.
*******************************************************************************/
void LogicSystem::Update() {
	//LOG_DEBUG("LOGICSYSYEM UPDATE.");
	for (Entity const& e : mEntities) {
		if (e.ShouldRun() && e.HasComponent<Script>()) {
			if (e.GetComponent<Script>().script != nullptr)
				e.GetComponent<Script>().script->UpdateScript(e);
			else
				LOG_ERROR("Update: Script failed to attach!!!");
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
			if (e.GetComponent<Script>().script != nullptr)
				e.GetComponent<Script>().script->EndScript(e);
			else
				LOG_ERROR("End: Script failed to attach!!!");
		}
	}
}
