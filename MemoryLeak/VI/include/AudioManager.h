/*!*****************************************************************************
\file AudioManager.h
\author Huang Wei Jhin
\par DP email: h.weijhin@digipen.edu
\par Group: Memory Leak Studios
\date 20-09-2022
\brief
This file contains function declarations for a audio system 
*******************************************************************************/
#pragma once
#include <fmod.hpp>
#include <ECS_systems.h>
#include "ECS_items.h"
#include "ECS_components.h"

class AudioManager : public System
{
public:
	AudioManager();								//constructor add fmod
	~AudioManager();							//Deconstructor

	void LoadSound();							//Load all sound 
	void PlayBGSound(std::string, int);
	void UpdateSound();
	void SetALLVolume(float vol);
	void SetBGMVolume(float vol);
	void SetSFXVolume(float vol);
	
private:
	void PlaySound(const Entity& e, int sound);	//Play sound 
	//WIP
	//void PauseSound(int, bool);				//pasue (sound enum, true/false) true - pause 
	//void SetSoundVolume(int, float);			//set volume (sound, 0.0f-1.0f, 0 or 1) 1.0f loudest
	//void SetALLSoundVolume(float);			//set volume ( 0.0f-1.0f, 0 or 1) 1.0f 
	//void StopSound(int);						//stop the sound
	//void LoopSound(int, bool);				// loop sound (true - loop  || false - stop loop)
	//bool isSoundPlaying(int);					//check if sound is playing true if playing
	//void SetSoundSpeed(int, float);			//Set sound speed
	//void SetSoundFrequence(int, float);		//Set sound frequency
	//void SetSoundPitch(int, float);			//Set sound pitch
	//void Update();
	FMOD_RESULT mResult;
	FMOD::System* system;
	std::map<std::string, FMOD::Sound*> mBgmSound;
	std::map<std::string, FMOD::Sound*> mSfxSound;
	std::vector<FMOD::Channel*> mChannel;
};