/*!*****************************************************************************
\file	Physics2DManager.cpp
\author Lee Hsien Wei, Joachim
\par	DP email: l.hsienweijoachim@digipen.edu
\par	Course: GAM200
\par	Group: Memory Leak Studios
\date	27-09-2022
\brief  This file contains the declaration of the Physics System Class and its
		member functions which handles the dynamics of entities stored in its list
		as well as the management of forces acting on the entities
*******************************************************************************/
#pragma once

// -----------------------------
// Include files
// -----------------------------
#include "ECS_systems.h"

/*!*****************************************************************************
\brief Physics system class that handles the updating of object's accumulated 
	   forces & positions through the use of forces.
*******************************************************************************/
class Physics2DManager : public System {
public:
// -----------------------------
// System functions
// -----------------------------
	/*!*****************************************************************************
	\brief
	Update function that simulates physics by stepping it in fixedDT when enough
	time has passed
	\param const double &
	A reference to a read-only variable that tells us the application's current
	delta time
	\return void
	NULL
	*******************************************************************************/
	void Update(const double& _appDT);

	/*!*****************************************************************************
	\brief
	Step function that executes fixed delta time physics stepping
	\param void
	NULL
	\return void
	NULL
	*******************************************************************************/
	void Step();

// -----------------------------
// Component-related functions
// -----------------------------
	/*!*****************************************************************************
	\brief
	AddPhysicsComponent function that adds a physics component to the given entity
	and initializes the component to the given values. If the component already
	exists in the entity, the function will set the component's data members to the
	given values. 
	
	
	\return void
	NULL
	*******************************************************************************/
	void AddPhysicsComponent();

	/*!*****************************************************************************
	\brief
	RemovePhysicsComponent function that removes the physics component from the 
	entity itself if it exists
	\param const Entity &
	A reference to a read-only Entity to remove the physics component from
	\return void
	NULL
	*******************************************************************************/
	void RemovePhysicsComponent(const Entity& _e);

	/*!*****************************************************************************
	\brief
	GetPhysicsComponent function that getsand returns the physics component of the
	given entity
	\param const Entity &
	A reference to a read-only Entity to get from
	\return Physics2D &
	A reference to the Physics2D component in the given entity
	*******************************************************************************/
	Physics2D& GetPhysicsComponent(const Entity& _e);

// -----------------------------
// Get / Set functions
// -----------------------------
	/*!*****************************************************************************
	\brief
	GetGravityEnabled function that returns the stored value of the entity's
	gravity enabled flag
	\param const Entity &
	A reference to a read-only Entity to
	\return bool
	The value of the entity's gravity enabled flag
	*******************************************************************************/
	bool GetGravityEnabled(const Entity& _e);
	/*!*****************************************************************************
	\brief
	SetGravityEnabled function that sets the stored value of the entity's
	gravity enabled flag to the given value
	\param const Entity &
	A reference to a read-only Entity to
	\param const bool &
	A reference to a read-only value containing value to set
	\return void
	NULL
	*******************************************************************************/
	void SetGravityEnabled(const Entity& _e, const bool& _gravityEnabled);

	/*!*****************************************************************************
	\brief
	GetGravityScale function that returns the stored value of the entity's
	gravity scale
	\param const Entity &
	A reference to a read-only Entity to
	\return double
	The value of the entity's gravity scale
	*******************************************************************************/
	double GetGravityScale(const Entity& _e);
	/*!*****************************************************************************
	\brief
	SetGravityScale function that sets the stored value of the entity's
	gravity scale value to the given value
	\param const Entity &
	A reference to a read-only Entity to
	\param const double &
	A reference to a read-only value containing value to set
	\return void
	NULL
	*******************************************************************************/
	void SetGravityScale(const Entity& _e, const double& _gravityScale);

	/*!*****************************************************************************
	\brief
	GetDynamicsEnabled function that returns the stored value of the entity's
	dynamics enabled flag
	\param const Entity &
	A reference to a read-only Entity to
	\return bool
	The value of the entity's dynamics enabled flag
	*******************************************************************************/
	bool GetDynamicsEnabled(const Entity& _e);
	/*!*****************************************************************************
	\brief
	SetDynamicsEnabled function that sets the stored value of the entity's
	dynamics enabled flag to the given value
	\param const Entity &
	A reference to a read-only Entity to
	\param const bool &
	A reference to a read-only value containing value to set
	\return void
	NULL
	*******************************************************************************/
	void SetDynamicsEnabled(const Entity& _e, const bool& _dynamicsEnabled);

	/*!*****************************************************************************
	\brief
	GetMass function that returns the stored value of the entity's mass
	\param const Entity &
	A reference to a read-only Entity to get from
	\return double
	A copy of the value of the entity's mass
	*******************************************************************************/
	double GetMass(const Entity& _e);
	/*!*****************************************************************************
	\brief
	SetMass function that sets the stored value of the entity's mass to the given 
	value. It also updates the stored value of the entity's inverse mass
	\param const Entity &
	A reference to a read-only Entity to set
	\param const double &
	A reference to a read-only value containing the mass to set to
	\return void
	NULL
	*******************************************************************************/
	void SetMass(const Entity& _e, const double& _mass);
	/*!*****************************************************************************
	\brief
	GetInverseMass function that returns the stored value of the entity's inverse mass
	\param const Entity &
	A reference to a read-only Entity to get from
	\return double
	A copy of the value of the entity's inverse mass
	*******************************************************************************/
	double GetInverseMass(const Entity& _e);
	/*!*****************************************************************************
	\brief
	SetInverseMass function that sets the stored value of the entity's inverse mass 
	to the given value. It also updates the stored value of the entity's mass
	\param const Entity &
	A reference to a read-only Entity to set
	\param const double &
	A reference to a read-only value containing the inverse mass to set to
	\return void
	NULL
	*******************************************************************************/
	void SetInverseMass(const Entity& _e, const double& _invMass);

	/*!*****************************************************************************
	\brief
	GetInertia function that returns the stored value of the entity's inertia
	\param const Entity &
	A reference to a read-only Entity to get from
	\return double
	A copy of the value of the entity's inertia
	*******************************************************************************/
	double GetInertia(const Entity& _e);
	/*!*****************************************************************************
	\brief
	SetInertia function that sets the stored value of the entity's inertia to the 
	given value. It also updates the stored value of the entity's inverse inertia
	\param const Entity &
	A reference to a read-only Entity to set
	\param const double &
	A reference to a read-only value containing the inertia to set to
	\return void
	NULL
	*******************************************************************************/
	void SetInertia(const Entity& _e, const double& _inertia);
	/*!*****************************************************************************
	\brief
	GetInverseInertia function that returns the stored value of the entity's inverse
	inertia
	\param const Entity &
	A reference to a read-only Entity to get from
	\return double
	A copy of the value of the entity's inverse inertia
	*******************************************************************************/
	double GetInverseInertia(const Entity& _e);
	/*!*****************************************************************************
	\brief
	SetInverseInertia function that sets the stored value of the entity's inverse 
	inertia to the given value. It also updates the stored value of the entity's
	inertia
	\param const Entity &
	A reference to a read-only Entity to set
	\param const double &
	A reference to a read-only value containing the inverse inertia to set to
	\return void
	NULL
	*******************************************************************************/
	void SetInverseInertia(const Entity& _e, const double& _invInertia);

	/*!*****************************************************************************
	\brief
	GetRestitution function that returns the stored value of the entity's restitution
	\param const Entity &
	A reference to a read-only Entity to get from
	\return double
	A copy of the value of the entity's restitution
	*******************************************************************************/
	double GetRestitution(const Entity& _e);
	/*!*****************************************************************************
	\brief
	SetRestitution function that sets the stored value of the entity's restitution
	to the given value
	\param const Entity &
	A reference to a read-only Entity to get from
	\param const double &
	A reference to a read-only value containing the inverse inertia to set to
	\return void
	NULL
	*******************************************************************************/
	void SetRestitution(const Entity& _e, const double& _restitution);

	/*!*****************************************************************************
	\brief
	GetFriction function that returns the stored value of the entity's friction
	\param const Entity &
	A reference to a read-only Entity to get from
	\return double
	A copy of the value of the entity's friction
	*******************************************************************************/
	double GetFriction(const Entity& _e);
	/*!*****************************************************************************
	\brief
	SetFriction function that sets the stored value of the entity's friction
	to the given value
	\param const Entity &
	A reference to a read-only Entity to get from
	\param const double &
	A reference to a read-only value containing the friction to set to
	\return void
	NULL
	*******************************************************************************/
	void SetFriction(const Entity& _e, const double& _friction);

	/*!*****************************************************************************
	\brief
	GetDamping function that returns the stored value of the entity's damping
	\param const Entity &
	A reference to a read-only Entity to get from
	\return double
	A copy of the value of the entity's damping
	*******************************************************************************/
	double GetDamping(const Entity& _e);
	/*!*****************************************************************************
	\brief
	SetDamping function that sets the stored value of the entity's damping to the 
	given value
	\param const Entity &
	A reference to a read-only Entity to get from
	\param const double &
	A reference to a read-only value containing the damping to set to
	\return void
	NULL
	*******************************************************************************/
	void SetDamping(const Entity& _e, const double& _damping);

	//float GetSpeed(const Entity& _e);
	//void SetSpeed(const Entity& _e, const float& _speed);

	//float GetMoveDirection(const Entity& _e);
	//void SetMoveDirection(const Entity& _e, const float& _moveDirection);

	/*!*****************************************************************************
	\brief
	GetAccumulatedForce function that returns the stored value of the entity's 
	final force
	\param const Entity &
	A reference to a read-only Entity to get from
	\return Math::Vec2
	A copy of the value of the entity's final force
	*******************************************************************************/
	Math::Vec2 GetAccumulatedForce(const Entity& _e);
	/*!*****************************************************************************
	\brief
	SetAccumulatedForce function that sets the stored value of the entity's 
	accumulated force to the given value
	\param const Entity &
	A reference to a read-only Entity to get from
	\param const Math::Vec2 &
	A reference to a read-only value containing the force to set to
	\return void
	NULL
	*******************************************************************************/
	void SetAccumulatedForce(const Entity& _e, const Math::Vec2& _accumulatedForce);

	/*!*****************************************************************************
	\brief
	GetVelocity function that returns the stored value of the entity's velocity
	\param const Entity &
	A reference to a read-only Entity to get from
	\return Math::Vec2
	A copy of the value of the entity's velocity
	*******************************************************************************/
	Math::Vec2 GetVelocity(const Entity& _e);
	/*!*****************************************************************************
	\brief
	SetVelocity function that sets the stored value of the entity's velocity
	to the given value
	\param const Entity &
	A reference to a read-only Entity to get from
	\param const Math::Vec2 &
	A reference to a read-only value containing the friction to set to
	\return void
	NULL
	*******************************************************************************/
	void SetVelocity(const Entity& _e, const Math::Vec2& _velocity);
	/*!*****************************************************************************
	\brief
	AddVelocity function that adds a given vector containing a velocity vector to add
	to he stored value of the entity's velocity
	\param const Entity &
	A reference to a read-only Entity to get from
	\param const Math::Vec2 &
	A reference to a read-only value containing the velocity vector to add
	\return void
	NULL
	*******************************************************************************/
	void AddVelocity(const Entity& _e, const Math::Vec2& _velocity);
	/*!*****************************************************************************
	\brief
	ScaleVelocity function that scales the entity's velocity by the given scalar
	\param const Entity &
	A reference to a read-only Entity to get from
	\param const float &
	A reference to a read-only value containing the scalar value
	\return void
	NULL
	*******************************************************************************/
	void ScaleVelocity(const Entity& _e, const float& _scalar);

	/*!*****************************************************************************
	\brief
	GetAcceleration function that returns the stored value of the entity's acceleration
	\param const Entity &
	A reference to a read-only Entity to get from
	\return Math::Vec2
	A copy of the value of the entity's acceleration
	*******************************************************************************/
	Math::Vec2 GetAcceleration(const Entity& _e);
	/*!*****************************************************************************
	\brief
	SetAcceleration function that sets the stored value of the entity's velocity
	to the given value
	\param const Entity &
	A reference to a read-only Entity to get from
	\param const Math::Vec2 &
	A reference to a read-only value containing the friction to set to
	\return void
	NULL
	*******************************************************************************/
	void SetAcceleration(const Entity& _e, const Math::Vec2& _acceleration);

	/*!*****************************************************************************
	\brief
	GetAngularVelocity function that returns the stored value of the entity's angular
	velocity
	\param const Entity &
	A reference to a read-only Entity to get from
	\return double
	A copy of the value of the entity's angular velocity
	*******************************************************************************/
	double GetAngularVelocity(const Entity& _e);
	void SetAngularVelocity(const Entity& _e, const double& _angVel);

	/*!*****************************************************************************
	\brief
	GetAngularTorque function that returns the stored value of the entity's angular
	acceleration
	\param const Entity &
	A reference to a read-only Entity to get from
	\return Math::Vec2
	A copy of the value of the entity's angular acceleration
	*******************************************************************************/
	double GetAngularTorque(const Entity& _e);
	void SetAngularTorque(const Entity& _e, const double& _angTorque);

	/*!*****************************************************************************
	\brief
	GetPhysicsRenderFlag function that returns the stored value of the entity's
	physics render flag
	\param const Entity &
	A reference to a read-only Entity to
	\return bool
	The value of the entity's physics render flag
	*******************************************************************************/
	bool GetPhysicsRenderFlag(const Entity& _e);
	/*!*****************************************************************************
	\brief
	SetPhysicsRenderFlag function that sets the stored value of the entity's
	physics render flag to the given value
	\param const Entity &
	A reference to a read-only Entity to
	\param const bool &
	A reference to a read-only value containing value to set
	\return void
	NULL
	*******************************************************************************/
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
	// -----------------------------
	// Constant values
	// -----------------------------
	double mAccumulatedDT{ 0.0 };	// Member variable storing accumulatedDT
	const double fixedDT{ 1.0 / 60.0 };		// Fixed delta time step of 1/60 steps a second
	const double accumulatedDTCap{ 1.0 };		// Accumulated cannot store more than 1 second worth of updates
	const float  velocityCap{ 1000.f };			// 
	const Math::Vec2 gravityForce{ 0.f, -9.81f };// Gravity pull
	bool StepMode;
};

