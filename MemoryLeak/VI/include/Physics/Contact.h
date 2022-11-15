#pragma once

/*!*****************************************************************************
\brief Contact class that encapsulates information about a collision
*******************************************************************************/
class Contact {
public:
	/*!*****************************************************************************
	\brief
	Default constructor
	\param const Entity &
	A reference to a read-only entity
	\param const Entity &
	A reference to a read-only entity
	\return void
	NULL
	*******************************************************************************/
	Contact(const Entity& _obj1, const Entity& _obj2, const int& _obj1Type, const int& _obj2Type);

	/*!*****************************************************************************
	\brief
	DetermineRestitution function computes the restitution value between the two
	entities
	\param void
	NULL
	\return float
	The computed restitution
	*******************************************************************************/
	float DetermineRestitution();

	/*!*****************************************************************************
	\brief
	DetermineFriction function computes the friction value between the two
	entities
	\param void
	NULL
	\return float
	The computed friction
	*******************************************************************************/
	float DetermineFriction();

	float DetermineSeperatingVelocity();

	/*!*****************************************************************************
	Class variables
	*******************************************************************************/
	Entity obj[2]{};				// Array of entity
	int objType[2]{};				// Array of entity objType
	//double interTime{};				// Collision time
	Math::Vec2 normal{};			// Collision normal
	float penetration{};			// Collision penetration depths
	float combinedRestitution{};	// Combined restitution value
	float combinedFriction{};		// Combined friction value
	Math::Vec2 newVelocity[2]{};	// Computed new velocity after collision
	float seperatingVelocity{};		// Computed seperating velocity scalar value
	float contactImpulse{};			// Contact impulse
	Math::Vec2 contacts{};			// Points of contact of the collision
};