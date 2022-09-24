#pragma once
#include "pch.h"
#include "SparseSet.h"
#include "Singleton.h"

//-------------------------------------------------------------------------
// Setting basic types
//-------------------------------------------------------------------------

// An ID for entities 
using EntityID = std::uint32_t;
const EntityID MAX_ENTITIES{ 5000 };

// An ID for components
using ComponentType = std::uint8_t;
const ComponentType MAX_COMPONENTS{ 32 };

// An ID indicating which component an entity posesses
using Signature = std::bitset<MAX_COMPONENTS>;



struct Entity {
	// Some of the member functions are defined in ECS_managers.cpp because
	// they require functions declared in ECS_managers.h
	EntityID id;

	Entity() = default;
	
	explicit Entity(EntityID id) : id(id) {}

	// This is required for std::set as set uses '<' operator to compare placement of items in set
	bool operator<(Entity const& entity2) const { return id < entity2.id; } 

	void Destroy() const;

	template<typename T, typename ...args>
	void AddComponent(T component, args...components) const;

	template<typename T>
	T& GetComponent() const;

	template<typename T>
	bool HasComponent() const;
};



//-------------------------------------------------------------------------
// IComponentArray
// Only used for polymorphism for ComponentManager
//-------------------------------------------------------------------------
class IComponentArray {
public:
	virtual ~IComponentArray() = default;
	virtual void RemoveData(EntityID) = 0;
	virtual bool HasEntity(EntityID) = 0;
};


//-------------------------------------------------------------------------
// ComponentArray
// An array for each components and entity ID to keep track which entity is using it
//-------------------------------------------------------------------------
template<typename T>
class ComponentArray : public IComponentArray {
public:
	ComponentArray();

	// Assign a component to an entity and give it a specified component data
	void InsertData(EntityID, T);
	// Remove a component from an entity
	void RemoveData(EntityID);
	// Access the component information of an entity
	T& GetData(EntityID);
	//void EntityDestroyed(EntityID);
	bool HasEntity(EntityID);

private:
	//------------------------
	// Rational for proxy ID structure
	// If std::unordered_map<EntityID, T> is used, everything will work fine.
	// But it will be slower, because there will be lots of gaps in the array 
	// of components, which doesn't work well with how cache functions. 
	// Wasted space = less information cache can store = inefficient but extensive
	// memory space have to be used.
	// This proxy ID method eliminates any gaps between each components, making it 
	// more memory efficient and easier to store in cache
	//------------------------
	
	SparseSet<T> mData;
};

struct Entity;
//-------------------------------------------------------------------------
// System
// Base class containing a set of entities which the system can operate on
// 
// A system is any functionality that iterates upon a list of entities with 
// a certain signature of components.
//-------------------------------------------------------------------------
class System {
public:
	//std::set<EntityID> mEntities;
	std::set<Entity> mEntities;
	//std::vector<Entity> mEntities;
};



//=========================================================================
// Template function declarations
//=========================================================================

//-------------------------------------------------------------------------
// ComponentArray
//-------------------------------------------------------------------------
template<typename T>
ComponentArray<T>::ComponentArray() : mData(MAX_ENTITIES) {}

template<typename T>
void ComponentArray<T>::InsertData(EntityID entity, T component) {
	mData.AddData(component, static_cast<short>(entity));
}

template<typename T>
void ComponentArray<T>::RemoveData(EntityID entity) {
	mData.RemoveData(static_cast<short>(entity));
}

template<typename T>
T& ComponentArray<T>::GetData(EntityID entity) {
	return mData[static_cast<short>(entity)];
}

template<typename T>
bool ComponentArray<T>::HasEntity(EntityID entity) {
	return mData.CheckData(static_cast<short>(entity));
}

//template<typename T>
//void EntityDestroyed(EntityID entity) {
//	// This function is pointless, just use RemoveData()
//}














