#pragma once
#include <memory>
#include "ECS_tools.h"

extern std::shared_ptr<LifespanManager> lifespanManager;

class ECSManager {
private:
	static void RegisterLifespanManager();
	static void RegisterAllSystems();
	static void RegisterAllComponents();

public:
	static void ECS_init();
};










