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
const double fixedDT{ 1.0 / 60.0 },			// Fixed delta time step of 1/60 steps a second
			 accumulatedDTCap{ 1.0 };		// Accumulated cannot store more than 1 second worth of updates
const float  velocityCap{ 0.99f };			// Velocity multipler cap to reach max velocity
const Math::Vec2 gravityForce{ 0.f, -9.81f };// Gravity pull


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
void Physics2DManager::Update(const double& _appDT) {
	// Increment accumulatedDT by the application's DT
	Physics2DManager::mAccumulatedDT += _appDT;

	// Prevent spiral of death
	if (Physics2DManager::mAccumulatedDT > accumulatedDTCap)
		Physics2DManager::mAccumulatedDT = accumulatedDTCap;

	// If the accumlatedDT is larger than or equal to the defined fixedDT,
	//	Execute a simulation tick of the physics using the defined fixedDT and subtract that value from accumulatedDT 
	while (Physics2DManager::mAccumulatedDT >= fixedDT) {
		Physics2DManager::Step();
		collision2DManager->Update(fixedDT);
		Physics2DManager::mAccumulatedDT -= fixedDT;
	}
}

/*!*****************************************************************************
\brief
Step function that executes fixed delta time physics stepping

\param void
NULL

\return void
NULL
*******************************************************************************/
void Physics2DManager::Step() {
	// Update all required entities physics based on object rotation/orientation
	for (const Entity& e : mEntities) {
		// Skip if entity does not have physics component
		if (!e.HasComponent<Physics2D>())
			continue;

		// If entity is a gravity enabled object, enact gravity force on it
		if (Physics2DManager::GetGravityEnabled(e))
			Physics2DManager::AddGravityForce(e);
		// Add movement as a force acting on the entity
		Physics2DManager::AddForces(e, Math::Vec2{ cos(Physics2DManager::GetMoveDirection(e)), sin(Physics2DManager::GetMoveDirection(e)) } * Physics2DManager::GetSpeed(e));
		// Compute acceleration and add to velocity
		if (Physics2DManager::GetMass(e) != 0.f)
			Physics2DManager::AddVelocity(e, (Physics2DManager::GetForces(e) / Physics2DManager::GetMass(e)) * static_cast<float>(fixedDT));
		else
			Physics2DManager::AddVelocity(e, Physics2DManager::GetForces(e) * static_cast<float>(fixedDT));
		// Cap velocity
		Physics2DManager::ScaleVelocity(e, velocityCap);
		// Move entity by velocitys
		e.GetComponent<Transform>().translation += Physics2DManager::GetVelocity(e) * static_cast<float>(fixedDT);

		// Reset forces on the object for next step
		Physics2DManager::SetForces(e, Math::Vec2{ 0.f, 0.f });
	}
}

/*!*****************************************************************************
\brief
HasPhysicsComponent function that checks if the given entity has a physics
component. If yes, the function returns true. Otherwise it returns false.

\param const Entity &
A reference to a read-only Entity to check for

\return bool
Evaluated result of whether the entity has a physics component
*******************************************************************************/
bool Physics2DManager::HasPhysicsComponent(const Entity& _e) {
	return _e.HasComponent<Physics2D>();
}

/*!*****************************************************************************
\brief
AddPhysicsComponent function that adds a physics component to the given entity
and initializes the component to the given values. If the component already
exists in the entity, the function will set the component's data members to the
given values. Finally, it will add the entity to the system's stored list if
it does not exists in the list yet.

\param const Entity &
A reference to a read-only Entity to check for

\param const float &
A reference to a read-only value containing the entity's mass

\param const float &
A reference to a read-only value containing the entity's speed

\param const float &
A reference to a read-only value containing the entity's movement direction in the
form of radian rotations

\param const bool &
A reference to a read-only value containing the flag value of the render flag

\return void
NULL
*******************************************************************************/
void Physics2DManager::AddPhysicsComponent(const Entity& _e, const bool & _gravityEnabled, const float& _mass, const float& _speed, const float& _moveDirection, const bool& _renderFlag) {
	// If the physics component does not exists in the entity yet, we add it to the entity with the given values
	// If it already exists, we reset the values to the given values
	if (!_e.HasComponent<Physics2D>()) {
		_e.AddComponent(Physics2D{ _gravityEnabled, _mass, _speed, _moveDirection, Math::Vec2{0, 0}, Math::Vec2{0, 0}, _renderFlag });
	}
	else {
		Physics2DManager::SetMass(_e, _mass);
		Physics2DManager::SetSpeed(_e, _speed);
		Physics2DManager::SetMoveDirection(_e, _moveDirection);
		Physics2DManager::SetForces(_e, Math::Vec2{ 0, 0 });
		Physics2DManager::SetVelocity(_e, Math::Vec2{ 0, 0 });
		Physics2DManager::SetPhysicsRenderFlag(_e, _renderFlag);
	}
}

/*!*****************************************************************************
\brief
RemovePhysicsComponent function that removes the given entity from the system's
stored list and remove the physics component from the entity itself

\param const Entity &
A reference to a read-only Entity to remove the physics component from

\return void
NULL
*******************************************************************************/
void Physics2DManager::RemovePhysicsComponent(const Entity& _e) {
	// Remove component if component exists
	if (_e.HasComponent<Physics2D>())
		_e.RemoveComponent<Physics2D>();
}

/*!*****************************************************************************
\brief
GetPhysicsComponent function that getsand returns the physics component of the
given entity

\param const Entity &
A reference to a read-only Entity to get from

\return Physics2D &
A reference to the Physics2D component in the given entity
*******************************************************************************/
Physics2D& Physics2DManager::GetPhysicsComponent(const Entity& _e) {
	return _e.GetComponent<Physics2D>();
}

/*!*****************************************************************************
\brief
GetGravityEnabled function that returns the stored value of the entity's
gravity enabled flag

\param const Entity &
A reference to a read-only Entity to

\return bool
The value of the entity's gravity enabled flag
*******************************************************************************/
bool Physics2DManager::GetGravityEnabled(const Entity& _e) {
	return Physics2DManager::GetPhysicsComponent(_e).gravityEnabled;
}

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
void Physics2DManager::SetGravityEnabled(const Entity& _e, const bool& _gravityEnabled) {
	Physics2DManager::GetPhysicsComponent(_e).gravityEnabled = _gravityEnabled;
}

/*!*****************************************************************************
\brief
GetMass function that returns the stored value of the entity's mass

\param const Entity &
A reference to a read-only Entity to get from

\return float
A copy of the value of the entity's mass
*******************************************************************************/
float Physics2DManager::GetMass(const Entity& _e) {
	return Physics2DManager::GetPhysicsComponent(_e).mass;
}

/*!*****************************************************************************
\brief
SetMass function that sets the stored value of the entity's mass to the given value

\param const Entity &
A reference to a read-only Entity to set

\param const float &
A reference to a read-only value containing the mass to set to

\return void
NULL
*******************************************************************************/
void Physics2DManager::SetMass(const Entity& _e, const float& _mass) {
	Physics2DManager::GetPhysicsComponent(_e).mass = _mass;
}

/*!*****************************************************************************
\brief
GetSpeed function that returns the stored value of the entity's speed

\param const Entity &
A reference to a read-only Entity to get from

\return float
A copy of the value of the entity's speed
*******************************************************************************/
float Physics2DManager::GetSpeed(const Entity& _e) {
	return Physics2DManager::GetPhysicsComponent(_e).speed;
}

/*!*****************************************************************************
\brief
SetSpeed function that sets the stored value of the entity's speed to the given
value

\param const Entity &
A reference to a read-only Entity to set

\param const float &
A reference to a read-only value containing the speed to set to

\return void
NULL
*******************************************************************************/
void Physics2DManager::SetSpeed(const Entity& _e, const float& _speed) {
	Physics2DManager::GetPhysicsComponent(_e).speed = _speed;
}

/*!*****************************************************************************
\brief
GetMoveDirection function that returns the stored value of the entity's
moveDirection in the form of radian rotations

\param const Entity &
A reference to a read-only Entity to remove the physics component from

\return float
A copy of the value of the entity's moveDirection
*******************************************************************************/
float Physics2DManager::GetMoveDirection(const Entity& _e) {
	return Physics2DManager::GetPhysicsComponent(_e).moveDirection;
}

/*!*****************************************************************************
\brief
SetMoveDirection function that sets the stored value of the entity's move direction
to the given value

\param const Entity &
A reference to a read-only Entity to set

\param const float &
A reference to a read-only value containing the move direction to set to
Value should be in radians

\return void
NULL
*******************************************************************************/
void Physics2DManager::SetMoveDirection(const Entity& _e, const float& _moveDirection) {
	Physics2DManager::GetPhysicsComponent(_e).moveDirection = _moveDirection;
}

/*!*****************************************************************************
\brief
GetForces function that returns the stored value of the entity's net forces

\param const Entity &
A reference to a read-only Entity to

\return Math::Vec2
A copy of the value of the entity's net forces
*******************************************************************************/
Math::Vec2 Physics2DManager::GetForces(const Entity& _e) {
	return Physics2DManager::GetPhysicsComponent(_e).forces;
}

/*!*****************************************************************************
\brief
SetForces function that sets the stored value of the entity's net forces to the
given value

\param const Entity &
A reference to a read-only Entity to set

\param const Math::Vec2 &
A reference to a read-only value containing net force to set to

\return void
NULL
*******************************************************************************/
void Physics2DManager::SetForces(const Entity& _e, const Math::Vec2& _forces) {
	Physics2DManager::GetPhysicsComponent(_e).forces = _forces;
}

/*!*****************************************************************************
\brief
AddForces function that adds the given force value to the stored value of the
entity's forces to become the updated net forces

\param const Entity &
A reference to a read-only Entity to set

\param const Math::Vec2 &
A reference to a read-only value containing force to add

\return void
NULL
*******************************************************************************/
void Physics2DManager::AddForces(const Entity& _e, const Math::Vec2& _forces) {
	Physics2DManager::GetPhysicsComponent(_e).forces += _forces;
}

/*!*****************************************************************************
\brief
AddGravityForce function that adds the gravity force value to the stored value of the
entity's forces to become the updated net forces

\param const Entity &
A reference to a read-only Entity to set

\return void
NULL
*******************************************************************************/
void Physics2DManager::AddGravityForce(const Entity& _e) {
	Physics2DManager::AddForces(_e, Physics2DManager::GetMass(_e) * gravityForce);
}

/*!*****************************************************************************
\brief
GetVelocity function that returns the stored value of the entity's velocity

\param const Entity &
A reference to a read-only Entity to

\return Math::Vec2
A copy of the value of the entity's velocity
*******************************************************************************/
Math::Vec2 Physics2DManager::GetVelocity(const Entity& _e) {
	return Physics2DManager::GetPhysicsComponent(_e).velocity;
}

/*!*****************************************************************************
\brief
SetVelocity function that sets the stored value of the entity's velocity to the
given value

\param const Entity &
A reference to a read-only Entity to set

\param const Math::Vec2 &
A reference to a read-only value containing velocity to set to

\return void
NULL
*******************************************************************************/
void Physics2DManager::SetVelocity(const Entity& _e, const Math::Vec2& _velocity) {
	Physics2DManager::GetPhysicsComponent(_e).velocity = _velocity;
}

/*!*****************************************************************************
\brief
AddVelocity function that adds the given velocity to the stored value of the
entity's velocity

\param const Entity &
A reference to a read-only Entity to set

\param const Math::Vec2 &
A reference to a read-only value containing velocity to add

\return void
NULL
*******************************************************************************/
void Physics2DManager::AddVelocity(const Entity& _e, const Math::Vec2& _velocity) {
	Physics2DManager::GetPhysicsComponent(_e).velocity += _velocity;
}

/*!*****************************************************************************
\brief
ScaleVelocity function that scales the stored value of the entity's velocity by
the given scalar value

\param const Entity &
A reference to a read-only Entity to set

\param const float &
A reference to a read-only value containing the scalar to scale the stored
velocity by

\return void
NULL
*******************************************************************************/
void Physics2DManager::ScaleVelocity(const Entity& _e, const float& _scalar) {
	Physics2DManager::GetPhysicsComponent(_e).velocity *= _scalar;
}

/*!*****************************************************************************
\brief
GetPhysicsRenderFlag function that returns the stored value of the entity's
physics render flag

\param const Entity &
A reference to a read-only Entity to

\return bool
The value of the entity's physics render flag
*******************************************************************************/
bool Physics2DManager::GetPhysicsRenderFlag(const Entity& _e) {
	return Physics2DManager::GetPhysicsComponent(_e).renderFlag;
}

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
void Physics2DManager::SetPhysicsRenderFlag(const Entity& _e, const bool& _renderFlag) {
	Physics2DManager::GetPhysicsComponent(_e).renderFlag = _renderFlag;
}


