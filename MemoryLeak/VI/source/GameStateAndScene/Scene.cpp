/*!*****************************************************************************
\file Scene.cpp
\author Jazz Teoh Yu Jue
\par DP email: j.teoh\@digipen.edu
\par Group: Memory Leak Studios
\date 24-09-2022
\brief
Scene base class. Each game state can have multiple scenes which encapsulates
a group of entities and operates on them.

For Milestone 2:
Added load and unload of scene using resourceManager
Added adding and removing of entity
*******************************************************************************/
#include "Scene.h"


Scene::Scene() : mEntities(), mIsPause(false), mName() {
	LOG_CUSTOM("SCENE", "New Scene created with no name");
}

Scene::Scene(ResourceManager::GUID const& _guid) : mEntities(), mIsPause(false), mName() {
	LOG_CUSTOM("SCENE", "New Scene created with no name");
}

Scene::Scene(std::string const& _name) : mEntities(), mIsPause(false), mName(_name) {
	LOG_CUSTOM("SCENE", "Scene created with name: " + mName);
}

Scene::~Scene() {
	LOG_CUSTOM("SCENE", "Scene with name " + mName + " destroyed");
}

void Scene::PrimaryUpdate() {
	if (mIsPause) return;
	Update();
}

void Scene::Pause(bool _pause) { 
	for (auto& e : mEntities)
		e.GetComponent<General>().isPaused = _pause;
	mIsPause = _pause; 
}

void Scene::Load(std::filesystem::path const& _path) {
	LOG_CUSTOM("SCENE", "Loading Scene: " + mName);
	serializationManager->LoadScene(*this, _path);
}

void Scene::Save() {
	LOG_CUSTOM("SCENE", "Saving Scene: " + mName);
	serializationManager->SaveScene(*this);
}

void Scene::Unload() {
	LOG_CUSTOM("SCENE", "Unloading Scene: " + mName);
	//ResourceManager::GetInstance()->UnloadScene(mGuid);
	//mEntities.clear();
}

// Input name of file. eg. Scene1.json
void Scene::Save(std::string _name) {
	// Scene file's location
	std::filesystem::path path{ ResourceManager::GetInstance()->FileTypePath(ResourceManager::E_RESOURCETYPE::scene) };

	// If no name specified, assume the file is already created and use it's old name.
	if (_name.empty()) {
		_name = ResourceManager::GetInstance()->GetFilePath(mGuid);
	} else {
		// Check if file name exists. If yes, just override it. If not, make a new one with a new guid and use it
		std::filesystem::path pathName = ResourceManager::GetInstance()->FileTypePath(ResourceManager::E_RESOURCETYPE::scene);
		_name = pathName.string() + _name;
		if (ResourceManager::FileExist(_name)) {
			LOG_CUSTOM("SCENE", "Saving scene into existing scene file: " + _name);
		} else mGuid = ResourceManager::GetInstance()->GUIDGenerator(_name); // Else create a new guid for it
	}

	// Open/create the file
	std::ofstream ofile{ _name };
	if (!ofile.is_open()) {
		LOG_WARN("Unable to open output file while attempting to save scene");
		return;
	}

	//----------------------------------------------
	// Save scene data here
	//----------------------------------------------

	// Save guid here
	// Save it's paused state here

	// Save scene entities. (mEntities)
	// Ask wei jhin how he's saving them now.

}

void Scene::AddEntity() {
	mEntities.insert(ECS::CreateEntity());
}

void Scene::RemoveEntity(Entity const& _e) {
	_e.Destroy();
	mEntities.erase(_e);
}
