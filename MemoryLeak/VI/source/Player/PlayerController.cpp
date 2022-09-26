#include "ECSManager.h"

#include "Input.h"

const double playerRotationSpeed{ 15.0 / 180.0 * glm::pi<double>() },
playerSpeedChange{ 5.0 };

void PlayerController::RegisterPlayer(const Entity& e) {
	PlayerController::mPlayer = e;
	PlayerController::mIsEnabled = true;
}

void PlayerController::Update(double dt) {
	if (!PlayerController::mIsEnabled)
		return;

	//if (Input::CheckKey(STATE::PRESS, KEY::A) && turnFlag) {
	//	transformManager->SetRotation(*(PlayerController::player), 
	//								  static_cast<float>(static_cast<double>(transformManager->GetRotation(*(PlayerController::player))) + PLAYER_ROT_SPEED * Helper::dt));
	//	physics2DManager->SetMoveDirection(*(PlayerController::player), transformManager->GetRotation(*(PlayerController::player)));
	//	turnFlag = !turnFlag;
	//}
	//if (Input::CheckKey(STATE::PRESS, KEY::D) && turnFlag) {
	//	transformManager->SetRotation(*(PlayerController::player), 
	//								  static_cast<float>(static_cast<double>(transformManager->GetRotation(*(PlayerController::player))) - PLAYER_ROT_SPEED * Helper::dt));
	//	physics2DManager->SetMoveDirection(*(PlayerController::player), transformManager->GetRotation(*(PlayerController::player)));
	//	turnFlag = !turnFlag;
	//}

	//if (Input::CheckKey(STATE::RELEASE, KEY::A) && !turnFlag)
	//	turnFlag = !turnFlag;

	//if (Input::CheckKey(STATE::RELEASE, KEY::D) && !turnFlag)
	//	turnFlag = !turnFlag;

	if (Input::CheckKey(STATE::PRESS, KEY::W)) {
		PlayerController::mPlayer.GetComponent<Physics2D>().speed += static_cast<float>(playerSpeedChange * dt);
	}
	if (Input::CheckKey(STATE::PRESS, KEY::S)) {
		PlayerController::mPlayer.GetComponent<Physics2D>().speed -= static_cast<float>(playerSpeedChange * dt);
	}
}

void PlayerController::RemovePlayer() {
	PlayerController::mIsEnabled = false;
}