#include "PlayerManager.h"

#include "ECSManager.h"
#include "Input.h"

const double PLAYER_ROT_SPEED{ 15.0 / 180.0 * glm::pi<double>() },
			 PLAYER_CHG_SPEED{ 5.0 };

static bool turnFlag{ true };

void PlayerManager::InitPlayer(const Entity &e) {
	PlayerManager::player = &e;
	if (!(physics2DManager->HasPhysicsComponent(e)))
		physics2DManager->AddPhysicsComponent(e);
}

void PlayerManager::Update() {
	if (Input::CheckKey(STATE::PRESS, KEY::A) && turnFlag) {
		transformManager->SetRotation(*(PlayerManager::player), 
									  static_cast<float>(static_cast<double>(transformManager->GetRotation(*(PlayerManager::player))) + PLAYER_ROT_SPEED * Helper::dt));
		physics2DManager->SetMoveDirection(*(PlayerManager::player), transformManager->GetRotation(*(PlayerManager::player)));
		turnFlag = !turnFlag;
	}
	if (Input::CheckKey(STATE::PRESS, KEY::D) && turnFlag) {
		transformManager->SetRotation(*(PlayerManager::player), 
									  static_cast<float>(static_cast<double>(transformManager->GetRotation(*(PlayerManager::player))) - PLAYER_ROT_SPEED * Helper::dt));
		physics2DManager->SetMoveDirection(*(PlayerManager::player), transformManager->GetRotation(*(PlayerManager::player)));
		turnFlag = !turnFlag;
	}

	if (Input::CheckKey(STATE::RELEASE, KEY::A) && !turnFlag)
		turnFlag = !turnFlag;

	if (Input::CheckKey(STATE::RELEASE, KEY::D) && !turnFlag)
		turnFlag = !turnFlag;

	//if (Input::CheckKey(STATE::PRESS, KEY::W))	
	//	physics2DManager->SetMoveDirection(*(PlayerManager::player), transformManager->GetRotation(*(PlayerManager::player)));
	//if (Input::CheckKey(STATE::PRESS, KEY::S))
	//	physics2DManager->SetMoveDirection(*(PlayerManager::player), 
	//									   static_cast<float>(static_cast<double>(transformManager->GetRotation(*(PlayerManager::player))) + glm::pi<double>()));
	if (Input::CheckKey(STATE::PRESS, KEY::W))
		physics2DManager->SetSpeed(*(PlayerManager::player), 
								   static_cast<float>(static_cast<double>(physics2DManager->GetSpeed(*(PlayerManager::player))) + PLAYER_CHG_SPEED * Helper::dt));
	if (Input::CheckKey(STATE::PRESS, KEY::S))
		physics2DManager->SetSpeed(*(PlayerManager::player),
								   static_cast<float>(static_cast<double>(physics2DManager->GetSpeed(*(PlayerManager::player))) - PLAYER_CHG_SPEED * Helper::dt));
}

void PlayerManager::RemovePlayer() {
	PlayerManager::player == nullptr;
}