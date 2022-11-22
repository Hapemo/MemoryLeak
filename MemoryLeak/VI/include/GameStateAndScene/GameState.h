#pragma once
#include "pch.h"
#include "Scene.h"

class GameState {
public:
	void Init(); // Only initially active scenes will init
	void Update(); // Only active scenes will update

	void Exit(); // All scene's exit will be called regardless of pause state

	// Load new gamestate with file path
	
	// *EDITOR ONLY FUNCTIONALITIES*
	void AddScene(std::filesystem::path const& _path = std::filesystem::path());
	void RemoveScene(std::string const& _name); 

	void Load(std::filesystem::path const& _path);
	void Save();
	void Unload();
	
	std::string mName="";
	std::vector<Scene> mScenes{};
private:

};






































