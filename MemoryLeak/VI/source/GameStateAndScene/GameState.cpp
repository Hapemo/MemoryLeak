#include "GameState.h"
//#include "Serialization.h"


void GameState::Init() {
	for (auto& scene : mScenes)
		scene.Init();
}
void GameState::Update() {
	for (auto& scene : mScenes)
		scene.PrimaryUpdate();
}

void GameState::Exit() {
	for (auto& scene : mScenes)
		scene.Exit();
}

// Load new gamestate with file path


void GameState::AddScene(std::filesystem::path const& _path) { // filesystem
	LOG_CUSTOM("GAMESTATE", "Adding scene \"" + _path.stem().string() + "\" to gamestate: " + mName);
	mScenes.emplace_back(Scene());
	Scene& latestScene{ mScenes.back() };
	latestScene.Load(_path);

	if (!latestScene.mIsPause) latestScene.Init();
}
void GameState::RemoveScene(std::string const& _name){
	LOG_CUSTOM("GAMESTATE", "Attempting to remove scene \"" + _name + "\" from gamestate: " + mName);
	
	for (auto it = mScenes.begin(); it != mScenes.end(); ++it) {
		if (it->mName == _name) {
			it->Unload();
			mScenes.erase(it);
			break;
		}
	}
}

void GameState::Load(std::filesystem::path const& _path){
	LOG_CUSTOM("GAMESTATE", "Load GameState: " + _path.string());
	serializationManager->LoadGameState(*this, _path);
	for (auto& scene : mScenes) {
		std::filesystem::path path{ ResourceManager::GetInstance()->FileTypePath(ResourceManager::E_RESOURCETYPE::scene).string() +"/Scene/" + scene.mName + ".json"};
		scene.Load(path);
		//std::cout << path.string()<<"\n";
	}
}

void GameState::Save() {
	LOG_CUSTOM("GAMESTATE", "Save GameState: " + mName);
	serializationManager->SaveGameState(*this);
}

void GameState::Unload() {
	LOG_CUSTOM("GAMESTATE", "Attempt to unload GameState: " + mName);
	for (auto& scene : mScenes)
		scene.Unload();
	mScenes.clear();
}






































