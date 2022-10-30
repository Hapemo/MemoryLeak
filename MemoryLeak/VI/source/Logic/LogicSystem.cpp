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

#include "ECS_tools.h"
#include "Logic/LogicSystem.h"
#include "Logic/ScriptManager.h"

LogicSystem::LogicSystem() {
}

LogicSystem::~LogicSystem() {
}

void LogicSystem::Init() {
	LOG_DEBUG("LOGICSYSYEM INIT.");
	std::set<Entity>::iterator it;
	for (it = mEntities.begin(); it != mEntities.end(); ++it) {
		if ((*it).GetComponent<General>().isActive && !(*it).GetComponent<General>().isPaused) {
			if ((*it).HasComponent<Script>()) {
				LOG_DEBUG("hasScript.");
				(*it).GetComponent<Script>().script->StartScript(const_cast<Entity*>(&(*it)));
			}
		}
	}
}

void LogicSystem::Update() {
	LOG_DEBUG("LOGICSYSYEM UPDATE.");
	std::set<Entity>::iterator it;
	for (it = mEntities.begin(); it != mEntities.end(); ++it) {
		if ((*it).GetComponent<General>().isActive && !(*it).GetComponent<General>().isPaused) {
			if ((*it).HasComponent<Script>()) {
				(*it).GetComponent<Script>().script->UpdateScript(const_cast<Entity*>(&(*it)));
			}
		}
	}
}

void LogicSystem::Exit() {
	LOG_DEBUG("LOGICSYSYEM EXITING.");
	std::set<Entity>::iterator it;
	for (it = mEntities.begin(); it != mEntities.end(); ++it) {
		if ((*it).GetComponent<General>().isActive && !(*it).GetComponent<General>().isPaused) {
			if ((*it).HasComponent<Script>()) {
				(*it).GetComponent<Script>().script->EndScript(const_cast<Entity*>(&(*it)));
			}
		}
	}
}
