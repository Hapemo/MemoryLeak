/*!*****************************************************************************
\file ExitGameButton.cpp
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 24-11-2022
\brief
The ExitGameButton script close the program on button press.
*******************************************************************************/

#include "ExitGameButton.h"

REGISTER_SCRIPT(ScriptComponent, ExitGameButton);

/*!*****************************************************************************
\brief
Function will run on initialisation of the entity.
*******************************************************************************/
void ExitGameButton::StartScript(Entity const& gob) {
	(void)gob;
	//LOG_INFO("How to Play button script starts works!!!");
}

/*!*****************************************************************************
\brief
Function will run on every update while the entity is active.
*******************************************************************************/
void ExitGameButton::UpdateScript(Entity const& gob) {
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
			FUNC->GameStateExit();
			FUNC->PlayAnySound("Button_Click_SFX", (int)E_AUDIO_CHANNEL::FORCEPLAY);
		}

	if (FUNC->CheckKey(E_STATE::RELEASE, E_KEY::ENTER)) FUNC->GameStateExit();
}

/*!*****************************************************************************
\brief
Function will run on exit or when the entity is destroyed.
*******************************************************************************/
void ExitGameButton::EndScript(Entity const& gob) {
	(void)gob;
	//LOG_INFO("How to Play button script end works!!!");
}
