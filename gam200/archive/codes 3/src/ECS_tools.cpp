#include "ECS_tools.h"


Entity ECS::CreateEntity() { return Coordinator::GetInstance()->CreateEntity(); }

void ECS::DestroyEntity(Entity entity) { Coordinator::GetInstance()->DestroyEntity(entity); }

void ECS::DestroyAllEntities() { Coordinator::GetInstance()->DestroyAllEntities(); }

void ECS::DestroySomeEntites(const std::vector<Entity>& dontDestroy) { Coordinator::GetInstance()->DestroySomeEntites(dontDestroy); }











