
#include "ECS_systems.h"

void LifespanManager::Update(float dt) {
	for (Entity e : mEntities) {
		bool& isActive{ e.GetComponent<IsActive>().isActive };
		if (!isActive) continue;

		Lifespan& lifespan{ e.GetComponent<Lifespan>() };
		lifespan.lifetime += dt;
		if (lifespan.lifetime >= lifespan.limit) {
			lifespan.lifetime = lifespan.limit;
			isActive = false;
		}
	}
}

void LifespanManager::Reset(std::set<Entity> entities, float newLimit) {
	for (Entity e : entities) {
		e.GetComponent<IsActive>().isActive = true;

		Lifespan& lifespan{ e.GetComponent<Lifespan>() };
		lifespan.lifetime = 0;
		if (newLimit) lifespan.limit = newLimit;
	}
}









