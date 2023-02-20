/*!*****************************************************************************
\file BackToMainMenuButton.h
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 24-11-2022
\brief
The BackToMainMenuButton script returns the scene to the main menu on button press.
*******************************************************************************/

#include "BackToMainMenuButton.h"

REGISTER_SCRIPT(ScriptComponent, BackToMainMenuButton);

/*!*****************************************************************************
\brief
Function will run when the gamestate of the entity is activated.
*******************************************************************************/
void BackToMainMenuButton::Alive(Entity const& _e) {
	(void)_e;
}

/*!*****************************************************************************
\brief
Function will run on initialisation of the entity.
*******************************************************************************/
void BackToMainMenuButton::Init(Entity const& _e) {
	(void)_e;
	//LOG_INFO("Back to Main Menu button script starts works!!!");
}

/*!*****************************************************************************
\brief
Function will run on every update while the entity is active.
*******************************************************************************/
void BackToMainMenuButton::Update(Entity const& _e) {
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
	if(_e.HasComponent<Button>())
		if (_e.GetComponent<Button>().activated) {
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
void BackToMainMenuButton::Exit(Entity const& _e) {
	(void)_e;
	//LOG_INFO("Back to Main Menu button script end works!!!");
}

/*!*****************************************************************************
\brief
Function will run when the gamestate of the entity exits.
*******************************************************************************/
void BackToMainMenuButton::Dead(Entity const& _e) {
	(void)_e;
}
