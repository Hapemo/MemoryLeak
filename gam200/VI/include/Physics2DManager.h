#pragma once

#include "ECS_systems.h"
#include <unordered_set>
#include "vec2.h"

class Physics2DManager : public System {
public:
// Manager functions
	void Init();
	void Init(const std::set<Entity> &_entityList);
	void UpdateFirstList();
	void UpdateFirstList(const std::set<Entity> &_entityList);
	void FirstUpdate();
	void FirstUpdate(const std::set<Entity> &_entityList);
	//void UpdateBoundingBox(const Entity&);
	
// Get /Set / Add / Remove Component

	bool HasPhysicsComponent(const Entity &_e);
	Physics2D& GetPhysicsComponent(const Entity& _e);
	void AddPhysicsComponent(const Entity &_e, const float &_mass = 0.f, const float &_speed = 0.f, const float &_moveDirection = 0.f, const bool &_renderFlag = false);
	//void RemovePhysicsComponent(const Entity &_e);

// Physics Components Get Set
	float GetMass(const Entity &_e);
	void SetMass(const Entity &_e, const float &_mass);
	float GetSpeed(const Entity &_e);
	void SetSpeed(const Entity &_e, const float &_speed);
	float GetMoveDirection(const Entity &_e);
	void SetMoveDirection(const Entity &_e, const float &_moveDirection);
	bool GetPhysicsRenderFlag(const Entity &_e);
	void SetPhysicsRenderFlag(const Entity &_e, const bool &_renderFlag);

private:
	std::unordered_set<const Entity*> mPhysicsFirstUpdate,
									  mPhysicsSecondUpdate;
};

