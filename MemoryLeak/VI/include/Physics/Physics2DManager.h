/*!*****************************************************************************
\file	Physics2DManager.cpp
\author Lee Hsien Wei, Joachim
\par	DP email: l.hsienweijoachim@digipen.edu
\par	Course: GAM200
\par	Group: Memory Leak Studios
\date	22-09-2022
\brief  This file contains the declaration of the Physics System Class and its
		member functions which handles the dynamics of entities stored in its list
*******************************************************************************/
#pragma once

// -----------------------------
// Include files
// -----------------------------
#include "ECS_systems.h"

/*!*****************************************************************************
\brief Physics system class that handles the updating of object's positions
	   through the use of forces and fixed dt updates
*******************************************************************************/
class Physics2DManager : public System {
public:
	// -----------------------------
	// System functions
	// -----------------------------
	void Update(const double& _appDT);

	void Step();

	// -----------------------------
	// Get / Set functions
	// -----------------------------
	Physics2D& GetPhysicsComponent(const Entity& _e);

	bool GetGravityEnabled(const Entity& _e);
	void SetGravityEnabled(const Entity& _e, const bool& _gravityEnabled);

	double GetGravityScale(const Entity& _e);
	void SetGravityScale(const Entity& _e, const double& _gravityScale);

	bool GetDynamicsEnabled(const Entity& _e);
	void SetDynamicsEnabled(const Entity& _e, const bool& _dynamicsEnabled);

	double GetMass(const Entity& _e);
	void SetMass(const Entity& _e, const double& _mass);
	double GetInverseMass(const Entity& _e);
	void SetInverseMass(const Entity& _e, const double& _invMass);

	double GetInertia(const Entity& _e);
	void SetInertia(const Entity& _e, const double& _inertia);
	double GetInverseInertia(const Entity& _e);
	void SetInverseInertia(const Entity& _e, const double& _invInertia);

	double GetRestitution(const Entity& _e);
	void SetRestitution(const Entity& _e, const double& _restitution);

	double GetFriction(const Entity& _e);
	void SetFriction(const Entity& _e, const double& _friction);

	double GetDamping(const Entity& _e);
	void SetDamping(const Entity& _e, const double& _damping);

	float GetSpeed(const Entity& _e);
	void SetSpeed(const Entity& _e, const float& _speed);

	float GetMoveDirection(const Entity& _e);
	void SetMoveDirection(const Entity& _e, const float& _moveDirection);

	Math::Vec2 GetAccumulatedForce(const Entity& _e);
	void SetAccumulatedForce(const Entity& _e, const Math::Vec2& _accumulatedForce);

	Math::Vec2 GetVelocity(const Entity& _e);
	void SetVelocity(const Entity& _e, const Math::Vec2& _velocity);
	void AddVelocity(const Entity& _e, const Math::Vec2& _velocity);
	void ScaleVelocity(const Entity& _e, const float& _scalar);

	Math::Vec2 GetAcceleration(const Entity& _e);
	void SetAcceleration(const Entity& _e, const Math::Vec2& _acceleration);

	double GetAngularVelocity(const Entity& _e);
	void SetAngularVelocity(const Entity& _e, const double& _angVel);

	double GetAngularTorque(const Entity& _e);
	void SetAngularTorque(const Entity& _e, const double& _angTorque);

	bool GetPhysicsRenderFlag(const Entity& _e);
	void SetPhysicsRenderFlag(const Entity& _e, const bool& _renderFlag);

	void UpdateEntitiesAccumulatedForce(const Entity& _e);

	void AddForce(const Entity& _e, const Math::Vec2& _unitDirection = { 0.f, 0.f }, const float& _magnitude = 1.f, 
				  const double& _lifetimeLimit = 0.0, const double& _age = 0.0, const bool& _isActive = true);
	void AddForce(const Entity& _e, const float& _torque = 0.f, 
				  const double& _lifetimeLimit = 0.0, const double& _age = 0.0, const bool& _isActive = true);
	void AddForce(const Entity& _e, const float& _directionDrag = 1.f, const float& _rotationDrag = 1.f, 
				  const double& _lifetimeLimit = 0.0, const double& _age = 0.0, const bool& _isActive = true);
	void ApplyImpulse(const Entity& _e, const Math::Vec2& _impulse, const Math::Vec2& _contact);
private:
	double mAccumulatedDT{ 0.0 };	// Member variable storing accumulatedDT
	const double fixedDT{ 1.0 / 60.0 };		// Fixed delta time step of 1/60 steps a second
	const double accumulatedDTCap{ 1.0 };		// Accumulated cannot store more than 1 second worth of updates
	const float  velocityCap{ 1000.f };			// 
	const Math::Vec2 gravityForce{ 0.f, -9.81f };// Gravity pull
	bool StepMode;
};

