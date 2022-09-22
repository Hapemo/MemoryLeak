#pragma once
#include "ECS_items.h"
#include "pch.h"
#include "ECSManager.h"

class Scene {
public:
	void Pause(bool pause);
	void PrimaryUpdate();
	//void Load();
	//void Save();

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Reset() = 0;
	virtual void Clear() = 0;

protected:
	std::set<Entity> mEntities;

private:
	bool pause;
};




