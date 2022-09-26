#pragma once

#include "ECSManager.h"

class PlayerController : public System {
public:
	void RegisterPlayer(const Entity& _e);
	void Update(double dt);
	void RemovePlayer();
private:
	Entity mPlayer;
	bool mIsEnabled{ false };
	bool mTurnFlag{ true };
};