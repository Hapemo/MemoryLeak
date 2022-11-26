#pragma once

#include "ECS_tools.h"
#include "ScriptManager.h"
#include "ScriptComponent.h"

class PlayerMovementScript : public ScriptComponent {
private:
	std::string name{ "PlayerMovementScript" };
	float playerNormalSpeed{ 500.f };
	float playerSpeed{ playerNormalSpeed };
	bool dialogueActivated = false;
	bool inited = false;
	bool canDie = true;
	float speedCheatMultiplier{ 3.f };
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