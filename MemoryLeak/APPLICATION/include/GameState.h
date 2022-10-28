/*!*****************************************************************************
\file GameState.h
\author Jazz Teoh Yu Jue
\par DP email: j.teoh\@digipen.edu
\par Group: Memory Leak Studios
\date 24-09-2022
\brief
Game state base class, contains Load, Init, Update, Draw, Free and Unload
functions.

How to make a gamestate?

1. Make a class for your gamestate, inherited from class GameState
2. Declare and define all the virtual functions
3. In GameStateManager.h > class enum GS, make a new enum for your game state
4. In GameStateManager's Init(), make a new line "GS_list.insert(GS_pair(<GS>, 
	 new <GameState>));" where <GS> is your game state's enum and <GameState> is 
	 your game state class
*******************************************************************************/
#pragma once

#include "pch.h"
#include "ECS_items.h"
#include "ResourceManager.h"
#include "Scene.h"

class Scene;
class ResourceManager;
struct Entity;

class GameState {
public:
	GameState() {};
	virtual ~GameState() {};

  /*!*****************************************************************************
   \brief
   Load any necessary resources in for the game state
  *******************************************************************************/
	virtual void Load() = 0;

	/*!*****************************************************************************
	 \brief
	 Initialise any values or resources for the game state
	 Any other initialising functions can be called here too
	*******************************************************************************/
	virtual void Init() = 0;

	/*!*****************************************************************************
	 \brief
	 Update the game state. This function will be called every game loop. Between 
	 First and Second Update from Application
	*******************************************************************************/
	virtual void Update() = 0;

	/*!*****************************************************************************
	 \brief
	 Draw the graphics for the game state.
	*******************************************************************************/
	virtual void Draw() = 0;

	/*!*****************************************************************************
	 \brief
	 Free any data that are not needed for the game state anymore, such as variables
	 and pointers.
	*******************************************************************************/
	virtual void Free() = 0;

	/*!*****************************************************************************
	 \brief
	 Unload any resources used in the game state, such as art assets and heap memory
	 data
	*******************************************************************************/
	virtual void Unload() = 0;

protected:
	void LoadWithGUID(ResourceManager::GUID const&);
	void UnloadWithGUID();

	std::vector<Scene*> mScenes;
	std::set<Entity> mEntities;
	ResourceManager::GUID mGuid;
	//std::vector<ResourceManager::GUID> mResources;

};
