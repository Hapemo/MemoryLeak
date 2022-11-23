#pragma once

#include "ECS_tools.h"
#include "ScriptManager.h"
#include "ScriptComponent.h"

class PlayerMovementScript : public ScriptComponent {
private:
	std::string name{ "PlayerMovementScript" };
	float playerSpeed{ 10.f };
public:
	PlayerMovementScript() = default;
	~PlayerMovementScript() override = default;

	void StartScript(const Entity& _e) override;

	void UpdateScript(const Entity& _e) override;

	void EndScript(const Entity& _e) override;
};