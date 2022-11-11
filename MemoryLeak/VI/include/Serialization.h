/*!*****************************************************************************
\file Serialization.h
\author Huang Wei Jhin
\par DP email: h.weijhin@digipen.edu
\par Group: Memory Leak Studios
\date 20-09-2022
\brief
This file contains function declarations for a Serialization system that modifies
Entities and its Components.
*******************************************************************************/
#pragma once
#include <ECS_systems.h>
#include "ECS_items.h"
#include "ECS_components.h"
#include <ECS_tools.h>
#include "ResourceManager.h"

#include "document.h"
#include "writer.h"
#include <istreamwrapper.h>
#include "stringbuffer.h"
#include <prettywriter.h>

// Data that a scene class should contain
struct SceneData {
	bool isActive;
	std::set<Entity> mEntities;
};

//Data that a gamestate class should contain
struct GameStateData {
	std::vector<ResourceManager::GUID> mGUIDs;
};


/*!*****************************************************************************
\brief
	This class encapsulates the functions for Serialization manager
*******************************************************************************/
class SerializationManager : public System
{
public:
	void LoadScene(std::string _filename = "SceneJ");
	void SaveScene(std::string _filename = "SceneJ");
	void LoadPrefabs(std::string _filename = "NewPrefab");
	void SavePrefabs(std::string _filename = "NewPrefab");
	void LoadDialogs(std::string _filename = "Dialog1");
	void SaveDialogs(std::string _filename = "Dialog1");

	static SceneData LoadSceneData(ResourceManager::GUID const& _guid);
	static SceneData LoadSceneData(std::string const& _filePath);
	static GameStateData LoadGameStateData(ResourceManager::GUID const& _guid); // (Deprecated)
	static GameStateData LoadGameStateData(std::string const& _filePath); // (Deprecated)
	static void SaveSceneData(ResourceManager::GUID const&);

private:
};