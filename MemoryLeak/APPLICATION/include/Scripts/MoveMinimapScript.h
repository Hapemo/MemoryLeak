/*!*****************************************************************************
\file	MoveMinimapScript.h
\author Kew Yu Jun
\par	DP email: k.yujun@digipen.edu
\par	Course: GAM200
\par	Group: Memory Leak Studios
\date	26-11-2022
\brief  This file contains the declaration of the MoveMinimapScript class
		that defines the game logic used to move the minimap
*******************************************************************************/
#pragma once

#include "ECS_tools.h"
#include "ScriptManager.h"
#include "ScriptComponent.h"

/*!*****************************************************************************
\brief MoveMinimapScript class that handles movement of the minimap
*******************************************************************************/
class MoveMinimapScript : public ScriptComponent {
private:
	std::string name{ "MoveMinimapScript" };
	Scene* currScene;
	bool inited;
	Math::Vec2 originalTranslate;
	Math::Vec2 originalScale;

public:
	/*!*****************************************************************************
	\brief
	Default constructor
	*******************************************************************************/
	MoveMinimapScript() = default;
	/*!*****************************************************************************
	\brief
	Default destructor.
	*******************************************************************************/
	~MoveMinimapScript() override = default;
	/*!*****************************************************************************
	\brief
	Function that contains logic to run on script start
	\param const Entity &
	A reference to read-only entity to update
	\return void
	NULL
	*******************************************************************************/
	void StartScript(const Entity& _e) override;
	/*!*****************************************************************************
	\brief
	Function that contains logic to run during each update frame
	\param const Entity &
	A reference to read-only entity to update
	\return void
	NULL
	*******************************************************************************/
	void UpdateScript(const Entity& _e) override;
	/*!*****************************************************************************
	\brief
	Function that contains logic to run on script end
	\param const Entity &
	A reference to read-only entity to update
	\return void
	NULL
	*******************************************************************************/
	void EndScript(const Entity& _e) override;
};