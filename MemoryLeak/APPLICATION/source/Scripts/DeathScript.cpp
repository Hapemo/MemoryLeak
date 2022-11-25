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
	if (FUNC->EntitiesCollided(player, _e)) {
		FUNC->SetTexture(player, "Textures\\Spritesheets\\BOAT\\capsize\\Props_Boat_NE_Capsize_Spritesheet.png");
		player.GetComponent<SheetAnimation>().frameCount = 11;
		if (player.GetComponent<SheetAnimation>().currFrameIndex == player.GetComponent<SheetAnimation>().frameCount - 1) player.Deactivate();
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
