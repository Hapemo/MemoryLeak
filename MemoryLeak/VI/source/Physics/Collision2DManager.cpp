/*!*****************************************************************************
\file	Collision2DManager.cpp
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

// -----------------------------
// Include files
// -----------------------------
#include "ECSManager.h"


Contact::Contact(const Entity& _obj1, const Entity& _obj2, const int& _obj1Type, const int& _obj2Type) {
	// Leave Empty
	obj[0] = _obj1;
	obj[1] = _obj2;
	objType[0] = _obj1Type;
	objType[1] = _obj2Type;

	combinedRestitution = DetermineRestitution();
	combinedFriction = DetermineFriction();
	seperatingVelocity = DetermineSeperatingVelocity();
}

float Contact::DetermineRestitution() {
	if (!obj[0].HasComponent<Physics2D>() || !obj[1].HasComponent<Physics2D>()) {
		return obj[0].HasComponent<Physics2D>() ? obj[0].GetComponent<Physics2D>().restitution : obj[1].HasComponent<Physics2D>() ? obj[1].GetComponent<Physics2D>().restitution : 0.f;
	}

	return std::min(obj[0].GetComponent<Physics2D>().restitution, obj[1].GetComponent<Physics2D>().restitution);
}

float Contact::DetermineFriction() {
	if (!obj[0].HasComponent<Physics2D>() || !obj[1].HasComponent<Physics2D>()) {
		return obj[0].HasComponent<Physics2D>() ? std::sqrt(obj[0].GetComponent<Physics2D>().friction) : obj[1].HasComponent<Physics2D>() ? std::sqrt(obj[1].GetComponent<Physics2D>().friction) : 0.f;
	}

	return std::sqrt(obj[0].GetComponent<Physics2D>().friction * obj[1].GetComponent<Physics2D>().friction);
}

float Contact::DetermineSeperatingVelocity() {
	Math::Vec2 relVel{};
	if (obj[0].HasComponent<Physics2D>() && obj[1].HasComponent<Physics2D>())
		relVel = obj[0].GetComponent<Physics2D>().velocity - obj[1].GetComponent<Physics2D>().velocity;
	else if (obj[0].HasComponent<Physics2D>())
		relVel = obj[0].GetComponent<Physics2D>().velocity;
	else if (obj[1].HasComponent<Physics2D>())
		relVel = obj[1].GetComponent<Physics2D>().velocity;

	return Math::Dot(relVel, normal);
}


bool Collision2DManager::CI_RectvsRect(Contact& _contact, const double& _dt) {
	// Get reference to the entities
	Entity& obj1{ _contact.obj[0] },
		& obj2{ _contact.obj[1] };

	// Store center and scale of both entities
	Math::Vec2	center1{ Math::Vec2{obj1.GetComponent<Transform>().translation} + obj1.GetComponent<RectCollider>().centerOffset },
		scale1{ static_cast<float>(static_cast<double>(obj1.GetComponent<Transform>().scale.x) * static_cast<double>(obj1.GetComponent<RectCollider>().scaleOffset.x) / 2.0),
				static_cast<float>(static_cast<double>(obj1.GetComponent<Transform>().scale.y) * static_cast<double>(obj1.GetComponent<RectCollider>().scaleOffset.y) / 2.0) },
		center2{ Math::Vec2{obj2.GetComponent<Transform>().translation} + obj2.GetComponent<RectCollider>().centerOffset },
		scale2{ static_cast<float>(static_cast<double>(obj2.GetComponent<Transform>().scale.x) * static_cast<double>(obj2.GetComponent<RectCollider>().scaleOffset.x) / 2.0),
				static_cast<float>(static_cast<double>(obj2.GetComponent<Transform>().scale.y) * static_cast<double>(obj2.GetComponent<RectCollider>().scaleOffset.y) / 2.0) };

	// Compute min and max of both entities
	Math::Vec2	aabb1min{ center1 - scale1 },
		aabb1max{ center1 + scale1 },
		aabb2min{ center2 - scale2 },
		aabb2max{ center2 + scale2 };

	// Static check
	if (aabb1max.x < aabb2min.x)
		return false;
	if (aabb1min.x > aabb2max.x)
		return false;
	if (aabb1max.y < aabb2min.y)
		return false;
	if (aabb1min.y > aabb2max.y)
		return false;

	// Dynamic check
		// Compute relative velocity
	Math::Vec2 Vb{};
	if (obj2.HasComponent<Physics2D>() && obj1.HasComponent<Physics2D>())
		Vb = obj2.GetComponent<Physics2D>().velocity * static_cast<float>(_dt) - obj1.GetComponent<Physics2D>().velocity * static_cast<float>(_dt);
	else if (obj1.HasComponent<Physics2D>())
		Vb = obj1.GetComponent<Physics2D>().velocity * static_cast<float>(_dt);
	else if (obj2.HasComponent<Physics2D>())
		Vb = obj2.GetComponent<Physics2D>().velocity * static_cast<float>(_dt);

	// Check if relative velocity is zero
	if (Vb == Math::Vec2{ 0.f, 0.f })
		return false;

	double tFirst{ 0 }, tLast{ _dt }, tTmp{ 0 };

	// ------ X axis -----
	if (static_cast<double>(Vb.x) < 0.0) {
		if (static_cast<double>(aabb1min.x) > static_cast<double>(aabb2max.x)) // Case 1
			return false;
		if (static_cast<double>(aabb1max.x) < static_cast<double>(aabb2min.x)) {// Case 4
			tTmp = (static_cast<double>(aabb1max.x) - static_cast<double>(aabb2min.x)) / static_cast<double>(Vb.x);
			tFirst = tTmp > tFirst ? tTmp : tFirst;
		}
		if (static_cast<double>(aabb1min.x) < static_cast<double>(aabb2max.x)) {// Case 4
			tTmp = (static_cast<double>(aabb1min.x) - static_cast<double>(aabb2max.x)) / static_cast<double>(Vb.x);
			tLast = tTmp < tLast ? tTmp : tLast;
		}
	}
	if (static_cast<double>(Vb.x) > 0.0) {
		if (static_cast<double>(aabb1min.x) > static_cast<double>(aabb2max.x)) {// Case 2
			tTmp = (static_cast<double>(aabb1min.x) - static_cast<double>(aabb2max.x)) / static_cast<double>(Vb.x);
			tFirst = tTmp > tFirst ? tTmp : tFirst;
		}
		if (static_cast<double>(aabb1max.x) > static_cast<double>(aabb2min.x)) {// Case 2
			tTmp = (static_cast<double>(aabb1max.x) - static_cast<double>(aabb2min.x)) / static_cast<double>(Vb.x);
			tLast = tTmp < tLast ? tTmp : tLast;
		}
		if (static_cast<double>(aabb1max.x) < static_cast<double>(aabb2min.x)) // Case 3
			return false;
	}
	if (tFirst > tLast) // Case 5
		return false;

	// ------ Y axis -----
	if (static_cast<double>(Vb.y) < 0.0) {
		if (static_cast<double>(aabb1min.y) > static_cast<double>(aabb2max.y)) // Case 1
			return false;
		if (static_cast<double>(aabb1max.y) < static_cast<double>(aabb2min.y)) {// Case 4
			tTmp = (static_cast<double>(aabb1max.y) - static_cast<double>(aabb2min.y)) / static_cast<double>(Vb.y);
			tFirst = tTmp > tFirst ? tTmp : tFirst;
		}
		if (static_cast<double>(aabb1min.y) < static_cast<double>(aabb2max.y)) {// Case 4
			tTmp = (static_cast<double>(aabb1min.y) - static_cast<double>(aabb2max.y)) / static_cast<double>(Vb.y);
			tLast = tTmp < tLast ? tTmp : tLast;
		}
	}
	if (static_cast<double>(Vb.y) > 0.0) {
		if (static_cast<double>(aabb1min.y) > static_cast<double>(aabb2max.y)) {// Case 2
			tTmp = (static_cast<double>(aabb1min.y) - static_cast<double>(aabb2max.y)) / static_cast<double>(Vb.y);
			tFirst = tTmp > tFirst ? tTmp : tFirst;
		}
		if (static_cast<double>(aabb1max.y) > static_cast<double>(aabb2min.y)) {// Case 2
			tTmp = (static_cast<double>(aabb1max.y) - static_cast<double>(aabb2min.y)) / static_cast<double>(Vb.y);
			tLast = tTmp < tLast ? tTmp : tLast;
		}
		if (static_cast<double>(aabb1max.y) < static_cast<double>(aabb2min.y)) // Case 3
			return false;
	}
	if (tFirst > tLast) // Case 5
		return false;

	// Use first as intersection time
	_contact.interTime = tFirst;

	// Compute position at intersection time
	Math::Vec2 obj1NewPos{ center1 },
		obj2NewPos{ center2 };
	if (obj1.HasComponent<Physics2D>())
		obj1NewPos += obj1.GetComponent<Physics2D>().velocity * static_cast<float>(_dt);
	if (obj2.HasComponent<Physics2D>())
		obj2NewPos += obj2.GetComponent<Physics2D>().velocity * static_cast<float>(_dt);

	// Compute penetration
	Math::Vec2 distVec{ obj1NewPos - obj2NewPos };
	Math::Vec2 diff{ scale1.x + scale2.x - std::fabs(distVec.x),
					 scale1.y + scale2.y - std::fabs(distVec.y) };

	//if (0.f < dist.x) {
	//	if (0.f < dist.y) {
	// 
	// Find axis that penetrates less and use it to resolve collision
	if (diff.x < diff.y) {
		// Set contact information
		_contact.normal = distVec.x < 0 ? Math::Vec2{ -1.f, 0.f } : Math::Vec2{ 1.f, 0.f };
		_contact.penetration = diff.x;
		_contact.contacts = _contact.normal * diff.x + obj1NewPos;
	}
	else {
		// Set contact information
		_contact.normal = distVec.y < 0 ? Math::Vec2{ 0.f, 1.f } : Math::Vec2{ 0.f, -1.f };
		_contact.penetration = diff.y;
		_contact.contacts = _contact.normal * diff.y + obj1NewPos;
	}
	//	}
	//}

	return true;
}

bool Collision2DManager::CI_CirclevsCircle(Contact& _contact, const double& _dt) {
	// Get reference to the entities
	Entity& obj1{ _contact.obj[0] },
		& obj2{ _contact.obj[1] };

	// Store radius of circle colliders
	float  obj1R{ (obj1.GetComponent<Transform>().scale.x * obj1.GetComponent<CircleCollider>().scaleOffset) / 2.f },
		obj2R{ (obj2.GetComponent<Transform>().scale.x * obj2.GetComponent<CircleCollider>().scaleOffset) / 2.f };

	// Store position of circle colliders
	Math::Vec2 obj1Pos{ obj1.GetComponent<Transform>().translation + obj1.GetComponent<CircleCollider>().centerOffset },
		obj2Pos{ obj2.GetComponent<Transform>().translation + obj2.GetComponent<CircleCollider>().centerOffset };

	float sqDist{ Math::SqDistance(obj2Pos, obj1Pos) };

	//if (sqDist >= (obj1R + obj2R) * (obj1R + obj2R))
	//	return false;

	//if (sqDist == 0.f) {
	//	_contact.penetration = obj1R;
	//	_contact.normal = Math::Vec2{ 1.f, 0.f };
	//	_contact.contacts = obj1Pos;
	//}
	//else {
	//	_contact.penetration = (obj1R + obj2R) - sqrt(sqDist);
	//	_contact.normal = (obj2Pos - obj1Pos).Normalized();
	//	_contact.contacts = _contact.normal * obj1R + obj1Pos;
	//}

// Static
	// Check if the distance between the circles' centers is smaller than their radius
	if (sqDist < ((obj1R + obj2R) * (obj1R + obj2R))) {
		// On top of each other
		if (sqDist == 0.f) {
			// Set contact information
			_contact.penetration = obj1R;
			_contact.normal = Math::Vec2{ 1.f, 0.f };
			_contact.contacts = obj1Pos;
		}
		else {
			// Set contact information
			_contact.penetration = (obj1R + obj2R) - sqrt(sqDist);
			_contact.normal = (obj2Pos - obj1Pos).Normalize();
			_contact.contacts = _contact.normal * obj1R + obj1Pos;
		}

		return true;
	}

	// Find the relative velocity of both entities
	Math::Vec2 relVel{};
	if (obj1.HasComponent<Physics2D>() && obj2.HasComponent<Physics2D>())
		relVel = obj1.GetComponent<Physics2D>().velocity * static_cast<float>(_dt) - obj2.GetComponent<Physics2D>().velocity * static_cast<float>(_dt);
	else if (_contact.obj[0].HasComponent<Physics2D>())
		relVel = obj1.GetComponent<Physics2D>().velocity * static_cast<float>(_dt);
	else if (_contact.obj[1].HasComponent<Physics2D>())
		relVel = obj2.GetComponent<Physics2D>().velocity * static_cast<float>(_dt);

	// Check if relVel is 0 (Will not collide)
	if (relVel == Math::Vec2{ 0.f, 0.f })
		return false;

	// Dynamic 
		// Reduce problem by checking a static circle (pillar) and a moving point (ray/line)
			// Create a third circle that inherits the following:
			//	second object's collider's translation (Transform + centreOffset)
			//  radius is the sum of the radius of the 2 circles
			//  scaleOffset is 1
	Transform tDataTmpCircle{ obj2.GetComponent<Transform>() };
	tDataTmpCircle.translation += obj2.GetComponent<CircleCollider>().centerOffset;
	tDataTmpCircle.scale = obj1.GetComponent<Transform>().scale * obj1.GetComponent<CircleCollider>().scaleOffset +
		obj2.GetComponent<Transform>().scale * obj2.GetComponent<CircleCollider>().scaleOffset;
	double  tmpCircleRadius{ static_cast<double>(tDataTmpCircle.scale.x) / 2.0 };

	// Create a ray that starts from first object's position and goes in the direction of the relative velocity
	Transform tDataTmpRay{ obj1.GetComponent<Transform>() };
	tDataTmpRay.translation += obj1.GetComponent<CircleCollider>().centerOffset;
	// Compute rotation from relative velocity
	if (relVel.y != 0.f && relVel.x >= 0.f)
		tDataTmpRay.rotation = atan2f(relVel.x, relVel.y);
	else if (relVel.y == 0.f && relVel.x > 0)
		tDataTmpRay.rotation = static_cast<float>(Math::PI / 2.0);
	else if (relVel.y != 0 && relVel.x < 0.f)
		tDataTmpRay.rotation = static_cast<float>(Math::PI / 2.0 + atan2(relVel.x, relVel.y));
	else
		tDataTmpRay.rotation = static_cast<float>(3.0 * Math::PI / 2.0);
	tDataTmpRay.scale.x = relVel.Magnitude();

	// Check if collision will occur 
		// Calculate m and check if ray is moving away from circle
	double m{ static_cast<double>(Math::Dot(tDataTmpCircle.translation - tDataTmpRay.translation, relVel.Normalized())) };
	if (
		(m < 0.0) &&
		(static_cast<double>((tDataTmpCircle.translation - tDataTmpRay.translation).SqMagnitude())
		> tmpCircleRadius * tmpCircleRadius)
		)
		return false;	// Ray will never hit the circle

	// Calculate and check if the closest distance to the circle is larger than the circle's radius
	double n2{ static_cast<double>((tDataTmpCircle.translation - tDataTmpRay.translation).SqMagnitude()) - (m * m) };
	if (n2 > tmpCircleRadius * tmpCircleRadius)
		return false;	// Ray  will never hit the circle

	// Find intersection time and take minimum value
	double s{ sqrt(tmpCircleRadius * tmpCircleRadius - n2) };
	double tmpInterTime1{ (m - s) / relVel.Magnitude() },
		tmpInterTime2{ (m + s) / relVel.Magnitude() };
	double interTime = (tmpInterTime1 < tmpInterTime2) ? tmpInterTime1 : tmpInterTime2;

	// Check if the intersection time is within 1 unit
	if (0.0 <= interTime && interTime <= 1.0) {
		// Set intersection time
		_contact.interTime = interTime;

		// Compute new positions 
		Math::Vec2 obj1NewPos{ obj1Pos },
			obj2NewPos{ obj2Pos };
		if (obj1.HasComponent<Physics2D>())
			obj1NewPos += obj1.GetComponent<Physics2D>().velocity * static_cast<float>(_dt);
		if (obj2.HasComponent<Physics2D>())
			obj2NewPos += obj2.GetComponent<Physics2D>().velocity * static_cast<float>(_dt);

		// Set contact information
		_contact.penetration = (obj1R + obj2R) - sqrt(Math::SqDistance(obj1NewPos, obj2NewPos));
		_contact.normal = (obj2NewPos - obj1NewPos).Normalize();
		_contact.contacts = _contact.normal * obj1R + obj1NewPos;

		return true;
	}
	else
		return false;
}

bool Collision2DManager::CI_CirclevsRect(Contact& _contact, const double& _dt) {
	_contact;
	_dt;

	return false;
}

bool Collision2DManager::CI_RectvsCircle(Contact& _contact, const double& _dt) {
	_contact;
	_dt;

	return false;
}

bool Collision2DManager::HasCollider(const Entity& _e) {
	return (_e.HasComponent<RectCollider>() || _e.HasComponent<CircleCollider>() /*|| _e.HasComponent<RectCollider>() || _e.HasComponent<RectCollider>()*/)
		? true : false;
}

//int Collision2DManager::NoOfColliders(const Entity& _e) {
//	int count{ 0 };
//	
//	if (_e.HasComponent<RectCollider>())
//		++count;
//	if (_e.HasComponent<CircleCollider>())
//		++count;
//
//	return count;
//}

void Collision2DManager::SetupCollisionDatabase() {
	RegisterCollisionTest(ColliderType::CIRCLE, ColliderType::CIRCLE, CI_CirclevsCircle);
	RegisterCollisionTest(ColliderType::RECT, ColliderType::RECT, CI_RectvsRect);
	RegisterCollisionTest(ColliderType::CIRCLE, ColliderType::RECT, CI_CirclevsRect);
	RegisterCollisionTest(ColliderType::RECT, ColliderType::CIRCLE, CI_RectvsCircle);
}

void Collision2DManager::RegisterCollisionTest(const ColliderType& typeA, const ColliderType& typeB, CollisionCallback function) {
	mCollisionDatabase[static_cast<int>(typeA)][static_cast<int>(typeB)] = function;
}


void Collision2DManager::ResolveCollisions(const double& _dt) {
	// Check for collision and generate contact list
	GenerateContactList(_dt);
	//bool notplayer = false;
	// Resolve collision
	for (Contact& item : mContactList) {
		ResolveContact(item, _dt);
		PositionCorrection(item);

		// Impulse response not working
		// For now, we just disable the movement
		//if (item.obj1.HasComponent<Physics2D>()) 
		//	item.obj1.GetComponent<Physics2D>().dynamicsEnabled = false;
		//if (item.obj2.HasComponent<Physics2D>())
		//	item.obj2.GetComponent<Physics2D>().dynamicsEnabled = false;

		// For now, we just clear the movement
		/*if (item.obj1.HasComponent<Physics2D>()) {
			item.obj1.GetComponent<Physics2D>().acceleration = Math::Vec2{ 0.f, 0.f };
			item.obj1.GetComponent<Physics2D>().velocity = Math::Vec2{ 0.f, 0.f };
			item.obj1.GetComponent<Physics2D>().accumulatedForce = Math::Vec2{ 0.f, 0.f };
			item.obj1.GetComponent<Physics2D>().forceList.clear();
		}
		if (item.obj2.HasComponent<Physics2D>()) {
			item.obj2.GetComponent<Physics2D>().acceleration = Math::Vec2{ 0.f, 0.f };
			item.obj2.GetComponent<Physics2D>().velocity = Math::Vec2{ 0.f, 0.f };
			item.obj2.GetComponent<Physics2D>().accumulatedForce = Math::Vec2{ 0.f, 0.f };
			item.obj2.GetComponent<Physics2D>().forceList.clear();
		}*/
	}

	ClearContactList();
}

void Collision2DManager::GenerateContactList(const double& _dt) {
	// Broad Phase Here


	// For now, we loop through the entity list
	for (auto e1{ mEntities.begin() }; e1 != mEntities.end(); ++e1) {
		if (!e1->GetComponent<General>().isActive)
			continue;

		for (auto e2{ e1 }; e2 != mEntities.end(); ++e2) {
			if (e1 == e2)
				continue;

			if (!e2->GetComponent<General>().isActive)
				continue;

			//if (!e1->HasComponent<Collider2D>() || !e2->HasComponent<Collider2D>())
			//	continue;
			// Prevents checks against 2 non moving object
			//if (!e1->GetComponent<Physics2D>().dynamicsEnabled || !e2->GetComponent<Physics2D>().dynamicsEnabled)	
			//	continue;

			// Check if either of the entities do not have collider
			if (!HasCollider(*e1) || !HasCollider(*e2))
				continue;

			// Code has not accounted for multiple colliders attached to an entity despite it being a constraint made to me by group members
			//for (int i{ 0 }; i < NoOfColliders(*e1); ++i){
			// Find collider type of 1st entity
			int e1Type{ 0 };
			if (e1->HasComponent<RectCollider>())
				e1Type = static_cast<int>(ColliderType::RECT);
			else if (e1->HasComponent<CircleCollider>())
				e1Type = static_cast<int>(ColliderType::CIRCLE);
			else
				continue;

			//	for (int j{ 0 }; j < NoOfColliders(*e2); ++j) {
			// Find collider type of 2nd entity
			int e2Type{ 0 };
			if (e2->HasComponent<RectCollider>())
				e2Type = static_cast<int>(ColliderType::RECT);
			else if (e2->HasComponent<CircleCollider>())
				e2Type = static_cast<int>(ColliderType::CIRCLE);
			else
				continue;

			// Initialize contact
			Contact contact{ *e1, *e2, e1Type, e2Type };

			// Call function to check for collision
			// If it returns true, means collision occurred
			if ((*mCollisionDatabase[static_cast<int>(contact.objType[0])][static_cast<int>(contact.objType[1])])(contact, _dt)) {
				mContactList.push_back(contact);
				LOG_INFO("Collision Detected\n");
			}
		}
	}

}

void Collision2DManager::ClearContactList() {
	mContactList.clear();
}

void Collision2DManager::ResolveContact(Contact& _contact, const double& _dt) {
	// Store bool value of whether entity has physics component
	bool obj1HasP{ _contact.obj[0].HasComponent<Physics2D>() },
		obj2HasP{ _contact.obj[0].HasComponent<Physics2D>() };

	// Check for infinite mass of both objects
	if (obj1HasP && obj2HasP) {
		if (_contact.obj[0].GetComponent<Physics2D>().mass == 0.f && _contact.obj[1].GetComponent<Physics2D>().mass == 0.f) {
			physics2DManager->SetVelocity(_contact.obj[0], { 0.f, 0.f });
			physics2DManager->SetAcceleration(_contact.obj[0], { 0.f, 0.f });
			physics2DManager->SetAccumulatedForce(_contact.obj[0], { 0.f, 0.f });

			physics2DManager->SetVelocity(_contact.obj[1], { 0.f, 0.f });
			physics2DManager->SetAcceleration(_contact.obj[1], { 0.f, 0.f });
			physics2DManager->SetAccumulatedForce(_contact.obj[1], { 0.f, 0.f });
			return;
		}
	}

	// Store positions
	Math::Vec2 obj1Pos{ _contact.obj[0].GetComponent<Transform>().translation },
		obj2Pos{ _contact.obj[1].GetComponent<Transform>().translation };
	if (_contact.objType[0] == static_cast<int>(ColliderType::RECT))
		obj1Pos += _contact.obj[0].GetComponent<RectCollider>().centerOffset;
	else if (_contact.objType[0] == static_cast<int>(ColliderType::CIRCLE))
		obj1Pos += _contact.obj[0].GetComponent<CircleCollider>().centerOffset;
	if (_contact.objType[1] == static_cast<int>(ColliderType::RECT))
		obj2Pos += _contact.obj[1].GetComponent<RectCollider>().centerOffset;
	else if (_contact.objType[1] == static_cast<int>(ColliderType::CIRCLE))
		obj2Pos += _contact.obj[1].GetComponent<CircleCollider>().centerOffset;

	// Calculate radii from COM to contact
	Math::Vec2	rObj1{ _contact.contacts - obj1Pos },
		rObj2{ _contact.contacts - obj2Pos };

	// Relative Velocity
	Math::Vec2 relVel{};
	if (obj1HasP && obj2HasP)
		relVel = _contact.obj[1].GetComponent<Physics2D>().velocity + Math::Cross(_contact.obj[1].GetComponent<Physics2D>().angularVelocity, rObj2) -
		_contact.obj[0].GetComponent<Physics2D>().velocity - Math::Cross(_contact.obj[0].GetComponent<Physics2D>().angularVelocity, rObj1);
	else if (obj2HasP)
		relVel = _contact.obj[1].GetComponent<Physics2D>().velocity + Math::Cross(_contact.obj[1].GetComponent<Physics2D>().angularVelocity, rObj2);
	else
		relVel = _contact.obj[0].GetComponent<Physics2D>().velocity - Math::Cross(_contact.obj[0].GetComponent<Physics2D>().angularVelocity, rObj1);

	// Relative velocity along the normal
	float contactVel{ Math::Dot(relVel, _contact.normal) };

	// Do not resolve if velocities are seperating
	if (contactVel > 0)
		return;

	// Velocity impulse
	//float	rObj1CrossN{ Math::Cross(rObj1, _contact.normal) },
	//		rObj2CrossN{ Math::Cross(rObj2, _contact.normal) };

	float invMassSum{};
	if (obj1HasP)
		invMassSum += (_contact.obj[0].GetComponent<Physics2D>().mass == 0.f) ? 0.f : 1.f / _contact.obj[0].GetComponent<Physics2D>().mass;;
	if (obj2HasP)
		invMassSum += (_contact.obj[1].GetComponent<Physics2D>().mass == 0.f) ? 0.f : 1.f / _contact.obj[1].GetComponent<Physics2D>().mass;;

	// Calculate impulse scalar J
	float scalar{ -(1.f + _contact.combinedRestitution) * contactVel };
	scalar /= invMassSum;
	//scalar /= static_cast<float>(_contact.contacts.size());

	// Apply velocity impulse
	Math::Vec2 impulse{ _contact.normal * scalar };
	if (obj1HasP)
		physics2DManager->ApplyImpulse(_contact.obj[0], -(impulse), { 0.f, 0.f });
	if (obj2HasP)
		physics2DManager->ApplyImpulse(_contact.obj[1], impulse, { 0.f, 0.f });

	// Compute new acceleration/force
	Math::Vec2 newForce{};
	if (obj1HasP) {
		//Math::Vec2 newAccel{ -impulse / static_cast<float>(_dt) };
		//physics2DManager->SetAcceleration(_contact.obj[0], newAccel);
		if (!_contact.obj[0].GetComponent<Physics2D>().forceList.empty()) {
			Force& moveForce{ _contact.obj[0].GetComponent<Physics2D>().forceList[0] };
			if (moveForce.forceID == 0) {
				//Math::Vec2 newForce{ newAccel * (physics2DManager->GetMass(_contact.obj[0]) == 0.f ? 0.f : physics2DManager->GetMass(_contact.obj[0])) };
				if (physics2DManager->GetMass(_contact.obj[0]) == 0.f)
					newForce = -impulse;
				else
					newForce = -impulse / physics2DManager->GetMass(_contact.obj[0]);
				moveForce.linearForce.unitDirection = newForce.Normalized();
				moveForce.linearForce.magnitude = newForce.Magnitude();
			}
		}
	}

	if (obj2HasP) {
		//Math::Vec2 newAccel{ impulse / static_cast<float>(_dt) };
		//physics2DManager->SetAcceleration(_contact.obj[1], newAccel);
		if (!_contact.obj[1].GetComponent<Physics2D>().forceList.empty()) {
			Force& moveForce{ _contact.obj[1].GetComponent<Physics2D>().forceList[0] };
			if (moveForce.forceID == 0) {
				//Math::Vec2 newForce{ newAccel * (physics2DManager->GetMass(_contact.obj[1]) == 0.f ? 0.f : physics2DManager->GetMass(_contact.obj[1])) };
				if (physics2DManager->GetMass(_contact.obj[1]) == 0.f)
					newForce = impulse;
				else
					newForce = impulse / physics2DManager->GetMass(_contact.obj[1]);
				moveForce.linearForce.unitDirection = newForce.Normalized();
				moveForce.linearForce.magnitude = newForce.Magnitude();
			}
		}
	}
}

void Collision2DManager::PositionCorrection(Contact& _contact) {
	// Compute total inverse mass
	float invMassSum{ 0.f };
	if (_contact.obj[0].HasComponent<Physics2D>())
		invMassSum += (_contact.obj[0].GetComponent<Physics2D>().mass == 0.f) ? 0.f : 1.f / _contact.obj[0].GetComponent<Physics2D>().mass;
	if (_contact.obj[1].HasComponent<Physics2D>())
		invMassSum += (_contact.obj[1].GetComponent<Physics2D>().mass == 0.f) ? 0.f : 1.f / _contact.obj[1].GetComponent<Physics2D>().mass;
	if (invMassSum == 0.f)
		invMassSum = 1.f;

	// Compute correction value and correct positions
	Math::Vec2 correction = std::max(_contact.penetration - penAllowance, 0.f) / invMassSum * _contact.normal * penPercentage;
	_contact.obj[0].GetComponent<Transform>().translation -= correction * (_contact.obj[0].HasComponent<Physics2D>() ? (_contact.obj[0].GetComponent<Physics2D>().mass == 0.f) ? 0.f : 1.f / _contact.obj[0].GetComponent<Physics2D>().mass : 1.f);
	_contact.obj[1].GetComponent<Transform>().translation += correction * (_contact.obj[1].HasComponent<Physics2D>() ? (_contact.obj[1].GetComponent<Physics2D>().mass == 0.f) ? 0.f : 1.f / _contact.obj[1].GetComponent<Physics2D>().mass : 1.f);
}

//void Collision2DManager::ResolvePositions() {
//	// Call physics manager to update based on new velocity
//	//physics2DManager->UpdatePosition(_contact.obj1);
//	//physics2DManager->UpdatePosition(_contact.obj2);
//
//
//	//int iteration{ 0 }, maxIteration{ static_cast<int>(_contact.contacts.size()) };
//	//while (iteration < maxIteration){
//	//	//if (_contact.penetration > Collision2DManager::penAllowance)
//	//
//	//	// Resolve penetration
//	//	ResolvePenetration(_contact);
//
//	//	++iteration;
//	//}
//
//	int itCount{ 0 }, itMax{ static_cast<int>(mContactList.size()) * 5 };
//	while (itCount < itMax) {
//		// Find the biggest penetration greater than
//		// the penetration allowance
//		float maxPen{ Collision2DManager::penAllowance };
//		size_t contactIndex{ mContactList.size() };
//		for (size_t i{ 0 }; i < mContactList.size(); ++i) {
//			if (mContactList[i].penetration > maxPen) {
//				maxPen = mContactList[i].penetration;
//				contactIndex = i;
//			}
//		}
//		if (contactIndex == mContactList.size())
//			break;
//
//		// Resolve penetration
//		ResolvePenetration(mContactList[contactIndex]);
//
//		// Update penetration of all related contacts
//		Math::Vec2* newVel{ mContactList[contactIndex].newVelocity };
//		for (size_t i{ 0 }; i < mContactList.size(); ++i) {
//			if (mContactList[i].obj[0].id == mContactList[contactIndex].obj[0].id || 
//				mContactList[i].obj[0].id == mContactList[contactIndex].obj[1].id)
//				mContactList[i].penetration -= Dot( (mContactList[i].obj[0].id == mContactList[contactIndex].obj[0].id ? newVel[0] : newVel[1]), 
//													mContactList[i].normal);
//			if (mContactList[i].obj[1].id == mContactList[contactIndex].obj[0].id ||
//				mContactList[i].obj[1].id == mContactList[contactIndex].obj[1].id)
//				mContactList[i].penetration += Dot((mContactList[i].obj[1].id == mContactList[contactIndex].obj[0].id ? newVel[0] : newVel[1]),
//													mContactList[i].normal);
//		}
//
//		++itCount;
//	}
//	
//}
//
//void Collision2DManager::ResolveVelocities(const double& _dt) {
//	//// Calculate relative velocity
//	//Math::Vec2 relVel{};
//	//if (_contact.obj[0].HasComponent<Physics2D>() && _contact.obj[1].HasComponent<Physics2D>())
//	//	relVel = _contact.obj[0].GetComponent<Physics2D>().velocity * static_cast<float>(_dt) - _contact.obj[1].GetComponent<Physics2D>().velocity * static_cast<float>(_dt);
//	//else if (_contact.obj[0].HasComponent<Physics2D>())
//	//	relVel = _contact.obj[0].GetComponent<Physics2D>().velocity * static_cast<float>(_dt);
//	//else if (_contact.obj[1].HasComponent<Physics2D>())
//	//	relVel = _contact.obj[1].GetComponent<Physics2D>().velocity * static_cast<float>(_dt);
//
//	//// Compute seperating velocity scalar
//	//float SepVelScalar{ Math::Dot(relVel, _contact.normal) };
//
//	//if (SepVelScalar < 0 && SepVelScalar < FLT_MAX)
//	//	return;
//
//	//// Compute updated seperating velocity scalar
//	//float newSepVelScalar{ -SepVelScalar * _contact.DetermineRestitution() };
//
//	//// No gravity in our game
//	////Math::Vec2 accCausedVel{};
//	////if (_contact.obj1.HasComponent<Physics2D>() && _contact.obj2.HasComponent<Physics2D>())
//	////	relVel = _contact.obj1.GetComponent<Physics2D>().acceleration - _contact.obj2.GetComponent<Physics2D>().acceleration;
//	////else if (_contact.obj1.HasComponent<Physics2D>())
//	////	relVel = _contact.obj1.GetComponent<Physics2D>().acceleration;
//	////else if (_contact.obj2.HasComponent<Physics2D>())
//	////	relVel = _contact.obj2.GetComponent<Physics2D>().acceleration;
//
//	////float accCausedVelScalar{ Math::Dot(accCausedVel, _contact.normal) * static_cast<float>(_dt) };
//	////if (accCausedVelScalar < 0){
//	////	newSepVelScalar += _contact.DetermineRestitution() * accCausedVelScalar;
//
//	////	if (newSepVelScalar < 0.f)
//	////		newSepVelScalar = 0.f;
//	////}
//
//	//// Compute total inverse mass
//	//float invMassSum{ 0.f };
//	//if (_contact.obj[0].HasComponent<Physics2D>())
//	//	invMassSum += (_contact.obj[0].GetComponent<Physics2D>().mass == 0.f) ? 0.f : 1.f / _contact.obj[0].GetComponent<Physics2D>().mass;;
//	//if (_contact.obj[1].HasComponent<Physics2D>())
//	//	invMassSum += (_contact.obj[1].GetComponent<Physics2D>().mass == 0.f) ? 0.f : 1.f / _contact.obj[1].GetComponent<Physics2D>().mass;;
//	//if (invMassSum == 0.f)
//	//	invMassSum = 1.f;
//
//	//// Compute change in velocity & impulse per mass
//	//float deltaVelocity{ newSepVelScalar - SepVelScalar };
//	//Math::Vec2 impulsePerMass{ _contact.normal * (deltaVelocity / invMassSum) };
//
//	//// Apply impulse
//	//if (_contact.obj[0].HasComponent<Physics2D>())
//	//	_contact.obj[0].GetComponent<Physics2D>().velocity += impulsePerMass * ((_contact.obj[0].GetComponent<Physics2D>().mass == 0.f) ? 0.f : 1.f / _contact.obj[0].GetComponent<Physics2D>().mass);
//	//if (_contact.obj[1].HasComponent<Physics2D>())
//	//	_contact.obj[1].GetComponent<Physics2D>().velocity += impulsePerMass * ((_contact.obj[1].GetComponent<Physics2D>().mass == 0.f) ? 0.f : 1.f / _contact.obj[1].GetComponent<Physics2D>().mass);
//	int itCount{ 0 }, itMax{ static_cast<int>(mContactList.size()) * 5 };
//	while (itCount < itMax) {
//		// Find contact with largest velocity
//		float maxVel{FLT_MAX};
//		size_t contactIndex{ mContactList.size() };
//		for (size_t i{ 0 }; i < mContactList.size(); ++i) {
//			// Compute seperating velocity scalar
//			float sepVel{ mContactList[i].DetermineSeperatingVelocity() };
//			if (sepVel < 0 && sepVel < maxVel) {
//				maxVel = sepVel;
//				contactIndex = i;
//			}
//		}
//
//		// Nothing to resolve, break
//		if (contactIndex == mContactList.size())
//			break;
//
//		// Compute their velocities
//		ResolveContactVelocity(mContactList[contactIndex], _dt);
//
//		++itCount;
//	}
//}
//
//void Collision2DManager::ResolveContactVelocity(Contact& _contact, const double& _dt) {
//	// Compute velocity scalar of the two objects along the contact normal
//	float sepVelScalar{ _contact.DetermineSeperatingVelocity() };
//	// Check if the returned dot product is larger than 1 (No longer moving towards each other
//	if (sepVelScalar > 0) {
//		_contact.contactImpulse = 0;
//	}
//
//	// Use combined restitution to determine percentage of the enegery along
//	// collision normal is conserved
//	float newSepVelScalar = -sepVelScalar * _contact.combinedRestitution;
//
//	// Get relative acceleration
//	Math::Vec2 relAcc{};
//	if (_contact.obj[0].HasComponent<Physics2D>() && _contact.obj[1].HasComponent<Physics2D>())
//		relAcc = _contact.obj[0].GetComponent<Physics2D>().acceleration - _contact.obj[1].GetComponent<Physics2D>().acceleration;
//	else if (_contact.obj[0].HasComponent<Physics2D>())
//		relAcc = _contact.obj[0].GetComponent<Physics2D>().acceleration;
//	else if (_contact.obj[1].HasComponent<Physics2D>())
//		relAcc = _contact.obj[1].GetComponent<Physics2D>().acceleration;
//	// Compute scalar of the velocity due to acceleration
//	float accCausedSepVelScalar{ Math::Dot(relAcc, _contact.normal) * static_cast<float>(_dt) };
//	// Check for closing velocity due to acceleration build-up
//	// Remove it from new seperating velocity
//	if (accCausedSepVelScalar < 0) {
//		newSepVelScalar += _contact.combinedRestitution * accCausedSepVelScalar;
//
//		// If less than 0, set it to 0
//		if (newSepVelScalar < 0)
//			newSepVelScalar = 0;
//	}
//
//	// Compute the total change in velocity on contact
//	float delVel{ newSepVelScalar - sepVelScalar };
//
//	// Compute total inverse mass
//	float invMassSum{ 0.f };
//	if (_contact.obj[0].HasComponent<Physics2D>())
//		invMassSum += (_contact.obj[0].GetComponent<Physics2D>().mass == 0.f) ? 0.f : 1.f / _contact.obj[0].GetComponent<Physics2D>().mass;
//	if (_contact.obj[1].HasComponent<Physics2D>())
//		invMassSum += (_contact.obj[1].GetComponent<Physics2D>().mass == 0.f) ? 0.f : 1.f / _contact.obj[1].GetComponent<Physics2D>().mass;
//	if (invMassSum == 0.f)
//		invMassSum = 1.f;
//
//	// Compute impulse & set
//	float impulse{ delVel / invMassSum };
//	_contact.contactImpulse = impulse;
//
//	// Find amount of impulse per unit of inverse mass
//	Math::Vec2 impulsePerInvMass{ _contact.normal * impulse };
//
//	// Apply impulse directly
//	if (_contact.obj[0].HasComponent<Physics2D>()) {
//		_contact.obj[0].GetComponent<Physics2D>().velocity = _contact.obj[0].GetComponent<Physics2D>().velocity + impulsePerInvMass * (1.f / _contact.obj[0].GetComponent<Physics2D>().mass);
//		_contact.obj[0].GetComponent<Physics2D>().accumulatedForce = Math::Vec2{ 0.f, 0.f };
//		_contact.obj[0].GetComponent<Physics2D>().forceList.clear();
//	}
//	if (_contact.obj[1].HasComponent<Physics2D>()){
//		_contact.obj[1].GetComponent<Physics2D>().velocity = _contact.obj[1].GetComponent<Physics2D>().velocity + impulsePerInvMass * (1.f / _contact.obj[1].GetComponent<Physics2D>().mass);
//		_contact.obj[0].GetComponent<Physics2D>().accumulatedForce = Math::Vec2{ 0.f, 0.f };
//		_contact.obj[0].GetComponent<Physics2D>().forceList.clear();
//	}
//}
//
//void Collision2DManager::ResolvePenetration(Contact& _contact) {
//	// Compute total inverse mass
//	float invMassSum{ 0.f };
//	if (_contact.obj[0].HasComponent<Physics2D>())
//		invMassSum += (_contact.obj[0].GetComponent<Physics2D>().mass == 0.f) ? 0.f : 1.f / _contact.obj[0].GetComponent<Physics2D>().mass;
//	if (_contact.obj[1].HasComponent<Physics2D>())
//		invMassSum += (_contact.obj[1].GetComponent<Physics2D>().mass == 0.f) ? 0.f : 1.f / _contact.obj[1].GetComponent<Physics2D>().mass;
//	if (invMassSum == 0.f)
//		invMassSum = 1.f;
//
//	// Compute amount of penetration solution per unit of inverse mass
//	Math::Vec2 movePerIMass{ _contact.normal * (_contact.penetration / invMassSum) };
//	
//	//If stack stability can be increased by not resolving all the penetrations
//	//in one step
//	movePerIMass *= Collision2DManager::penPercentage;
//
//	// Compute new velocity
//	_contact.newVelocity[0] = movePerIMass * (_contact.obj[0].HasComponent<Physics2D>() ? (_contact.obj[0].GetComponent<Physics2D>().mass == 0.f) ? 0.f : 1.f / _contact.obj[0].GetComponent<Physics2D>().mass : 0.f);
//	_contact.newVelocity[1] = movePerIMass * (_contact.obj[1].HasComponent<Physics2D>() ? (_contact.obj[1].GetComponent<Physics2D>().mass == 0.f) ? 0.f : 1.f / _contact.obj[1].GetComponent<Physics2D>().mass : 0.f);
//
//	// Apply penetration resolution
//	_contact.obj[0].GetComponent<Transform>().translation += _contact.newVelocity[0];
//	_contact.obj[1].GetComponent<Transform>().translation += _contact.newVelocity[1];
//}