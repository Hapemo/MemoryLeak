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

#include "Logic/LogicSystem.h"
#include "Logic/ScriptManager.h"

LogicSystem::LogicSystem() {
}

LogicSystem::~LogicSystem() {
	//for (size_t index = 0; index < m_behaviours.size(); ++index)
		//delete m_behaviours[index];
	// for (auto& ptr : m_behaviours)
		// delete ptr;
	/*
	std::map<std::string, ScriptManager*>::iterator it;
	for (it = mBehaviours.begin(); it != mBehaviours.end(); ++it)
		delete it->second;
	*/
}

void LogicSystem::Init() {
	std::map<std::string, ScriptComponent*>::iterator it;
	for (it = mBehaviourComponents.begin(); it != mBehaviourComponents.end(); ++it)
		mBehaviours[it->second->GetBehaviourKey()]->GetInit()(it->second->GetOwner());
}

bool LogicSystem::Update() {
	std::map<std::string, ScriptComponent*>::iterator it;
	for (it = mBehaviourComponents.begin(); it != mBehaviourComponents.end(); ++it)
		mBehaviours[it->second->GetBehaviourKey()]->GetUpdate()(it->second->GetOwner());
	//for (auto& iter : m_behaviourComponents)
		//m_behaviours[iter->GetBehaviourIndex()]->m_UpdateBehaviour(iter->GetOwner());
	return true;
}

void LogicSystem::Exit() {
	std::map<std::string, ScriptComponent*>::iterator it;
	for (it = mBehaviourComponents.begin(); it != mBehaviourComponents.end(); ++it)
		mBehaviours[it->second->GetBehaviourKey()]->GetExit()(it->second->GetOwner());
}

void LogicSystem::AddBehaviour(std::string _key, ScriptManager* _behaviour) {
	mBehaviours[_key] = _behaviour;
}
