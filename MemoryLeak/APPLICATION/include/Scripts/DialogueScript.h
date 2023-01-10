/*!*****************************************************************************
\file DialogueScript.h
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 23-11-2022
\brief
The DialogueScript handles the dialogue functionalities such as proceeding to
the next line of dialogue and the zooming in of the camera during the dialogue
scene.
*******************************************************************************/

#pragma once
#include "ECS_tools.h"
#include "ScriptManager.h"
#include "ScriptComponent.h"

class DialogueScript : public ScriptComponent {
private:
	std::string name = "DialogueScript";
	Math::Vec2 initialCamScale;
	Math::Vec2 targetCamScale;
	Math::Vec2 currCamScale;
	Scene* currScn;
	Transform* currCamera;
public:
	DialogueScript() = default;
	~DialogueScript() override = default;

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
