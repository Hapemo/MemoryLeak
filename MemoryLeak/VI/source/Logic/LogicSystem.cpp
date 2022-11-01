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

/*!*****************************************************************************
\brief
Run the initialisation function for all active entities' scripts.
*******************************************************************************/
void LogicSystem::Init() {
	LOG_DEBUG("LOGICSYSYEM INIT.");
	for (Entity const& e : mEntities) {
		if (e.ShouldRun()) {
			LOG_DEBUG("hasScript.");
			e.GetComponent<Script>().script->StartScript(e);
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
			Script& script = e.GetComponent<Script>();
			script.script->UpdateScript(e);
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
			e.GetComponent<Script>().script->EndScript(e);
		}
	}
}
