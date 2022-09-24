#pragma once
#include "GameState.h"
#include "ECSManager.h"

class GameState1 : public GameState {
public:
	GameState1() = default;
	//~Start() {};

	virtual void Load();
	virtual void Init();
	virtual void Update();
	virtual void Draw();
	virtual void Free();
	virtual void Unload();
private:
	std::set<Entity> mEntities;
};
