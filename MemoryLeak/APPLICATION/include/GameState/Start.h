/*!*****************************************************************************
\file Start.h
\author Jazz Teoh Yu Jue
\par DP email: j.teoh\@digipen.edu
\par Group: Memory Leak Studios
\date 24-09-2022
\brief
First game state ever, going to be deprecated
*******************************************************************************/
#pragma once
#include "pch.h"
#include "GameState.h"
#include "ECSManager.h"
#include "Scene.h"

class Start : public GameState {
public:
	Start() = default;
	//~Start() {};

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


