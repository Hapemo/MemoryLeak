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

struct Contact {
	Contact(const Entity& _e1, const Entity& _e2) : e1{ _e1 }, e2{ _e2 } {};
	Entity e1;
	Entity e2;

	int e1Index;
	int e2Index;
	float penetration;
	Math::Vec2 normal;
	std::vector<Math::Vec2> contacts;

};

typedef bool (*CollisionCallback)(Contact &);

class Collision2DManager : public System {
public:
	void SetupCollisionDatabase();
	void RegisterCollisionTest(const ColliderType& typeA, const ColliderType& typeB, CollisionCallback function);

	void GenerateContactList();

	double DetermineRestitution(const Entity& e1, const Entity& e2);
	double DetermineFriction(const Entity& e1, const Entity& e2);

	void ResolveContact(Contact& contact);
private:
	CollisionCallback CollisionDatabase[static_cast<int>(ColliderType::MAXTYPESOFCOLLIDERS)][static_cast<int>(ColliderType::MAXTYPESOFCOLLIDERS)];
	std::vector<Contact> boardPhase;
	std::vector<Contact> contactList;

	const float EPSILON{ 0.0001f };
};
