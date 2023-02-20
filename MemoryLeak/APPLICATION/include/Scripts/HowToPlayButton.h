/*!*****************************************************************************
\file HowToPlayButton.h
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 24-11-2022
\brief
The HowToPlayButton script opens the "How To Play" screen on button press.
*******************************************************************************/

#pragma once
#include "ECS_tools.h"
#include "ScriptManager.h"
#include "ScriptComponent.h"

class HowToPlayButton : public ScriptComponent {
private:
	std::string name = "HowToPlayButton";

public:
	HowToPlayButton() = default;
	~HowToPlayButton() override = default;

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
	Function will run on exit or when the entity is destroyed.
	*******************************************************************************/
	void Exit(Entity const& _e) override;

	/*!*****************************************************************************
	\brief
	Function will run when the gamestate of the entity exits.
	*******************************************************************************/
	void Dead(Entity const& _e) override;
};
