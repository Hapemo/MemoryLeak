

#include "ECSManager.h"

std::shared_ptr<LifespanManager> lifespanManager{ nullptr };

void ECSManager::RegisterLifespanManager() {
	Signature signature;
	signature.set(ECS::GetComponentType<Lifespan>());
	signature.set(ECS::GetComponentType<IsActive>());

	lifespanManager = ECS::RegisterSystem<LifespanManager>();
	ECS::SetSystemSignature<LifespanManager>(signature);
}



void ECSManager::RegisterAllSystems() {
	RegisterLifespanManager();
	// More to come
}

void ECSManager::RegisterAllComponents() {
	ECS::RegisterComponent<IsActive>();
	ECS::RegisterComponent<Lifespan>();
	// More to come
}

void ECSManager::ECS_init() {
	RegisterAllComponents();
	RegisterAllSystems();
}









