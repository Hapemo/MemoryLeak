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
std::vector<bool> PlayerController::check{ true, true, true,true };
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
		if (!e.HasComponent<Physics2D>())
			continue;

		if (e.GetComponent<General>().tag != TAG::PLAYER)
			continue;
		
		// Hack so that debug render is correct
		if (FirstUpdate) {
			physics2DManager->ApplyImpulse(e, Math::Vec2{ 0.f, 1.f }, Math::Vec2{ 0.f, 0.f });
		}

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

	// --------------------------------------------
	// Response hack for player (done by Wei Jhin)
	// --------------------------------------------
		// cout debugs by Wei Jhin
		//if (!check[0])
		//	std::cout << "wwwwwwwwwwwwwwwwwwwww\n";
		//if (!check[1])
		//	std::cout << "sssssssssssssssssssssssssss\n";
		//if (!check[2])
		//	std::cout << "aaaaaaaaaaaaaaaaaaaaaaaaaaaa\n";
		//if (!check[3])
		//	std::cout << "ddddddddddddddddddddddddddddddn";
	
	// -----------------------------
	// Movement input second draft (key movement)
	// -----------------------------
	// Contains response hack for player (done by Wei Jhin)

		// Up movement
		if ((Input::CheckKey(E_STATE::PRESS, E_KEY::W) || Input::CheckKey(E_STATE::HOLD, E_KEY::W))&&check[0]) {
			physics2DManager->ApplyImpulse(e, Math::Vec2{ 0.f, 1.f } * static_cast<float>(playerSpeed), Math::Vec2{ 0.f, 0.f });
		}
		
		// Down movement
		if ((Input::CheckKey(E_STATE::PRESS, E_KEY::S) || Input::CheckKey(E_STATE::HOLD, E_KEY::S)) && check[1]) {
			physics2DManager->ApplyImpulse(e, Math::Vec2{ 0.f, -1.f } *static_cast<float>(playerSpeed), Math::Vec2{ 0.f, 0.f });
		}

		// Left movement
		if ((Input::CheckKey(E_STATE::PRESS, E_KEY::A) || Input::CheckKey(E_STATE::HOLD, E_KEY::A)) && check[2]) {
			physics2DManager->ApplyImpulse(e, Math::Vec2{ -1.f, 0.f } *static_cast<float>(playerSpeed), Math::Vec2{ 0.f, 0.f });
		}

		// Right movement
		if ((Input::CheckKey(E_STATE::PRESS, E_KEY::D) || Input::CheckKey(E_STATE::HOLD, E_KEY::D)) && check[3]) {
			physics2DManager->ApplyImpulse(e, Math::Vec2{ 1.f, 0.f } *static_cast<float>(playerSpeed), Math::Vec2{ 0.f, 0.f });
		}

		// Cap player speed
		if (Math::Dot(physics2DManager->GetVelocity(e), physics2DManager->GetVelocity(e)) > playerSpeedCap * playerSpeedCap) {
			physics2DManager->SetVelocity(e, physics2DManager->GetVelocity(e).Normalize() * static_cast<float>(playerSpeedCap));
		}

		// No movement input, scale down the speed to slow it down
		physics2DManager->ScaleVelocity(e, static_cast<float>(playerSpeedNaturalLossScalar));
	}

	// Hack so that debug render is correct
	if (FirstUpdate)
		FirstUpdate = false;
	
}