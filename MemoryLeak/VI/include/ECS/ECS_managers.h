/*!*****************************************************************************
\file ECS_managers.h
\author Jazz Teoh Yu Jue
\par DP email: j.teoh\@digipen.edu
\par Group: Memory Leak Studios
\date 24-09-2022
\brief
This file contains 4 different classes that makes up the whole ECS system.
Entity Manager - manages all the entities
ComponentArrayManager - Manages all the components
SystemManager - Manages all the system in the game
Coordinator - Encapsulation of all 3 systems using smart pointers. Anyone who
							wishes to use the ECS should go through Cooridnator
*******************************************************************************/
#pragma once
#include "pch.h"

#include "ECS_items.h"

//-------------------------------------------------------------------------
// EntityID Manager
// Manages the creation and destruction of entities, incharge of 
// distributing entities on request.
// Manages the system each entities can use.
//-------------------------------------------------------------------------
class EntityManager {
public:
	/*!*****************************************************************************
	Default constructor of EntityManager. Initialises all entity IDs and reserve the
	0th entity to be null.
	*******************************************************************************/
	EntityManager() :
		mAvailableEntities(), mSignatures(), mLivingEntityCount()
	{
		mAvailableEntities.resize(MAX_ENTITIES);
		for (size_t i = 0; i < MAX_ENTITIES; ++i)
			mAvailableEntities[i] = static_cast<std::uint32_t>(i);

		CreateEntity(); // EntityID 0 shall be reserved for null
	}

	/*!*****************************************************************************
	Creates and returns an entity.
	*******************************************************************************/
	EntityID CreateEntity() {
		assert(mLivingEntityCount < MAX_ENTITIES && "Too many instances of entities.");
		EntityID id = mAvailableEntities.front();
		mAvailableEntities.pop_front();
		++mLivingEntityCount;
		return id;
	}

	/*!*****************************************************************************
	Frees an entity id for future usage
	
	\param EntityID
	- ID of an entity
	*******************************************************************************/
	void DestroyEntity(EntityID entity) {
		assert(entity < MAX_ENTITIES && "EntityID out of range.");

		mSignatures[entity].reset();
		mAvailableEntities.push_back(entity);
		--mLivingEntityCount;
	}

	/*!*****************************************************************************
	Assign an signature to an entity
	
	\param EntityID
	- ID of an entity

	\param Signature
	- Signature of an entity
	*******************************************************************************/
	void SetSignature(EntityID entity, Signature signature) {
		assert(entity < MAX_ENTITIES && "EntityID out of range.");

		mSignatures[entity] = signature;
	}

	/*!*****************************************************************************
	Access the signature of an entity
	
	\param EntityID
	- ID of an entity
	*******************************************************************************/
	Signature GetSignature(EntityID entity) {
		assert(entity < MAX_ENTITIES && "EntityID out of range.");

		return mSignatures[entity];
	}

private:
	// A container of unused entity ids
	std::deque<EntityID> mAvailableEntities;
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

	/*!*****************************************************************************
	Initialise and register a new component
	*******************************************************************************/
	template<typename T>
	void RegisterComponent() {
		std::string typeName{ typeid(T).name() };

		assert(mComponentTypes.find(typeName) == mComponentTypes.end() && "Attempted to register component more than once.");
		mComponentTypes.insert({ typeName, mNextComponentType++ });
		mComponentArrays.insert({ typeName, std::make_shared<ComponentArray<T>>() });
	}
	
	/*!*****************************************************************************
	Access the ComponentType, which is ID, of a component array

	\return ComponentType
	- Component Type of a component
	*******************************************************************************/
	template<typename T>
	ComponentType GetComponentType() {
		std::string typeName{ typeid(T).name() };

		assert(mComponentTypes.find(typeName) != mComponentTypes.end() && "Attempted to access unregistered component.");
		return mComponentTypes[typeName];
	}
	
	/*!*****************************************************************************
	Add an entity to a component array

	\param EntityID
	- ID of an entity

	\param T
	- Component data to add to entity
	*******************************************************************************/
	template<typename T>
	void AddComponent(EntityID entity, T component) {
		GetComponentArray<T>()->InsertData(entity, component);
	}

	/*!*****************************************************************************
	Remove an entity from a component array

	\param EntityID
	- ID of an entity
	*******************************************************************************/
	template<typename T>
	void RemoveComponent(EntityID entity) {
		GetComponentArray<T>()->RemoveData(entity);
	}
	
	/*!*****************************************************************************
	Get component data of an entity

	\param EntityID
	- ID of an entity
	*******************************************************************************/
	template<typename T>
	T& GetComponent(EntityID entity) {
		return GetComponentArray<T>()->GetData(entity);
	}
	
	/*!*****************************************************************************
	Destroy all components of an entity in each respective component array

	\param EntityID
	- ID of an entity
	*******************************************************************************/
	void EntityDestroyed(EntityID entity) {
		for (auto const& [name, component] : mComponentArrays) {
			if (!component->HasEntity(entity)) continue;
			
			component->RemoveData(entity);
		}
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

	/*!*****************************************************************************
	Initialises system and register it into SystemManager

	\return std::shared_ptr<T>
	- Pointer to templated ComponentArray
	*******************************************************************************/
	template<typename T>
	std::shared_ptr<T> RegisterSystem() {
		std::string typeName{ typeid(T).name() };

		assert(mSystems.find(typeName) == mSystems.end() && "Attempted to register system more than once.");

		auto system = std::make_shared<T>();
		mSystems.insert({ typeName, system });
		return system;
	}
 
	/*!*****************************************************************************
	Assign a signature to a system

	\param Signature
	- Signature of system
	*******************************************************************************/
	template<typename T>
	void SetSignature(Signature signature) {
		std::string typeName{ typeid(T).name() };

		assert(mSystems.find(typeName) != mSystems.end() && "Attempted to set signature to non-existance System.");

		mSignatures.insert({ typeName, signature });
	}

	/*!*****************************************************************************
	Remove a destroyed entity from all system's set

	\param EntityID
	- ID of an entity
	*******************************************************************************/
	void EntityDestroyed(EntityID entity) {
		for (auto const&[name, system] : mSystems)
			system->mEntities.erase(Entity{ entity });
	}
 
	/*!*****************************************************************************
	Notify all systems that an entity's signature has changed.
	Remove or add it to the appropriate system's set

	\param EntityID
	- ID of an entity

	\param Signature
	- New signature of entity
	*******************************************************************************/
	void EntitySignatureChanged(EntityID entity, Signature entitySignature) {
		for (auto const& [name, system] : mSystems) {
			Signature systemSignature{ mSignatures[name] };

			if ((entitySignature & systemSignature) == systemSignature)
				system->mEntities.insert(Entity{ entity });
			else system->mEntities.erase(Entity{ entity });
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
// The main Coordinator system, combination of EntityID, Component Array and System managers
//-------------------------------------------------------------------------
class Coordinator : public Singleton<Coordinator> {
public:
	/*!*****************************************************************************
	Initialise EntityManager, ComponentArrayManager and SystemManager.
	*******************************************************************************/
	Coordinator() {
		mEntityManager = std::make_unique<EntityManager>();
		mComponentArrayManager = std::make_unique<ComponentArrayManager>();
		mSystemManager = std::make_unique<SystemManager>();
	}

	// From EntityID Manager
	/*!*****************************************************************************
	Create an entity

	\param EntityID
	- ID of newly created entity
	*******************************************************************************/
	EntityID CreateEntity() { return mEntityManager->CreateEntity(); }

	/*!*****************************************************************************
	Destroy entity from all ECS managers

	\param EntityID
	- ID of entity
	*******************************************************************************/
	void DestroyEntity(EntityID entity) {
		mEntityManager->DestroyEntity(entity);
		mComponentArrayManager->EntityDestroyed(entity);
		mSystemManager->EntityDestroyed(entity);
	}

	// From Component Manager
	/*!*****************************************************************************
	Register new component to ECS
	*******************************************************************************/
	template<typename T>
	void RegisterComponent() { mComponentArrayManager->RegisterComponent<T>(); }

	/*!*****************************************************************************
	Add a component to entity
	
	\param EntityID
	- ID of an Entity

	\param T
	- Component data to add into entity
	*******************************************************************************/
	template<typename T>
	void AddComponent(EntityID entity, T component) {
		mComponentArrayManager->AddComponent<T>(entity, component);

		Signature signature = mEntityManager->GetSignature(entity);
		signature.set(mComponentArrayManager->GetComponentType<T>(), true);
		mEntityManager->SetSignature(entity, signature);
		mSystemManager->EntitySignatureChanged(entity, signature);
	};

	/*!*****************************************************************************
	Remove a component from an entity
	
	\param EntityID
	- ID of an Entity
	*******************************************************************************/
	template<typename T>
	void RemoveComponent(EntityID entity) {
		mComponentArrayManager->RemoveComponent<T>(entity);
		Signature signature = mEntityManager->GetSignature(entity);
		signature.set(mComponentArrayManager->GetComponentType<T>(), false);
		mEntityManager->SetSignature(entity, signature);
		mSystemManager->EntitySignatureChanged(entity, signature);
	}

	/*!*****************************************************************************
	Get the component data of an entity

	\param EntityID
	- ID of an Entity

	\return T&
	- Component data of an entity
	*******************************************************************************/
	template<typename T>
	T& GetComponent(EntityID entity) { return mComponentArrayManager->GetComponent<T>(entity); }

	/*!*****************************************************************************
	Get the component type of a component

	\return ComponentType
	- ComponentType of a component
	*******************************************************************************/
	template<typename T>
	ComponentType GetComponentType() { return mComponentArrayManager->GetComponentType<T>(); }

	/*!*****************************************************************************
	Checks if an entity has a component

	\return EntityID
	- ID of an entity
	*******************************************************************************/
	template<typename T>
	bool HasComponent(EntityID entity) {
		return mEntityManager->GetSignature(entity)[mComponentArrayManager->GetComponentType<T>()];
	}

	// From System Manager
	/*!*****************************************************************************
	Register a system

	\return std::shared_ptr<T>
	- Pointer to newly registered system
	*******************************************************************************/
	template<typename T>
	std::shared_ptr<T> RegisterSystem() { return mSystemManager->RegisterSystem<T>(); }

	/*!*****************************************************************************
	Set the signature of a system

	\param const Signature&
	- Signature to assign to system
	*******************************************************************************/
	template<typename T>
	void SetSystemSignature(const Signature& signature) { return mSystemManager->SetSignature<T>(signature); }

	// Extra
	/*!*****************************************************************************
	Destroy all entities in ECS
	*******************************************************************************/
	void DestroyAllEntities() {
		for (EntityID entity = 0; entity < MAX_ENTITIES; ++entity)
			if (mEntityManager->GetSignature(entity) != 0)
				DestroyEntity(entity);
	}

	/*!*****************************************************************************
	Destroy all entities except specified ones


	*******************************************************************************/
	void DestroySomeEntites(const std::vector<EntityID>& dontDestroy) {
		for (EntityID entity = 0; entity < MAX_ENTITIES; ++entity) {
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
 
//-------------------------------------------------------------------------
// EntityID
// EntityID and it's functions
//-------------------------------------------------------------------------

template<typename T, typename ...args>
void Entity::AddComponent(T _component, args... _components) const {
	Coordinator::GetInstance()->AddComponent<T>(id, _component);

	if constexpr (sizeof...(_components) > 0)
		return AddComponent(_components...);
}

template<typename T>
T& Entity::GetComponent() const { return Coordinator::GetInstance()->GetComponent<T>(id); }

template<typename T>
bool Entity::HasComponent() const { return Coordinator::GetInstance()->HasComponent<T>(id); }