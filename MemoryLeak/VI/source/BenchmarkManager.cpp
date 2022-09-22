
#include "pch.h"
#include "ECS_systems.h"

void BenchmarkManager::MultiSqrtTest() {
	for (Entity e : mEntities) {
		double temp{ sqrt(e.id) };
		Lifespan& lifespan{ e.GetComponent<Lifespan>() };
		double uselessLifespan{ temp * lifespan.lifetime };
		lifespan.limit = (float)(sqrt((double)lifespan.limit + temp) * uselessLifespan);
		(float)(sqrt((double)234 + temp) * 235);
	}
}

void BenchmarkManager::StartTime() {
	startTime = glfwGetTime();
}

double BenchmarkManager::RecordTime() {
	return glfwGetTime() - startTime;
}



