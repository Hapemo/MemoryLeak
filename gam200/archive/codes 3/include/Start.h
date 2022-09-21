#pragma once
#include <array>
#include "GameState.h"
#include "ECSManager.h"

class Start : public GameState {
public:
	//~Start() {};

	virtual void Load();
	virtual void Init();
	virtual void Update();
	virtual void Draw();
	virtual void Free();
	virtual void Unload();

private:
	std::array<Entity, 100> someEntities;
	std::set<Entity> entitiesA;
	std::set<Entity> entitiesB;
	std::set<Entity> entitiesC;
};


