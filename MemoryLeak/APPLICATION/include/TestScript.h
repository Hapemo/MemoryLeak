#pragma once

#include "ECS_items.h"
#include "ScriptComponent.h"
#include "Logger.h"

class TestScript : public ScriptComponent {
public:
	static void StartScript(Entity* gob) {
		(void)gob;
		LOG_INFO("Test script starts works!!!");
	}

	static void UpdateScript(Entity* gob) {
		(void)gob;
		LOG_INFO("Test script updating works!!!");
	}

	static void EndScript(Entity* gob) {
		(void)gob;
		LOG_INFO("Test script end works!!!");
	}
};
