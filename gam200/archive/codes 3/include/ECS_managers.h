#pragma once
#include <deque>
#include <array>
#include <unordered_map>
#include <cstring>
#include <memory>
#include <cassert>

#include "ECS_items.h"

//-------------------------------------------------------------------------
// Entity Manager
// Manages the creation and destruction of entities, incharge of 
// distributing entities on request.
// Manages the system each entities can use.
//-------------------------------------------------------------------------
class EntityManager {
public:
	EntityManager() :
		mAvailableEntities(), mSignatures(), mLivingEntityCount()
	{
		mAvailableEntities.resize(MAX_ENTITIES);
		for (size_t i = 0; i < MAX_ENTITIES; ++i)
			mAvailableEntities[i] = i;

		CreateEntity(); // Entity 0 shall be reserved for null
	}

	// Creates and returns an entity
	Entity CreateEntity() {
		assert(mLivingEntityCount < MAX_ENTITIES && "Too many instances of entities.");
		Entity id = mAvailableEntities.front();
		mAvailableEntities.pop_front();
		++mLivingEntityCount;
		return id;
	}
	// Frees an entity id for future usage
	void DestroyEntity(Entity entity) {
		assert(entity < MAX_ENTITIES && "Entity out of range.");

		mSignatures[entity].reset();
		mAvailableEntities.push_back(entity);
		--mLivingEntityCount;
	}
	// Assign an signature to an entity
	void SetSignature(Entity entity, Signature signature) {
		assert(entity < MAX_ENTITIES && "Entity out of range.");

		mSignatures[entity] = signature;
	}
	// Access the signature of an entity
	Signature GetSignature(Entity entity) {
		assert(entity < MAX_ENTITIES && "Entity out of range.");

		return mSignatures[entity];
	}

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
class ComponentArrayManager {
public:
	ComponentArrayManager() :
		mComponentTypes(), mComponentArrays(), mNextComponentType()
	{}

	// Initialise and register a new component
	template<typename T>
	void RegisterComponent() {
		std::string typeName{ typeid(T).name() };

		assert(mComponentTypes.find(typeName) == mComponentTypes.end() && "Attempted to register component more than once.");
		mComponentTypes.insert({ typeName, mNextComponentType++ });
		mComponentArrays.insert({ typeName, std::make_shared<ComponentArray<T>>() });
	}
	// Access the ComponentType of a component array
	template<typename T>
	ComponentType GetComponentType() {
		std::string typeName{ typeid(T).name() };

		assert(mComponentTypes.find(typeName) != mComponentTypes.end() && "Attempted to access unregistered component.");
		return mComponentTypes[typeName];
	}
	// Add an entity to a component array
	template<typename T>
	void AddComponent(Entity entity, T component) {
		GetComponentArray<T>()->InsertData(entity, component);
	}
	// Remove an entity from a component array
	template<typename T>
	void RemoveComponent(Entity entity) {
		GetComponentArray<T>()->RemoveData(entity);
	}
	// Access the component of an entity through the component array
	template<typename T>
	T& GetComponent(Entity entity) {
		return GetComponentArray<T>()->GetData(entity);
	}
	// Destroy all components of an entity in each respective component array
	void EntityDestroyed(Entity entity) {
		for (auto const& [name, component] : mComponentArrays)
			component->RemoveData(entity);
	}

private:
	// Map of component name to ComponentType
	std::unordered_map<std::string, ComponentType> mComponentTypes;
	// Map of component name to component array
	std::unordered_map<std::string, std::shared_ptr<IComponentArray>> mComponentArrays;
	// Counting the amount of component, for assigning ComponentType to each component array
	ComponentType mNextComponentType;
	
	//Helper function
	template<typename T>
	std::shared_ptr<ComponentArray<T>> GetComponentArray() {
		std::string typeName{ typeid(T).name()};

		assert(mComponentTypes.find(typeName) != mComponentTypes.end() && "Attempted to access unregistered component.");
		return std::static_pointer_cast<ComponentArray<T>>(mComponentArrays[typeName]);
	}
};


//-------------------------------------------------------------------------
// System Manager
// Manages the creation of all component arrays and assign them an unique 
// ComponentType id.
// Controls the inflow and outflow of entities in all component arrays.
//-------------------------------------------------------------------------
class SystemManager {
public:
	SystemManager() :
		mSignatures(), mSystems()
	{}

	// Initialises system and register it into SystemManager
	template<typename T>
	std::shared_ptr<T> RegisterSystem() {
		std::string typeName{ typeid(T).name() };

		assert(mSystems.find(typeName) == mSystems.end() && "Attempted to register system more than once.");

		auto system = std::make_shared<T>();
		mSystems.insert({ typeName, system });
		return system;
	}

	// Assign a signature to a system
	template<typename T>
	void SetSignature(Signature signature) {
		std::string typeName{ typeid(T).name() };

		assert(mSystems.find(typeName) != mSystems.end() && "Attempted to set signature to non-existance System.");

		mSignatures.insert({ typeName, signature });
	}

	// Remove a destroyed entity from all system's set
	void EntityDestroyed(Entity entity) {
		for (auto const&[name, system] : mSystems)
			system->mEntities.erase(entity);
	}

	// Notify all systems that an entity's signature has changed
	// Remove or add it to the appropriate system's set
	void EntitySignatureChanged(Entity entity, Signature entitySignature) {
		for (auto const& [name, system] : mSystems) {
			Signature systemSignature{ mSignatures[name] };

			if ((entitySignature & systemSignature) == systemSignature)
				system->mEntities.insert(entity);
			else system->mEntities.erase(entity);
		}
	}

private:
	// Map system's name to their unique signature
	std::unordered_map<std::string, Signature> mSignatures;
	// Map system's name to a pointer to the system itself
	std::unordered_map<std::string, std::shared_ptr<System>> mSystems;

};



//-------------------------------------------------------------------------
// Coordinator
// The main Coordinator system, combination of Entity, Component Array and System managers
//-------------------------------------------------------------------------
class Coordinator : public Singleton<Coordinator> {
public:
	Coordinator() {
		mEntityManager = std::make_unique<EntityManager>();
		mComponentArrayManager = std::make_unique<ComponentArrayManager>();
		mSystemManager = std::make_unique<SystemManager>();
	}

	// From Entity Manager
	Entity CreateEntity() { return mEntityManager->CreateEntity(); }

	void DestroyEntity(Entity entity) {
		mEntityManager->DestroyEntity(entity);
		mComponentArrayManager->EntityDestroyed(entity);
		mSystemManager->EntityDestroyed(entity);
	}

	// From Component Manager
	template<typename T>
	void RegisterComponent() { mComponentArrayManager->RegisterComponent<T>(); }

	template<typename T>
	void AddComponent(Entity entity, T component) {
		mComponentArrayManager->AddComponent<T>(entity, component);

		Signature signature = mEntityManager->GetSignature(entity);
		signature.set(mComponentArrayManager->GetComponentType<T>(), true);
		mEntityManager->SetSignature(entity, signature);
		mSystemManager->EntitySignatureChanged(entity, signature);
	};

	template<typename T>
	void RemoveComponent(Entity entity) {
		mComponentArrayManager->RemoveComponent<T>(entity);
		Signature signature = mEntityManager->GetSignature(entity);
		signature.set(mComponentArrayManager->GetComponentType<T>(), false);
		mEntityManager->SetSignature(entity, signature);
		mSystemManager->EntitySignatureChanged(entity, signature);
	}

	template<typename T>
	T& GetComponent(Entity entity) { return mComponentArrayManager->GetComponent<T>(entity); }

	template<typename T>
	ComponentType GetComponentType() { return mComponentArrayManager->GetComponentType<T>(); }

	// From System Manager
	template<typename T>
	std::shared_ptr<T> RegisterSystem() { return mSystemManager->RegisterSystem<T>(); }

	template<typename T>
	void SetSystemSignature(const Signature& signature) { return mSystemManager->SetSignature<T>(signature); }

	// Extra
	void DestroyAllEntities() {
		for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
			if (mEntityManager->GetSignature(entity) != 0)
				DestroyEntity(entity);
	}

	void DestroySomeEntites(const std::vector<Entity>& dontDestroy) {
		for (Entity entity = 0; entity < MAX_ENTITIES; ++entity) {
			if (mEntityManager->GetSignature(entity) != 0)
				// Skip those in dontDestroy
				if (std::find(dontDestroy.begin(), dontDestroy.end(), entity) == dontDestroy.end())
					DestroyEntity(entity);
		}
	}

private:
	std::unique_ptr<EntityManager> mEntityManager;
	std::unique_ptr<ComponentArrayManager> mComponentArrayManager;
	std::unique_ptr<SystemManager> mSystemManager;
};



//======================================================================
// Function Definitions
//======================================================================

//-------------------------------------------------------------------------
// Entity Manager
//-------------------------------------------------------------------------











//-------------------------------------------------------------------------
// Component Array Manager
//-------------------------------------------------------------------------

















//-------------------------------------------------------------------------
// System Manager
//-------------------------------------------------------------------------










//-------------------------------------------------------------------------
// Coordinator
//-------------------------------------------------------------------------

















