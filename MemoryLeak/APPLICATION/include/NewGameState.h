#pragma once
#include "pch.h"

class Scene;

class NewGameState {
public:
	void Init();
	void Update();

	void Exit();

	// Load new gamestate with file path
	void AddScene(std::string const& _path);
	void RemoveScene(std::string const& _name); 
	void Unload();
	void Restart();
	
private:
	std::string mName;
	std::vector<Scene> mScenes;

};






































