/*!*****************************************************************************
\file DeathScript.cpp
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 25-11-2022
\brief
This file contains the function definitions of the class DeathScript.
*******************************************************************************/

#include "DeathScript.h"

REGISTER_SCRIPT(ScriptComponent, DeathScript);

/*!*****************************************************************************
\brief
Function will run on initialisation of the entity.
*******************************************************************************/
void DeathScript::StartScript(Entity const& _e) {
	(void)_e;
	//LOG_INFO("Death script starts works!!!");
	player = FUNC->GetEntity("Boat", "Level1");
}

/*!*****************************************************************************
\brief
Function will run on every update while the entity is active.
*******************************************************************************/
void DeathScript::UpdateScript(Entity const& _e) {
	static bool onEntry = false;
	if (FUNC->EntitiesCollided(player, _e)) {
		onEntry = true;
	}
	if (onEntry==true) //once collided
	{
		static bool first = false;
		FUNC->SetTexture(player, "Textures\\Spritesheets\\BOAT\\capsize\\Props_Boat_NE_Capsize_Spritesheet.png");
		if (first == false) //set stuff once
		{
			player.GetComponent<SheetAnimation>().frameCount = 11;
			player.GetComponent<SheetAnimation>().timePerFrame = 0.15f;
			player.GetComponent<SheetAnimation>().currFrameIndex = 0;
			first = true;
		}
			
		if (player.GetComponent<SheetAnimation>().currFrameIndex == player.GetComponent<SheetAnimation>().frameCount - 1) {
			player.Deactivate();
			(FUNC->SelectScene("Level1")).Pause(true);
			(FUNC->SelectScene("Game Over")).Pause(false);
			onEntry = false;
			first = false;
		}
	}
}

/*!*****************************************************************************
\brief
Function will run on exit or when the entity is destroyed.
*******************************************************************************/
void DeathScript::EndScript(Entity const& _e) {
	(void)_e;
	//LOG_INFO("Death script end works!!!");
}
