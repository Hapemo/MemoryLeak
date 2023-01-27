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
#include "Contact.h"
#include "ColliderType.h"
#include "QuadTree.h"

/*!*****************************************************************************
Define a function callback for collision dispatch
*******************************************************************************/
typedef bool (*CollisionCallback)(Contact&, const double&, const bool&);


/*!*****************************************************************************
\brief Collision2DManager system class that handles the collision store to detect
	   and resolve collisions
*******************************************************************************/
class Collision2DManager : public System {
public:
// -----------------------------
// Specific/Specialized Collision Check Lib
// -----------------------------
	//static std::vector<Entity> CI_PlayervsEnemy(const Entity& _player, const Entity& _enemy);

	//static bool SCI_RectvsCircle(const Math::Vec2& _rectPos, const Math::Vec2& _rectScale, const Math::Vec2& _circlePos, const float& _circleScale);

// -----------------------------
// Collision Callback Lib
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
	static bool CI_RectvsRect(Contact& _contact, const double& _dt, const bool& _dynamicCheck = false);

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
	static bool CI_CirclevsCircle(Contact& _contact, const double& _dt, const bool& _dynamicCheck = false);

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
	static bool CI_RectvsCircle(Contact& _contact, const double& _dt, const bool& _dynamicCheck = false);

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
	static bool CI_CirclevsRect(Contact& _contact, const double& _dt, const bool& _dynamicCheck = false);

// -----------------------------
// Component-related functions
// -----------------------------
	/*!*****************************************************************************
	\brief
	HasCollider function that checks if the given entity contains a collider
	\param const Entity &
	A reference to a read-only Entity to check
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
	database which uses the collider type value as index
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

	void Update(const double& _dt);

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
	EntitiesCollided function that checks if two given entities have collided by
	checking whether if a contact with the two entities exists
	\param const Entity &
	A reference to a read-only entity to compare with
	\param const Entity &
	A reference to a read-only entity to compare against
	\return bool
	Evaluated result of whether a collision happened between the two given entities
	*******************************************************************************/
	bool EntitiesCollided(const Entity& _e1, const Entity& _e2);

	bool CheckCollision(const Entity& _e1, const Entity& _e2, const bool& _dynamicCheck = false);

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

	/*!*****************************************************************************
	\brief
	ResolveContact function that resolves the collision by updating the entities'
	velocities, acceleration and forces
	\param Contact &
	A reference to the contact to resolve
	\param const double &
	A reference to a read-only variable containing the delta time
	\return void
	NULL
	*******************************************************************************/
	void ResolveContact(Contact& _contact, const double& _dt);

	/*!*****************************************************************************
	\brief
	PositionCorrection function that resolves the penetration of the entities by
	correcting their positions
	\param Contact &
	A reference to the contact to resolve
	\return void
	NULL
	*******************************************************************************/
	void PositionCorrection(Contact& _contact);

	QuadTree& GetQuadTree();

	void SetupQuadTree();

	void UpdateEntityInQuadTree(const Entity& _e);

	const std::vector<std::pair<Entity, Entity>>& GetPossibleContactList() const;

private:
	// Database of callback functions to collision checks 
	CollisionCallback mCollisionDatabase[static_cast<int>(ColliderType::MAXTYPESOFCOLLIDERS)][static_cast<int>(ColliderType::MAXTYPESOFCOLLIDERS)];
	
	QuadTree mQuadTree;
	std::vector<std::pair<Entity, Entity>> mPossibleContactList;
	std::vector<Contact> mContactList;		// List of contacts in the current frame

	bool mFirstUpdate{ true };

	const float	penAllowance{ 0.01f },		// Penetration allowance
				penPercentage{ 2.0f };		// Penetration percentage to correct

	double mAccumulatedDT{ 0.0 };					// Member variable storing accumulatedDT
	const double mFixedDT{ 1.0 / 60.0 };			// Fixed delta time step of 1/60 steps a second
	const double mAccumulatedDTCap{ 1.0 };			// Accumulated cannot store more than 1 second worth of updates

};