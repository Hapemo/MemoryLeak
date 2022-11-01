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

void Scene::AddEntity() {
	mEntities.insert(ECS::CreateEntity());
}

void Scene::RemoveEntity(Entity const& _e) {
	_e.Destroy();
	mEntities.erase(_e);
}



