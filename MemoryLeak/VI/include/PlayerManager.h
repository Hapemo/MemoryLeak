#pragma once

#include "ECS_systems.h"


class PlayerManager : public System {
public:
	void InitPlayer(const Entity& _e);
	void Update();
	void RemovePlayer();
private:
	Entity mPlayer;
	bool mIsEnabled{ false };
	bool mTurnFlag{ true };
};