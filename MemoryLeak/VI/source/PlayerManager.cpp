#include "PlayerManager.h"

#include "ECSManager.h"
#include "Input.h"

const double playerRotationSpeed{ 15.0 / 180.0 * glm::pi<double>() },
playerSpeedChange{ 5.0 };

void PlayerManager::InitPlayer(const Entity& e) {
	PlayerManager::mPlayer = e;
	PlayerManager::mIsEnabled = true;
}

void PlayerManager::Update() {
	if (!PlayerManager::mIsEnabled)
		return;

	//if (Input::CheckKey(STATE::PRESS, KEY::A) && turnFlag) {
	//	transformManager->SetRotation(*(PlayerManager::player), 
	//								  static_cast<float>(static_cast<double>(transformManager->GetRotation(*(PlayerManager::player))) + PLAYER_ROT_SPEED * Helper::dt));
	//	physics2DManager->SetMoveDirection(*(PlayerManager::player), transformManager->GetRotation(*(PlayerManager::player)));
	//	turnFlag = !turnFlag;
	//}
	//if (Input::CheckKey(STATE::PRESS, KEY::D) && turnFlag) {
	//	transformManager->SetRotation(*(PlayerManager::player), 
	//								  static_cast<float>(static_cast<double>(transformManager->GetRotation(*(PlayerManager::player))) - PLAYER_ROT_SPEED * Helper::dt));
	//	physics2DManager->SetMoveDirection(*(PlayerManager::player), transformManager->GetRotation(*(PlayerManager::player)));
	//	turnFlag = !turnFlag;
	//}

	//if (Input::CheckKey(STATE::RELEASE, KEY::A) && !turnFlag)
	//	turnFlag = !turnFlag;

	//if (Input::CheckKey(STATE::RELEASE, KEY::D) && !turnFlag)
	//	turnFlag = !turnFlag;

	//if (Input::CheckKey(STATE::PRESS, KEY::W))
	//	physics2DManager->SetSpeed(*(PlayerManager::player), 
	//							   static_cast<float>(static_cast<double>(physics2DManager->GetSpeed(*(PlayerManager::player))) + PLAYER_CHG_SPEED * Helper::dt));
	//if (Input::CheckKey(STATE::PRESS, KEY::S))
	//	physics2DManager->SetSpeed(*(PlayerManager::player),
	//							   static_cast<float>(static_cast<double>(physics2DManager->GetSpeed(*(PlayerManager::player))) - PLAYER_CHG_SPEED * Helper::dt));
	if (Input::CheckKey(STATE::PRESS, KEY::W))
		PlayerManager::mPlayer.GetComponent<Physics2D>();//.speed;// += static_cast<double>(PLAYER_CHG_SPEED) * Helper::dt;
	if (Input::CheckKey(STATE::PRESS, KEY::S))
		PlayerManager::mPlayer.GetComponent<Physics2D>();// .speed;// -= static_cast<double>(PLAYER_CHG_SPEED) * Helper::dt;
}

void PlayerManager::RemovePlayer() {
	PlayerManager::mIsEnabled = false;
}