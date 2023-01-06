/*!*****************************************************************************
\file ExitConfirmationButton.h
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 27-11-2022
\brief
The ExitConfirmationButton script activates the exit game confirmation screen
on button press.
*******************************************************************************/

#pragma once
#include "ECS_tools.h"
#include "ScriptManager.h"
#include "ScriptComponent.h"

class ExitConfirmationButton : public ScriptComponent {
private:
	std::string name = "BackToMainMenuButton";

public:
	ExitConfirmationButton() = default;
	~ExitConfirmationButton() override = default;

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
