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
#include "ECS_components.h"

//-------------------------------------------------------------------------
// Definitions from ECS_items
//-------------------------------------------------------------------------
// This file only contains this function to support forward declaration of function for ECS_items.h > struct Entity
void Entity::Destroy() const { Coordinator::GetInstance()->DestroyEntity(id); }

bool Entity::ShouldRun() const {
	General genComponent = this->GetComponent<General>();
	return genComponent.isPaused && genComponent.isActive;
}


Prefab::Prefab() : mName(""), mPrefabees(), mComponents() {
	for (void* ptr : mComponents) ptr = nullptr;
	//ComponentType genType = Coordinator::GetInstance()->GetComponentType<General>();
	//General* genComponent = static_cast<General*>(mComponents[genType]);
	//genComponent->prefab = this;
	General genComponent = { "", TAG::OTHERS, SUBTAG::NOSUBTAG, true, this };
	AddComponent<General>(genComponent);
}

Prefab::~Prefab() {
	//for (void* ptr : mComponents) 
	//	delete ptr;

	// TODO: Very dangerous. If there is a change in component order, whole thing breaks
	delete static_cast<General*>(mComponents[0]);
	delete static_cast<Lifespan*>(mComponents[1]);
	delete static_cast<Transform*>(mComponents[2]);
	delete static_cast<Sprite*>(mComponents[3]);
	delete static_cast<Animation*>(mComponents[4]);
	delete static_cast<SheetAnimation*>(mComponents[5]);
	delete static_cast<Physics2D*>(mComponents[6]);
	delete static_cast<CircleCollider*>(mComponents[7]);
	delete static_cast<RectCollider*>(mComponents[8]);
	delete static_cast<Edge2DCollider*>(mComponents[9]);
	delete static_cast<Point2DCollider*>(mComponents[10]);
	delete static_cast<PlayerTmp*>(mComponents[11]);
	delete static_cast<Stuff*>(mComponents[12]);
	delete static_cast<Audio*>(mComponents[13]);
	delete static_cast<Text*>(mComponents[14]);
}

Entity Prefab::CreatePrefabee() {
	int compType{};
	Entity e = { (Entity)Coordinator::GetInstance()->CreateEntity() };

	// Loop through all components, if component exists, add it to entity.
	for (void* component : mComponents) {
		if (!component) continue;

		// TODO: Very dangerous. If there is a change in component order, whole thing breaks
		switch (compType++) {
		case 0: // General
			e.AddComponent<General>(*(static_cast<General*>(component)));
			break;

		case 1: // Lifespan
			e.AddComponent<Lifespan>(*(static_cast<Lifespan*>(component)));
			break;

		case 2: // Transform
			e.AddComponent<Transform>(*(static_cast<Transform*>(component)));
			break;

		case 3: // Sprite
			e.AddComponent<Sprite>(*(static_cast<Sprite*>(component)));
			break;

		case 4: // Animation
			e.AddComponent<Animation>(*(static_cast<Animation*>(component)));
			break;

		case 5: // SheetAnimation
			e.AddComponent<SheetAnimation>(*(static_cast<SheetAnimation*>(component)));
			break;

		case 6: // Physics2D
			e.AddComponent<Physics2D>(*(static_cast<Physics2D*>(component)));
			break;

		case 7: // CircleCollider
			e.AddComponent<CircleCollider>(*(static_cast<CircleCollider*>(component)));
			break;

		case 8: // RectCollider
			e.AddComponent<RectCollider>(*(static_cast<RectCollider*>(component)));
			break;

		case 9: // Edge2DCollider
			e.AddComponent<Edge2DCollider>(*(static_cast<Edge2DCollider*>(component)));
			break;

		case 10: // Point2DCollider
			e.AddComponent<Point2DCollider>(*(static_cast<Point2DCollider*>(component)));
			break;

		case 11: // PlayerTmp
			e.AddComponent<PlayerTmp>(*(static_cast<PlayerTmp*>(component)));
			break;

		case 12: // Stuff
			e.AddComponent<Stuff>(*(static_cast<Stuff*>(component)));
			break;

		case 13: // Audio
			e.AddComponent<Audio>(*(static_cast<Audio*>(component)));
			break;

		case 14: // Text
			e.AddComponent<Text>(*(static_cast<Text*>(component)));
			break;

		}
	}

	mPrefabees.insert(e);
	return e;
}

void Prefab::UnlinkPrefabee(Entity const& _e) { // Should be called when Entity gets freed
	mPrefabees.erase(_e);
	_e.GetComponent<General>().prefab = nullptr;
}


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
	assert(std::find(mAvailableEntities.begin(), mAvailableEntities.end(), _entity) == mAvailableEntities.end() 
				 && "Attempted to delete non-existant Entity");

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

// Get the prefab to cut the ties between this entity and the prefab
void Coordinator::UnlinkPrefab(EntityID _entity) {
	if (!HasComponent<Lifespan>(_entity)) return;
	if (!HasComponent<General>(_entity)) return;
	General genComponent = GetComponent<General>(_entity);
	if (!genComponent.prefab) {
		LOG_WARN("Attempted to unlink non-existing prefab from entity. Ignore this if it happens during DestroyEntity.");
		return;
	}
	genComponent.prefab->UnlinkPrefabee(static_cast<Entity>(_entity));
}

void Coordinator::DestroyEntity(EntityID _entity) {
	UnlinkPrefab(_entity);
	mEntityManager->DestroyEntity(_entity);
	mComponentArrayManager->EntityDestroyed(_entity);
	mSystemManager->EntityDestroyed(_entity);
}

void Coordinator::DestroyAllEntities() {
	for (EntityID entity = 0; entity < MAX_ENTITIES; ++entity)
		if (mEntityManager->GetSignature(entity) != 0)
			DestroyEntity(entity);
}

void Coordinator::DestroySomeEntites(const std::set<Entity>& _e) {
	for (Entity const& e : _e)
		e.Destroy();
}
