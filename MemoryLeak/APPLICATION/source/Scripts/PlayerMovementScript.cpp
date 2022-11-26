#include "PlayerMovementScript.h"

REGISTER_SCRIPT(ScriptComponent, PlayerMovementScript);

namespace {
	static bool speedCheat{ false };
}

void PlayerMovementScript::StartScript(const Entity& _e) {
	(void)_e;
	inited = false;
}

void PlayerMovementScript::UpdateScript(const Entity& _e) {
	if (!inited) {
		littleGirl = FUNC->GetEntity("ActivateLittleGirlScript", "Level1");
		dialogueText = FUNC->GetEntity("DialogueText", "Level1");
		water = FUNC->GetEntity("Water", "Level1");
		currScene = &(FUNC->SelectScene("Level1"));
		initialCamScale = currScene->mCamera.scale;
		inited = true;
	}
	if (dialogueActivated ==false)
		if (currScene->mCamera.scale.x < initialCamScale.x)
			currScene->mCamera.scale.x += 500 * (float)FUNC->GetDeltaTime();
	_e.GetComponent<Transform>().scale.x = std::abs(_e.GetComponent<Transform>().scale.x);
	if (Input::CheckKey(HOLD, LEFT_CONTROL) && Input::CheckKey(PRESS, C)) speedCheat = !speedCheat; // speed cheat toggle

	if (FUNC->CheckKey(E_STATE::HOLD, M_BUTTON_L)) {
		if ((dialogueText.HasComponent<General>() && dialogueText.GetComponent<General>().isActive == false)/*|| _e.GetComponent<General>().name != "Boat"*/) {
			Math::Vec2 dirVector{ FUNC->GetWorldMousePos() + currScene->mCamera.translation - _e.GetComponent<Transform>().translation };
			if (dirVector.SqMagnitude() > FLT_EPSILON * FLT_EPSILON)
				FUNC->ApplyImpulse(_e, (dirVector.Normalized() * playerSpeed * (speedCheat ? speedCheatMultiplier : 1)) * (float)FUNC->GetDeltaTime(), Math::Vec2{ 0.f, 0.f });

			float pi = (float) Math::PI;
			float rotation{};
			if (dirVector.y != 0.f && dirVector.x >= 0.f)
				rotation = atan2f(dirVector.y, dirVector.x);
			else if (dirVector.y == 0.f && dirVector.x > 0.f)
				rotation = (float)Math::PI / 2.f;
			else if (dirVector.y != 0.f && dirVector.x < 0.f) {
				rotation = atan2f(dirVector.y, dirVector.x);
				rotation += rotation < 0.f ? pi * 2.f : 0.f;
			} else rotation = 3.f * pi / 2.f;

			if ((rotation > 15.f * pi / 8.f && rotation <= 2.f * pi) || (rotation > 0.f && rotation <= pi / 8.f))
				spriteManager->SetTexture(_e, "Textures\\Spritesheets\\BOAT\\Props_Boat_E_Spritesheet.png");
			else if (rotation > pi / 8.f && rotation <= 3.f * pi / 8.f)
				spriteManager->SetTexture(_e, "Textures\\Spritesheets\\BOAT\\Props_Boat_NE_spritesheet.png");
			else if (rotation > 3.f * pi / 8.f && rotation <= 5.f * pi / 8.f)
				spriteManager->SetTexture(_e, "Textures\\Spritesheets\\BOAT\\Props_Boat_N_Spritesheet.png");
			else if (rotation > 5.f * pi / 8.f && rotation <= 7.f * pi / 8.f)
				spriteManager->SetTexture(_e, "Textures\\Spritesheets\\BOAT\\Props_Boat_NW_Spritesheet.png");
			else if (rotation > 7.f * pi / 8.f && rotation <= 9.f * pi / 8.f)
				spriteManager->SetTexture(_e, "Textures\\Spritesheets\\BOAT\\Props_Boat_W_Spritesheet.png");
			else if (rotation > 9.f * pi / 8.f && rotation <= 11.f * pi / 8.f)
				spriteManager->SetTexture(_e, "Textures\\Spritesheets\\BOAT\\Props_Boat_SW_spritesheet.png");
			else if (rotation > 11.f * pi / 8.f && rotation <= 13.f * pi / 8.f)
				spriteManager->SetTexture(_e, "Textures\\Spritesheets\\BOAT\\Props_Boat_S_Spritesheet.png");
			else
				spriteManager->SetTexture(_e, "Textures\\Spritesheets\\BOAT\\Props_Boat_SE_spritesheet.png");

			if (FUNC->EntitiesCollided(_e, littleGirl)) {
				if (dialogueActivated == false) {
					dialogueText.Activate();
					dialogueActivated = true;
				}
			}
			else  dialogueActivated = false;
		}
	}
	Transform eXform = _e.GetComponent<Transform>();
	Transform waterXform = water.GetComponent<Transform>();
	Math::Vec2 waterMin = waterXform.translation - waterXform.scale / 2.f + currScene->mCamera.scale / 2.f;
	Math::Vec2 waterMax = waterXform.translation + waterXform.scale / 2.f - currScene->mCamera.scale / 2.f;

	if (eXform.translation.x < waterMin.x)
		_e.GetComponent<Transform>().translation.x = waterMin.x;
	else if (eXform.translation.x > waterMax.x)
		_e.GetComponent<Transform>().translation.x = waterMax.x;
	if (eXform.translation.y < waterMin.y)
		_e.GetComponent<Transform>().translation.y = waterMin.y;
	else if (eXform.translation.y > waterMax.y)
		_e.GetComponent<Transform>().translation.y = waterMax.y;

	if (currScene) {
		currScene->mCamera.translation += (_e.GetComponent<Transform>().translation - currScene->mCamera.translation) * static_cast<float>(FPSManager::dt);
	}

	if (FUNC->CheckKey(E_STATE::RELEASE, E_KEY::ESCAPE)) {
		(FUNC->SelectScene("Settings")).Pause(true);
		(FUNC->SelectScene("How_To_Play")).Pause(true);
		(FUNC->SelectScene("Pause")).Pause(false);
		(FUNC->SelectScene("Level1")).Pause(true);
	}
}

void PlayerMovementScript::EndScript(const Entity& _e) {
	(void)_e;
}