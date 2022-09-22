#pragma once
#include "pch.h"

#include "ECS_components.h"
#include "ECS_items.h"
#include "ECS_managers.h"

class LifespanManager : public System {
public:
	// Update the lifespan of entity
	void Update(float dt);
	void Reset(std::set<Entity> entities, float newLimit = 0);

private:
	// Nothing for now 
};

class BenchmarkManager : public System {
public:
	void MultiSqrtTest();
	void StartTime();
	double RecordTime();

private:
	double startTime = 0;
};

















