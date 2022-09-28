/*!*****************************************************************************
\file AudioManager.cpp
\author Huang Wei Jhin
\par DP email: h.weijhin@digipen.edu
\par Group: Memory Leak Studios
\date 20-09-2022
\brief
This file contains function definations for a audio system to play sound in the game
*******************************************************************************/
#include "AudioManager.h"

/*!*****************************************************************************
\brief
    Initializes FMOD

\return
None.
*******************************************************************************/
void AudioManager::Init()
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
void AudioManager::Unload()
{
    for (auto& i : mSfxSound)
        i.second->release();

    for (auto& i : mBgmSound)
        i.second->release();
    
    mChannel.clear();
    
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
    system->createSound("..\\resources\\Audio\\SHOOT1.wav", FMOD_DEFAULT, nullptr, &snd);
    mSfxSound["SHOOT1.wav"] = snd;
    system->createSound("..\\resources\\Audio\\DAMAGE.wav", FMOD_DEFAULT, nullptr, &snd);
    mSfxSound["DAMAGE.wav"] = snd;
    system->createSound("..\\resources\\Audio\\HEALTH.wav", FMOD_DEFAULT, nullptr, &snd);
    mSfxSound["HEALTH.wav"] = snd;
    system->createSound("..\\resources\\Audio\\SHOOT5.wav", FMOD_DEFAULT, nullptr, &snd);
    mSfxSound["SHOOT5.wav"] = snd;
    system->createSound("..\\resources\\Audio\\MENUBG.wav", FMOD_DEFAULT, nullptr, &snd);
    mBgmSound["MENUBG.wav"] = snd;

    //printf("FMOD error: (%d) %s\n", result, FMOD_ErrorString(result));
}
/*!*****************************************************************************
\brief
    Plays a single sound

\return
None.
*******************************************************************************/
void AudioManager::PlaySound(const Entity& _e, int _channel)
{
    //for (int i = 0; i < e.GetComponent<Audio>().sound.size(); i++) 
    if (!_e.GetComponent<Audio>().sound.isPaused)
    {
        std::string snd = _e.GetComponent<Audio>().sound.path;
        //mSfxSound[snd]->setMode(2);
        bool f;
        mChannel[_channel]->isPlaying(&f);
        if(!f)
        {
            LOG_INFO("Play Collision sound");
            mChannel[_channel]->setVolume(_e.GetComponent<Audio>().sound.volume);
            system->playSound(mSfxSound[snd], nullptr, false, &mChannel[_channel]);
        }
    }
}

/*!*****************************************************************************
\brief
    Plays a single background sound

\return
None.
*******************************************************************************/
void AudioManager::PlayBGSound(std::string _snd, int _channel)
{
    mBgmSound[_snd]->setMode(2);
    bool f;
    mChannel[_channel]->isPlaying(&f);
    if (!f)
    {
        LOG_INFO("Play BG sound");
        mChannel[_channel]->setVolume(0.5f);
        system->playSound(mBgmSound[_snd], nullptr, false, &mChannel[_channel]);
    }
}
/*!*****************************************************************************
\brief
    Update function to play sounds of entities that need to be played

\return
None.
*******************************************************************************/
void AudioManager::UpdateSound()
{
    for (const Entity& e : mEntities)
    {
        if (e.GetComponent<Audio>().sound.toPlay==true)
        {
            
            PlaySound(e, (int)(std::rand()%10));
            if (!e.GetComponent<Audio>().sound.isLoop)
            {
                e.GetComponent<Audio>().sound.toPlay = false;
            }
        }
    }
    system->update();
}
/*!*****************************************************************************
\brief
    Set all volume
\param vol
    volume to set to

\return
None.
*******************************************************************************/
void AudioManager::SetALLVolume(float vol)
{
    for (const Entity& e : mEntities)
    {
        e.GetComponent<Audio>().sound.volume = vol;
    }
}
/*!*****************************************************************************
\brief
    Set all volume
\param vol
    volume to set to

\return
None.
*******************************************************************************/
void AudioManager::SetBGMVolume(float vol)
{
    for (const Entity& e : mEntities)
    {
        e.GetComponent<Audio>().sound.volume = vol;
    }
}
/*!*****************************************************************************
\brief
    Set all volume
\param vol
    volume to set to

\return
None.
*******************************************************************************/
void AudioManager::SetSFXVolume(float vol)
{
    for (const Entity& e : mEntities)
    {
        e.GetComponent<Audio>().sound.volume = vol;
    }
}