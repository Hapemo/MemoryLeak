#pragma once
#include <cstdint>
#include <bitset>
#include <algorithm>
#include <cassert>

#include "Singleton.h"

//-------------------------------------------------------------------------
// Setting basic types
//-------------------------------------------------------------------------

// An ID for entities 
using Entity = std::uint32_t;
const Entity MAX_ENTITIES{ 5000 };

// An ID for components
using ComponentType = std::uint8_t;
const ComponentType MAX_COMPONENTS{ 32 };

// An ID indicating which component an entity posesses
using Signature = std::bitset<MAX_COMPONENTS>;


//-------------------------------------------------------------------------
// IComponentArray
// Only used for polymorphism for ComponentManager
//-------------------------------------------------------------------------
class IComponentArray {
public:
	virtual ~IComponentArray() = default;
	virtual void EntityDestroyed(Entity) = 0;
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
	void InsertData(Entity, T);
	// Remove a component from an entity
	void RemoveData(Entity);
	// Access the component information of an entity
	T& GetData(Entity);
	//void EntityDestroyed(Entity);

private:
	//------------------------
	// Rational for proxy ID structure
	// If std::unordered_map<Entity, T> is used, everything will work fine.
	// But it will be slower, because there will be lots of gaps in the array 
	// of components, which doesn't work well with how cache functions. 
	// Wasted space = less information cache can store = inefficient but extensive
	// memory space have to be used.
	// This proxy ID method eliminates any gaps between each components, making it 
	// more memory efficient and easier to store in cache
	//------------------------
	
	// Array of proxy ID to component
	std::array<T, MAX_ENTITIES> mComponentArray;
	// Array of proxy ID to entity
	std::array<Entity, MAX_ENTITIES> mIndexToEntity;
	// Amount of active proxy IDs
	size_t mSize;

	// Helper function
	// Get the proxy ID of entity in mComponentArrays
	size_t EntityPosition(Entity);
};










//=========================================================================
// Template function declarations
//=========================================================================

//-------------------------------------------------------------------------
// ComponentArray
//-------------------------------------------------------------------------
template<typename T>
ComponentArray<T>::ComponentArray() :
	mComponentArray(T()), mIndexToEntity(0), mSize(0)
{}

template<typename T>
void ComponentArray<T>::InsertData(Entity entity, T component) {
	assert( EntityPosition() != mComponentArray.size() && "Unable to assign component to entity with existing component");
	
	mComponenetArray[mSize] = component;
	mIndexToEntity[mSize] = entity;
	++mSize;
}

template<typename T>
void ComponentArray<T>::RemoveData(Entity entity) {
	size_t pos{ EntityPosition(entity) };
	assert( pos != mIndexToEntity.size() && "Unable to remove non-existance component from entity");

	mComponentArray[pos] = mComponentArray[mSize];
	mIndexToEntity[pos] = mIndexToEntity[mSize];
	--mSize;
}

template<typename T>
T& ComponentArray<T>::GetData(Entity entity) {
	return mComponentArray[EntityPosition(entity)];
}

//template<typename T>
//void EntityDestroyed(Entity entity) {
//	// This function is pointless, just use RemoveData()
//}

template<typename T>
size_t ComponentArray<T>::EntityPosition(Entity) {
	size_t pos = std::find(entity, mIndexToEntity.begin(), mIndexToEntity.end()) - mIndexToEntity.begin();
	assert(pos != mIndexToEntity.size() && "No such entity found in component array");
	return pos;
}















