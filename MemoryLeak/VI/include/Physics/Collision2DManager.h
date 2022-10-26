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
	//Manifold(const Entity& _e1, const Entity& _e2) : {};

	Entity e1;
	Entity e2;

	float penetration;
	Math::Vec2 normal;
};

enum class ColliderType {
	CIRCLE = 0,
	RECT,
	MAXTYPESOFCOLLIDERS
};

typedef bool (*CollisionCallback)(void);

class Collision2DManager : public System {
public:
	void SetupCollisionDatabase();
	void RegisterCollisionTest(const ColliderType& typeA, const ColliderType& typeB, CollisionCallback function);

	void GenerateContactList();
private:
	CollisionCallback CollisionDatabase[static_cast<int>(ColliderType::MAXTYPESOFCOLLIDERS)][static_cast<int>(ColliderType::MAXTYPESOFCOLLIDERS)];
	std::vector<Contact> contactList;
};
