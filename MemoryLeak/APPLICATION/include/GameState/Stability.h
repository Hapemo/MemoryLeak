/*!*****************************************************************************
\file Stability.h
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 02-11-2022
\brief
\brief
Game state for testing 2500 objects stability.

*******************************************************************************/
#pragma once
#include "GameState.h"
#include "ECS_items.h"
#include "ECSManager.h"

class Stability : public GameState {
public:
	Stability() = default;

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

};
