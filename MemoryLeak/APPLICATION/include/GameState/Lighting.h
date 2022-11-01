#pragma once

#include "GameState.h"
#include "ECS_items.h"
#include "ECSManager.h"
class Lighting : public GameState {
public:
	Lighting() = default;

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
