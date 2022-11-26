/*!*****************************************************************************
\file	PlayerMovementScript.h
\author Lee Hsien Wei, Joachim
\par	DP email: l.hsienweijoachim@digipen.edu
\par	Course: GAM200
\par	Group: Memory Leak Studios
\date	26-11-2022
\brief  This file contains the declaration of the PlayerMovementScript class
		that defines the game logic used to move the player
*******************************************************************************/
#pragma once

// -----------------------------
// Include files
// -----------------------------
#include "ECS_tools.h"
#include "ScriptManager.h"
#include "ScriptComponent.h"

/*!*****************************************************************************
\brief PlayerMovementScript class that handles game logic for player movement
*******************************************************************************/
class PlayerMovementScript : public ScriptComponent {
private:
	std::string name{ "PlayerMovementScript" };
	float playerSpeed{ 500.f };
	bool dialogueActivated = false;
	bool dialogueZoomOut = false;
	bool inited = false;
	bool canDie = true;
	float speedCheatMultiplier{ 2.5f };
	Entity dialogueText;
	Entity littleGirl;
	Entity water;
	Entity enemy;
	Scene* currScene;
	Math::Vec2 initialCamScale;

public:
	/*!*****************************************************************************
	\brief
	Default constructor
	*******************************************************************************/
	PlayerMovementScript() = default;

	/*!*****************************************************************************
	\brief
	Default destructor.
	*******************************************************************************/
	~PlayerMovementScript() override = default;

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