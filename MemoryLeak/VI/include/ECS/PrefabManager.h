#pragma once
#include "pch.h"

/*
Prefabs are resources. They're json files containing information of components.
Load in prefabs into a vector container. 

Prefab manager can create prefabs and store it as a new prefab json file.


*/


class Prefab;

class PrefabManager {
public:
	// Load all prefabs in from resource manager.
	// Store them into the container here for ease of usage. (1)
	// Maybe store pointers to those data instead. (2)
	void LoadInPrefabs();

	

private:
	std::vector<Prefab> mPrefabs;
};
