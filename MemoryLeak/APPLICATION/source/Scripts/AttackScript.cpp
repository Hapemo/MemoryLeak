/*!*****************************************************************************
\file AttackScript.cpp
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 25-11-2022
\brief
The AttackScript handles the detection of when the player is nearby the enemy,
causing the enemy's rising out of the water animation to run and then run the
attacking animation.
*******************************************************************************/

#include "AttackScript.h"

REGISTER_SCRIPT(ScriptComponent, AttackScript);

/*!*****************************************************************************
\brief
Function will run on initialisation of the entity.
*******************************************************************************/
void AttackScript::StartScript(Entity const& _e) {
	(void)_e;
	//LOG_INFO("Attack script starts works!!!");
	player = FUNC->GetEntity("Boat", "Level1");
	enemy = FUNC->GetEntity("Enemy", "Level1");
	if (_e.HasComponent<Audio>()) {
		_e.GetComponent<Audio>().sound.toPlay = true;
		_e.GetComponent<Audio>().sound.isLoop = true;
	}
}

/*!*****************************************************************************
\brief
Function will run on every update while the entity is active.
*******************************************************************************/
void AttackScript::UpdateScript(Entity const& _e) {
	static bool raised = false;
	if (FUNC->EntitiesCollidedByEntity(player, _e)) {
		if(visible == 0) {
			if (!raised) {
				enemy.GetComponent<SheetAnimation>().currFrameIndex = 0;
				raised = true;
			}
			FUNC->SetTextureByEntity(enemy, "Textures\\Spritesheets\\MONSTER\\Character_Monster_SE_rising_spritesheet.png");
			enemy.GetComponent<SheetAnimation>().frameCount = 8;
			enemy.GetComponent<SheetAnimation>().timePerFrame = 0.170f;
			enemy.GetComponent<Transform>().scale.x = -523.000f;
			enemy.GetComponent<Transform>().scale.y = 353.000f;
			enemy.GetComponent<Transform>().translation.x = 876.748f;
			enemy.GetComponent<Transform>().translation.y = -201.188f;
			if (enemy.GetComponent<SheetAnimation>().currFrameIndex == enemy.GetComponent<SheetAnimation>().frameCount - 1) {
				enemy.GetComponent<SheetAnimation>().currFrameIndex = 0;
				visible = 1;
			}
		}
		if (visible == 1) {
			FUNC->SetTextureByEntity(enemy, "Textures\\Spritesheets\\MONSTER\\monster-attack-1-spritesheet.png");
			enemy.GetComponent<SheetAnimation>().frameCount = 9;
			enemy.GetComponent<SheetAnimation>().timePerFrame = 0.100f;
			enemy.GetComponent<Transform>().scale.x = -591.000f;
			enemy.GetComponent<Transform>().scale.y = 392.000f;
			enemy.GetComponent<Transform>().translation.x = 866.091f;
			enemy.GetComponent<Transform>().translation.y = -223.773f;
		}
	} else {
		visible = 0;
		raised = false;
		FUNC->SetTextureByEntity(enemy, "Textures\\Spritesheets\\MONSTER\\Character_Monster_SE_idle_spritesheet.png");
		enemy.GetComponent<SheetAnimation>().frameCount = 8;
		enemy.GetComponent<SheetAnimation>().timePerFrame = 0.100f;
		enemy.GetComponent<Transform>().scale.x = -200.000f;
		enemy.GetComponent<Transform>().scale.y = 86.000f;
		enemy.GetComponent<Transform>().translation.x = 812.552f;
		enemy.GetComponent<Transform>().translation.y = -279.941f;
	}
}

/*!*****************************************************************************
\brief
Function will run on exit or when the entity is destroyed.
*******************************************************************************/
void AttackScript::EndScript(Entity const& _e) {
	(void)_e;
	//LOG_INFO("Attack script end works!!!");
}
