/*!*****************************************************************************
\file Scene.h
\author Jazz Teoh Yu Jue
\par DP email: j.teoh\@digipen.edu
\par Group: Memory Leak Studios
\date 24-09-2022
\brief
Scene base class. Each game state can have multiple scenes which encapsulates
a group of entities and operates on them.

For Milestone 2:
Added load and unload of scene using resourceManager
*******************************************************************************/
#pragma once
#include "ECS_items.h"
#include "pch.h"
#include "ECSManager.h"
#include "ResourceManager.h"

class Scene {
public:
	Scene();
	Scene(ResourceManager::GUID const&);
	Scene(std::string const&);
	~Scene();
	/*!*****************************************************************************
	Set the scene's pause status

	\param bool
	- True to pause the scene's update loop, otherwise false
	*******************************************************************************/
	void Pause(bool);

	/*!*****************************************************************************
	Main update loop of the game that dismisses all other updates if game is paused
	*******************************************************************************/
	void PrimaryUpdate();

	/*!*****************************************************************************
	Initialise variables and entities for the scene
	*******************************************************************************/
	void Init() {};

	/*!*****************************************************************************
	Update the scene and entity operations every game loop.
	*******************************************************************************/
	void Update() {};

	/*!*****************************************************************************
	Resets the scene variables. This should be called in the init function. 
	*******************************************************************************/
	void Exit() {};
	
	/*!*****************************************************************************
	Load scene with guid, using resource manager

	\param ResourceManager::GUID const&
	- GUID that references to the scene
	*******************************************************************************/
	void Load(ResourceManager::GUID const& _guid);

	/*!*****************************************************************************
	Unload scene using resource manager
	*******************************************************************************/
	void Unload();

	// Save scene to a scene file. If no scene file found, create one.
	// Return the guid for the game state to save it in their file
	// This should be called whenever someone wants to save a scene
	void Save(std::string = "");

	/*!*****************************************************************************
	Add Entity to scene
	*******************************************************************************/
	void AddEntity();

	/*!*****************************************************************************
	Remove entity from scene

	\param Entity const&
	- Entity to remove
	*******************************************************************************/
	void RemoveEntity(Entity const&);

	std::set<Entity> mEntities;			// Entities in the scene 
	bool mIsPause;											// Paused state of the scene
	ResourceManager::GUID mGuid;		// Scene's GUID
	std::string mName;
	Transform mCamera;
	int mLayer;
	int mOrder;

private:
};




