/*!*****************************************************************************
\file PlayGameButton.cpp
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 24-11-2022
\brief
The PlayGameButton script starts the game (level 1) on button press.
*******************************************************************************/

#include "PlayGameButton.h"

REGISTER_SCRIPT(ScriptComponent, PlayGameButton);

/*!*****************************************************************************
\brief
Function will run on initialisation of the entity.
*******************************************************************************/
void PlayGameButton::StartScript(Entity const& gob) {
	(void)gob;
	//LOG_INFO("Play button script starts works!!!");
}

/*!*****************************************************************************
\brief
Function will run on every update while the entity is active.
*******************************************************************************/
void PlayGameButton::UpdateScript(Entity const& gob) {
	static float x = gob.GetComponent<Transform>().scale.x;
	static float y = gob.GetComponent<Transform>().scale.y;
	if (gob.GetComponent<Button>().isHover) {
		if (gob.GetComponent<Transform>().scale.x < x + 15.f)
			++(gob.GetComponent<Transform>().scale.x);
		if (gob.GetComponent<Transform>().scale.y < y + 15.f)
			++(gob.GetComponent<Transform>().scale.y);
	}
	else {
		if (gob.GetComponent<Transform>().scale.x > x)
			--(gob.GetComponent<Transform>().scale.x);
		if (gob.GetComponent<Transform>().scale.y > y)
			--(gob.GetComponent<Transform>().scale.y);
	}

	if(gob.HasComponent<Button>())
		if (gob.GetComponent<Button>().activated)
		{
			FUNC->ChangeGameState("Level1");
			(FUNC->SelectScene("Settings")).Pause(true);
			(FUNC->SelectScene("How_To_Play")).Pause(true);
			(FUNC->SelectScene("Pause")).Pause(true);
			(FUNC->SelectScene("Level1")).Pause(false);
		}
}

/*!*****************************************************************************
\brief
Function will run on exit or when the entity is destroyed.
*******************************************************************************/
void PlayGameButton::EndScript(Entity const& gob) {
	(void)gob;
	//LOG_INFO("Play button script end works!!!");
}
