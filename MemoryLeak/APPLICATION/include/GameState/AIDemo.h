/*!*****************************************************************************
\file AIDemo.h
\author Huang Wei Jhin
\par DP email: h.weijhin\@digipen.edu
\par Group: Memory Leak Studios
\date 24-09-2022
\brief
Game state for testing AI
*******************************************************************************/
#pragma once
#include "GameState.h"
#include "ECS_items.h"
#include "ECSManager.h"
class AIDemo : public GameState {
public:
	AIDemo() = default;

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
	//std::set<Entity> mEntities;
};
