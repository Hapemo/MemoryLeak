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


Contact::Contact(const Entity& _obj1, const Entity& _obj2) : obj1{ _obj1 }, obj2{ _obj2 } {
	// Leave Empty
}

float Contact::DetermineRestitution() {
	if (!obj1.HasComponent<Physics2D>() || !obj2.HasComponent<Physics2D>()) {
		return obj1.HasComponent<Physics2D>() ? obj1.GetComponent<Physics2D>().restitution : obj2.HasComponent<Physics2D>() ? obj2.GetComponent<Physics2D>().restitution : 0.f;
	}

	return std::min(obj1.GetComponent<Physics2D>().restitution, obj2.GetComponent<Physics2D>().restitution);
}

float Contact::DetermineFriction() {
	if (!obj1.HasComponent<Physics2D>() || !obj2.HasComponent<Physics2D>()) {
		return obj1.HasComponent<Physics2D>() ? std::sqrt(obj1.GetComponent<Physics2D>().friction) : obj2.HasComponent<Physics2D>() ? std::sqrt(obj2.GetComponent<Physics2D>().friction) : 0.f;
	}

	return std::sqrt(obj1.GetComponent<Physics2D>().friction * obj2.GetComponent<Physics2D>().friction);
}


bool Collision2DManager::CI_RectvsRect(Contact& _contact, const double& _dt) {
	// Get reference to the entities
	Entity& obj1{ _contact.obj1 },
		  & obj2{ _contact.obj2 };

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
		obj1NewPos += obj1.GetComponent<Physics2D>().velocity * static_cast<float>(_contact.interTime);
	if (obj2.HasComponent<Physics2D>())
		obj2NewPos += obj2.GetComponent<Physics2D>().velocity * static_cast<float>(_contact.interTime);

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
		_contact.contacts.push_back(_contact.normal * diff.x + obj1NewPos);
	}
	else {
		// Set contact information
		_contact.normal = distVec.y < 0 ? Math::Vec2{ 0.f, 1.f } : Math::Vec2{ 0.f, -1.f };
		_contact.penetration = diff.y;
		_contact.contacts.push_back(_contact.normal * diff.y + obj1NewPos);
	}
	//	}
	//}

	return true;
}

bool Collision2DManager::CI_CirclevsCircle(Contact& _contact, const double& _dt) {
	// Get reference to the entities
	Entity& obj1{ _contact.obj1 }, 
		  & obj2{ _contact.obj2 };

	// Store radius of circle colliders
	float  obj1R{ (obj1.GetComponent<Transform>().scale.x * obj1.GetComponent<CircleCollider>().scaleOffset) / 2.f },
		   obj2R{ (obj2.GetComponent<Transform>().scale.x * obj2.GetComponent<CircleCollider>().scaleOffset) / 2.f };

	// Store position of circle colliders
	Math::Vec2 obj1Pos{ obj1.GetComponent<Transform>().translation + obj1.GetComponent<CircleCollider>().centerOffset },
			   obj2Pos{ obj2.GetComponent<Transform>().translation + obj2.GetComponent<CircleCollider>().centerOffset };
// Static
	// Check if the distance between the circles' centers is smaller than their radius
	float sqDist{ Math::SqDistance(obj1Pos, obj2Pos)};
	if ( sqDist < (obj1R * obj1R + obj2R * obj2R)) {
		// On top of each other
		if (sqDist == 0.f) {
			// Set contact information
			_contact.penetration = obj1R;
			_contact.normal = Math::Vec2{ 1.f, 0.f };
			_contact.contacts.push_back(obj1Pos);
		}
		else {
			// Set contact information
			_contact.penetration = (obj1R + obj2R) - sqrt(sqDist);
			_contact.normal = (obj2Pos - obj1Pos).Normalize();
			_contact.contacts.push_back(_contact.normal * obj1R + obj1Pos);
		}

		return true;
	}

	// Find the relative velocity of both entities
	Math::Vec2 relVel{};
	if (obj1.HasComponent<Physics2D>() && obj2.HasComponent<Physics2D>())
		relVel = obj1.GetComponent<Physics2D>().velocity * static_cast<float>(_dt) - obj2.GetComponent<Physics2D>().velocity * static_cast<float>(_dt);
	else if (_contact.obj1.HasComponent<Physics2D>())
		relVel = obj1.GetComponent<Physics2D>().velocity * static_cast<float>(_dt);
	else if (_contact.obj2.HasComponent<Physics2D>())
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

		// Compute position at intersection time
		Math::Vec2 obj1NewPos{ obj1Pos }, 
				   obj2NewPos{ obj2Pos };
		if (obj1.HasComponent<Physics2D>())
			obj1NewPos += obj1.GetComponent<Physics2D>().velocity * static_cast<float>(_contact.interTime);
		if (obj2.HasComponent<Physics2D>())
			obj2NewPos += obj2.GetComponent<Physics2D>().velocity * static_cast<float>(_contact.interTime);

		// Set contact information
		_contact.penetration = sqrt(Math::SqDistance(obj1NewPos, obj2NewPos)) - (obj1R + obj2R);
		_contact.normal = (obj2NewPos - obj1NewPos).Normalize();
		_contact.contacts.push_back(_contact.normal * obj1R + obj1NewPos);

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
	bool notplayer = false;
	// Resolve collision
	// Uncomment and move player into a circle collider to see the player spin
	//for (Contact &item : mContactList)
	//	ResolveContact(item);

	for (Contact &item : mContactList) {
		//UpdatePositions(item);
		//UpdateVelocities(item, _dt);
		//PositionCorrection(item);

		// Impulse response not working
		// For now, we just disable the movement
		//if (item.obj1.HasComponent<Physics2D>()) 
		//	item.obj1.GetComponent<Physics2D>().dynamicsEnabled = false;
		//if (item.obj2.HasComponent<Physics2D>())
		//	item.obj2.GetComponent<Physics2D>().dynamicsEnabled = false;
		
		// For now, we just clear the movement
		if (item.obj1.HasComponent<Physics2D>()) {
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
		}

	// --------------------------------------------
	// Response hack for player (done by Wei Jhin)
	// --------------------------------------------
		if (item.obj1.GetComponent<General>().tag == TAG::PLAYER)
		{
			Math::Vec2 distance = item.obj1.GetComponent<Transform>().translation - item.obj2.GetComponent<Transform>().translation;
			if (distance.y <= 0)
				playerManager->getCheck()[0] = false;
			if (distance.y >= 0)
				playerManager->getCheck()[1] = false;
			if(distance.x <= 0)
				playerManager->getCheck()[3] = false;
			if (distance.x >= 0)
				playerManager->getCheck()[2] = false;
			notplayer = true;
		}
		else if (item.obj2.GetComponent<General>().tag == TAG::PLAYER)
		{
			Math::Vec2 distance = item.obj2.GetComponent<Transform>().translation - item.obj1.GetComponent<Transform>().translation;
			if (distance.y <= 0)
			{
				playerManager->getCheck()[0] = false;
				playerManager->getCheck()[1] = true;
			}
			if (distance.y >= 0)
			{
				playerManager->getCheck()[1] = false;
				playerManager->getCheck()[0] = true;
			}
			if (distance.x <= 0)
			{
				playerManager->getCheck()[3] = false;
				playerManager->getCheck()[2] = true;
			}
			if (distance.x >= 0)
			{
				playerManager->getCheck()[2] = false;
				playerManager->getCheck()[3] = true;
			}
			notplayer = true;
		}
		else
		{
			notplayer = false;
		}
	}
	if (notplayer== false) //player not coliding reset
	{
		playerManager->getCheck()[0] = true;
		playerManager->getCheck()[1] = true;
		playerManager->getCheck()[2] = true;
		playerManager->getCheck()[3] = true;
	}

	ClearContactList();
}

void Collision2DManager::GenerateContactList(const double& _dt) {
	// Broad Phase Here


	// For now, we loop through the entity list
	for (auto e1{ mEntities.begin() }; e1 != mEntities.end(); ++e1) {
		for (auto e2{ e1 }; e2 != mEntities.end(); ++e2) {
			if (e1 == e2)
				continue;

			//if (!e1->HasComponent<Collider2D>() || !e2->HasComponent<Collider2D>())
			//	continue;
			// Prevents checks against 2 non moving object
			//if (!e1->GetComponent<Physics2D>().dynamicsEnabled || !e2->GetComponent<Physics2D>().dynamicsEnabled)	
			//	continue;
			// Callback function to generate contact
			//auto e1ColliderList{ e1->GetComponent<Collider2D>().colliderList };
			//auto e2ColliderList{ e2->GetComponent<Collider2D>().colliderList };
			//for (int i{ 0 }; i < static_cast<int>(e1ColliderList.size()); ++i) {
			//	for (int j{ 0 }; j < static_cast<int>(e2ColliderList.size()); ++j) {
			//		Contact contact{ *e1, *e2 };
			//		(*mCollisionDatabase[static_cast<int>(e1ColliderList[i].typeID)][static_cast<int>(e2ColliderList[i].typeID)])(contact, _dt);
			//		if (contact.contacts.size() != 0)
			//			mContactList.push_back(contact);
			//	}
			//}

			// Check if either of the entities do not have collider
			if (!HasCollider(*e1) || !HasCollider(*e2))
				continue;

			// Code has not accounted for multiple colliders attached to an entity despite it being a constraint made to me by group members
			//for (int i{ 0 }; i < NoOfColliders(*e1); ++i){
			// Find collider type of 1st entity
			int e1Type{0};
			if (e1->HasComponent<RectCollider>())
				e1Type = static_cast<int>(ColliderType::RECT);
			else if (e1->HasComponent<CircleCollider>())
				e1Type = static_cast<int>(ColliderType::CIRCLE);
			else
				continue;

			//	for (int j{ 0 }; j < NoOfColliders(*e2); ++j) {
			// Find collider type of 2nd entity
			int e2Type{0};
			if (e2->HasComponent<RectCollider>())
				e2Type = static_cast<int>(ColliderType::RECT);
			else if (e2->HasComponent<CircleCollider>())
				e2Type = static_cast<int>(ColliderType::CIRCLE);
			else
				continue;

			// Initialize contact
			Contact contact{ *e1, *e2 };
			contact.obj1Type = e1Type;
			contact.obj2Type = e2Type;
			// Call function to check for collision
			(*mCollisionDatabase[static_cast<int>(contact.obj1Type)][static_cast<int>(contact.obj2Type)])(contact, _dt);

			// If contact isnt empty, means collision occurred
			if (!contact.contacts.empty()) {
				mContactList.push_back(contact);
				LOG_INFO("Collision Detected\n");
			}
			//	}
			//}
		}
	}

}

void Collision2DManager::ClearContactList() {
	mContactList.clear();
}

void Collision2DManager::ResolveContact(Contact& _contact) {
	// Compute average restitution and friction of the two entities
	float avgRestitution{ _contact.DetermineRestitution() },
		  cofFriction{ _contact.DetermineFriction() };

	// Store bool value of whether entity has physics component
	bool obj1HasP{ _contact.obj1.HasComponent<Physics2D>() },
		 obj2HasP{ _contact.obj1.HasComponent<Physics2D>() };

	// Check for infinite mass
	if (obj1HasP && obj2HasP) {
		if (_contact.obj1.GetComponent<Physics2D>().mass == 0.f && _contact.obj2.GetComponent<Physics2D>().mass == 0.f) {
			_contact.obj1.GetComponent<Physics2D>().velocity = Math::Vec2{ 0.f,0.f };
			_contact.obj2.GetComponent<Physics2D>().velocity = Math::Vec2{ 0.f,0.f };
			return;
		}
	}

	// Store positions
	Math::Vec2 obj1Pos{ _contact.obj1.GetComponent<Transform>().translation },
			   obj2Pos{ _contact.obj2.GetComponent<Transform>().translation };
	if (_contact.obj1Type == static_cast<int>(ColliderType::RECT))
		obj1Pos += _contact.obj1.GetComponent<RectCollider>().centerOffset;
	else if (_contact.obj1Type == static_cast<int>(ColliderType::CIRCLE))
		obj1Pos += _contact.obj1.GetComponent<CircleCollider>().centerOffset;
	if (_contact.obj2Type == static_cast<int>(ColliderType::RECT))
		obj2Pos += _contact.obj2.GetComponent<RectCollider>().centerOffset;
	else if (_contact.obj2Type == static_cast<int>(ColliderType::CIRCLE))
		obj2Pos += _contact.obj2.GetComponent<CircleCollider>().centerOffset;

	for (auto contact : _contact.contacts) {
		// Calculate radii from COM to contact
		Math::Vec2 rObj1{ contact - obj1Pos },
					rObj2{ contact - obj2Pos };

		// Relative Velocity
		Math::Vec2 relVel{ 0.f, 0.f };
		if (obj2HasP)
			relVel += _contact.obj2.GetComponent<Physics2D>().velocity + Math::Cross(_contact.obj2.GetComponent<Physics2D>().angularVelocity, rObj2);
		if (obj1HasP)
			relVel -= _contact.obj1.GetComponent<Physics2D>().velocity - Math::Cross(_contact.obj1.GetComponent<Physics2D>().angularVelocity, rObj1);

		// Relative velocity along the normal
		float contactVel{ Math::Dot(relVel, _contact.normal) };

		// Do not resolve if velocities are seperating
		if (contactVel > 0)
			return;

	// Velocity impulse
		float rObj1CrossN{ Math::Cross(rObj1, _contact.normal) },
			  rObj2CrossN{ Math::Cross(rObj2, _contact.normal) };
		float invMassSum{ 0 };
		if (obj1HasP)
			invMassSum += ((_contact.obj1.GetComponent<Physics2D>().mass == 0.f) ? 0.f : 1.f / _contact.obj1.GetComponent<Physics2D>().mass) + (rObj1CrossN * rObj1CrossN) * ((_contact.obj1.GetComponent<Physics2D>().inertia == 0.f) ? 0.f : 1.f / _contact.obj1.GetComponent<Physics2D>().inertia);
		if (obj2HasP)
			invMassSum += ((_contact.obj2.GetComponent<Physics2D>().mass == 0.f) ? 0.f : 1.f / _contact.obj2.GetComponent<Physics2D>().mass) + (rObj2CrossN * rObj2CrossN) * ((_contact.obj2.GetComponent<Physics2D>().inertia == 0.f) ? 0.f : 1.f / _contact.obj2.GetComponent<Physics2D>().inertia);

		// Calculate impulse scalar
		float scalar{ -(1.f + avgRestitution) * contactVel };
		scalar /= invMassSum;
		scalar /= static_cast<float>(_contact.contacts.size());

		// Apply impulse
		physics2DManager->ApplyImpulse(_contact.obj1, -(_contact.normal * scalar), rObj1);
		physics2DManager->ApplyImpulse(_contact.obj2, _contact.normal * scalar, rObj2);
	
		// Friction impulse
		if (obj2HasP)
			relVel += _contact.obj2.GetComponent<Physics2D>().velocity + Math::Cross(_contact.obj2.GetComponent<Physics2D>().angularVelocity, rObj2);
		if (obj1HasP)
			relVel -= _contact.obj1.GetComponent<Physics2D>().velocity - Math::Cross(_contact.obj1.GetComponent<Physics2D>().angularVelocity, rObj1);

		// Tangent
		Math::Vec2 tangent{ relVel - (_contact.normal * Math::Dot(relVel, _contact.normal)) };
		tangent.Normalize();

		// Compute scalar impulse tangent magnitude
		float scalarTangent{ -Math::Dot(relVel, tangent) };
		scalarTangent /= invMassSum;
		scalarTangent /= static_cast<float>(_contact.contacts.size());

		// If the magnitude is 0, dont apply the impulse
		if (scalarTangent == 0.f)
			return;

		// Coulumb's law
		Math::Vec2 tangentImpulse{};
		if (std::fabs(scalarTangent) < scalarTangent * cofFriction)
			tangentImpulse = tangent * scalarTangent;
		else
			tangentImpulse = tangent * -scalar * cofFriction;

		// Apply friction impulse
		physics2DManager->ApplyImpulse(_contact.obj1, -tangentImpulse, rObj1);
		physics2DManager->ApplyImpulse(_contact.obj2, tangentImpulse, rObj2);
	}
}

void Collision2DManager::UpdatePositions(const Contact& _contact) {
	// Call physics manager to update based on new velocity
	physics2DManager->UpdatePosition(_contact.obj1);
	physics2DManager->UpdatePosition(_contact.obj2);
}

void Collision2DManager::PositionCorrection(Contact& _contact) {
	// Compute total inverse mass
	float invMassSum{ 0.f };
	if (_contact.obj1.HasComponent<Physics2D>())
		invMassSum += (_contact.obj1.GetComponent<Physics2D>().mass == 0.f) ? 0.f : 1.f / _contact.obj1.GetComponent<Physics2D>().mass;
	if (_contact.obj2.HasComponent<Physics2D>())
		invMassSum += (_contact.obj2.GetComponent<Physics2D>().mass == 0.f) ? 0.f : 1.f / _contact.obj2.GetComponent<Physics2D>().mass;
	if (invMassSum == 0.f)
		invMassSum = 1.f;

	// Compute correction value and correct positions
	Math::Vec2 correction = std::max(_contact.penetration - penAllowance, 0.f) / invMassSum * _contact.normal * penPercentage;
	_contact.obj1.GetComponent<Transform>().translation -= correction * (_contact.obj1.HasComponent<Physics2D>() ? (_contact.obj1.GetComponent<Physics2D>().mass == 0.f) ? 0.f : 1.f / _contact.obj1.GetComponent<Physics2D>().mass : 1.f);
	_contact.obj2.GetComponent<Transform>().translation += correction * (_contact.obj2.HasComponent<Physics2D>() ? (_contact.obj2.GetComponent<Physics2D>().mass == 0.f) ? 0.f : 1.f / _contact.obj2.GetComponent<Physics2D>().mass : 1.f);
}

void Collision2DManager::UpdateVelocities(Contact& _contact, const double& _dt) {
	// Calculate relative velocity
	Math::Vec2 relVel{};
	if (_contact.obj1.HasComponent<Physics2D>() && _contact.obj2.HasComponent<Physics2D>())
		relVel = _contact.obj1.GetComponent<Physics2D>().velocity * static_cast<float>(_dt) - _contact.obj2.GetComponent<Physics2D>().velocity * static_cast<float>(_dt);
	else if (_contact.obj1.HasComponent<Physics2D>())
		relVel = _contact.obj1.GetComponent<Physics2D>().velocity * static_cast<float>(_dt);
	else if (_contact.obj2.HasComponent<Physics2D>())
		relVel = _contact.obj2.GetComponent<Physics2D>().velocity * static_cast<float>(_dt);

	// Compute seperating velocity scalar
	float SepVelScalar{ Math::Dot(relVel, _contact.normal) };

	if (SepVelScalar < 0 && SepVelScalar < FLT_MAX)
		return;

	// Compute updated seperating velocity scalar
	float newSepVelScalar{ -SepVelScalar * _contact.DetermineRestitution() };

	// No gravity in our game
	//Math::Vec2 accCausedVel{};
	//if (_contact.obj1.HasComponent<Physics2D>() && _contact.obj2.HasComponent<Physics2D>())
	//	relVel = _contact.obj1.GetComponent<Physics2D>().acceleration - _contact.obj2.GetComponent<Physics2D>().acceleration;
	//else if (_contact.obj1.HasComponent<Physics2D>())
	//	relVel = _contact.obj1.GetComponent<Physics2D>().acceleration;
	//else if (_contact.obj2.HasComponent<Physics2D>())
	//	relVel = _contact.obj2.GetComponent<Physics2D>().acceleration;

	//float accCausedVelScalar{ Math::Dot(accCausedVel, _contact.normal) * static_cast<float>(_dt) };
	//if (accCausedVelScalar < 0){
	//	newSepVelScalar += _contact.DetermineRestitution() * accCausedVelScalar;

	//	if (newSepVelScalar < 0.f)
	//		newSepVelScalar = 0.f;
	//}

	// Compute total inverse mass
	float invMassSum{ 0.f };
	if (_contact.obj1.HasComponent<Physics2D>())
		invMassSum += (_contact.obj1.GetComponent<Physics2D>().mass == 0.f) ? 0.f : 1.f / _contact.obj1.GetComponent<Physics2D>().mass;;
	if (_contact.obj2.HasComponent<Physics2D>())
		invMassSum += (_contact.obj2.GetComponent<Physics2D>().mass == 0.f) ? 0.f : 1.f / _contact.obj2.GetComponent<Physics2D>().mass;;
	if (invMassSum == 0.f)
		invMassSum = 1.f;

	// Compute change in velocity & impulse per mass
	float deltaVelocity{ newSepVelScalar - SepVelScalar };
	Math::Vec2 impulsePerMass{ _contact.normal * (deltaVelocity / invMassSum) };

	// Apply impulse
	if (_contact.obj1.HasComponent<Physics2D>())
		_contact.obj1.GetComponent<Physics2D>().velocity += impulsePerMass * ((_contact.obj1.GetComponent<Physics2D>().mass == 0.f) ? 0.f : 1.f / _contact.obj1.GetComponent<Physics2D>().mass);
	if (_contact.obj2.HasComponent<Physics2D>())
		_contact.obj2.GetComponent<Physics2D>().velocity += impulsePerMass * ((_contact.obj2.GetComponent<Physics2D>().mass == 0.f) ? 0.f : 1.f / _contact.obj2.GetComponent<Physics2D>().mass);
		
}