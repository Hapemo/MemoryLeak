#pragma once
#include "pch.h"
#include "Scene.h"

class GameState {
public:
	void Init();
	void Update();

	void Exit();

	// Load new gamestate with file path
	
	// *EDITOR ONLY FUNCTIONALITIES*
	void AddScene(std::filesystem::path const& _path);
	void RemoveScene(std::string const& _name); 

	void Load(std::filesystem::path const& _path);
	void Save();
	void Unload();
	
	std::string mName;
	std::vector<Scene> mScenes;
private:

};






































