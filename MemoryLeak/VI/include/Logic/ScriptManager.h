/*!*****************************************************************************
\file ScriptManager.h
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 19-10-2022
\brief
This file contains the function declarations of the class ScriptManager.
The ScriptManager class handles the C# scripting for the engine.
*******************************************************************************/

#pragma once

#include "ECS_items.h"
#include <string>
#include <vector>

typedef void(*InitBehaviour)(Entity*);
typedef void(*UpdateBehaviour)(Entity*);
typedef void(*ExitBehaviour)(Entity*);

// allows making bahaviour objects
class ScriptManager
{
public:
	/*!*****************************************************************************
	\brief
	Constructor.
	*******************************************************************************/
	ScriptManager(const std::string _key, const InitBehaviour& _init, const UpdateBehaviour& _update, const ExitBehaviour& _exit);

	/*!*****************************************************************************
	\brief
	Delete copy constructor.
	*******************************************************************************/
	ScriptManager(const ScriptManager&) = delete;
	const ScriptManager& operator=(const ScriptManager&) = delete;

	InitBehaviour GetInit() { return mInitBahaviour; }
	UpdateBehaviour GetUpdate() { return mUpdateBehaviour; }
	ExitBehaviour GetExit() { return mExitBehaviour; }

private:
	// 3 global function pointers that define a script (on the game code side)
	// this is a containment method, trying to avoid inheritance and vtables.
	// Versus, making these 3 functions as virtual=0 and forcing users to derive
	// from this class to make custom scripts, on the game code side
	InitBehaviour mInitBahaviour;
	UpdateBehaviour mUpdateBehaviour;
	ExitBehaviour mExitBehaviour;
};
