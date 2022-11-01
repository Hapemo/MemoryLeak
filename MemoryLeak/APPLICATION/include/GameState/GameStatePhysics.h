/*!*****************************************************************************
\file GameStatePhysics.h
\author Jazz Teoh Yu Jue
\par DP email: j.teoh\@digipen.edu
\par Group: Memory Leak Studios
\date 01-11-2022
\brief
Game state for testing physics
*******************************************************************************/
#pragma once
#include "GameState.h"
#include "ECS_items.h"
#include "ECSManager.h"
class GameStatePhysics : public GameState {
public:
	GameStatePhysics() = default;

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