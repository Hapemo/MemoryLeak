#pragma once
enum class E_CHANNEL
{
	BGM = 0,
	SFX,
	LAST
};
/*!*****************************************************************************
\brief
	This struct contains the data for a single Sound
*******************************************************************************/
struct Sound
{
	std::string path;
	bool toPlay = false;
	float volume =1.0f;
	float volumeMod =1.0f;
	float pitch = 1.0f;
	bool isPaused = false;
	bool isMute = false;
	bool isLoop = false;
	bool isRandPitch = false;

	int channel =0;
	
};
//play = vol *volmod*spacialdistance*slider