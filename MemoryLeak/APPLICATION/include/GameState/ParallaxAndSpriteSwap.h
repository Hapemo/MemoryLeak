/*!*****************************************************************************
\file GameState3.h
\author Jazz Teoh Yu Jue
\par DP email: j.teoh\@digipen.edu
\par Group: Memory Leak Studios
\date 24-09-2022
\brief
Game state for testing parallex implementation
*******************************************************************************/
#pragma once
#include "GameState.h"
#include "ECSManager.h"
class ParallaxAndSpriteSwap : public GameState {
public:
	ParallaxAndSpriteSwap() = default;

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