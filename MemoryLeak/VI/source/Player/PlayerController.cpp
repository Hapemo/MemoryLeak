#include "ECSManager.h"

#include "Input.h"

const double playerRotationSpeed{ 30.0 / 180.0 * Math::PI },
			 playerSpeedChange{ 80.0 },
			 playerSpeedNaturalLossScalar{ 0.97 };

void PlayerController::Update(double _dt) {
	for (const Entity& e : mEntities) {
		// Rotational turn
		if (Input::CheckKey(STATE::PRESS, KEY::A) || Input::CheckKey(STATE::HOLD, KEY::A)) {
			e.GetComponent<Physics2D>().moveDirection += static_cast<double>(playerRotationSpeed) * _dt;
		}
		if (Input::CheckKey(STATE::PRESS, KEY::D) || Input::CheckKey(STATE::HOLD, KEY::D)) {
			e.GetComponent<Physics2D>().moveDirection -= static_cast<double>(playerRotationSpeed) * _dt;
		}

		// Movement forward or backward
		if (Input::CheckKey(STATE::PRESS, KEY::W) || Input::CheckKey(STATE::HOLD, KEY::W)) {
			e.GetComponent<Physics2D>().speed += static_cast<float>(playerSpeedChange * _dt);
		}
		if (Input::CheckKey(STATE::PRESS, KEY::S) || Input::CheckKey(STATE::HOLD, KEY::S)) {
			e.GetComponent<Physics2D>().speed -= static_cast<float>(playerSpeedChange * _dt);
		}
		
		// No movement input, scale down the speed to slow it down
		e.GetComponent<Physics2D>().speed *= playerSpeedNaturalLossScalar;
	}
}