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
Function will run when the gamestate of the entity is activated.
*******************************************************************************/
void ExitConfirmationButton::Alive(Entity const& _e) {
	(void)_e;
}

/*!*****************************************************************************
\brief
Function will run on initialisation of the entity.
*******************************************************************************/
void ExitConfirmationButton::Init(Entity const& _e) {
	(void)_e;
	//LOG_INFO("Back to Main Menu button script starts works!!!");
}

/*!*****************************************************************************
\brief
Function will run on every update while the entity is active.
*******************************************************************************/
void ExitConfirmationButton::Update(Entity const& _e) {
	static float x = _e.GetComponent<Transform>().scale.x;
	static float y = _e.GetComponent<Transform>().scale.y;
	if (_e.GetComponent<Button>().isClick)
	{
		if (_e.GetComponent<Transform>().scale.x > x - 10.f)
			_e.GetComponent<Transform>().scale.x -= 250.f * (float)FPSManager::dt;
		if (_e.GetComponent<Transform>().scale.y > y - 10.f)
			_e.GetComponent<Transform>().scale.y -= 250.f * (float)FPSManager::dt;
	}
	else if (_e.GetComponent<Button>().isHover) {
		if (_e.GetComponent<Transform>().scale.x < x + 15.f)
			_e.GetComponent<Transform>().scale.x += 100.f * (float)FPSManager::dt;
		if (_e.GetComponent<Transform>().scale.y < y + 15.f)
			_e.GetComponent<Transform>().scale.y += 100.f * (float)FPSManager::dt;
	}
	else
	{
		if (_e.GetComponent<Transform>().scale.x < x)
			_e.GetComponent<Transform>().scale.x += 250.f * (float)FPSManager::dt;
		if (_e.GetComponent<Transform>().scale.y < y)
			_e.GetComponent<Transform>().scale.y += 250.f * (float)FPSManager::dt;
		if (_e.GetComponent<Transform>().scale.x > x)
			_e.GetComponent<Transform>().scale.x -= 250.f * (float)FPSManager::dt;
		if (_e.GetComponent<Transform>().scale.y > y)
			_e.GetComponent<Transform>().scale.y -= 250.f * (float)FPSManager::dt;
	}

	if (_e.HasComponent<Button>() && _e.GetComponent<Button>().activated){
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
Function will run on fixed delta time.
*******************************************************************************/
void ExitConfirmationButton::FixedUpdate(Entity const& _e) {
	(void)_e;
}

/*!*****************************************************************************
\brief
Function will run on exit or when the entity is destroyed.
*******************************************************************************/
void ExitConfirmationButton::Exit(Entity const& _e) {
	(void)_e;
	//LOG_INFO("Back to Main Menu button script end works!!!");
}

/*!*****************************************************************************
\brief
Function will run when the gamestate of the entity exits.
*******************************************************************************/
void ExitConfirmationButton::Dead(Entity const& _e) {
	(void)_e;
}
