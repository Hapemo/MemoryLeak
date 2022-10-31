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
const double playerSpeed{30.f},
			 playerSpeedNaturalLossScalar{ 0.99 },				// Player speed decceleration scalar
		     playerSpeedCap {300.f};							// Player speed cap

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
		if (!e.HasComponent<PlayerTmp>() || !e.HasComponent<Physics2D>())
			continue;

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
		// Up movement
		if (Input::CheckKey(E_STATE::PRESS, E_KEY::I) || Input::CheckKey(E_STATE::HOLD, E_KEY::I)) {
			physics2DManager->ApplyImpulse(e, Math::Vec2{ 0.f, 1.f } * static_cast<float>(playerSpeed), Math::Vec2{ 0.f, 0.f });
		}
		
		// Down movement
		if (Input::CheckKey(E_STATE::PRESS, E_KEY::K) || Input::CheckKey(E_STATE::HOLD, E_KEY::K)) {
			physics2DManager->ApplyImpulse(e, Math::Vec2{ 0.f, -1.f } *static_cast<float>(playerSpeed), Math::Vec2{ 0.f, 0.f });
		}

		// Left movement
		if (Input::CheckKey(E_STATE::PRESS, E_KEY::J) || Input::CheckKey(E_STATE::HOLD, E_KEY::J)) {
			physics2DManager->ApplyImpulse(e, Math::Vec2{ -1.f, 0.f } *static_cast<float>(playerSpeed), Math::Vec2{ 0.f, 0.f });
		}

		// Right movement
		if (Input::CheckKey(E_STATE::PRESS, E_KEY::L) || Input::CheckKey(E_STATE::HOLD, E_KEY::L)) {
			physics2DManager->ApplyImpulse(e, Math::Vec2{ 1.f, 0.f } *static_cast<float>(playerSpeed), Math::Vec2{ 0.f, 0.f });
		}

		// Cap player speed
		if (Math::Dot(physics2DManager->GetVelocity(e), physics2DManager->GetVelocity(e)) > playerSpeedCap * playerSpeedCap) {
			physics2DManager->SetVelocity(e, physics2DManager->GetVelocity(e).Normalize() * playerSpeedCap);
		}

		// No movement input, scale down the speed to slow it down
		physics2DManager->ScaleVelocity(e, static_cast<float>(playerSpeedNaturalLossScalar));
	}
}