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
#include <vec2.h>

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

using namespace rapidjson;
/*!*****************************************************************************
\brief
	This class encapsulates the functions for Serialization manager
*******************************************************************************/
class SerializationManager : public System
{
public:
	void LoadScene(std::string _filename = "SceneJ");
	void SaveScene(std::string _filename = "SceneJ");
	void LoadPrefab(std::string _filename = "NewPrefab");
	void SavePrefab(std::string _filename = "NewPrefab");
	void LoadDialogs(std::string _filename = "Dialog1");
	void SaveDialogs(std::string _filename = "Dialog1");


private:
	
	static Math::Vec2 GetVec2(Value& vecIn);
	static void addVectorMember(Document& scene, Value& parent, const char* name, Math::Vec2 data);
	template<typename T>
	static void addVectorArrayStrMember(Document& scene, Value& parent, const char* name, std::vector <T> data);
	template<typename T>
	static void addVectorArrayForceMember(Document& scene, Value& parent, const char* name, std::vector <T> data);
	template<typename T>
	static void addVectorArrayMember(Document& scene, Value& parent, const char* name, std::vector <T> data);
	template<typename T>
	static void addVectorsMember(Document& scene, Value& parent, const char* name, std::vector <T> data);





public:
	static SceneData LoadSceneData(ResourceManager::GUID const& _guid);
	static SceneData LoadSceneData(std::string const& _filePath);
	static GameStateData LoadGameStateData(ResourceManager::GUID const& _guid); // (Deprecated)
	static GameStateData LoadGameStateData(std::string const& _filePath); // (Deprecated)
	static void SaveSceneData(ResourceManager::GUID const&);

};