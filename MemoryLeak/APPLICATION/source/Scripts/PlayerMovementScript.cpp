/*!*****************************************************************************
\file PlayerMovementScript.cpp
\author Lee Hsien Wei, Joachim, Kew Yu Jun, Chen Jia Wen
\par DP email: l.hsienweijoachim@digipen.edu, c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 24-11-2022
\brief
The PlayerMovementScript allows the player to move around the map according to
the mouse click position. It also handles the sprites changes according to the
direction the boat is facing. The end dialogue scene camera zoom out is also
handled here.

Press "CTRL+SHIFT+L" to skip to the game over screen.
Press "CTRL+SHIFT+M" to toggle player invincible mode.
Press "CTRL+SHIFT+B" to toggle player's speed increase.
Press "ESC" to toggle the pause menu.
*******************************************************************************/

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
	if (!FUNC->IsPlaying((int)E_AUDIO_CHANNEL::MAINBACKGROUND))
		FUNC->PlayBGSound("Bon_Voyage_BGM", (int)E_AUDIO_CHANNEL::MAINBACKGROUND);
	if (_e.HasComponent<Audio>())
		_e.GetComponent<Audio>().sound.volume = 0.0f;

	if (!inited) {
		littleGirl = FUNC->GetEntity("ActivateLittleGirlScript", "Level1");
		dialogueText = FUNC->GetEntity("DialogueText", "Level1");
		water = FUNC->GetEntity("Water", "Level1");
		enemy = FUNC->GetEntity("Enemy", "Level1");
		if (_e.HasComponent<Audio>()) {
			_e.GetComponent<Audio>().sound.toPlay = true;
			_e.GetComponent<Audio>().sound.isLoop = true;
		}
		currScene = &(FUNC->SelectScene("Level1"));
		currCamera = &FUNC->CurrentCamera();
		initialCamScale = currCamera->scale;
		inited = true;
	}
	if (dialogueZoomOut == true)
		if (currCamera->scale.x < initialCamScale.x)
			currCamera->scale.x += 500 * (float)FUNC->GetDeltaTime();
	_e.GetComponent<Transform>().scale.x = std::abs(_e.GetComponent<Transform>().scale.x);

	if (FUNC->CheckKey(E_STATE::PRESS, E_KEY::ESCAPE)) {
		(FUNC->SelectScene("Settings")).Pause(true);
		(FUNC->SelectScene("How_To_Play")).Pause(true);
		(FUNC->SelectScene("Level1")).Pause(true);
		(FUNC->SelectScene("Game Over")).Pause(true);
		(FUNC->SelectScene("Pause")).Pause(false);
		FUNC->PlayAnySound("Button_Click_SFX", (int)E_AUDIO_CHANNEL::FORCEPLAY);
	}

	if (FUNC->CheckKey(E_STATE::HOLD, E_KEY::LEFT_CONTROL) && FUNC->CheckKey(E_STATE::HOLD, E_KEY::LEFT_SHIFT)) {
		if (FUNC->CheckKey(E_STATE::PRESS, E_KEY::L)) {
			(FUNC->SelectScene("Level1")).Pause(true);
			(FUNC->SelectScene("Game Over")).Pause(false);
			_e.Deactivate();
		}
		if (FUNC->CheckKey(E_STATE::PRESS, E_KEY::M)) canDie = !canDie;
		if (FUNC->CheckKey(E_STATE::PRESS, E_KEY::B)) speedCheat = !speedCheat; // speed cheat toggle
	}

	if (FUNC->CheckKey(E_STATE::HOLD, M_BUTTON_L) && (!FUNC->EntitiesCollidedByEntity(enemy, _e) || !canDie)) {
		if ((dialogueText.HasComponent<General>() && dialogueText.GetComponent<General>().isActive == false)/*|| _e.GetComponent<General>().name != "Boat"*/) {
			Math::Vec2 dirVector{ FUNC->GetWorldMousePos() + currCamera->translation - _e.GetComponent<Transform>().translation };
			if (dirVector.SqMagnitude() > FLT_EPSILON * FLT_EPSILON)
				FUNC->ApplyImpulseByEntity(_e, (dirVector.Normalized() * playerSpeed * (speedCheat ? speedCheatMultiplier : 1)) * (float)FUNC->GetDeltaTime(), Math::Vec2{ 0.f, 0.f });
			if (_e.HasComponent<Audio>())
				_e.GetComponent<Audio>().sound.volume = 0.2f;
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
				FUNC->SetTextureByEntity(_e, "Textures\\Spritesheets\\BOAT\\Props_Boat_E_Spritesheet.png");
			else if (rotation > pi / 8.f && rotation <= 3.f * pi / 8.f)
				FUNC->SetTextureByEntity(_e, "Textures\\Spritesheets\\BOAT\\Props_Boat_NE_spritesheet.png");
			else if (rotation > 3.f * pi / 8.f && rotation <= 5.f * pi / 8.f)
				FUNC->SetTextureByEntity(_e, "Textures\\Spritesheets\\BOAT\\Props_Boat_N_Spritesheet.png");
			else if (rotation > 5.f * pi / 8.f && rotation <= 7.f * pi / 8.f)
				FUNC->SetTextureByEntity(_e, "Textures\\Spritesheets\\BOAT\\Props_Boat_NW_Spritesheet.png");
			else if (rotation > 7.f * pi / 8.f && rotation <= 9.f * pi / 8.f)
				FUNC->SetTextureByEntity(_e, "Textures\\Spritesheets\\BOAT\\Props_Boat_W_Spritesheet.png");
			else if (rotation > 9.f * pi / 8.f && rotation <= 11.f * pi / 8.f)
				FUNC->SetTextureByEntity(_e, "Textures\\Spritesheets\\BOAT\\Props_Boat_SW_spritesheet.png");
			else if (rotation > 11.f * pi / 8.f && rotation <= 13.f * pi / 8.f)
				FUNC->SetTextureByEntity(_e, "Textures\\Spritesheets\\BOAT\\Props_Boat_S_Spritesheet.png");
			else
				FUNC->SetTextureByEntity(_e, "Textures\\Spritesheets\\BOAT\\Props_Boat_SE_spritesheet.png");

			if (FUNC->EntitiesCollidedByEntity(_e, littleGirl)) {
				if (dialogueActivated == false) {
					dialogueText.Activate();
					dialogueActivated = true;
					dialogueZoomOut = false;
				}
			}
			else {
				dialogueActivated = false;
				dialogueZoomOut = true;
			}
		}
		else {
			if (FUNC->EntitiesCollidedByEntity(_e, littleGirl)) {
				dialogueZoomOut = true;
			}
		}
	}

	Transform eXform = _e.GetComponent<Transform>();
	Transform waterXform = water.GetComponent<Transform>();
	Math::Vec2 waterMin = waterXform.translation - waterXform.scale / 2.f + currCamera->scale / 2.f;
	Math::Vec2 waterMax = waterXform.translation + waterXform.scale / 2.f - currCamera->scale / 2.f;

	if (eXform.translation.x < waterMin.x)
		_e.GetComponent<Transform>().translation.x = waterMin.x;
	else if (eXform.translation.x > waterMax.x)
		_e.GetComponent<Transform>().translation.x = waterMax.x;
	if (eXform.translation.y < waterMin.y)
		_e.GetComponent<Transform>().translation.y = waterMin.y;
	else if (eXform.translation.y > waterMax.y)
		_e.GetComponent<Transform>().translation.y = waterMax.y;

	if (currScene)
		currCamera->translation += (_e.GetComponent<Transform>().translation - currCamera->translation) * static_cast<float>(FUNC->GetDeltaTime()) * (speedCheat ? speedCheatMultiplier : 1);
}

void PlayerMovementScript::EndScript(const Entity& _e) {
	(void)_e;
}