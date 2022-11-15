/*!*****************************************************************************
\file	Collision2DManager.h
\author Lee Hsien Wei, Joachim
\par	DP email: l.hsienweijoachim@digipen.edu
\par	Course: GAM200
\par	Group: Memory Leak Studios
\date	01-11-2022
\brief  This file contains the declaration of the Collision System Class and its
		member functions which handles a database of possible collision checks
		stored in its list. It also defines the CollisionStore struct that is
		used to store the information about the entity pair and its collision
*******************************************************************************/
#pragma once

// -----------------------------
// Include files
// -----------------------------
#include "ECS_systems.h"

/*!*****************************************************************************
\brief ColliderType enum class that encapsulates the different types of colliders
*******************************************************************************/
enum class ColliderType : int {
	RECT = 1,				// Rect
	CIRCLE,					// Circle
	MAXTYPESOFCOLLIDERS		// Max size
};


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

/*!*****************************************************************************
Define a function callback for collision dispatch
*******************************************************************************/
typedef bool (*CollisionCallback)(Contact&, const double&);


/*!*****************************************************************************
\brief Collision2DManager system class that handles the collision store to detect
	   and resolve collisions
*******************************************************************************/
class Collision2DManager : public System {
public:
	// -----------------------------
	// Collision Checks Lib
	// -----------------------------
		/*!*****************************************************************************
		\brief
		CI_RectvsRect function that checks for collision between 2 entities that have
		AABB/rectangular colliders
		\param Contact &
		A reference to struct containing entity pair data to check
		\param const double &
		A reference to a read-only variable containing the delta time
		\return bool
		Evaluated result of whether collision has occurred between the given entity pair
		*******************************************************************************/
	static bool CI_RectvsRect(Contact& _contact, const double& _dt);
	/*!*****************************************************************************
	\brief
	CI_CirclevsCircle function that checks for collision between 2 entities that
	have circular colliders
	\param Contact &
	A reference to struct containing entity pair data to check
	\param const double &
	A reference to a read-only variable containing the delta time
	\return bool
	Evaluated result of whether collision has occurred between the given entity pair
	*******************************************************************************/
	static bool CI_CirclevsCircle(Contact& _contact, const double& _dt);
	/*!*****************************************************************************
	\brief
	CI_RectvsCircle function that currently returns false and is a placeholder
	\param Contact &
	A reference to struct containing entity pair data to check
	\param const double &
	A reference to a read-only variable containing the delta time
	\return bool
	Evaluated result of whether collision has occurred between the given entity pair
	*******************************************************************************/
	static bool CI_RectvsCircle(Contact& _contact, const double& _dt);
	/*!*****************************************************************************
	\brief
	CI_CirclevsRect function that currently returns false and is a placeholder
	\param Contact &
	A reference to struct containing entity pair data to check
	\param const double &
	A reference to a read-only variable containing the delta time
	\return bool
	Evaluated result of whether collision has occurred between the given entity pair
	*******************************************************************************/
	static bool CI_CirclevsRect(Contact& _contact, const double& _dt);

	// -----------------------------
	// Component-related functions
	// -----------------------------
		/*!*****************************************************************************
		\brief
		HasCollider function that checks if the given entity contains a collider
		\param const Entity &
		A reference to a read-only Entity to add collider to
		\return bool
		Evaluated result of whether the entity has a collider
		*******************************************************************************/
	bool HasCollider(const Entity& _e);
	//int NoOfColliders(const Entity& e);

// -----------------------------
// System functions
// -----------------------------
	/*!*****************************************************************************
	\brief
	SetupCollisionDatabase function sets up the database registry of the collision
	callback functions
	\param void
	NULL
	\return void
	NULL
	*******************************************************************************/
	void SetupCollisionDatabase();
	/*!*****************************************************************************
	\brief
	RegisterCollisionTest function adds the given callback function to the system's
	database uses the collider type value as index
	\param const ColliderType &
	Reference to read-only enum value containing the 1st collider type
	\param const ColliderType &
	Reference to read-only enum value containing the 2nd collider type
	\param CollisionCallback
	The collision check function
	\return void
	NULL
	*******************************************************************************/
	void RegisterCollisionTest(const ColliderType& typeA, const ColliderType& typeB, CollisionCallback function);

	/*!*****************************************************************************
	\brief
	ResolveCollisions function that calls the different system functions in order to
	detect & resolve collisions
	\param const double &
	A reference to a read-only variable containing the delta time
	\return void
	NULL
	*******************************************************************************/
	void ResolveCollisions(const double& _dt);
	/*!*****************************************************************************
	\brief
	GenerateContactList function that detects for collision between entities in the
	state and push the contact into the contactList container for resolution
	\param const double &
	A reference to a read-only variable containing the delta time
	\return void
	NULL
	*******************************************************************************/
	void GenerateContactList(const double& _dt);
	/*!*****************************************************************************
	\brief
	ClearContactList function that clears the contactList container for the next
	frame
	\param void
	NULL
	\return void
	NULL
	*******************************************************************************/
	void ClearContactList();

	void ResolveContact(Contact& _contact);
	void PositionCorrection(Contact& _contact);
	//void ResolvePositions();
	//void ResolveVelocities(const double& _dt);
	//void ResolveContactVelocity(Contact& _contact, const double& _dt);
	//void ResolvePenetration(Contact& _contact);
private:
	// Database of callback functions to collision checks 
	CollisionCallback mCollisionDatabase[static_cast<int>(ColliderType::MAXTYPESOFCOLLIDERS)][static_cast<int>(ColliderType::MAXTYPESOFCOLLIDERS)];
	std::vector<Contact> mContactList;				// List of contacts in the current frame

	// const float penEpsilion{ 0.0001f };
	const float	penAllowance{ 0.05f },		// Penetration allowance
		penPercentage{ 0.4f };		// Penetration percentage to correct
};