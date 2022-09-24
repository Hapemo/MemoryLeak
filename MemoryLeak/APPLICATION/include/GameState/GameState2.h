#pragma once
#include "GameState.h"

class GameState2 : public GameState {
public:
	GameState2() = default;
	//~Start() {};

	virtual void Load();
	virtual void Init();
	virtual void Update();
	virtual void Draw();
	virtual void Free();
	virtual void Unload();
private:

};
