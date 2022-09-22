#pragma once

#include "ECS_systems.h"
#include "ECS_items.h"
#include "ECS_managers.h"

// This file is dangerous. It simplifies the typing needed to use Coordinator, but you MUST know
// how this Coordinator works to use the functions here properly.
// If you want to understand what these function does, refer to class Coordinate, all these function calls the functions there.

namespace ECS {
	// From EntityID Manager
	Entity CreateEntity();

	void DestroyEntity(EntityID entity);

	// From Component Manager
	template<typename T>
	void RegisterComponent() { Coordinator::GetInstance()->RegisterComponent<T>(); }

	template<typename T>
	void AddComponent(EntityID entity, T component) { Coordinator::GetInstance()->AddComponent<T>(entity, component); }
	
	template<typename T>
	void RemoveComponent(EntityID entity) { Coordinator::GetInstance()->RemoveComponent(entity); }

	template<typename T>
	T& GetComponent(EntityID entity) { return Coordinator::GetInstance()->GetComponent<T>(entity); }

	template<typename T>
	ComponentType GetComponentType() { return Coordinator::GetInstance()->GetComponentType<T>(); }

	// From System Manager
	template<typename T>
	std::shared_ptr<T> RegisterSystem() { return Coordinator::GetInstance()->RegisterSystem<T>(); }

	template<typename T>
	void SetSystemSignature(const Signature& signature) { return Coordinator::GetInstance()->SetSystemSignature<T>(signature); }

	// Extra
	void DestroyAllEntities();

	void DestroySomeEntites(const std::vector<EntityID>& dontDestroy);
}










