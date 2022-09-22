#pragma once

#include "ECS_systems.h"


class PlayerManager : public System {
public:
	void InitPlayer(const Entity &_e);
	void Update();
	void RemovePlayer();
private:
	const Entity *player;
};