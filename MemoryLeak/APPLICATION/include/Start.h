#pragma once
#include "pch.h"
#include "GameState.h"
#include "ECSManager.h"
#include "Scene.h"

class Start : public GameState {
public:
	Start() = default;
	//~Start() {};

	virtual void Load();
	virtual void Init();
	virtual void Update();
	virtual void Draw();
	virtual void Free();
	virtual void Unload();

private:
};


