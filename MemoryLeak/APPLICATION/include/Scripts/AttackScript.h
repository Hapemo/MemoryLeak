/*!*****************************************************************************
\file AttackScript.cpp
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 25-11-2022
\brief
The AttackScript handles the detection of when the player is nearby the enemy,
causing the enemy's rising out of the water animation to run and then run the
attacking animation.
*******************************************************************************/

#pragma once
#include "ECS_tools.h"
#include "ScriptManager.h"
#include "ScriptComponent.h"

class AttackScript : public ScriptComponent {
private:
	std::string name = "AttackScript";
	Entity enemy;
	Entity player;
	size_t visible = 0;
public:
	AttackScript() = default;
	~AttackScript() override = default;

	/*!*****************************************************************************
	\brief
	Function will run on initialisation of the entity.
	*******************************************************************************/
	void StartScript(Entity const& gob) override;

	/*!*****************************************************************************
	\brief
	Function will run on every update while the entity is active.
	*******************************************************************************/
	void UpdateScript(Entity const& gob) override;

	/*!*****************************************************************************
	\brief
	Function will run on exit or when the entity is destroyed.
	*******************************************************************************/
	void EndScript(Entity const& gob) override;
};
