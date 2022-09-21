#pragma once
#include <deque>
#include <array>
#include <unordered_map>
#include <cstring>
#include <memory>

#include "ECS_items.h"

//-------------------------------------------------------------------------
// Entity Manager
// Manages the creation and destruction of entities, incharge of 
// distributing entities on request.
// Manages the system each entities can use.
//-------------------------------------------------------------------------
class EntityManager : public Singleton<EntityManager> {
public:
	EntityManager();

	// Creates and returns an entity
	Entity CreateEntity();
	// Frees an entity id for future usage
	void DestroyEntity(Entity);
	// Assign an signature to an entity
	void SetSignature(Entity, Signature);
	// Access the signature of an entity
	Signature GetSignature(Entity);

private:
	// A container of unused entity ids
	std::deque<Entity> mAvailableEntities;
	// A container of signatures with entities assigned to it
	std::array<Signature, MAX_ENTITIES> mSignatures;
	// Count of total living entities
	uint32_t mLivingEntityCount;

};


//-------------------------------------------------------------------------
// Component Array Manager
// Manages the creation of all component arrays and assign them an unique 
// ComponentType id.
// Controls the inflow and outflow of entities in all component arrays.
//-------------------------------------------------------------------------
class ComponentArrayManager : public Singleton<ComponentArrayManager> {
public:
	ComponentArrayManager();

	// Initialise and register a new component
	template<typename T> void RegisterComponent();
	// Access the ComponentType of a component array
	template<typename T> ComponentType GetComponentType();
	// Add an entity to a component array
	template<typename T> void AddComponent(Entity, T);
	// Remove an entity from a component array
	template<typename T> void RemoveComponent(Entity);
	// Access the component of an entity through the component array
	template<typename T> T& GetComponent(Entity);
	// Destroy all components of an entity in each respective component array
	void EntityDestroyed(Entity);

private:
	// Map of component name to ComponentType
	std::unordered_map<std::string, ComponentType> mComponentTypes;
	// Map of component name to component array
	std::unordered_map<std::string, std::shared_ptr<IComponentArray>> mComponentArrays;
	// Counting the amount of component, for assigning ComponentType to each component array
	ComponentType mNextComponentType;
	
	//Helper function
	template<typename T> std::shared_ptr<ComponentArray<T>> GetComponentArray();
};










