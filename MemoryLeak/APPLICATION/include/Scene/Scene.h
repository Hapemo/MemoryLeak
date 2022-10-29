/*!*****************************************************************************
\file Scene.h
\author Jazz Teoh Yu Jue
\par DP email: j.teoh\@digipen.edu
\par Group: Memory Leak Studios
\date 24-09-2022
\brief
Scene base class. Each game state can have multiple scenes which encapsulates
a group of entities and operates on them.
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
	~Scene();
	/*!*****************************************************************************
	 \brief
	 Set the scene's pause status

	 \param bool
	 True to pause the scene's update loop, otherwise false
	*******************************************************************************/
	void Pause(bool);

	/*!*****************************************************************************
	 \brief
	 Main update loop of the game that dismisses all other updates if game is paused
	*******************************************************************************/
	void PrimaryUpdate();
	//void Load();
	//void Save();

	/*!*****************************************************************************
	 \brief
	 Initialise variables and entities for the scene
	*******************************************************************************/
	void Init() {};

	/*!*****************************************************************************
	 \brief
	 Update the scene and entity operations every game loop.
	*******************************************************************************/
	void Update() {};

	/*!*****************************************************************************
	 \brief
	 Resets the scene variables. This should be called in the init function. 
	*******************************************************************************/
	void Exit() {};
	
	// Load with guid
	void Load(ResourceManager::GUID const& _guid);

	void Unload();

	void AddEntity();

	void RemoveEntity(Entity const&);

	std::set<Entity> mEntities;
	bool pause; // TODO can change this to IsActive
	ResourceManager::GUID mGuid;

protected:

private:
};




