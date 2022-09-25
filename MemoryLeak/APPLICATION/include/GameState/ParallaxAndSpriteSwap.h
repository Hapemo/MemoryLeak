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
	std::set<Entity> mEntities;
};