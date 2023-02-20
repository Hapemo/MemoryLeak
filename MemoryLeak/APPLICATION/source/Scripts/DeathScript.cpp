/*!*****************************************************************************
\file DeathScript.cpp
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 25-11-2022
\brief
The DeathScript runs the player's death animation on the boat collides with
the enemy.

Press "CTRL+SHIFT+M" to toggle player invincible mode.
*******************************************************************************/

#include "DeathScript.h"

REGISTER_SCRIPT(ScriptComponent, DeathScript);

/*!*****************************************************************************
\brief
Function will run when the gamestate of the entity is activated.
*******************************************************************************/
void DeathScript::Alive(Entity const& _e) {
	(void)_e;
}

/*!*****************************************************************************
\brief
Function will run on initialisation of the entity.
*******************************************************************************/
void DeathScript::Init(Entity const& _e) {
	(void)_e;
	//LOG_INFO("Death script starts works!!!");
	player = FUNC->GetEntity("Boat", "Level1");
}

/*!*****************************************************************************
\brief
Function will run on every update while the entity is active.
*******************************************************************************/
void DeathScript::Update(Entity const& _e) {
	if (FUNC->CheckKey(HOLD, LEFT_CONTROL) && FUNC->CheckKey(HOLD, LEFT_SHIFT) && FUNC->CheckKey(PRESS, M)) canDie = !canDie;

	static bool onEntry = false;
	if (FUNC->EntitiesCollidedByEntity(player, _e)) onEntry = true;
	if (onEntry && canDie) {
		static bool capsized = false;
		FUNC->SetTextureByEntity(player, "Textures\\Spritesheets\\BOAT\\capsize\\Props_Boat_NE_Capsize_Spritesheet.png");
		if (capsized == false) {
			player.GetComponent<SheetAnimation>().frameCount = 11;
			player.GetComponent<SheetAnimation>().timePerFrame = 0.15f;
			player.GetComponent<SheetAnimation>().currFrameIndex = 0;
			capsized = true;
		}

		if (player.GetComponent<SheetAnimation>().currFrameIndex == player.GetComponent<SheetAnimation>().frameCount - 1) {
			player.Deactivate();
			(FUNC->SelectScene("Level1")).Pause(true);
			(FUNC->SelectScene("Game Over")).Pause(false);
			onEntry = false;
			capsized = false;
		}
	}
}

/*!*****************************************************************************
\brief
Function will run on exit or when the entity is destroyed.
*******************************************************************************/
void DeathScript::Exit(Entity const& _e) {
	(void)_e;
	//LOG_INFO("Death script end works!!!");
}

/*!*****************************************************************************
\brief
Function will run when the gamestate of the entity exits.
*******************************************************************************/
void DeathScript::Dead(Entity const& _e) {
	(void)_e;
}
