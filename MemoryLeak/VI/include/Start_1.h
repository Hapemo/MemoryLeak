#pragma once
#include "pch.h"
#include "Scene.h"
#include "Input.h"

class Start_1 : public Scene, public Singleton<Start_1> {
public:
	virtual void Init();
	virtual void Update();
	virtual void Reset();
	virtual void Clear();

private:
	void PrintOrResetEntityLifespan(std::set<Entity> entities, KEY key);


};











