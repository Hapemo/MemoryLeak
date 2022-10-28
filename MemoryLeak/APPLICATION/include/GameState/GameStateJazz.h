/*!*****************************************************************************
\file GameStateJazz.h
\author Jazz Teoh Yu Jue
\par DP email: j.teoh\@digipen.edu
\par Group: Memory Leak Studios
\date 25-10-2022
\brief
Game state for testing jazz's stuff
*******************************************************************************/
#pragma once
#include "GameState.h"
#include "ECSManager.h"
class GameStateJazz : public GameState {
public:
	GameStateJazz() = default;

	//------------------------------------------------------------------------------
	// Virtual Functions from GameState. Refer to GameState for details
	//------------------------------------------------------------------------------
	virtual void Load();
	virtual void Init();
	virtual void Update();
	virtual void Draw();
	virtual void Free();
	virtual void Unload();
};
