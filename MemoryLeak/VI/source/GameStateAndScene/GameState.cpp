#include "GameState.h"
//#include "Serialization.h"


void GameState::Init() {

}
void GameState::Update() {

}

void GameState::Exit() {

}

// Load new gamestate with file path


void GameState::AddScene(std::filesystem::path const& _path) { // filesystem
	LOG_CUSTOM("GAMESTATE", "Adding scene \"" + _path.stem().string() + "\" to gamestate: " + mName);
	mScenes.emplace_back(Scene());
	mScenes.back().Load(_path);
}
void GameState::RemoveScene(std::string const& _name){
	LOG_CUSTOM("GAMESTATE", "Attempting to remove scene \"" + _name + "\" from gamestate: " + mName);
}

void GameState::Load(std::filesystem::path const& _path){
	serializationManager->LoadGameState(*this, _path);
}

void GameState::Save() {
	serializationManager->SaveGameState(*this);
}

void GameState::Unload(){

}

void GameState::Restart(){

}






































