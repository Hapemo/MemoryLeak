#pragma once
enum class E_CHANNEL
{
	BGM = 0,
	SFX,
	LAST
};

struct Sound
{
	std::string path;
	float volume =1.0f;
	float volumeMod =1.0f;
	float pitch = 1.0f;
	bool isPaused = false;
	bool isMute = false;
	bool isLoop = false;
	bool isRandPitch = false;
	
};
//play = vol *volmod*spacialdistance*slider