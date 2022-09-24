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

class Scene {
public:
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
	virtual void Init() = 0;

	/*!*****************************************************************************
	 \brief
	 Update the scene and entity operations every game loop.
	*******************************************************************************/
	virtual void Update() = 0;

	/*!*****************************************************************************
	 \brief
	 Resets the scene variables. This should be called in the init function. 
	*******************************************************************************/
	virtual void Reset() = 0;

	/*!*****************************************************************************
	 \brief
	 Clear all entities and free all scene data. Should be called before exiting
	 the scene.
	*******************************************************************************/
	virtual void Clear() = 0;

protected:
	std::set<Entity> mEntities;

private:
	bool pause;
};




