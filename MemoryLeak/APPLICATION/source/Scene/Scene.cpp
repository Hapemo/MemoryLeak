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


Scene::Scene() : mEntities(), pause(false), mGuid(0) {
	LOG_CUSTOM("SCENE", "Scene created with mGuid: " + std::to_string(mGuid));
}

Scene::Scene(ResourceManager::GUID const& _guid) : mEntities(), pause(false), mGuid(_guid) {
	LOG_CUSTOM("SCENE", "Scene created with mGuid: " + std::to_string(mGuid));
}

Scene::~Scene() {
	LOG_CUSTOM("SCENE", "Scene destroyed with mGuid: " + std::to_string(mGuid));
}

void Scene::PrimaryUpdate() {
	if (pause) return;
	Update();
}

void Scene::Pause(bool _pause) { 
	for (auto& e : mEntities)
		e.GetComponent<General>().isPaused = _pause;
	pause = _pause; 
}

void Scene::Load(ResourceManager::GUID const& _guid) {
	LOG_CUSTOM("SCENE", "Loading Scene " + std::to_string(_guid));
	SceneData sceneData = ResourceManager::GetInstance()->LoadScene(_guid);
	mEntities = sceneData.mEntities;
	pause = sceneData.isActive;
	mGuid = _guid;
}

void Scene::Unload() {
	LOG_CUSTOM("SCENE", "Unloading Scene with mGuid: " + std::to_string(mGuid));
	ResourceManager::GetInstance()->UnloadScene(mGuid);
	mEntities.clear();
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
		if (ResourceManager::GetInstance()->FileExist(_name)) {
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



