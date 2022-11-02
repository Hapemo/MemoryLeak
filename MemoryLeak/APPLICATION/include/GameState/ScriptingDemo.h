/*!*****************************************************************************
\file ScriptingDemo.h
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 01-11-2022
\brief
Gamestate for testing scripting.
*******************************************************************************/

#pragma once
#include "GameState.h"
#include "ECSManager.h"
#include "Application.h"
#include "Input.h"

class ScriptingDemo : public GameState {
public:
	ScriptingDemo() = default;

	//------------------------------------------------------------------------------
	// Virtual Functions from GameState. Refer to GameState for details
	//------------------------------------------------------------------------------
	virtual void Load();
	virtual void Init();
	virtual void Update();
	virtual void Draw();
	virtual void Free();
	virtual void Unload();
private:
	Prefab pref;
};
