

#include "ECS_systems.h"
#include "ECS_components.h"

//-------------------------------------------------------------
// Lifespan Manager
//-------------------------------------------------------------
void LifespanManager::Update(float dt) {
	for (Entity e : mEntities) {
		bool& isActive{ Coordinator::GetInstance()->GetComponent<IsActive>(e).isActive };
		if (!isActive) continue;

		Lifespan& lifespan{ Coordinator::GetInstance()->GetComponent<Lifespan>(e) };
		lifespan.lifetime += dt;
		if (lifespan.lifetime >= lifespan.limit) {
			lifespan.lifetime = lifespan.limit;
			isActive = false;
		}
	}
}

void LifespanManager::Reset(std::set<Entity> entities, float newLimit) {
	for (Entity e : entities) {
		Coordinator::GetInstance()->GetComponent<IsActive>(e).isActive = true;

		Lifespan& lifespan{ Coordinator::GetInstance()->GetComponent<Lifespan>(e) };
		lifespan.lifetime = 0;
		if (newLimit) lifespan.limit = newLimit;
	}
}

