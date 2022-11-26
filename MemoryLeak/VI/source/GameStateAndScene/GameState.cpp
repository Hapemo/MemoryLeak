/*!*****************************************************************************
\file GameState.cpp
\author Jazz Teoh Yu Jue
\par DP email: j.teoh\@digipen.edu
\par Group: Memory Leak Studios
\date 24-09-2022
GameState is a container that manages a range of scenes. It acts as manager for
the scenes. Only 1 gmae state should be loaded and running in the game at a
time.
*******************************************************************************/
#include "GameState.h"
//#include "Serialization.h"


void GameState::Init() {
	for (auto& scene : mScenes)
		if (!scene.mIsPause) scene.Init();
}

void GameState::Update() {
	for (auto& scene : mScenes)
		if (!scene.mIsPause) scene.PrimaryUpdate();
}

void GameState::Exit() {
	for (auto& scene : mScenes)
		scene.Exit();
}

// Load new gamestate with file path


void GameState::AddScene(std::filesystem::path const& _path) { // filesystem
	mScenes.emplace_back(Scene());
	Scene& latestScene{ mScenes.back() };
	
	if (_path.string().size() == 0) {
		static int newSceneCount = 1;
		latestScene.mName = "New Scene " + std::to_string(newSceneCount++);  //cannot have same GS name
		LOG_CUSTOM("GAMESTATE", "Adding NEW scene to gamestate: " + mName);
	} else {
		latestScene.Load(_path);
		LOG_CUSTOM("GAMESTATE", "Adding scene \"" + _path.stem().string() + "\" to gamestate: " + mName);
	}

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
		std::filesystem::path path{ ResourceManager::GetInstance()->FileTypePath(ResourceManager::E_RESOURCETYPE::scene).string() + scene.mName + ".json"};
		scene.Load(path);
		//renderManager->GetGameCamera().SetInitialPos(scene.mCamera.translation); //need set initial for multiple scenes
		//renderManager->GetGameCamera().SetInitialZoom(scene.mCamera.rotation);
		//renderManager->GetGameCamera().SetCameraWidth(scene.mCamera.scale.x); //need set initial scale
		//renderManager->GetGameCamera().SetCameraHeight(scene.mCamera.scale.y);
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






































