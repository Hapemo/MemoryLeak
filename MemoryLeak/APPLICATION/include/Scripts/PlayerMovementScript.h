#pragma once

#include "ECS_tools.h"
#include "ScriptManager.h"
#include "ScriptComponent.h"

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
	PlayerMovementScript() = default;
	~PlayerMovementScript() override = default;

	void StartScript(const Entity& _e) override;

	void UpdateScript(const Entity& _e) override;

	void EndScript(const Entity& _e) override;
};