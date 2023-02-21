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
	Entity e = gob;

	e.AddComponent(ParticleSystem{
		ParticleSystem::ParticleInfo{
			1, // mScale			
			0, // mFacing		
			3, // mLifespan	
			Sprite{
				RED, // color
				SPRITE::CIRCLE, // sprit
				0, // texture
				e.GetComponent<Sprite>().layer + 1  // layer
			}, // mSprite		
			0, // mRotation	
			10, // mSpeed			
			false, // mFading			
			100  // mLayer				
		},
		5, // mDensity 
		e.GetComponent<Transform>().translation, // mCenter
		1, // mAreaWidth 
		0, // mDirection
		0, // mSpread 
		10, // mDuration 
		true // mIsActive 
	});
	LOG_INFO(gob.GetComponent<General>().name + "Added component particle system============================================");
}

/*!*****************************************************************************
\brief
Function will run on every update while the entity is active.
*******************************************************************************/
void PlayGameButton::UpdateScript(Entity const& gob) {
	static bool first = true;
	if (first) {
		FUNC->PlayBGSound("SwampNightTime_Loop", (int)E_AUDIO_CHANNEL::MAINBACKGROUND);
		first = false;
	}
	if (!FUNC->IsPlaying((int)E_AUDIO_CHANNEL::MAINBACKGROUND))
		FUNC->PlayBGSound("SwampNightTime_Loop", (int)E_AUDIO_CHANNEL::MAINBACKGROUND);

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
Function will run on exit or when the entity is destroyed.
*******************************************************************************/
void PlayGameButton::EndScript(Entity const& gob) {
	(void)gob;
	//LOG_INFO("Play button script end works!!!");
}
