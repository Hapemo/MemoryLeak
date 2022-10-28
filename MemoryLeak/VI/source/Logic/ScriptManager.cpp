/*!*****************************************************************************
\file ScriptManager.cpp
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 19-10-2022
\brief
This file contains the function definitions of the class ScriptManager.
The ScriptManager class handles the C# scripting for the engine.
*******************************************************************************/

#include "ScriptManager.h"
#include "LogicSystem.h"

ScriptManager::ScriptManager(const std::string _key, const InitBehaviour& _init, const UpdateBehaviour& _update, const ExitBehaviour& _exit) :
	mInitBahaviour(_init),
	mUpdateBehaviour(_update),
	mExitBehaviour(_exit) {
	// attaching this to the LogicSystem
	LogicSystem::GetInstance()->AddBehaviour(_key, this); // MyLogicSystem can be unique instance of "LogicSystem"
}