#include "ECSManager.h"

void Collision2DManager::AddRectColliderComponent(const Entity& e, const glm::vec2& _centerOffset, const glm::vec2& _scaleOffset, const bool& _renderFlag) {
	if (!e.HasComponent<RectCollider>())
		e.AddComponent(RectCollider{ _centerOffset, _scaleOffset, _renderFlag });
	else {
		Collision2DManager::SetRectCenterOffset(e, _centerOffset);
		Collision2DManager::SetRectScaleOffset(e, _scaleOffset);
		Collision2DManager::SetRectRenderFlag(e, _renderFlag);
	}
}

void Collision2DManager::AddCircleColliderComponent(const Entity& e, const glm::vec2& _centerOffset, const float& _radiusOffset, const bool& _renderFlag) {
	if (!e.HasComponent<CircleCollider>())
		e.AddComponent(CircleCollider{ _centerOffset, _radiusOffset, _renderFlag });
	else {
		Collision2DManager::SetCircleCenterOffset(e, _centerOffset);
		Collision2DManager::SetCircleRadiusOffset(e, _radiusOffset);
		Collision2DManager::SetCircleRenderFlag(e, _renderFlag);
	}
}

void Collision2DManager::AddEdgeColliderComponent(const Entity& e, const glm::vec2& _p0Offset, const float& _rotationOffset, const float& _scaleOffset, const bool& _renderFlag) {
	if (!e.HasComponent<Edge2DCollider>())
		e.AddComponent(Edge2DCollider{ _p0Offset, _rotationOffset, _scaleOffset, _renderFlag });
	else {
		Collision2DManager::SetEdgeP0Offset(e, _p0Offset);
		Collision2DManager::SetEdgeScaleOffset(e, _scaleOffset);
		Collision2DManager::SetEdgeRotationOffset(e, _rotationOffset);
		Collision2DManager::SetEdgeRenderFlag(e, _renderFlag);
	}
}

bool Collision2DManager::HasCollider(const Entity& e) {
	if (e.HasComponent<RectCollider>() || e.HasComponent<CircleCollider>())
		return true;
	else
		return false;
}

CircleCollider& Collision2DManager::GetCircleCollider(const Entity& e) {
	return e.GetComponent<CircleCollider>();
}

glm::vec2 Collision2DManager::GetCircleCenterOffset(const Entity& e) {
	return Collision2DManager::GetCircleCollider(e).centerOffset;
}

void Collision2DManager::SetCircleCenterOffset(const Entity& e, const glm::vec2& _centerOffset) {
	Collision2DManager::GetCircleCollider(e).centerOffset = _centerOffset;
}

float Collision2DManager::GetCircleRadiusOffset(const Entity& e) {
	return Collision2DManager::GetCircleCollider(e).scaleOffset;
}

void Collision2DManager::SetCircleRadiusOffset(const Entity& e, const float& _scaleOffset) {
	Collision2DManager::GetCircleCollider(e).scaleOffset = _scaleOffset;
}

bool Collision2DManager::GetCircleRenderFlag(const Entity& e) {
	return Collision2DManager::GetCircleCollider(e).renderFlag;
}

void Collision2DManager::SetCircleRenderFlag(const Entity& e, const bool& _renderFlag) {
	Collision2DManager::GetCircleCollider(e).renderFlag = _renderFlag;
}

RectCollider& Collision2DManager::GetRectCollider(const Entity& e) {
	return e.GetComponent<RectCollider>();
}

glm::vec2 Collision2DManager::GetRectCenterOffset(const Entity& e) {
	return Collision2DManager::GetRectCollider(e).centerOffset;
}

void Collision2DManager::SetRectCenterOffset(const Entity& e, const glm::vec2& _centerOffset) {
	Collision2DManager::GetRectCollider(e).centerOffset = _centerOffset;
}

glm::vec2 Collision2DManager::GetRectScaleOffset(const Entity& e) {
	return Collision2DManager::GetRectCollider(e).scaleOffset;
}

void Collision2DManager::SetRectScaleOffset(const Entity& e, const glm::vec2& _scaleOffset) {
	Collision2DManager::GetRectCollider(e).scaleOffset = _scaleOffset;
}

bool Collision2DManager::GetRectRenderFlag(const Entity& e) {
	return Collision2DManager::GetRectCollider(e).renderFlag;
}

void Collision2DManager::SetRectRenderFlag(const Entity& e, const bool& _renderFlag) {
	Collision2DManager::GetRectCollider(e).renderFlag = _renderFlag;
}

Edge2DCollider& Collision2DManager::GetEdgeCollider(const Entity& e) {
	return e.GetComponent<Edge2DCollider>();
}

glm::vec2 Collision2DManager::GetEdgeP0Offset(const Entity& e) {
	return Collision2DManager::GetEdgeCollider(e).p0Offset;
}

void Collision2DManager::SetEdgeP0Offset(const Entity& e, const glm::vec2& _centerOffset) {
	Collision2DManager::GetEdgeCollider(e).p0Offset = _centerOffset;
}

float Collision2DManager::GetEdgeScaleOffset(const Entity& e) {
	return Collision2DManager::GetEdgeCollider(e).scaleOffset;
}

void Collision2DManager::SetEdgeScaleOffset(const Entity& e, const float& _scaleOffset) {
	Collision2DManager::GetEdgeCollider(e).scaleOffset = _scaleOffset;
}

float Collision2DManager::GetEdgeRotationOffset(const Entity& e) {
	return Collision2DManager::GetEdgeCollider(e).rotationOffset;
}

void Collision2DManager::SetEdgeRotationOffset(const Entity& e, const float& _rotationOffset) {
	Collision2DManager::GetEdgeCollider(e).rotationOffset = _rotationOffset;
}

bool Collision2DManager::GetEdgeRenderFlag(const Entity& e) {
	return Collision2DManager::GetEdgeCollider(e).renderFlag;
}

void Collision2DManager::SetEdgeRenderFlag(const Entity& e, const bool& _renderFlag) {
	Collision2DManager::GetEdgeCollider(e).renderFlag = _renderFlag;
}

bool Collision2DManager::ExistsInCollisionList(const Entity& e1, const Entity& e2) {
	if (mCollisionCheckList.size() == 0)
		return false;

	for (const CollisionStore& cs : mCollisionCheckList) {
		if ((cs.obj1.id == e1.id && cs.obj2.id == e2.id) ||
			(cs.obj1.id == e2.id && cs.obj2.id == e1.id))
			return true;
	}

	return false;
}

void Collision2DManager::UpdateCollisionList() {
	Collision2DManager::UpdateCollisionList(mEntities);
}

void Collision2DManager::UpdateCollisionList(const std::set<Entity>& _entityList) {
	mCollisionCheckList.clear();

	for (const Entity& e1 : _entityList) {
		for (const Entity& e2 : _entityList) {
			if (e1.id == e2.id || !Collision2DManager::HasCollider(e1) || !Collision2DManager::HasCollider(e2))
				continue;

			if (!Collision2DManager::ExistsInCollisionList(e1, e2))
				mCollisionCheckList.emplace_back(CollisionStore{ 0, e1, e2 });
		}
	}

	//for (CollisionStore& cs : mCollisionCheckList) {
	//	std::cout << cs.obj1->GetComponent<General>().name << " | " << cs.obj2->GetComponent<General>().name << std::endl;
	//}

	//std::cout << std::endl;
}

void Collision2DManager::Update() {
	Collision2DManager::Update(mEntities);
}

void Collision2DManager::Update(const std::set<Entity>& _entityList) {
	Collision2DManager::UpdateCollisionList(_entityList);

	for (CollisionStore& cs : Collision2DManager::mCollisionCheckList) {
		if (Collision2DManager::CheckCollision(cs)) {
			Collision2DManager::ResolveCollision(cs);
		}
	}
}

bool Collision2DManager::CheckCollision(CollisionStore& _collisionData) {
	// Rect vs Rect
	if (_collisionData.obj1.HasComponent<RectCollider>() && _collisionData.obj2.HasComponent<RectCollider>()) {
		_collisionData.collisionType = 1;
		return Collision2DManager::CI_RectvsRect(_collisionData);
	}

	// Rect vs Circle
	if (_collisionData.obj1.HasComponent<RectCollider>() && _collisionData.obj2.HasComponent<CircleCollider>()) {
		//return Physics2DManager::CollisionIntersection_RectvsCircle(CollisionData.obj1, CollisionData.obj2) ? 2 : 0;
	}
	if (_collisionData.obj1.HasComponent<CircleCollider>() && _collisionData.obj2.HasComponent<RectCollider>()) {
		//return Physics2DManager::CollisionIntersection_RectvsCircle(CollisionData.obj2, CollisionData.obj1) ? 3 :0;
	}

	// Rect vs Line
	// result = 4;
	// result = 5


	// Circle vs Circle
	if (_collisionData.obj1.HasComponent<CircleCollider>() && _collisionData.obj2.HasComponent<CircleCollider>()) {
		_collisionData.collisionType = 6;
		return Collision2DManager::CI_CirclevsCircle(_collisionData);
	}

	// Circle vs Line
	// result = 7;
	// result = 8

	// Line vs Line
	// result = 9


	// result = 0;
	return false;
}

void Collision2DManager::ResolveCollision(CollisionStore& _collisionData) {
	switch (_collisionData.collisionType) {
	case 1:	// Rect vs Rect
		Collision2DManager::CR_RectvsRect(_collisionData);
		break;
	case 2:	// Rect vs Circle

		break;
	case 3:	// Circle vs Rect

		break;
	case 4:	// Rect vs Line

		break;
	case 5:	// Line vs Rect

		break;
	case 6:	// Circle vs Circle
		Collision2DManager::CR_CirclevsCircle(_collisionData);
		break;
	case 7:	// Circle vs Line

		break;
	case 8:	// Line vs Circle

		break;
	case 9:	// Line vs Line

		break;
	case 0:
	default:
		break;
	}

	if (_collisionData.obj1.HasComponent<Audio>()) {
		audioManager->PlaySound(_collisionData.obj1, 3);
	}
	if (_collisionData.obj2.HasComponent<Audio>()) {
		audioManager->PlaySound(_collisionData.obj2, 4);
	}
}

// Physics function checking
bool Collision2DManager::CI_RectvsRect(CollisionStore& _collisionData) {
	glm::vec2 center1{ _collisionData.obj1.GetComponent<Transform>().translation + _collisionData.obj1.GetComponent<RectCollider>().centerOffset },
		scale1{ static_cast<float>(static_cast<double>(_collisionData.obj1.GetComponent<Transform>().scale.x) * static_cast<double>(_collisionData.obj1.GetComponent<RectCollider>().scaleOffset.x) / 2.0),
				 static_cast<float>(static_cast<double>(_collisionData.obj1.GetComponent<Transform>().scale.y) * static_cast<double>(_collisionData.obj1.GetComponent<RectCollider>().scaleOffset.y) / 2.0) },
		center2{ _collisionData.obj2.GetComponent<Transform>().translation + _collisionData.obj2.GetComponent<RectCollider>().centerOffset },
		scale2{ static_cast<float>(static_cast<double>(_collisionData.obj2.GetComponent<Transform>().scale.x) * static_cast<double>(_collisionData.obj2.GetComponent<RectCollider>().scaleOffset.x) / 2.0),
				 static_cast<float>(static_cast<double>(_collisionData.obj2.GetComponent<Transform>().scale.y) * static_cast<double>(_collisionData.obj2.GetComponent<RectCollider>().scaleOffset.y) / 2.0) };

	glm::vec2 aabb1min{ center1 - scale1 },
		aabb1max{ center1 + scale1 },
		aabb2min{ center2 - scale2 },
		aabb2max{ center2 + scale2 };

	// Static
	if (aabb1max.x < aabb2min.x)
		return false;
	if (aabb1min.x > aabb2max.x)
		return false;
	if (aabb1max.y < aabb2min.y)
		return false;
	if (aabb1min.y > aabb2max.y)
		return false;

	//Vb.x = vel2.x - vel1.x;
	//Vb.y = vel2.y - vel1.y;
	//glm::vec2 Vb{obj2.GetComponent<Physics2D>().velocity - obj1.GetComponent<Physics2D>().velocity};
	glm::vec2 Vb{ (glm::vec2{glm::cos(_collisionData.obj2.GetComponent<Physics2D>().moveDirection), glm::sin(_collisionData.obj2.GetComponent<Physics2D>().moveDirection)} *_collisionData.obj2.GetComponent<Physics2D>().speed) -
				  (glm::vec2{glm::cos(_collisionData.obj1.GetComponent<Physics2D>().moveDirection), glm::sin(_collisionData.obj1.GetComponent<Physics2D>().moveDirection)} *_collisionData.obj1.GetComponent<Physics2D>().speed) };

	// If relative velocity is zero
	if (Vb == glm::vec2{ 0.f, 0.f })
		return false;

	// Dynamic
	double tFirst{ 0 }, tLast{ Helper::dt }, tTmp{ 0 };

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

	_collisionData.interTime = tFirst;

	return true;
}

bool Collision2DManager::CI_CirclevsCircle(CollisionStore& _collisionData) {
	// Find the relative velocity of both circles
	glm::vec2 relVel{ (glm::vec2{glm::cos(_collisionData.obj1.GetComponent<Physics2D>().moveDirection), glm::sin(_collisionData.obj1.GetComponent<Physics2D>().moveDirection)} *_collisionData.obj1.GetComponent<Physics2D>().speed * static_cast<float>(Helper::dt)) -
					  (glm::vec2{glm::cos(_collisionData.obj2.GetComponent<Physics2D>().moveDirection), glm::sin(_collisionData.obj2.GetComponent<Physics2D>().moveDirection)} *_collisionData.obj2.GetComponent<Physics2D>().speed * static_cast<float>(Helper::dt)) };

	// Static
		// If relVel is 0
	if (relVel == glm::vec2{ 0.f, 0.f }) {
		if (glm::abs(glm::distance(_collisionData.obj1.GetComponent<Transform>().translation + _collisionData.obj1.GetComponent<CircleCollider>().centerOffset, _collisionData.obj2.GetComponent<Transform>().translation + _collisionData.obj2.GetComponent<CircleCollider>().centerOffset) -
			(_collisionData.obj1.GetComponent<Transform>().scale.x * _collisionData.obj1.GetComponent<CircleCollider>().scaleOffset + _collisionData.obj2.GetComponent<Transform>().scale.x * _collisionData.obj2.GetComponent<CircleCollider>().scaleOffset)) > 0.f)
			return false;
		else
			return true;
	}

	// Dynamic 
	// Reduce problem by checking a static circle (pillar) and a moving point (ray/line)
		// Create a third circle that inherits the following:
		//	second object's collider's translation (Transform + centreOffset)
		//  radius is the sum of the radius of the 2 circles
		//  scaleOffset is 1
	Transform tDataTmpCircle{ _collisionData.obj2.GetComponent<Transform>() };
	tDataTmpCircle.translation += _collisionData.obj2.GetComponent<CircleCollider>().centerOffset;
	tDataTmpCircle.scale = _collisionData.obj1.GetComponent<Transform>().scale * _collisionData.obj1.GetComponent<CircleCollider>().scaleOffset +
		_collisionData.obj2.GetComponent<Transform>().scale * _collisionData.obj2.GetComponent<CircleCollider>().scaleOffset;

	//std::cout << (_collisionData.obj2.GetComponent<Transform>().translation + _collisionData.obj2.GetComponent<CircleCollider>().centerOffset).x << ", " << (_collisionData.obj2.GetComponent<Transform>().translation + _collisionData.obj2.GetComponent<CircleCollider>().centerOffset).y << " | " 
	//			<< tDataTmpCircle.translation.x << ", " << tDataTmpCircle.translation.y << std::endl;

	//std::cout << (_collisionData.obj1.GetComponent<Transform>().scale * _collisionData.obj1.GetComponent<CircleCollider>().scaleOffset +
	//	_collisionData.obj2.GetComponent<Transform>().scale * _collisionData.obj2.GetComponent<CircleCollider>().scaleOffset).x << " | " << tDataTmpCircle.scale.x << std::endl;

	// Create a ray that starts from first object's position and goes in the direction of the relative velocity
	Transform tDataTmpRay{};
	tDataTmpRay.translation = _collisionData.obj1.GetComponent<Transform>().translation + _collisionData.obj1.GetComponent<CircleCollider>().centerOffset;
	tDataTmpRay.rotation = static_cast<float>(glm::acos(static_cast<double>(relVel.x) / static_cast<double>(glm::length(relVel))));
	tDataTmpRay.scale.x = glm::length(relVel);

	//std::cout << (_collisionData.obj1.GetComponent<Transform>().translation + _collisionData.obj1.GetComponent<CircleCollider>().centerOffset).x << ", " << (_collisionData.obj1.GetComponent<Transform>().translation + _collisionData.obj1.GetComponent<CircleCollider>().centerOffset).y << " | "
	//	<< tDataTmpRay.translation.x << ", " << tDataTmpRay.translation.y << std::endl;
	//std::cout << relVel.x << ", " << relVel.y << " | " << tDataTmpRay.rotation << std::endl;

	// Check if collision will occur by calling the RayCircle collision function
	// Get normalized direction of the ray
	glm::vec2 relVelDir{ glm::normalize(relVel) };

	// Calculate m and check if ray is moving away from circle
	double m{ static_cast<double>(glm::dot(tDataTmpCircle.translation - tDataTmpRay.translation, relVelDir)) };
	if ((m < 0.0) &&
		(static_cast<double>(glm::length(tDataTmpCircle.translation - tDataTmpRay.translation)) > (tDataTmpCircle.scale.x / 2.0)))
		return false;

	// Calculate and check if the closest distance to the circle is larger than the circle's radius
	double n{ static_cast<double>(glm::length(tDataTmpCircle.translation - tDataTmpRay.translation)) - m };
	if (n > (static_cast<double>(tDataTmpCircle.scale.x) / 2.0))
		return false;

	// Find intersection time and take minimum value
	double s{ static_cast<double>(tDataTmpCircle.scale.x) / 2.0 - n };
	double tmpInterTime1{ (m - s) / static_cast<double>(tDataTmpRay.scale.x) },
		tmpInterTime2{ (m + s) / static_cast<double>(tDataTmpRay.scale.x) };
	double interTime = (tmpInterTime1 < tmpInterTime2) ? tmpInterTime1 : tmpInterTime2;

	// Check if the intersection time is within 1 unit
	if (0.0 <= interTime && interTime <= 1.0) {
		_collisionData.interTime = interTime;
		return true;
	}
	else
		return false;
}

void Collision2DManager::CR_RectvsRect(CollisionStore& _collisionData) {
	//Collision2DManager::CR_CirclevsCircle(_collisionData);
	// Compute and store objects' current velocity
	glm::vec2 velObj1{ glm::vec2{glm::cos(_collisionData.obj1.GetComponent<Physics2D>().moveDirection), glm::sin(_collisionData.obj1.GetComponent<Physics2D>().moveDirection)} *_collisionData.obj1.GetComponent<Physics2D>().speed * static_cast<float>(Helper::dt) },
		velObj2{ glm::vec2{glm::cos(_collisionData.obj2.GetComponent<Physics2D>().moveDirection), glm::sin(_collisionData.obj2.GetComponent<Physics2D>().moveDirection)} *_collisionData.obj2.GetComponent<Physics2D>().speed * static_cast<float>(Helper::dt) };

	glm::vec2 interPtObj1{ _collisionData.obj1.GetComponent<Transform>().translation + velObj1 * static_cast<float>(_collisionData.interTime) },
		interPtObj2{ _collisionData.obj2.GetComponent<Transform>().translation + velObj2 * static_cast<float>(_collisionData.interTime) };

	//glm::vec2 normal{ glm::normalize(interPtObj1 - interPtObj2) };
	//double aA{ glm::dot(velObj1, normal) },
	//	   aB{ glm::dot(velObj2, normal) };

	_collisionData.obj1.GetComponent<Transform>().translation = interPtObj1;
	_collisionData.obj2.GetComponent<Transform>().translation = interPtObj2;

	/*float tmpDir = _collisionData.obj1.GetComponent<Physics2D>().moveDirection;
	_collisionData.obj1.GetComponent<Physics2D>().moveDirection = _collisionData.obj2.GetComponent<Physics2D>().moveDirection;
	_collisionData.obj2.GetComponent<Physics2D>().moveDirection = tmpDir;

	transformManager->SetTranslate(*_collisionData.obj1, transformManager->GetTranslate(*_collisionData.obj1) + glm::vec2{ glm::cos(physics2DManager->GetMoveDirection(*_collisionData.obj1)), glm::sin(physics2DManager->GetMoveDirection(*_collisionData.obj1)) } * physics2DManager->GetSpeed(*_collisionData.obj1) * static_cast<float>(Helper::dt));
	transformManager->SetTranslate(*_collisionData.obj2, transformManager->GetTranslate(*_collisionData.obj2) + glm::vec2{ glm::cos(physics2DManager->GetMoveDirection(*_collisionData.obj2)), glm::sin(physics2DManager->GetMoveDirection(*_collisionData.obj2)) } * physics2DManager->GetSpeed(*_collisionData.obj2) * static_cast<float>(Helper::dt));*/
}

void Collision2DManager::CR_CirclevsCircle(CollisionStore& _collisionData) {
	// Compute and store objects' current velocity
	glm::vec2 velObj1{ glm::vec2{glm::cos(_collisionData.obj1.GetComponent<Physics2D>().moveDirection), glm::sin(_collisionData.obj1.GetComponent<Physics2D>().moveDirection)} *_collisionData.obj1.GetComponent<Physics2D>().speed * static_cast<float>(Helper::dt) },
		velObj2{ glm::vec2{glm::cos(_collisionData.obj2.GetComponent<Physics2D>().moveDirection), glm::sin(_collisionData.obj2.GetComponent<Physics2D>().moveDirection)} *_collisionData.obj2.GetComponent<Physics2D>().speed * static_cast<float>(Helper::dt) };

	// Compute and store objects' meeting point
	glm::vec2 interPtObj1{ _collisionData.obj1.GetComponent<Transform>().translation + velObj1 * static_cast<float>(_collisionData.interTime) },
		interPtObj2{ _collisionData.obj2.GetComponent<Transform>().translation + velObj2 * static_cast<float>(_collisionData.interTime) };
	// Get normal to collision occurance
	glm::vec2 normal{ glm::normalize(interPtObj1 - interPtObj2) };
	double aA{ glm::dot(velObj1, normal) },
		aB{ glm::dot(velObj2, normal) };

	// Compute objects' reflected velocity after collision
	glm::vec2 reflectedVelObj1{ velObj1 - static_cast<float>(((2.0 * (aA - aB)) / (static_cast<double>(_collisionData.obj1.GetComponent<Physics2D>().mass) + static_cast<double>(_collisionData.obj2.GetComponent<Physics2D>().mass))) * static_cast<double>(_collisionData.obj2.GetComponent<Physics2D>().mass)) * normal },
		reflectedVelObj2{ velObj2 + static_cast<float>(((2.0 * (aA - aB)) / (static_cast<double>(_collisionData.obj1.GetComponent<Physics2D>().mass) + static_cast<double>(_collisionData.obj2.GetComponent<Physics2D>().mass))) * static_cast<double>(_collisionData.obj1.GetComponent<Physics2D>().mass)) * normal };

	// Compute objects' velocity direction after collision
	_collisionData.obj1.GetComponent<Physics2D>().moveDirection = static_cast<float>(glm::acos(static_cast<double>(reflectedVelObj1.x) / static_cast<double>(glm::length(reflectedVelObj2))));
	_collisionData.obj2.GetComponent<Physics2D>().moveDirection = static_cast<float>(glm::acos(static_cast<double>(reflectedVelObj2.x) / static_cast<double>(glm::length(reflectedVelObj2))));

	// Compute speed of the objects
	_collisionData.obj1.GetComponent<Physics2D>().speed = static_cast<float>(static_cast<double>(glm::length(reflectedVelObj1)) / Helper::dt);
	_collisionData.obj2.GetComponent<Physics2D>().speed = static_cast<float>(static_cast<double>(glm::length(reflectedVelObj2)) / Helper::dt);

	// Compute objects' position the frame after the collision
	_collisionData.obj1.GetComponent<Transform>().translation = interPtObj1 + reflectedVelObj1 * static_cast<float>(1.0 - _collisionData.interTime);
	_collisionData.obj2.GetComponent<Transform>().translation = interPtObj2 + reflectedVelObj2 * static_cast<float>(1.0 - _collisionData.interTime);
}


//	if (0.0 <= interTime && interTime <= 1.0)
//		return true;
//	else
//		return false;
//}
