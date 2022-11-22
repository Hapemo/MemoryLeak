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
		return obj[0].HasComponent<Physics2D>() ? std::sqrtf(obj[0].GetComponent<Physics2D>().friction) : obj[1].HasComponent<Physics2D>() ? std::sqrtf(obj[1].GetComponent<Physics2D>().friction) : 0.f;
	}

	return std::sqrtf(obj[0].GetComponent<Physics2D>().friction * obj[1].GetComponent<Physics2D>().friction);
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

//std::vector<Entity> Collision2DManager::CI_PlayervsEnemy(const Entity& _player, const Entity& _enemy) {
//	return 
//}


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

// Will intersect within the next delta time
	// Use first as intersection time
	//_contact.interTime = tFirst;

	// Compute next frame's position and use that data for collision response 
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

	// Find axis that penetrates less and use it to resolve collision
	if (diff.x < diff.y) {
		// Set contact information
		_contact.normal = distVec.x < 0.f ? Math::Vec2{ 1.f, 0.f } : Math::Vec2{ -1.f, 0.f };
		_contact.penetration = diff.x;
		_contact.contacts = _contact.normal * scale1.x + center1;
	}
	else {
		// Set contact information
		_contact.normal = distVec.y < 0.f ? Math::Vec2{ 0.f, 1.f } : Math::Vec2{ 0.f, -1.f };
		_contact.penetration = diff.y;
		_contact.contacts = _contact.normal * scale1.y + center1;
	}
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
			_contact.penetration = (obj1R + obj2R) - sqrtf(sqDist);
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
		//_contact.interTime = interTime;

		// Compute new positions 
		Math::Vec2 obj1NewPos{ obj1Pos },
			obj2NewPos{ obj2Pos };
		if (obj1.HasComponent<Physics2D>())
			obj1NewPos += obj1.GetComponent<Physics2D>().velocity * static_cast<float>(_dt);
		if (obj2.HasComponent<Physics2D>())
			obj2NewPos += obj2.GetComponent<Physics2D>().velocity * static_cast<float>(_dt);

		// Set contact information
		_contact.penetration = (obj1R + obj2R) - sqrtf(Math::SqDistance(obj1NewPos, obj2NewPos));
		_contact.normal = (obj2NewPos - obj1NewPos).Normalize();
		_contact.contacts = _contact.normal * obj1R + obj1NewPos;

		return true;
	}
	else
		return false;
}

bool Collision2DManager::CI_CirclevsRect(Contact& _contact, const double& _dt) {
	_dt;

	// Get reference to the entities
	Entity& objCircle{ _contact.obj[0] },
		  & objRect{ _contact.obj[1] };

	
	Math::Vec2	objCirclePos{ objCircle.GetComponent<Transform>().translation + objCircle.GetComponent<CircleCollider>().centerOffset },
				objRectPos{ objRect.GetComponent<Transform>().translation + objRect.GetComponent<RectCollider>().centerOffset };
	float  objCircleR{ (objCircle.GetComponent<Transform>().scale.x * objCircle.GetComponent<CircleCollider>().scaleOffset) / 2.f };
	Math::Vec2 objRectScale{ static_cast<float>(static_cast<double>(objRect.GetComponent<Transform>().scale.x) * static_cast<double>(objRect.GetComponent<RectCollider>().scaleOffset.x) / 2.0),
							 static_cast<float>(static_cast<double>(objRect.GetComponent<Transform>().scale.y) * static_cast<double>(objRect.GetComponent<RectCollider>().scaleOffset.y) / 2.0) };

	Math::Vec2 p{ objCirclePos },
		minV{ objRectPos - objRectScale },
		maxV{ objRectPos + objRectScale };

	Math::Vec2 q{};
	for (int i{ 0 }; i < 2; ++i) {
		float v{ p[i] };
		if (v < minV[i])
			v = minV[i];
		if (v > maxV[i])
			v = maxV[i];
		q[i] = v;
	}

	float sqDist{ Math::SqDistance(q, p) };	
	if (sqDist < objCircleR * objCircleR) {
		if (sqDist == 0.f) {
			Math::Vec2 distVec{ objCirclePos - objRectPos };
			Math::Vec2 diff{ objCircleR + objRectScale.x - std::fabs(distVec.x),
							 objCircleR + objRectScale.y - std::fabs(distVec.y) };

			if (diff.x < diff.y) {
				_contact.normal = distVec.x < 0.f ? Math::Vec2{ 1.f, 0.f } : Math::Vec2{ -1.f, 0.f };
				_contact.penetration = diff.x;
				_contact.contacts = _contact.normal * objRectScale.x + objRectPos;
			}
			else {
				_contact.normal = distVec.y < 0.f ? Math::Vec2{ 0.f, 1.f } : Math::Vec2{ 0.f, -1.f };
				_contact.penetration = diff.y;
				_contact.contacts = _contact.normal * objRectScale.y + objRectPos;
			}
			return true;
		}
		else {
			_contact.normal = (q - p).Normalized();
			_contact.penetration = objCircleR - Math::Distance(q, p);
			_contact.contacts = _contact.normal * objCircleR + objCirclePos;
			return true;
		}
	}
	return false;
}

bool Collision2DManager::CI_RectvsCircle(Contact& _contact, const double& _dt) {
	std::swap(_contact.obj[0], _contact.obj[1]);
	std::swap(_contact.objType[0], _contact.objType[1]);

	return CI_CirclevsRect(_contact, _dt);
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
		PositionCorrection(item);
		ResolveContact(item, _dt);
	}

	ClearContactList();
}

void Collision2DManager::GenerateContactList(const double& _dt) {
	// Broad Phase Here


	// For now, we loop through the entity list
	// Converted to check player entities against all other entities for M3
	for (auto e1{ mEntities.begin() }; e1 != mEntities.end(); ++e1) {
		if (!e1->ShouldRun())
			continue;
		//if (!e1->GetComponent<General>().isActive)
			//continue;

		if (e1->GetComponent<General>().tag != TAG::PLAYER)
			continue;

		//for (auto e2{ e1 }; e2 != mEntities.end(); ++e2) {
		for (auto e2{ mEntities.begin() }; e2 != mEntities.end(); ++e2) {
			if (e1 == e2)
				continue;

			if (!e2->ShouldRun())
				continue;
			//if (!e2->GetComponent<General>().isActive)
			//	continue;

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
				mContactList.emplace_back(contact);
				//LOG_INFO("Collision Detected\n");
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

	// Error handling: Check for infinite mass of both objects
	// Do not do anything further
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

	// Error handling: Check if either objects are of infinite mass and set all movement values to 0
	if (obj1HasP) {
		if (_contact.obj[0].GetComponent<Physics2D>().mass == 0.f) {
			physics2DManager->SetVelocity(_contact.obj[0], { 0.f, 0.f });
			physics2DManager->SetAcceleration(_contact.obj[0], { 0.f, 0.f });
			physics2DManager->SetAccumulatedForce(_contact.obj[0], { 0.f, 0.f });
		}
	}

	if (obj2HasP) {
		if (_contact.obj[1].GetComponent<Physics2D>().mass == 0.f) {
			physics2DManager->SetVelocity(_contact.obj[1], { 0.f, 0.f });
			physics2DManager->SetAcceleration(_contact.obj[1], { 0.f, 0.f });
			physics2DManager->SetAccumulatedForce(_contact.obj[1], { 0.f, 0.f });
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
	//Math::Vec2	rObj1{ _contact.contacts - obj1Pos },
	//			rObj2{ _contact.contacts - obj2Pos };

	// Relative Velocity
	// Accounts for rotation
	//Math::Vec2 relVel{};
	//if (obj1HasP && obj2HasP)
	//	relVel = _contact.obj[1].GetComponent<Physics2D>().velocity + Math::Cross(_contact.obj[1].GetComponent<Physics2D>().angularVelocity, rObj2) -
	//	_contact.obj[0].GetComponent<Physics2D>().velocity - Math::Cross(_contact.obj[0].GetComponent<Physics2D>().angularVelocity, rObj1);
	//else if (obj2HasP)
	//	relVel = _contact.obj[1].GetComponent<Physics2D>().velocity + Math::Cross(_contact.obj[1].GetComponent<Physics2D>().angularVelocity, rObj2);
	//else if (obj1HasP)
	//	relVel = -(_contact.obj[0].GetComponent<Physics2D>().velocity - Math::Cross(_contact.obj[0].GetComponent<Physics2D>().angularVelocity, rObj1));
	
	Math::Vec2 relVel{ 0.f, 0.f };
	if (obj1HasP && obj2HasP) 
		relVel = _contact.obj[1].GetComponent<Physics2D>().velocity - _contact.obj[0].GetComponent<Physics2D>().velocity;
	else if (obj2HasP) 
		relVel = _contact.obj[1].GetComponent<Physics2D>().velocity;
	else if (obj1HasP) 
		relVel = _contact.obj[0].GetComponent<Physics2D>().velocity;

	// Relative velocity along the normal
	float contactVel{ Math::Dot(relVel, _contact.normal) };

	// Do not resolve if velocities are seperating
	if (contactVel > 0)
		return;

	// Rotation Velocity impulse
	//float	rObj1CrossN{ Math::Cross(rObj1, _contact.normal) },
	//		rObj2CrossN{ Math::Cross(rObj2, _contact.normal) };

	float invMassSum{};
	if (obj1HasP)
		invMassSum += (_contact.obj[0].GetComponent<Physics2D>().mass == 0.f) ? 0.f : 1.f / _contact.obj[0].GetComponent<Physics2D>().mass;;
	if (obj2HasP)
		invMassSum += (_contact.obj[1].GetComponent<Physics2D>().mass == 0.f) ? 0.f : 1.f / _contact.obj[1].GetComponent<Physics2D>().mass;;

	// Calculate impulse scalar J
	// No need to handle invMassSum == 0 (hence nan) as we already handled the case upon function entnry
	float scalar{ (-(1.f + _contact.combinedRestitution) * contactVel) / invMassSum };

	// Apply velocity impulse
	Math::Vec2 impulse{ _contact.normal * scalar };

	// Check for zero vector
	if ((fabs(impulse.x) < Math::epsilonValue) && (fabs(impulse.y) < Math::epsilonValue))
		return;

	// Has physics component (Response required)
	if (obj1HasP) {
	// Move object to resolve contact
		// Check if there is mass (not infinite)
		if (physics2DManager->GetMass(_contact.obj[0]) != 0.f) {
			physics2DManager->ApplyImpulse(_contact.obj[0], -(impulse), { 0.f, 0.f });
			_contact.obj[0].GetComponent<Transform>().translation += physics2DManager->GetVelocity(_contact.obj[0]) * static_cast<float>(_dt);

			// Compute new acceleration/force after resolution
			// Look for 1st force that dictates the movement force (constraint)
			if (!_contact.obj[0].GetComponent<Physics2D>().forceList.empty()) {
				// Get reference to the first force
				Force& moveForce{ _contact.obj[0].GetComponent<Physics2D>().forceList[0] };
				// Check if its linear
				if (moveForce.forceID == 0) {
					// Compute new force after resolution
					Math::Vec2 newForceVec{};
					if (physics2DManager->GetMass(_contact.obj[0]) == 0.f)
						newForceVec = -impulse;
					else
						newForceVec = -impulse / physics2DManager->GetMass(_contact.obj[0]);

					// Check if magnitude would not cause zero division nan
					if (newForceVec.SqMagnitude() > Math::epsilonValue * Math::epsilonValue) {
						moveForce.linearForce.unitDirection = newForceVec.Normalized();
						moveForce.linearForce.magnitude = newForceVec.Magnitude();
					}
					else {
						moveForce.linearForce.unitDirection = { 0.f, 0.f };
						moveForce.linearForce.magnitude = 0.f;
					}
				}
			}
		}		
	}

	// Do the same for the other entity
	if (obj2HasP) {
		if (physics2DManager->GetMass(_contact.obj[1]) != 0.f) {
			physics2DManager->ApplyImpulse(_contact.obj[1], impulse, { 0.f, 0.f });
			_contact.obj[1].GetComponent<Transform>().translation += physics2DManager->GetVelocity(_contact.obj[1]) * static_cast<float>(_dt);

			if (!_contact.obj[1].GetComponent<Physics2D>().forceList.empty()) {
				Force& moveForce{ _contact.obj[1].GetComponent<Physics2D>().forceList[0] };
				if (moveForce.forceID == 0) {
					Math::Vec2 newForceVec{};
					if (physics2DManager->GetMass(_contact.obj[1]) == 0.f)
						newForceVec = impulse;
					else
						newForceVec = impulse / physics2DManager->GetMass(_contact.obj[1]);

					// Check if magnitude would not cause zero division nan
					if (newForceVec.SqMagnitude() > Math::epsilonValue * Math::epsilonValue) {
						moveForce.linearForce.unitDirection = newForceVec.Normalized();
						moveForce.linearForce.magnitude = newForceVec.Magnitude();
					}
					else {
						moveForce.linearForce.unitDirection = { 0.f, 0.f };
						moveForce.linearForce.magnitude = 0.f;
					}
				}
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

	// Compute correction value
	Math::Vec2 correction = std::max(_contact.penetration - penAllowance, 0.f) / invMassSum * _contact.normal * penPercentage;
	
	// Correct positions
	if (_contact.obj[0].HasComponent<Physics2D>())
		if (_contact.obj[0].GetComponent<Physics2D>().mass != 0.f)
			_contact.obj[0].GetComponent<Transform>().translation += correction * -(1.f / _contact.obj[0].GetComponent<Physics2D>().mass);
	
	if (_contact.obj[1].HasComponent<Physics2D>())
		if (_contact.obj[1].GetComponent<Physics2D>().mass != 0.f)
			_contact.obj[1].GetComponent<Transform>().translation += correction * (1.f / _contact.obj[1].GetComponent<Physics2D>().mass);
}