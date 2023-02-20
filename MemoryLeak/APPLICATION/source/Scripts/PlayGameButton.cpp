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
Function will run when the gamestate of the entity is activated.
*******************************************************************************/
void PlayGameButton::Alive(Entity const& _e) {
	(void)_e;
}

/*!*****************************************************************************
\brief
Function will run on initialisation of the entity.
*******************************************************************************/
void PlayGameButton::Init(Entity const& _e) {
	(void)_e;
	//LOG_INFO("Play button script starts works!!!");
}

/*!*****************************************************************************
\brief
Function will run on every update while the entity is active.
*******************************************************************************/
void PlayGameButton::Update(Entity const& _e) {
	static bool first = true;
	if (first) {
		FUNC->PlayBGSound("SwampNightTime_Loop", (int)E_AUDIO_CHANNEL::MAINBACKGROUND);
		first = false;
	}
	if (!FUNC->IsPlaying((int)E_AUDIO_CHANNEL::MAINBACKGROUND))
		FUNC->PlayBGSound("SwampNightTime_Loop", (int)E_AUDIO_CHANNEL::MAINBACKGROUND);

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
			FUNC->ChangeGameState("Level1");
			(FUNC->SelectScene("Settings")).Pause(true);
			(FUNC->SelectScene("How_To_Play")).Pause(true);
			(FUNC->SelectScene("Pause")).Pause(true);
			(FUNC->SelectScene("Level1")).Pause(false);
			FUNC->PlayBGSound("Bon_Voyage_BGM", (int)E_AUDIO_CHANNEL::MAINBACKGROUND);
			first = false;
		}
}

/*!*****************************************************************************
\brief
Function will run on fixed delta time.
*******************************************************************************/
void PlayGameButton::FixedUpdate(Entity const& _e) {
	(void)_e;
}

/*!*****************************************************************************
\brief
Function will run on exit or when the entity is destroyed.
*******************************************************************************/
void PlayGameButton::Exit(Entity const& _e) {
	(void)_e;
	//LOG_INFO("Play button script end works!!!");
}

/*!*****************************************************************************
\brief
Function will run when the gamestate of the entity exits.
*******************************************************************************/
void PlayGameButton::Dead(Entity const& _e) {
	(void)_e;
}
