/*!*****************************************************************************
\file	Physics2DManager.cpp
\author Lee Hsien Wei, Joachim
\par	DP email: l.hsienweijoachim@digipen.edu
\par	Course: GAM200
\par	Group: Memory Leak Studios
\date	22-09-2022
\brief  This file contains the definition of the Physics System Class member
		functions which handles the dynamics of entities stored in its list
*******************************************************************************/

// -----------------------------
// Include files
// -----------------------------
#include "ECSManager.h"

// -----------------------------
// Constant values
// -----------------------------

void Physics2DManager::Update(const double& _appDT) {
	// Increment accumulatedDT by the application's DT
	Physics2DManager::mAccumulatedDT += _appDT;

	// Prevent spiral of death
	if (Physics2DManager::mAccumulatedDT > Physics2DManager::accumulatedDTCap)
		Physics2DManager::mAccumulatedDT = Physics2DManager::accumulatedDTCap;

	// If the accumlatedDT is larger than or equal to the defined fixedDT,
	//	Execute a simulation tick of the physics using the defined fixedDT and subtract that value from accumulatedDT 
	while (Physics2DManager::mAccumulatedDT >= Physics2DManager::fixedDT) {
		Physics2DManager::Step();
		//collision2DManager->Update(Physics2DManager::fixedDT);
		Physics2DManager::mAccumulatedDT -= Physics2DManager::fixedDT;
	}
}

void Physics2DManager::Step() {
	// Update all required entities physics based on object rotation/orientation
	for (const Entity& e : mEntities) {
		// Skip if entity does not have physics component
		if (!e.HasComponent<Physics2D>())
			continue;

		// Skip if entity is a static object
		if (!GetDynamicsEnabled(e))
			continue;

		// If entity is a gravity enabled object, enact gravity force on it
		if (GetGravityEnabled(e)) {
			SetAcceleration(e, Physics2DManager::gravityForce);
		}
		// Add movement as a force acting on the entity
		// AddForce(e, Math::Vec2{ cos(GetMoveDirection(e)), sin(GetMoveDirection(e)) } *GetSpeed(e));

		// Determine acceleration
		SetAcceleration(e, GetAccumulatedForce(e) * GetInverseMass(e) + GetAcceleration(e));

		// Determine velocity
		SetVelocity(e, GetVelocity(e) + GetAcceleration(e) * static_cast<float>(fixedDT));

		// Dampen velocity (for soft drag)
		SetVelocity(e, GetVelocity(e) * std::pow(GetDamping(e), fixedDT));

		// Cap velocity
		if (Math::Dot(GetVelocity(e), GetVelocity(e)) > Physics2DManager::velocityCap * Physics2DManager::velocityCap) {
			SetVelocity(e, GetVelocity(e).Normalize() * Physics2DManager::velocityCap);
		}

		// Move entity by velocity
		e.GetComponent<Transform>().translation += GetVelocity(e) * static_cast<float>(fixedDT);

		// Reset forces on the object for next step
		SetAccumulatedForce(e, Math::Vec2{ 0.f, 0.f });
	}
}


Physics2D& Physics2DManager::GetPhysicsComponent(const Entity& _e) {
	return _e.GetComponent<Physics2D>();
}

bool Physics2DManager::GetGravityEnabled(const Entity& _e) {
	return GetPhysicsComponent(_e).gravityEnabled;
}

void Physics2DManager::SetGravityEnabled(const Entity& _e, const bool& _gravityEnabled) {
	GetPhysicsComponent(_e).gravityEnabled = _gravityEnabled;
}

bool Physics2DManager::GetDynamicsEnabled(const Entity& _e) {
	return GetPhysicsComponent(_e).dynamicsEnabled;
}

void Physics2DManager::SetDynamicsEnabled(const Entity& _e, const bool& _dynamicsEnabled) {
	GetPhysicsComponent(_e).dynamicsEnabled = _dynamicsEnabled;
}

double Physics2DManager::GetMass(const Entity& _e) {
	return GetPhysicsComponent(_e).mass;
}

void Physics2DManager::SetMass(const Entity& _e, const double& _mass) {
	GetPhysicsComponent(_e).mass = _mass;
}

double Physics2DManager::GetInverseMass(const Entity& _e) {
	return GetPhysicsComponent(_e).invMass;
}

void Physics2DManager::SetInverseMass(const Entity& _e, const double& _invMass) {
	GetPhysicsComponent(_e).invMass  =  _invMass;
}

double Physics2DManager::GetRestitution(const Entity& _e) {
	return GetPhysicsComponent(_e).restitution;
}

void Physics2DManager::SetRestitution(const Entity& _e, const double& _restitution) {
	GetPhysicsComponent(_e).restitution = _restitution;
}

double Physics2DManager::GetFriction(const Entity& _e) {
	return GetPhysicsComponent(_e).friction;
}

void Physics2DManager::SetFriction(const Entity& _e, const double& _friction) {
	GetPhysicsComponent(_e).friction = _friction;
}

double Physics2DManager::GetDamping(const Entity& _e) {
	return GetPhysicsComponent(_e).damping;
}

void Physics2DManager::SetDamping(const Entity& _e, const double& _damping) {
	GetPhysicsComponent(_e).damping = _damping;
}

float Physics2DManager::GetSpeed(const Entity& _e) {
	return GetPhysicsComponent(_e).speed;
}

void Physics2DManager::SetSpeed(const Entity& _e, const float& _speed) {
	GetPhysicsComponent(_e).speed = _speed;
}

float Physics2DManager::GetMoveDirection(const Entity& _e) {
	return GetPhysicsComponent(_e).moveDirection;
}

void Physics2DManager::SetMoveDirection(const Entity& _e, const float& _moveDirection) {
	GetPhysicsComponent(_e).moveDirection = _moveDirection;
}

Math::Vec2 Physics2DManager::GetAccumulatedForce(const Entity& _e) {
	return GetPhysicsComponent(_e).accumulatedForce;
}

void Physics2DManager::SetAccumulatedForce(const Entity& _e, const Math::Vec2& _accumulatedForce) {
	GetPhysicsComponent(_e).accumulatedForce = _accumulatedForce;
}

void Physics2DManager::UpdateAccumulatedForce(const Entity& _e) {

}

Math::Vec2 Physics2DManager::GetVelocity(const Entity& _e) {
	return GetPhysicsComponent(_e).velocity;
}

void Physics2DManager::SetVelocity(const Entity& _e, const Math::Vec2& _velocity) {
	GetPhysicsComponent(_e).velocity = _velocity;
}

void Physics2DManager::AddVelocity(const Entity& _e, const Math::Vec2& _velocity) {
	GetPhysicsComponent(_e).velocity += _velocity;
}

void Physics2DManager::ScaleVelocity(const Entity& _e, const float& _scalar) {
	GetPhysicsComponent(_e).velocity *= _scalar;
}

Math::Vec2 Physics2DManager::GetAcceleration(const Entity& _e) {
	return GetPhysicsComponent(_e).acceleration;
}

void Physics2DManager::SetAcceleration(const Entity& _e, const Math::Vec2& _acceleration) {
	GetPhysicsComponent(_e).acceleration = _acceleration;
}

bool Physics2DManager::GetPhysicsRenderFlag(const Entity& _e) {
	return GetPhysicsComponent(_e).renderFlag;
}

void Physics2DManager::SetPhysicsRenderFlag(const Entity& _e, const bool& _renderFlag) {
	GetPhysicsComponent(_e).renderFlag = _renderFlag;
}

void Physics2DManager::AddForce(const Entity& _e, const Force& _force) {
	GetPhysicsComponent(_e).ActingForces.push_back(_force);
}
