#pragma once
#include "pch.h"
#include "ResourceManager.h"
#include "Singleton.h"
/*
Prefabs are resources. They're json files containing information of components.
Load in prefabs into a vector container. 

Prefab manager can create prefabs and store it as a new prefab json file.

Prefab is an "editor-only" functionality. Start of editor application should
load in all prefabs usable by designers.

Prefab's memory is dynamic, thus unable to use resource manager to manage
*/


class Prefab;

// Prefab manager contains all the prefabs, drawing these data from resource manager.
// It allows editor to present all prefabs. 
// It also allows creation, and saving of new/current prefabs.
class PrefabManager : public Singleton<PrefabManager> {
public:
	using PrefabPtr = std::shared_ptr<Prefab>;
	// Load all prefabs in from resource manager.
	// Store them into the container here for ease of usage. (1)
	// Maybe store pointers to those data instead. (2)
	
	// This function should be called by resource manager when it is loading all resources
	void LoadPrefab(std::filesystem::path const&);

	PrefabPtr CreatePrefab();

	void SavePrefab(std::string const&);

	// Should we include this? To delete prefab files and their meta file.
	// void DeletePrefab(ResourceManager::GUID const&);

	PrefabPtr GetPrefab(std::string const&);
	std::vector<PrefabPtr>& GetPrefab() { return mPrefabs; }
private:
	std::vector<PrefabPtr> mPrefabs;
};
