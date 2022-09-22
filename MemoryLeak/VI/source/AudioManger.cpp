/*!*****************************************************************************
\file AudioManager.cpp
\author Huang Wei Jhin
\par DP email: h.weijhin@digipen.edu
\par Group: Memory Leak Studios
\date 20-09-2022
\brief
This file contains function definations for a audio system 
*******************************************************************************/
#include "AudioManager.h"

/*!*****************************************************************************
\brief
    Initializes FMOD

\return
None.
*******************************************************************************/
AudioManager::AudioManager()
{

    mResult = FMOD::System_Create(&system);      // Create the main system object.
    if (mResult != FMOD_OK)
    {
        //printf("FMOD error: (%d) %s\n", result, FMOD_ErrorString(result));
        exit(-1);
    }

    mResult = system->init(512, FMOD_INIT_NORMAL, 0);    // Initialize FMOD.
    if (mResult != FMOD_OK)
    {
        //printf("FMOD error: (%d) %s\n", result, FMOD_ErrorString(result));
        exit(-1);
    }
    LoadSound();
}
/*!*****************************************************************************
\brief
    Deconstructor 

\return
None.
*******************************************************************************/
AudioManager::~AudioManager()
{
    system->release();

}
/*!*****************************************************************************
\brief
    Load all the sounds needed to FMOD

\return
None.
*******************************************************************************/
void AudioManager::LoadSound() //Load all the sound needed in the game
{
    mChannel.resize(20);
    FMOD::Sound* snd;
    system->createSound("resources\\Audio\\SHOOT1.wav", FMOD_DEFAULT, nullptr, &snd);
    mSfxSound["SHOOT1.wav"] = snd;
    system->createSound("resources\\Audio\\DAMAGE.wav", FMOD_DEFAULT, nullptr, &snd);
    mSfxSound["DAMAGE.wav"] = snd;
    system->createSound("resources\\Audio\\HEALTH.wav", FMOD_DEFAULT, nullptr, &snd);
    mSfxSound["HEALTH.wav"] = snd;
    //printf("FMOD error: (%d) %s\n", result, FMOD_ErrorString(result));
}
/*!*****************************************************************************
\brief
    Plays a single sound

\return
None.
*******************************************************************************/
void AudioManager::PlaySound(const Entity& _e, int _sound)
{
    //for (int i = 0; i < e.GetComponent<Audio>().sound.size(); i++) 
    if (!_e.GetComponent<Audio>().sound.isPaused)
    {
        std::string snd = _e.GetComponent<Audio>().sound.path;
        //mSfxSound[snd]->setMode(2);
        bool f;
        mChannel[_sound]->isPlaying(&f);
        if(!f)
        {
            mChannel[_sound]->setVolume(_e.GetComponent<Audio>().sound.volume);
            system->playSound(mSfxSound[snd], nullptr, false, &mChannel[_sound]);
        }
    }
}
void AudioManager::UpdateSound()
{
    for (const Entity& e : mEntities)
    {
        if (e.GetComponent<Audio>().sound.toPlay)
        {
            PlaySound(e, 1);
            if (!e.GetComponent<Audio>().sound.isLoop)
            {
                e.GetComponent<Audio>().sound.toPlay = false;
            }
        }
    }
    system->update();
}
void AudioManager::SetALLVolume(float vol)
{
    for (const Entity& e : mEntities)
    {
        e.GetComponent<Audio>().sound.volume = vol;
    }
}
void AudioManager::SetBGMVolume(float vol)
{

}
void AudioManager::SetSFXVolume(float vol)
{

}