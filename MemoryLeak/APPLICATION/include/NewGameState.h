#pragma once
#include "pch.h"

class Scene;

class NewGameState {
public:
	void Init();
	void Update();

	void Exit();

	// Load new gamestate with file path
	void Load(std::string const& _path);
	void Unload();
	void Restart();
	void Pause(bool _pause) { mPaused = _pause; }; // For editor

private:
	std::string mName;
	std::vector<Scene> mScenes;
	bool mPaused; // For editor

};






































