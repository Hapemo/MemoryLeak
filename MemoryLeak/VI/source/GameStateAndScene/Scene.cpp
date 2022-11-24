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
#include "LogicSystem.h"


Scene::Scene() : mEntities(), mIsPause(false), mName(), mCamera(), mLayer(), mOrder() {
	LOG_CUSTOM("SCENE", "New Scene created with no name");
}

Scene::Scene(ResourceManager::GUID const& _guid) : mEntities(), mIsPause(false), mName(), mCamera(), mLayer(), mOrder() {
	LOG_CUSTOM("SCENE", "New Scene created with no name");
}

Scene::Scene(std::string const& _name) : mEntities(), mIsPause(false), mName(_name), mCamera(), mLayer(), mOrder() {
	LOG_CUSTOM("SCENE", "Scene created with name: " + mName);
}

Scene::~Scene() {
	//LOG_CUSTOM("SCENE", "Scene with name " + mName + " destroyed");
}

void Scene::Init() {
	//std::set<Entity> shouldRun{};
	for (auto e : mEntities) if (e.GetComponent<General>().isActive) e.Activate(); // shouldRun.insert(e);
	
	//logicSystem->Init(shouldRun);
};

void Scene::Update() {
	
};

void Scene::Exit() {
	//std::set<Entity> shouldRun{};
	for (auto e : mEntities) if (e.GetComponent<General>().isActive) e.Deactivate(); // shouldRun.insert(e);

	//logicSystem->Exit(shouldRun);
};

void Scene::PrimaryUpdate() {
	if (mIsPause) return;
	Update();
}

void Scene::Pause(bool _pause) { 
	LOG_CUSTOM("SCENE", "Changed Scene \"" + mName + "\" pause status to " + (_pause ? "true" : "false"));
	for (auto& e : mEntities)
		e.GetComponent<General>().isPaused = _pause;
	mIsPause = _pause; 
	Camera& cam = renderManager->GetGameCamera();
	if (mIsPause)
	{
		mCamera = { { cam.GetCameraWidth(), cam.GetCameraHeight() }, mCamera.rotation, cam.GetPos() };
		renderManager->GetGameCamera().Reset();
	}
	else
	{
		(void)mCamera;
		renderManager->GetGameCamera().SetCameraWidth(mCamera.scale.x);
		renderManager->GetGameCamera().SetPos(mCamera.translation);
	}
}

void Scene::Load(std::filesystem::path const& _path) {
	LOG_CUSTOM("SCENE", "Loading Scene: " + mName);
	serializationManager->LoadScene(*this, _path);
	for (auto e : mEntities) {
		e.GetComponent<General>().isPaused = mIsPause;
	}
}

void Scene::Save() {
	LOG_CUSTOM("SCENE", "Saving Scene: " + mName);
	serializationManager->SaveScene(*this);
}

void Scene::Unload() {
	LOG_CUSTOM("SCENE", "Unloading Scene: " + mName);

	decltype(mEntities) tempEntities = mEntities;
	for (auto e : tempEntities)
		RemoveEntity(e);
	if (!mEntities.empty()) LOG_WARN("Scene \"" + mName + "\"still contains " + std::to_string(mEntities.size()) + " after unloading");

	// Clearing all scene data
	mEntities.clear();
	mIsPause = false;
	mName = decltype(mName)();
	mCamera = decltype(mCamera)();
	mLayer = decltype(mLayer)();
	mOrder = decltype(mOrder)();
}

Entity Scene::AddEntity() {
	Entity e{ ECS::CreateEntity() };
	mEntities.insert(e);
	return e;
}

void Scene::RemoveEntity(Entity const& _e) {
	if (_e.GetComponent<General>().isActive) _e.Deactivate();
	_e.Destroy();
	
	mEntities.erase(_e);
}

