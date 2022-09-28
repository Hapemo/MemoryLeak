/*!*****************************************************************************
\file	PlayerController.cpp
\author Lee Hsien Wei, Joachim
\par	DP email: l.hsienweijoachim@digipen.edu
\par	Course: GAM200
\par	Group: Memory Leak Studios
\date	27-09-2022
\brief  This file contains the definition of the Player Controller and its
		member functions which handles movement inpupt control of the player.
		It also defines certain constants used by the controller
*******************************************************************************/

// -----------------------------
// Include files
// -----------------------------
#include "ECSManager.h"
#include "Input.h"

// -----------------------------
// Constant values
// -----------------------------
const double playerRotationSpeed{ 40.0 / 180.0 * Math::PI },	// Player rotation speed in radians
			 playerSpeedChange{ 20.0 },							// Player speed change
			 playerSpeedNaturalLossScalar{ 0.98 },				// Player speed decceleration scalar
		     playerSpeedCap {100.f};							// Player speed cap

/*!*****************************************************************************
\brief
Update function that checks for keyboard input to modify physics components values
to move player entities

\param void
NULL

\return void
NULL
*******************************************************************************/
void PlayerController::Update() {
	// Loop through entity container
	for (const Entity& e : mEntities) {
	// -----------------------------
	// Movement input first draft (Direction based movement)
	// -----------------------------
		//// Rotational turn
		//if (Input::CheckKey(STATE::PRESS, KEY::A) || Input::CheckKey(STATE::HOLD, KEY::A))
		//	e.GetComponent<Physics2D>().moveDirection += static_cast<double>(playerRotationSpeed) * _dt;
		//if (Input::CheckKey(STATE::PRESS, KEY::D) || Input::CheckKey(STATE::HOLD, KEY::D))
		//	e.GetComponent<Physics2D>().moveDirection -= static_cast<double>(playerRotationSpeed) * _dt;

		//// Movement forward or backward
		//if (Input::CheckKey(STATE::PRESS, KEY::W) || Input::CheckKey(STATE::HOLD, KEY::W))
		//	e.GetComponent<Physics2D>().speed += static_cast<float>(playerSpeedChange * _dt);
		//if (Input::CheckKey(STATE::PRESS, KEY::S) || Input::CheckKey(STATE::HOLD, KEY::S))
		//	e.GetComponent<Physics2D>().speed -= static_cast<float>(playerSpeedChange * _dt);

	// -----------------------------
	// Movement input second draft (key movement)
	// -----------------------------
		if (Input::CheckKey(STATE::PRESS, KEY::W) || Input::CheckKey(STATE::HOLD, KEY::W)) {
			e.GetComponent<Physics2D>().moveDirection = static_cast<float>(Math::PI / 2.0);
			e.GetComponent<Physics2D>().speed += static_cast<float>(playerSpeedChange);
		}
		if (Input::CheckKey(STATE::PRESS, KEY::S) || Input::CheckKey(STATE::HOLD, KEY::S)) {
			e.GetComponent<Physics2D>().moveDirection = static_cast<float>(-Math::PI / 2.0);
			e.GetComponent<Physics2D>().speed += static_cast<float>(playerSpeedChange);
		}
		if (Input::CheckKey(STATE::PRESS, KEY::A) || Input::CheckKey(STATE::HOLD, KEY::A)) {
			e.GetComponent<Physics2D>().moveDirection = static_cast<float>(Math::PI);
			e.GetComponent<Physics2D>().speed += static_cast<float>(playerSpeedChange);
		}
		if (Input::CheckKey(STATE::PRESS, KEY::D) || Input::CheckKey(STATE::HOLD, KEY::D)) {
			e.GetComponent<Physics2D>().moveDirection = 0.f;
			e.GetComponent<Physics2D>().speed += static_cast<float>(playerSpeedChange);
		}

		// Cap player speed
		if (e.GetComponent<Physics2D>().speed > playerSpeedCap)
			e.GetComponent<Physics2D>().speed = playerSpeedCap;

		// No movement input, scale down the speed to slow it down
		e.GetComponent<Physics2D>().speed *= static_cast<float>(playerSpeedNaturalLossScalar);
	}
}