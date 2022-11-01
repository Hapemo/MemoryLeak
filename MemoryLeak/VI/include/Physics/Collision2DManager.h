/*!*****************************************************************************
\file	Collision2DManager.h
\author Lee Hsien Wei, Joachim
\par	DP email: l.hsienweijoachim@digipen.edu
\par	Course: GAM200
\par	Group: Memory Leak Studios
\date	25-09-2022
\brief  This file contains the declaration of the Collision System Class member
		functions which handles the collision detection and resolution of entities
		stored in its list. It also defines the CollisionStore struct that is
		used to store the information about the entity pair and its collision
*******************************************************************************/
#pragma once

// -----------------------------
// Include files
// -----------------------------
#include "ECS_systems.h"

class Contact {
public:
	Contact(const Entity& _obj1, const Entity& _obj2);

	float DetermineRestitution();
	float DetermineFriction();

	Entity obj1;
	Entity obj2;

	int obj1Type{};
	int obj2Type{};
	double interTime{};
	float penetration{};
	Math::Vec2 normal{};
	std::vector<Math::Vec2> contacts{};
};

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
	static bool CI_RectvsRect(Contact& _contact, const double& _dt);
	static bool CI_CirclevsCircle(Contact& _contact, const double& _dt);
	static bool CI_RectvsCircle(Contact& _contact, const double& _dt);
	static bool CI_CirclevsRect(Contact& _contact, const double& _dt);

// -----------------------------
// Component-related functions
// -----------------------------
	bool HasCollider(const Entity& _e);
	int NoOfColliders(const Entity& e);

// -----------------------------
// System functions
// -----------------------------
	void SetupCollisionDatabase();
	void RegisterCollisionTest(const ColliderType& typeA, const ColliderType& typeB, CollisionCallback function);

	void ResolveCollisions(const double &_dt);
	void GenerateContactList(const double& _dt);
	void ClearContactList();

	void ResolveContact(Contact& _contact);
	void UpdatePositions(const Contact& _contact);
	void PositionCorrection(Contact& _contact);
	void UpdateVelocities(Contact& _contact, const double& _dt);

private:
	CollisionCallback mCollisionDatabase[static_cast<int>(ColliderType::MAXTYPESOFCOLLIDERS)][static_cast<int>(ColliderType::MAXTYPESOFCOLLIDERS)];
	std::vector<Contact> mContactList;

	// const float penEpsilion{ 0.0001f };
	const float	penAllowance{ 0.05f },
				penPercentage{ 0.4f };
};