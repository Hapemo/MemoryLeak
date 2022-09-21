#include "ECS_managers.h"
#include <cassert>
//-------------------------------------------------------------------------
// Entity Manager
//-------------------------------------------------------------------------
EntityManager::EntityManager() :
	mAvailableEntities(), mSignatures(), mLivingEntityCount()
{
	mAvailableEntities.resize(MAX_ENTITIES);
	for (size_t i = 0; i < MAX_ENTITIES; ++i)
		mAvailableEntities[i] = i;

	CreateEntity(); // Entity 0 shall be reserved for null
}

Entity EntityManager::CreateEntity() {
	assert(mLivingEntityCount < MAX_ENTITIES && "Too many instances of entities.");
	Entity id = mAvailableEntities.front();
	mAvailableEntities.pop_front();
	++mLivingEntityCount;
	return id;
}

void EntityManager::DestroyEntity(Entity entity) {
	assert(entity < MAX_ENTITIES && "Entity out of range.");

	mSignatures[entity].reset();
	mAvailableEntities.push_back(entity);
	--mLivingEntityCount;
}

void EntityManager::SetSignature(Entity entity, Signature signature) {
	assert(entity < MAX_ENTITIES && "Entity out of range.");

	mSignatures[entity] = signature;
}

Signature EntityManager::GetSignature(Entity entity) {
	assert(entity < MAX_ENTITIES && "Entity out of range.");

	return mSignatures[entity];
}


//-------------------------------------------------------------------------
// Component Array Manager
//-------------------------------------------------------------------------
ComponentArrayManager::ComponentArrayManager() :
	mComponentTypes(), mComponentArrays(), mNextComponentType()
{}

template<typename T>
void ComponentArrayManager::RegisterComponent() {
	std::string typeName{ typeid(T).name() };

	assert(mComponentTypes.find(typeName) == mComponentTypes.end() && "Attempted to register component more than once.");
	mComponentTypes.insert({ typeName, mNextcomponentType++ });
	mComponentArrays.insert({ typeName, std::make_shared<ComponentArray<T>>() });
}

template<typename T>
ComponentType ComponentArrayManager::GetComponentType() {
	std::string typeName{ typeid(T).name() };

	assert(mComponentTypes.find(typeName) != mComponentTypes.end() && "Attempted to access unregistered component.");
	return mComponentTypes[typeName];
}

template<typename T>
void ComponentArrayManager::AddComponent(Entity entity, T component) {
	GetComponentArray<T>()->InsertData(entity, component);
}

template<typename T>
void ComponentArrayManager::RemoveComponent(Entity entity) {
	GetComponentArray<T>()->RemoveData(entity);
}

template<typename T>
T& ComponentArrayManager::GetComponent(Entity entity) {
	return GetComponentArray<T>()->GetData(entity);
}

void ComponentArrayManager::EntityDestroyed(Entity entity) {
	for (auto const& [name, component] : mComponentArrays)
		component->EntityDestroyed(entity);
}

template<typename T>
std::shared_ptr<ComponentArray<T>> ComponentArrayManager::GetComponentArray() {
	std::string typeName{ typeid(T).name() };

	assert(mComponentTypes.find(typeName) != mComponentTypes.end() && "Attempted to access unregistered component.");
	return mComponentArrays[typeName];
}













