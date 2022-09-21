#pragma once
#include "GameState.h"

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

};


