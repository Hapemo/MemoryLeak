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

// -----------------------------
// Physics System
// -----------------------------
class Physics2DManager : public System {
public:
// -----------------------------
// System functions
// -----------------------------
	/*!*****************************************************************************
	\brief
	Update function that simulates physics by stepping it in fixedDT when enough
	time has passed

	\param int const double &
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
// System object list functions
// -----------------------------
	/*!*****************************************************************************
	\brief
	IsEmptyPhyObjList function that checks if the system's stored entity list is empty.
	If yes, the function returns true. Otherwise, it returns false

	\param void
	NULL

	\return bool
	Evaluated result of whether the list is empty
	*******************************************************************************/
	bool IsEmptyPhyObjList();

	/*!*****************************************************************************
	\brief
	IsEntityInObjList function that checks if the given entity exists in the system's
	list to update dynamics for. If it exists, the function reurns true. Otherwise,
	it returns false

	\param const Entity &
	A reference to a read-only Entity to check for

	\return bool
	Evaluated result of whether the entity exists in the list
	*******************************************************************************/
	bool IsEntityInPhyObjList(const Entity& _e);

	/*!*****************************************************************************
	\brief
	IsEntityInObjList function that removes the given entity from the system's list.
	The function will check if the entity exists in the list before proceeding with
	removal. If successful, the function returns true. Otherwise, it returns false

	\param const Entity &
	A reference to a read-only Entity to remove

	\return bool
	Evaluated result of whether the removal was successful
	*******************************************************************************/
	bool RemoveEntityInPhyObjList(const Entity& _e);

	/*!*****************************************************************************
	\brief
	PhyObjListClear function that removes all entities in the system's stored list

	\param const void
	NULL

	\return void
	NULL
	*******************************************************************************/
	void PhyObjListClear();

	/*!*****************************************************************************
	\brief
	UpdatePhyObjList function that removes any non-existent entities, and adds new
	entities that require physics update given the list of entities in the current
	scene

	\param const std::set<Entity> &
	A reference to a read-only set of entities that contains the entities in the current
	scene

	\return void
	NULL
	*******************************************************************************/
	void UpdatePhyObjList(const std::set<Entity>& _entityList);


// -----------------------------
// Component-related functions
// -----------------------------
		/*!*****************************************************************************
	\brief
	HasPhysicsComponent function that checks if the given entity has a physics
	component. If yes, the function returns true. Otherwise it returns false.

	\param const Entity &
	A reference to a read-only Entity to check for

	\return bool
	Evaluated result of whether the entity has a physics component
	*******************************************************************************/
	bool HasPhysicsComponent(const Entity& _e);

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
	void AddPhysicsComponent(const Entity& _e,
							 const bool& _gravityEnabled = false,
							 const float& _mass = 1.f,
							 const float& _speed = 0.f,
							 const float& _moveDirection = 0.f,
							 const bool& _renderFlag = false);

	/*!*****************************************************************************
	\brief
	RemovePhysicsComponent function that removes the given entity from the system's
	stored list and remove the physics component from the entity itself

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
	GetMass function that returns the stored value of the entity's mass

	\param const Entity &
	A reference to a read-only Entity to get from

	\return float
	A copy of the value of the entity's mass
	*******************************************************************************/
	float GetMass(const Entity& _e);

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
	void SetMass(const Entity& _e, const float& _mass);

	/*!*****************************************************************************
	\brief
	GetSpeed function that returns the stored value of the entity's speed

	\param const Entity &
	A reference to a read-only Entity to get from

	\return float
	A copy of the value of the entity's speed
	*******************************************************************************/
	float GetSpeed(const Entity& _e);

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
	void SetSpeed(const Entity& _e, const float& _speed);

	/*!*****************************************************************************
	\brief
	GetMoveDirection function that returns the stored value of the entity's
	moveDirection in the form of radian rotations

	\param const Entity &
	A reference to a read-only Entity to remove the physics component from

	\return float
	A copy of the value of the entity's moveDirection
	*******************************************************************************/
	float GetMoveDirection(const Entity& _e);

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
	void SetMoveDirection(const Entity& _e, const float& _moveDirection);

	/*!*****************************************************************************
	\brief
	GetForces function that returns the stored value of the entity's net forces

	\param const Entity &
	A reference to a read-only Entity to

	\return Math::Vec2
	A copy of the value of the entity's net forces
	*******************************************************************************/
	Math::Vec2 GetForces(const Entity& _e);

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
	void SetForces(const Entity& _e, const Math::Vec2& _forces);

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
	void AddForces(const Entity& _e, const Math::Vec2& _forces);

	/*!*****************************************************************************
	\brief
	AddGravityForce function that adds the gravity force value to the stored value of the
	entity's forces to become the updated net forces

	\param const Entity &
	A reference to a read-only Entity to set

	\return void
	NULL
	*******************************************************************************/
	void AddGravityForce(const Entity& _e);

	/*!*****************************************************************************
	\brief
	GetVelocity function that returns the stored value of the entity's velocity

	\param const Entity &
	A reference to a read-only Entity to

	\return Math::Vec2
	A copy of the value of the entity's velocity
	*******************************************************************************/
	Math::Vec2 GetVelocity(const Entity& _e);

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
	void SetVelocity(const Entity& _e, const Math::Vec2& _velocity);

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
	void AddVelocity(const Entity& _e, const Math::Vec2& _velocity);

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
	void ScaleVelocity(const Entity& _e, const float& _scalar);

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
private:
	std::set<Entity> mPhysicsObjectList;	// Member variable storing list of entities to update dynamics for
	double mAccumulatedDT{ 0.0 };				// Member variable storing accumulatedDT
};

