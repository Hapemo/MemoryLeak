#include "PlayerMovementScript.h"

REGISTER_SCRIPT(ScriptComponent, PlayerMovementScript);

void PlayerMovementScript::StartScript(const Entity& _e) {
	(void)_e;
	inited = false;
}

void PlayerMovementScript::UpdateScript(const Entity& _e) {
	if (!inited) {
		littleGirl = FUNC->GetEntity("ActivateLittleGirlScript", "Level1");
		dialogueText = FUNC->GetEntity("DialogueText", "Level1");
		currScene = &(FUNC->SelectScene("Level1"));
		initialCamScale = currScene->mCamera.scale;
		inited = true;
	}
	if (currScene->mCamera.scale.x < initialCamScale.x)
		currScene->mCamera.scale.x += 500 * (float)FUNC->GetDeltaTime();
	_e.GetComponent<Transform>().scale.x = std::abs(_e.GetComponent<Transform>().scale.x);

	if (FUNC->CheckKey(E_STATE::HOLD, M_BUTTON_L)) {
		if (dialogueText.HasComponent<General>() && dialogueText.GetComponent<General>().isActive == false) {
			Math::Vec2 dirVector{ FUNC->GetWorldMousePos() + currScene->mCamera.translation - _e.GetComponent<Transform>().translation };
			if (dirVector.SqMagnitude() > FLT_EPSILON * FLT_EPSILON)
				FUNC->ApplyImpulse(_e, (dirVector.Normalized() * playerSpeed) * (float)FUNC->GetDeltaTime(), Math::Vec2{ 0.f, 0.f });

			float rotation{};
			if (dirVector.y != 0.f && dirVector.x >= 0.f)
				rotation = atan2f(dirVector.y, dirVector.x);
			else if (dirVector.y == 0.f && dirVector.x > 0.f)
				rotation = (float)Math::PI / 2.f;
			else if (dirVector.y != 0.f && dirVector.x < 0.f) {
				rotation = atan2f(dirVector.y, dirVector.x);
				rotation += rotation < 0.f ? (float)Math::PI * 2.f : 0.f;
			} else rotation = 3.f * (float)Math::PI / 2.f;

			if (rotation >= 0.f && rotation < (float)Math::PI / 2.f)
				FUNC->SetTexture(_e, "Textures\\Spritesheets\\BOAT\\Props_Boat_NE_spritesheet.png");
			else if (rotation >= (float)Math::PI / 2.f && rotation < (float)Math::PI)
				FUNC->SetTexture(_e, "Textures\\Spritesheets\\BOAT\\boat_NW_spritesheet.png");
			else if (rotation >= (float)Math::PI && rotation < (float)Math::PI * 3.f / 2.f)
				FUNC->SetTexture(_e, "Textures\\Spritesheets\\BOAT\\Props_Boat_SW_spritesheet.png");
			else
				FUNC->SetTexture(_e, "Textures\\Spritesheets\\BOAT\\Props_Boat_SE_spritesheet.png");

			if (FUNC->EntitiesCollided(_e, littleGirl)) {
				if (dialogueActivated == false) {
					dialogueText.Activate();
					dialogueActivated = true;
				}
			}
			else {
				dialogueActivated = false;
			}
		}
	}

	if (currScene)
		currScene->mCamera.translation = _e.GetComponent<Transform>().translation;

	if (FUNC->CheckKey(E_STATE::PRESS, E_KEY::ESCAPE))
	{
		(FUNC->SelectScene("Settings")).Pause(true);
		(FUNC->SelectScene("How_To_Play")).Pause(true);
		(FUNC->SelectScene("Pause")).Pause(false);
		(FUNC->SelectScene("Level1")).Pause(true);
	}
}

void PlayerMovementScript::EndScript(const Entity& _e) {
	(void)_e;
}