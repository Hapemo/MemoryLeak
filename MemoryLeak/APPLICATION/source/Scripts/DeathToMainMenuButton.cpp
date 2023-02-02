/*!*****************************************************************************
\file BackToMainMenuButton.h
\author Jazz Teoh Yu Jue
\par DP email: j.teoh\@digipen.edu
\par Course: GAM250
\par Group: Memory Leak Studios
\date 01-02-2023
\brief
The BackToMainMenuButton script returns the scene to the main menu on button press.
*******************************************************************************/

#include "DeathToMainMenuButton.h"

REGISTER_SCRIPT(ScriptComponent, DeathToMainMenuButton);

/*!*****************************************************************************
\brief
Function will run on initialisation of the entity.
*******************************************************************************/
void DeathToMainMenuButton::StartScript(Entity const& gob) {
	(void)gob;
	//LOG_INFO("Back to Main Menu button script starts works!!!");
}

/*!*****************************************************************************
\brief
Function will run on every update while the entity is active.
*******************************************************************************/
void DeathToMainMenuButton::UpdateScript(Entity const& gob) {
	static float x = gob.GetComponent<Transform>().scale.x;
	static float y = gob.GetComponent<Transform>().scale.y;
	if (gob.GetComponent<Button>().isClick)
	{
		if (gob.GetComponent<Transform>().scale.x > x - 10.f)
			gob.GetComponent<Transform>().scale.x -= 250.f * (float)FPSManager::dt;
		if (gob.GetComponent<Transform>().scale.y > y - 10.f)
			gob.GetComponent<Transform>().scale.y -= 250.f * (float)FPSManager::dt;

	}
	else if (gob.GetComponent<Button>().isHover) {
		if (gob.GetComponent<Transform>().scale.x < x + 15.f)
			gob.GetComponent<Transform>().scale.x += 100.f * (float)FPSManager::dt;
		if (gob.GetComponent<Transform>().scale.y < y + 15.f)
			gob.GetComponent<Transform>().scale.y += 100.f * (float)FPSManager::dt;

	}
	else
	{
		if (gob.GetComponent<Transform>().scale.x < x)
			gob.GetComponent<Transform>().scale.x += 250.f * (float)FPSManager::dt;
		if (gob.GetComponent<Transform>().scale.y < y)
			gob.GetComponent<Transform>().scale.y += 250.f * (float)FPSManager::dt;
		if (gob.GetComponent<Transform>().scale.x > x)
			gob.GetComponent<Transform>().scale.x -= 250.f * (float)FPSManager::dt;
		if (gob.GetComponent<Transform>().scale.y > y)
			gob.GetComponent<Transform>().scale.y -= 250.f * (float)FPSManager::dt;
	}
	if(gob.HasComponent<Button>())
		if (gob.GetComponent<Button>().activated) {
			FUNC->ChangeGameState("Menu");
			(FUNC->SelectScene("Settings")).Pause(true);
			(FUNC->SelectScene("How_To_Play")).Pause(true);
			(FUNC->SelectScene("Quit Confirmation")).Pause(true);
			(FUNC->SelectScene("Menu_Main")).Pause(false);
			(FUNC->SelectScene("Pause")).Pause(false);
		}
}

/*!*****************************************************************************
\brief
Function will run on exit or when the entity is destroyed.
*******************************************************************************/
void DeathToMainMenuButton::EndScript(Entity const& gob) {
	(void)gob;
	//LOG_INFO("Back to Main Menu button script end works!!!");
}
