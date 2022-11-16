#include "GameState.h"
//#include "Serialization.h"


void GameState::Init() {

}
void GameState::Update() {

}

void GameState::Exit() {

}

// Load new gamestate with file path


void GameState::AddScene(std::string const& _path) { // filesystem
	//mScenes.emplace_back(SerialisationManager::LoadScene("NAME"));
	(void)_path;
}
void GameState::RemoveScene(std::string const& _name){
	(void)_name;
}

void GameState::Load(std::filesystem::path const& _path){
	serializationManager->LoadGameState(*this, _path);
}

void GameState::Save() {
	serializationManager->LoadGameState(*this);
}

void GameState::Unload(){

}

void GameState::Restart(){

}






































