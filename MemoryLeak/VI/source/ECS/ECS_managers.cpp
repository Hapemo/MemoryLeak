/*!*****************************************************************************
\file ECS_managers.cpp
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

#include "ECS_managers.h"

// This file only contains this function to support forward declaration of function for ECS_items.h > struct Entity
void Entity::Destroy() const { Coordinator::GetInstance()->DestroyEntity(id); }

//-------------------------------------------------------------------------
// Entity Manager
//-------------------------------------------------------------------------
EntityManager::EntityManager() :
	mAvailableEntities(), mSignatures(), mLivingEntityCount()
{
	mAvailableEntities.resize(MAX_ENTITIES);
	for (size_t i = 0; i < MAX_ENTITIES; ++i)
		mAvailableEntities[i] = static_cast<std::uint32_t>(i);

	CreateEntity(); // EntityID 0 shall be reserved for null
}

EntityID EntityManager::CreateEntity() {
	assert(mLivingEntityCount < MAX_ENTITIES && "Too many instances of entities.");
	EntityID id = mAvailableEntities.front();
	mAvailableEntities.pop_front();
	++mLivingEntityCount;
	return id;
}

void EntityManager::DestroyEntity(EntityID _entity) {
	assert(_entity < MAX_ENTITIES && "EntityID out of range.");

	mSignatures[_entity].reset();
	mAvailableEntities.push_back(_entity);
	--mLivingEntityCount;
}

void EntityManager::SetSignature(EntityID _entity, Signature _signature) {
	assert(_entity < MAX_ENTITIES && "EntityID out of range.");

	mSignatures[_entity] = _signature;
}

Signature EntityManager::GetSignature(EntityID _entity) {
	assert(_entity < MAX_ENTITIES && "EntityID out of range.");

	return mSignatures[_entity];
} 


//-------------------------------------------------------------------------
// Component Manager
//-------------------------------------------------------------------------
ComponentArrayManager::ComponentArrayManager() : 
	mComponentTypes(), mComponentArrays(), mNextComponentType() {}

void ComponentArrayManager::EntityDestroyed(EntityID _entity) {
	for (auto const& [name, component] : mComponentArrays) {
		if (!component->HasEntity(_entity)) continue;

		component->RemoveData(_entity);
	}
}


//-------------------------------------------------------------------------
// System Manager
//-------------------------------------------------------------------------
SystemManager::SystemManager() :
	mSignatures(), mSystems() {}

void SystemManager::EntityDestroyed(EntityID _entity) {
	for (auto const& [name, system] : mSystems)
		system->mEntities.erase(Entity{ _entity });
}

void SystemManager::EntitySignatureChanged(EntityID _entity, Signature _entitySignature) {
	for (auto const& [name, system] : mSystems) {
		Signature systemSignature{ mSignatures[name] };

		if ((_entitySignature & systemSignature) == systemSignature)
			system->mEntities.insert(Entity{ _entity });
		else system->mEntities.erase(Entity{ _entity });
	}
}


//-------------------------------------------------------------------------
// Coordinator
//-------------------------------------------------------------------------
Coordinator::Coordinator() {
	mEntityManager = std::make_unique<EntityManager>();
	mComponentArrayManager = std::make_unique<ComponentArrayManager>();
	mSystemManager = std::make_unique<SystemManager>();
}

EntityID Coordinator::CreateEntity() { return mEntityManager->CreateEntity(); }

void Coordinator::DestroyEntity(EntityID _entity) {
	mEntityManager->DestroyEntity(_entity);
	mComponentArrayManager->EntityDestroyed(_entity);
	mSystemManager->EntityDestroyed(_entity);
}

void Coordinator::DestroyAllEntities() {
	for (EntityID entity = 0; entity < MAX_ENTITIES; ++entity)
		if (mEntityManager->GetSignature(entity) != 0)
			DestroyEntity(entity);
}

void Coordinator::DestroySomeEntites(const std::vector<EntityID>& _dontDestroy) {
	for (EntityID entity = 0; entity < MAX_ENTITIES; ++entity) {
		if (mEntityManager->GetSignature(entity) != 0)
			// Skip those in dontDestroy
			if (std::find(_dontDestroy.begin(), _dontDestroy.end(), entity) == _dontDestroy.end())
				DestroyEntity(entity);
	}
}
