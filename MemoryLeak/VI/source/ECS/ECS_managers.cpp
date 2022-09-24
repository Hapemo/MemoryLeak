#include "ECS_managers.h"

// This file only contains this function to support forward declaration of function for ECS_items.h > struct Entity
void Entity::Destroy() const { Coordinator::GetInstance()->DestroyEntity(id); }

