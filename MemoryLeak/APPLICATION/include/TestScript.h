#pragma once

#include "ECS_items.h"
#include "ScriptComponent.h"
#include "Logger.h"

class TestScript : public ScriptComponent {
public:
	static void StartScript(Entity const& gob) {
		(void)gob;
		LOG_INFO("Test script starts works!!!");
	}

	static void UpdateScript(Entity const& gob) {
		(void)gob;
		LOG_INFO("Test script updating works!!!");
	}

	static void EndScript(Entity const& gob) {
		(void)gob;
		LOG_INFO("Test script end works!!!");
	}
};
