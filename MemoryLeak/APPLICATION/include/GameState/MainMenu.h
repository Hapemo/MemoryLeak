/*!*****************************************************************************
\file MainMenu.h
\author Huang Wei Jhin
\par DP email: h.weijhin\@digipen.edu
\par Group: Memory Leak Studios
\date 05-11-2022
\brief
Game state for main menu
*******************************************************************************/
#pragma once
#include "GameState.h"
#include "ECS_items.h"
#include "ECSManager.h"
class MainMenu : public GameState {
public:
	MainMenu() = default;

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