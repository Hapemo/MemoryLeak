#pragma once

#include "ECSManager.h"

class PlayerController : public System {
public:
	void Update(double dt);
private:
	bool mTurnFlag{ true };
};