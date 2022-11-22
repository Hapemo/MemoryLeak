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
#include <sys/stat.h>
#include <ECSManager.h>
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
    mChannel.resize(20);
    
    ///LoadSound();
}

/*!*****************************************************************************
\brief
    Load all the sounds needed to FMOD

\return
None.
*******************************************************************************/
FMOD::Sound* AudioManager::LoadAudio(std::filesystem::path const& audio) //Load a sound needed in the game
{
  FMOD::Sound* snd;
  system->createSound(audio.string().c_str(), FMOD_DEFAULT, nullptr, &snd);
  if (audio.parent_path().string() == "..\\resources\\Audio\\SFX") 
  {
      mSfxSound[audio.stem().string()] = snd;
  
  }
  else  if (audio.parent_path().string() == "..\\resources\\Audio\\BGM")
  {
      mBgmSound[audio.stem().string()] = snd;
  }
  else  if (audio.parent_path().string() == "..\\resources\\Audio\\Songs")
  {
      mBgmSound[audio.stem().string()] = snd;
      songs.push_back(audio.stem().string());
  }
  return snd;
}
/*!*****************************************************************************
\brief
    Load all the dialogue sounds needed to FMOD

\return
None.
*******************************************************************************/
void AudioManager::LoadDialogueAudio(std::string audio) //Load a sound needed in the game
{
    for (auto& i : mDialogueSound)
        i.second->release();
    mDialogueSound.clear();
    FMOD::Sound* snd;
    std::string parent = "..\\resources\\Audio\\Dialogue\\";
    std::string rootPath = parent + audio;
    struct stat buffer;
    if (stat(rootPath.c_str(), &buffer) != 0)
    {
        LOG_WARN("No Dialogue Audio files found! ");
        return;
    }
    std::filesystem::path m_CurrentDirectory = std::filesystem::path(rootPath);
    for (auto& directory : std::filesystem::directory_iterator(m_CurrentDirectory))
    {
        const auto& path = directory.path();
        if (path.extension() == ".meta")
            continue;
        system->createSound(path.string().c_str(), FMOD_DEFAULT, nullptr, &snd);
        mDialogueSound[path.stem().string()] = snd;
    }
    
}
/*!*****************************************************************************
\brief
    Load all the sounds needed to FMOD

\return
None.
*******************************************************************************/
/*void AudioManager::LoadSound() //Load all the sound needed in the game
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
//}
//////resourceManager->GetResource<FMOD::Sound*>(guid);*/

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
        //if (!e.ShouldRun())
           // continue;
        if (e.GetComponent<Audio>().sound.toPlay == true)
        {
            if (e.GetComponent<Audio>().sound.channel == 0)
                e.GetComponent<Audio>().sound.channel = AddChannel();
            PlaySound(e);
        }
    }
    system->update();
}


/*!*****************************************************************************
\brief
    Plays a single sound

\return
None.
*******************************************************************************/
void AudioManager::PlaySound(const Entity& _e)
{
    //for (int i = 0; i < e.GetComponent<Audio>().sound.size(); i++) 
    if (!_e.GetComponent<Audio>().sound.isPaused)
    {
        std::string snd = _e.GetComponent<Audio>().sound.path;
        int channel = _e.GetComponent<Audio>().sound.channel;
        //mSfxSound[snd]->setMode(2);
        if (!isPlaying(channel))
        {
            LOG_INFO("Play Entity sound");
            system->playSound(mSfxSound[snd], nullptr, false, &mChannel[channel]);
            if (_e.GetComponent<Audio>().isSpacial && _e.HasComponent<Transform>())
            {
                float vol = _e.GetComponent<Audio>().sound.volume;
                Math::Vec2 distance = _e.GetComponent<Transform>().translation - renderManager->GetGameCamera().GetPos();
                Math::Vec2 max = { renderManager->GetGameCamera().GetCameraWidth()/2.f* _e.GetComponent<Audio>().spacialDistance,
                    renderManager->GetGameCamera().GetCameraHeight()/2.f* _e.GetComponent<Audio>().spacialDistance };

                float spacial = (max.Magnitude()-distance.Magnitude())/  max.Magnitude();
                spacial = spacial < 0.f ? 0.f : spacial;

                vol = vol *(1.f - _e.GetComponent<Audio>().spacialRatio) + spacial* _e.GetComponent<Audio>().spacialRatio;
                
                #ifdef NDEBUG
                std::cout << "sound vol :  " << _e.GetComponent<Audio>().sound.volume << "\n";
                std::cout << "Spacial ratio :  " << spacial << "\n";
                std::cout << "finial sound :  " << vol << "\n";
                #endif
                mChannel[channel]->setVolume(vol);
            }
            else
                mChannel[channel]->setVolume(_e.GetComponent<Audio>().sound.volume);
        }
    }
    if (!_e.GetComponent<Audio>().sound.isLoop)
    {
        _e.GetComponent<Audio>().sound.toPlay = false;
    }
}
/*!*****************************************************************************
\brief
    Plays a single background sound

\return
None.
*******************************************************************************/
void AudioManager::PlayAnySound(std::string _snd, int _channel)
{
    /* bool f;
    mChannel[_channel]->isPlaying(&f);*/
    if (isPlaying(_channel))
    {
        mChannel[_channel]->stop();
    }
    
    LOG_INFO("Play a sound");
    if (mBgmSound.find(_snd) != mBgmSound.end())
    {
        mBgmSound[_snd]->setMode(1);
        system->playSound(mBgmSound[_snd], nullptr, false, &mChannel[_channel]);
    }
    else if (mSfxSound.find(_snd) != mSfxSound.end())
    {
        mSfxSound[_snd]->setMode(1);
        system->playSound(mSfxSound[_snd], nullptr, false, &mChannel[_channel]);
    }
    mChannel[_channel]->setVolume(1.5f);
    
}
void AudioManager::PlayDialogueSound(std::string _snd, int _channel)
{
    /*bool f;
    mChannel[_channel]->isPlaying(&f);*/
    if (isPlaying(_channel))
    {
        mChannel[_channel]->stop();
    }

    mChannel[_channel]->setVolume(1.0f);
    if (mDialogueSound.find(_snd) != mDialogueSound.end())
    {
        mDialogueSound[_snd]->setMode(1);
        system->playSound(mDialogueSound[_snd], nullptr, false, &mChannel[_channel]);
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
   /* bool f;
    mChannel[_channel]->isPlaying(&f);*/
    if (isPlaying(_channel))
    {
        mChannel[_channel]->stop();
    }
    LOG_INFO("Play BG sound");
    system->playSound(mBgmSound[_snd], nullptr, false, &mChannel[_channel]);
    mChannel[_channel]->setVolume(0.0f);
}

bool AudioManager::isPlaying(int _channel)
{
    bool f;
    mChannel[_channel]->isPlaying(&f);
    return f;
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

int AudioManager::AddChannel()
{
    //FMOD::Channel* newChannel;
    // mChannel.emplace_back(newChannel);
    mChannel.resize(mChannel.size() + 1);
    return ((int)mChannel.size() - 1);
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

    for (auto& i : mDialogueSound)
        i.second->release();

    mChannel.clear();

    system->release();
}