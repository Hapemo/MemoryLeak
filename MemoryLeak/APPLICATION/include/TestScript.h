#pragma once
#include "ECS_items.h"
#include "ScriptManager.h"
#include "Logger.h"

class TestScript {
public:
	TestScript(){
		m_behaviour = new ScriptManager("TestScript", StartScript, UpdateScript, EndScript);
	}
	~TestScript() { delete m_behaviour; }

	static void StartScript(Entity* gob) {
		(void)gob;
		LOG_INFO("Script starts works!!!");
	}

	static void UpdateScript(Entity* gob) {
		(void)gob;
		LOG_INFO("Script updating works!!!");
	}

	static void EndScript(Entity* gob) {
		(void)gob;
		LOG_INFO("Script end works!!!");
	}

private:
	ScriptManager* m_behaviour;
};
