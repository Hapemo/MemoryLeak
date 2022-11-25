#pragma once

#include "ECS_tools.h"
#include "ScriptManager.h"
#include "ScriptComponent.h"

class MoveMinimapScript : public ScriptComponent {
private:
	std::string name{ "MoveMinimapScript" };
	Scene* currScene;
	bool inited;
	Math::Vec2 originalTranslate;
	Math::Vec2 originalScale;

public:
	MoveMinimapScript() = default;
	~MoveMinimapScript() override = default;

	void StartScript(const Entity& _e) override;

	void UpdateScript(const Entity& _e) override;

	void EndScript(const Entity& _e) override;
};