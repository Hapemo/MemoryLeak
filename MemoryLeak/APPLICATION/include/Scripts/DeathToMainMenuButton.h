/*!*****************************************************************************
\file DeathToMainMenuButton.h
\author Jazz Teoh Yu Jue
\par DP email: j.teoh\@digipen.edu
\par Course: GAM250
\par Group: Memory Leak Studios
\date 01-02-2023
\brief
The BackToMainMenuButton script returns the scene to the main menu on button press.
*******************************************************************************/

#pragma once
#include "ECS_tools.h"
#include "ScriptManager.h"
#include "ScriptComponent.h"

class DeathToMainMenuButton : public ScriptComponent {
private:
	std::string name = "DeathToMainMenuButton";

public:
	DeathToMainMenuButton() = default;
	~DeathToMainMenuButton() override = default;

	/*!*****************************************************************************
	\brief
	Function will run when the gamestate of the entity is activated.
	*******************************************************************************/
	void Alive(Entity const& _e) override;

	/*!*****************************************************************************
	\brief
	Function will run on initialisation of the entity.
	*******************************************************************************/
	void Init(Entity const& _e) override;

	/*!*****************************************************************************
	\brief
	Function will run on every update while the entity is active.
	*******************************************************************************/
	void Update(Entity const& _e) override;

	/*!*****************************************************************************
	\brief
	Fixed update script to run on fixed delta time.
	*******************************************************************************/
	void FixedUpdate(Entity const& _e) override;

	/*!*****************************************************************************
	\brief
	Function will run on exit or when the entity is destroyed.
	*******************************************************************************/
	void Exit(Entity const& _e) override;

	/*!*****************************************************************************
	\brief
	Function will run when the gamestate of the entity exits.
	*******************************************************************************/
	void Dead(Entity const& _e) override;
};
