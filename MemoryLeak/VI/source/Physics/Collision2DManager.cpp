/*!*****************************************************************************
\file	Collision2DManager.cpp
\author Lee Hsien Wei, Joachim
\par	DP email: l.hsienweijoachim@digipen.edu
\par	Course: GAM200
\par	Group: Memory Leak Studios
\date	25-09-2022
\brief  This file contains the definition of the Collision System Class member
		functions which handles the collision detection and resolution of entities 
		stored in its list
*******************************************************************************/

// -----------------------------
// Include files
// -----------------------------
#include "ECSManager.h"

bool CI_CirclevsCircle(Contact& _contactInfo) {
	// Find relative velocity of both circles
	

	return false;
}

bool CI_RectvsRect(Contact& _contactInfo) {
	return false;
}

void Collision2DManager::SetupCollisionDatabase() {
	RegisterCollisionTest(ColliderType::CIRCLE, ColliderType::CIRCLE, CI_CirclevsCircle);
	RegisterCollisionTest(ColliderType::RECT, ColliderType::RECT, CI_RectvsRect);
}

void Collision2DManager::RegisterCollisionTest(const ColliderType& typeA, const ColliderType& typeB, CollisionCallback function) {
	CollisionDatabase[static_cast<int>(typeA)][static_cast<int>(typeB)] = function;
}

void Collision2DManager::GenerateContactList() {
	// Broad phase here

	for (auto e1{ mEntities.begin() }; e1 != mEntities.end(); ++e1) {
		for (auto e2{e1}; e2 != mEntities.end();++e2) {
			if (e1 == e2)
				continue;

			// Prevents checks against 2 non moving object
			//if (e1->GetComponent<Physics2D>().dynamicsEnabled || e2->GetComponent<Physics2D>().dynamicsEnabled) {	
				//CollisionDatabase
			//}

			// Callback function to generate contact
			Contact contact{*e1, *e2};
			//(*CollisionDatabase[static_cast<int>(e1->GetComponent<Collider2D>().typeID)][static_cast<int>(e2->GetComponent<Collider2D>().typeID)])(contact);
		}
	}
}