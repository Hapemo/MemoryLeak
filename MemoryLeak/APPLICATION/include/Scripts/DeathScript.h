/*!*****************************************************************************
\file DeathScript.cpp
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 25-11-2022
\brief
The DeathScript runs the player's death animation on the boat collides with
the enemy.

Press "CTRL+SHIFT+M" to toggle player invincible mode.
*******************************************************************************/

#pragma once
#include "ECS_tools.h"
#include "ScriptManager.h"
#include "ScriptComponent.h"

class DeathScript : public ScriptComponent {
private:
	std::string name = "DeathScript";
	Entity player;
	bool canDie = true;
	std::string prevTexture = "";
public:
	DeathScript() = default;
	~DeathScript() override = default;

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
