#pragma once
#include "pch.h"
#include "Scene.h"

class GameState {
public:
	void Init();
	void Update();

	void Exit();

	// Load new gamestate with file path
	

	void AddScene(std::string const& _path); //{ // filesystem
		//mScenes.emplace_back(SerialisationManager::LoadScene("NAME"));
	//}
	void RemoveScene(std::string const& _name); 
	void Load(std::filesystem::path const& _path);
	void Unload();
	void Restart();
	
private:
	std::string mName;
	std::vector<Scene> mScenes;

};






































