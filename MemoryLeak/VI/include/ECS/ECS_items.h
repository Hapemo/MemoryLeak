/*!*****************************************************************************
\file ECS_items.h
\author Jazz Teoh Yu Jue
\par DP email: j.teoh\@digipen.edu
\par Group: Memory Leak Studios
\date 24-09-2022
\brief
This file contains the basic structs that make up the ECS system. It contains 
Entity, IComponentArray and ComponentArray.
*******************************************************************************/
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
	
	// Copy Constructor
	explicit Entity(EntityID _id) : id(_id) {}

	/*!*****************************************************************************
	\brief
	Operator overload for '<' operator. This is required for std::set as set uses 
	'<' operator to arrange placement of items in std::set.

	\param 
	- the interval (in seconds) at which fps is to be calculated
	*******************************************************************************/
	bool operator<(Entity const& _entity) const { return id < _entity.id; } 

	/*!*****************************************************************************
	 \brief
	 Destroy an entity, returning it's ID and components.
	*******************************************************************************/
	void Destroy() const;

	/*!*****************************************************************************
	\brief
	Add components to an existing Entity

	\param T
	- First component to add in

	\param ...args
	- Other components to add in if there is any
	*******************************************************************************/
	template<typename T, typename ...args>
	void AddComponent(T, args...) const;

	/*!*****************************************************************************
	Get a reference to an Entity's component 

	\param T
	- First component to add in

	\param ...args
	- Other components to add in if there is any

	\return T&
	- Reference to entity's component
	*******************************************************************************/
	template<typename T>
	T& GetComponent() const;

	/*!*****************************************************************************
	Remove a component from entity
	*******************************************************************************/
	template<typename T>
	void RemoveComponent() const;

	/*!*****************************************************************************
	Checks if an entity has the indicated component
	
	\return bool
	- True if has indicated component, otherwise false
	*******************************************************************************/
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

	/*!*****************************************************************************
	\brief
	Remove component from an entity

	\return bool
	- True if has indicated component, otherwise false
	*******************************************************************************/
	virtual void RemoveData(EntityID) = 0;

	/*!*****************************************************************************
	\brief
	Checks if a component array has data of an entity

	\return bool
	- True if has data of entity, otherwise false
	*******************************************************************************/
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

	/*!*****************************************************************************
	\brief
	Assign a component to an entity and give it a specified component data

	\param EntityID
	- ID of entity

	\param T
	- Component data to insert into entity
	*******************************************************************************/
	void InsertData(EntityID, T);

	/*!*****************************************************************************
	\brief
	Remove a component from an entity

	\param EntityID
	- ID of entity
	*******************************************************************************/
	void RemoveData(EntityID);
	
	/*!*****************************************************************************
	\brief
	Access the component information of an entity

	\param EntityID
	- ID of entity

	\return T&
	- Reference of component to entity
	*******************************************************************************/
	T& GetData(EntityID);

	/*!*****************************************************************************
	\brief
	Checks if the Component array has data of an entity

	\param EntityID
	- ID of entity

	\return bool
	- True if has data of the entity, otherwise false
	*******************************************************************************/
	bool HasEntity(EntityID);

private:
	SparseSet<T> mData;
};

//-------------------------------------------------------------------------
// System
// Base class containing a set of entities which the system can operate on
// 
// A system is any functionality that iterates upon a list of entities with 
// a certain signature of components.
//-------------------------------------------------------------------------
class System {
public:
	std::set<Entity> mEntities;
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
void ComponentArray<T>::InsertData(EntityID _entity, T _component) {
	mData.AddData(_component, static_cast<short>(_entity));
}

template<typename T>
void ComponentArray<T>::RemoveData(EntityID _entity) {
	mData.RemoveData(static_cast<short>(_entity));
}

template<typename T>
T& ComponentArray<T>::GetData(EntityID _entity) {
	return mData[static_cast<short>(_entity)];
}

template<typename T>
bool ComponentArray<T>::HasEntity(EntityID _entity) {
	return mData.CheckData(static_cast<short>(_entity));
}

//template<typename T>
//void EntityDestroyed(EntityID entity) {
//	// This function is pointless, just use RemoveData()
//}














