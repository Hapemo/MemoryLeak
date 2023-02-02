/*!*****************************************************************************
\file ExitConfirmationButton.h
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 27-11-2022
\brief
The ExitConfirmationButton script activates the exit game confirmation screen
on button press.
*******************************************************************************/

#include "ExitConfirmationButton.h"

REGISTER_SCRIPT(ScriptComponent, ExitConfirmationButton);

/*!*****************************************************************************
\brief
Function will run on initialisation of the entity.
*******************************************************************************/
void ExitConfirmationButton::StartScript(Entity const& gob) {
	(void)gob;
	//LOG_INFO("Back to Main Menu button script starts works!!!");
}

/*!*****************************************************************************
\brief
Function will run on every update while the entity is active.
*******************************************************************************/
void ExitConfirmationButton::UpdateScript(Entity const& gob) {
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

	if (gob.HasComponent<Button>() && gob.GetComponent<Button>().activated){
		(FUNC->SelectScene("Settings")).Pause(true);
		(FUNC->SelectScene("How_To_Play")).Pause(true);
		(FUNC->SelectScene("Menu_Main")).Pause(true);
		(FUNC->SelectScene("Pause")).Pause(true);
		(FUNC->SelectScene("Level1")).Pause(true);
		(FUNC->SelectScene("Menu_Main")).Pause(true);
		(FUNC->SelectScene("Game Over")).Pause(true);
		(FUNC->SelectScene("Quit Confirmation")).Pause(false);
	}
}

/*!*****************************************************************************
\brief
Function will run on exit or when the entity is destroyed.
*******************************************************************************/
void ExitConfirmationButton::EndScript(Entity const& gob) {
	(void)gob;
	//LOG_INFO("Back to Main Menu button script end works!!!");
}
