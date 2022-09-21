#include "ECS_tools.h"


Entity ECS::CreateEntity() { 
	return Entity{ Coordinator::GetInstance()->CreateEntity() };
}

void ECS::DestroyEntity(EntityID entity) { Coordinator::GetInstance()->DestroyEntity(entity); }

void ECS::DestroyAllEntities() { Coordinator::GetInstance()->DestroyAllEntities(); }

void ECS::DestroySomeEntites(const std::vector<EntityID>& dontDestroy) { Coordinator::GetInstance()->DestroySomeEntites(dontDestroy); }











