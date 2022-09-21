//
//
//#include "ECSManager.h"
//
//void Physics2DManager::AddRectColliderComponent(const Entity& e, const glm::vec2& _centerOffset, const glm::vec2& _scaleOffset, const bool& _renderFlag) {
//	if (!e.HasComponent<RectCollider>())
//		e.AddComponent(RectCollider{ _centerOffset, _scaleOffset, _renderFlag });
//	else {
//		Physics2DManager::SetRectCenterOffset(e, _centerOffset);
//		Physics2DManager::SetRectScaleOffset(e, _scaleOffset);
//		Physics2DManager::SetRectRenderFlag(e, _renderFlag);
//	}
//}
//
//void Physics2DManager::AddCircleColliderComponent(const Entity& e, const glm::vec2& _centerOffset, const float& _radiusOffset, const bool& _renderFlag) {
//	if (!e.HasComponent<CircleCollider>())
//		e.AddComponent(CircleCollider{ _centerOffset, _radiusOffset, _renderFlag });
//	else {
//		Physics2DManager::SetCircleCenterOffset(e, _centerOffset);
//		Physics2DManager::SetCircleRadiusOffset(e, _radiusOffset);
//		Physics2DManager::SetCircleRenderFlag(e, _renderFlag);
//	}
//}
//
//void Physics2DManager::AddEdgeColliderComponent(const Entity& e, const glm::vec2& _p0Offset, const float& _rotationOffset, const float& _scaleOffset, const bool& _renderFlag) {
//	if (!e.HasComponent<Edge2DCollider>())
//		e.AddComponent(Edge2DCollider{ _p0Offset, _rotationOffset, _scaleOffset, _renderFlag });
//	else {
//		Physics2DManager::SetEdgeP0Offset(e, _p0Offset);
//		Physics2DManager::SetEdgeScaleOffset(e, _scaleOffset);
//		Physics2DManager::SetEdgeRotationOffset(e, _rotationOffset);
//		Physics2DManager::SetEdgeRenderFlag(e, _renderFlag);
//	}
//}
//
//bool Physics2DManager::HasCollider(const Entity& e) {
//	if (e.HasComponent<RectCollider>() || e.HasComponent<CircleCollider>())
//		return true;
//	else
//		return false;
//}
//
//CircleCollider& Physics2DManager::GetCircleCollider(const Entity& e) {
//	return e.GetComponent<CircleCollider>();
//}
//
//glm::vec2 Physics2DManager::GetCircleCenterOffset(const Entity& e) {
//	return Physics2DManager::GetCircleCollider(e).centerOffset;
//}
//
//void Physics2DManager::SetCircleCenterOffset(const Entity& e, const glm::vec2& _centerOffset) {
//	Physics2DManager::GetCircleCollider(e).centerOffset = _centerOffset;
//}
//
//float Physics2DManager::GetCircleRadiusOffset(const Entity& e) {
//	return Physics2DManager::GetCircleCollider(e).scaleOffset;
//}
//
//void Physics2DManager::SetCircleRadiusOffset(const Entity& e, const float& _scaleOffset) {
//	Physics2DManager::GetCircleCollider(e).scaleOffset = _scaleOffset;
//}
//
//bool Physics2DManager::GetCircleRenderFlag(const Entity& e) {
//	return Physics2DManager::GetCircleCollider(e).renderFlag;
//}
//
//void Physics2DManager::SetCircleRenderFlag(const Entity& e, const bool& _renderFlag) {
//	Physics2DManager::GetCircleCollider(e).renderFlag = _renderFlag;
//}
//
//RectCollider& Physics2DManager::GetRectCollider(const Entity& e) {
//	return e.GetComponent<RectCollider>();
//}
//
//glm::vec2 Physics2DManager::GetRectCenterOffset(const Entity& e) {
//	return Physics2DManager::GetRectCollider(e).centerOffset;
//}
//
//void Physics2DManager::SetRectCenterOffset(const Entity& e, const glm::vec2& _centerOffset) {
//	Physics2DManager::GetRectCollider(e).centerOffset = _centerOffset;
//}
//
//glm::vec2 Physics2DManager::GetRectScaleOffset(const Entity& e) {
//	return Physics2DManager::GetRectCollider(e).scaleOffset;
//}
//
//void Physics2DManager::SetRectScaleOffset(const Entity& e, const glm::vec2& _scaleOffset) {
//	Physics2DManager::GetRectCollider(e).scaleOffset = _scaleOffset;
//}
//
//bool Physics2DManager::GetRectRenderFlag(const Entity& e) {
//	return Physics2DManager::GetRectCollider(e).renderFlag;
//}
//
//void Physics2DManager::SetRectRenderFlag(const Entity& e, const bool& _renderFlag) {
//	Physics2DManager::GetRectCollider(e).renderFlag = _renderFlag;
//}
//
//Edge2DCollider& Physics2DManager::GetEdgeCollider(const Entity& e) {
//	return e.GetComponent<Edge2DCollider>();
//}
//
//glm::vec2 Physics2DManager::GetEdgeP0Offset(const Entity& e) {
//	return Physics2DManager::GetEdgeCollider(e).p0Offset;
//}
//
//void Physics2DManager::SetEdgeP0Offset(const Entity& e, const glm::vec2& _centerOffset) {
//	Physics2DManager::GetEdgeCollider(e).p0Offset = _centerOffset;
//}
//
//float Physics2DManager::GetEdgeScaleOffset(const Entity& e) {
//	return Physics2DManager::GetEdgeCollider(e).scaleOffset;
//}
//
//void Physics2DManager::SetEdgeScaleOffset(const Entity& e, const float& _scaleOffset) {
//	Physics2DManager::GetEdgeCollider(e).scaleOffset = _scaleOffset;
//}
//
//float Physics2DManager::GetEdgeRotationOffset(const Entity& e) {
//	return Physics2DManager::GetEdgeCollider(e).rotationOffset;
//}
//
//void Physics2DManager::SetEdgeRotationOffset(const Entity& e, const float& _rotationOffset) {
//	Physics2DManager::GetEdgeCollider(e).rotationOffset = _rotationOffset;
//}
//
//bool Physics2DManager::GetEdgeRenderFlag(const Entity& e) {
//	return Physics2DManager::GetEdgeCollider(e).renderFlag;
//}
//
//void Physics2DManager::SetEdgeRenderFlag(const Entity& e, const bool& _renderFlag) {
//	Physics2DManager::GetEdgeCollider(e).renderFlag = _renderFlag;
//}
//
//
//int Physics2DManager::CheckCollision(const Entity& obj1, const Entity& obj2) {
//	// Rect vs Rect
//	if (obj1.HasComponent<RectCollider>() && obj2.HasComponent<RectCollider>()) {
//		return Physics2DManager::CI_RectvsRect(obj1.GetComponent<Transform>(), Physics2DManager::GetPhysicsComponent(obj1), Physics2DManager::GetRectCollider(obj1),
//			obj2.GetComponent<Transform>(), Physics2DManager::GetPhysicsComponent(obj2), Physics2DManager::GetRectCollider(obj2))
//			? 1 : 0;
//	}
//
//	// Rect vs Circle
//	if (obj1.HasComponent<RectCollider>() && obj2.HasComponent<CircleCollider>()) {
//		//return Physics2DManager::CollisionIntersection_RectvsCircle(obj1, obj2) ? 2 : 0;
//	}
//	if (obj1.HasComponent<CircleCollider>() && obj2.HasComponent<RectCollider>()) {
//		//return Physics2DManager::CollisionIntersection_RectvsCircle(obj2, obj1) ? 3 :0;
//	}
//
//	// Rect vs Line
//	// result = 4;
//
//
//	// Circle vs Circle
//	if (obj1.HasComponent<CircleCollider>() && obj2.HasComponent<CircleCollider>()) {
//		return Physics2DManager::CI_CirclevsCircle(obj1.GetComponent<Transform>(), Physics2DManager::GetPhysicsComponent(obj1), Physics2DManager::GetCircleCollider(obj1),
//			obj2.GetComponent<Transform>(), Physics2DManager::GetPhysicsComponent(obj2), Physics2DManager::GetCircleCollider(obj2))
//			? 5 : 0;
//	}
//
//	// Circle vs Line
//	// result = 6;
//
//
//	// Line vs Line
//	// result = 7
//
//
//	// result = 0;
//	return false;
//}
//
//// Physics function checking
//bool Physics2DManager::CI_RectvsRect(const Transform& tData1, const Physics2D& pData1, const RectCollider& cData1,
//	const Transform& tData2, const Physics2D& pData2, const RectCollider& cData2) {
//	//Collider2D aabb1{ obj1.GetComponent<Collider2D>()}, 
//	//			aabb2{ obj2.GetComponent<Collider2D>()};
//
//	//glm::vec2 center1{ obj1.GetComponent<Transform>().translation + obj1.GetComponent<Collider2D>().centerOffset },
//	//		  scale1 { obj1.GetComponent<Transform>().scale.x * obj1.GetComponent<Collider2D>().dimensionScale.x,
//	//				   obj1.GetComponent<Transform>().scale.y * obj1.GetComponent<Collider2D>().dimensionScale.y },
//	//		  center2{ obj2.GetComponent<Transform>().translation + obj2.GetComponent<Collider2D>().centerOffset },
//	//		  scale2 { obj2.GetComponent<Transform>().scale.x * obj2.GetComponent<Collider2D>().dimensionScale.x,
//	//				   obj2.GetComponent<Transform>().scale.y * obj2.GetComponent<Collider2D>().dimensionScale.y };
//
//	glm::vec2 center1{ tData1.translation + cData1.centerOffset },
//		scale1{ static_cast<float>(static_cast<double>(tData1.scale.x) * static_cast<double>(cData1.scaleOffset.x) / 2.0),
//				 static_cast<float>(static_cast<double>(tData1.scale.y) * static_cast<double>(cData1.scaleOffset.y) / 2.0) },
//		center2{ tData2.translation + cData2.centerOffset },
//		scale2{ static_cast<float>(static_cast<double>(tData2.scale.x) * static_cast<double>(cData2.scaleOffset.x) / 2.0),
//				 static_cast<float>(static_cast<double>(tData2.scale.y) * static_cast<double>(cData2.scaleOffset.y) / 2.0) };
//
//	AABB aabb1{ center1, center1 }, aabb2{ center2, center2 };
//	aabb1.min -= scale1;
//	aabb1.max += scale1;
//	aabb2.min -= scale2;
//	aabb2.max += scale2;
//
//	if (aabb1.max.x < aabb2.min.x)
//		return false;
//	if (aabb1.min.x > aabb2.max.x)
//		return false;
//	if (aabb1.max.y < aabb2.min.y)
//		return false;
//	if (aabb1.min.y > aabb2.max.y)
//		return false;
//
//
//	//float tFirst{ 0 }, tLast{ Helper::dt }, tTmp{ 0 };
//	double tFirst{ 0 }, tLast{ Helper::dt }, tTmp{ 0 };
//
//	//Vb.x = vel2.x - vel1.x;
//	//Vb.y = vel2.y - vel1.y;
//	//glm::vec2 Vb{obj2.GetComponent<Physics2D>().velocity - obj1.GetComponent<Physics2D>().velocity};
//	glm::vec2 Vb{ (pData2.moveDirection * pData2.speed) -
//				  (pData1.moveDirection * pData2.speed) };
//
//	// Relative velocity is zero
//	if (Vb == glm::vec2{ 0.f, 0.f })
//		return false;
//
//	// ------ X axis -----
//	if (static_cast<double>(Vb.x) < 0.0) {
//		if (static_cast<double>(aabb1.min.x) > static_cast<double>(aabb2.max.x)) // Case 1
//			return false;
//		if (static_cast<double>(aabb1.max.x) < static_cast<double>(aabb2.min.x)) {// Case 4
//			tTmp = (static_cast<double>(aabb1.max.x) - static_cast<double>(aabb2.min.x)) / static_cast<double>(Vb.x);
//			tFirst = tTmp > tFirst ? tTmp : tFirst;
//		}
//		if (static_cast<double>(aabb1.min.x) < static_cast<double>(aabb2.max.x)) {// Case 4
//			tTmp = (static_cast<double>(aabb1.min.x) - static_cast<double>(aabb2.max.x)) / static_cast<double>(Vb.x);
//			tLast = tTmp < tLast ? tTmp : tLast;
//		}
//	}
//	if (static_cast<double>(Vb.x) > 0.0) {
//		if (static_cast<double>(aabb1.min.x) > static_cast<double>(aabb2.max.x)) {// Case 2
//			tTmp = (static_cast<double>(aabb1.min.x) - static_cast<double>(aabb2.max.x)) / static_cast<double>(Vb.x);
//			tFirst = tTmp > tFirst ? tTmp : tFirst;
//		}
//		if (static_cast<double>(aabb1.max.x) > static_cast<double>(aabb2.min.x)) {// Case 2
//			tTmp = (static_cast<double>(aabb1.max.x) - static_cast<double>(aabb2.min.x)) / static_cast<double>(Vb.x);
//			tLast = tTmp < tLast ? tTmp : tLast;
//		}
//		if (static_cast<double>(aabb1.max.x) < static_cast<double>(aabb2.min.x)) // Case 3
//			return false;
//	}
//	if (tFirst > tLast) // Case 5
//		return false;
//
//	// ------ Y axis -----
//	if (static_cast<double>(Vb.y) < 0.0) {
//		if (static_cast<double>(aabb1.min.y) > static_cast<double>(aabb2.max.y)) // Case 1
//			return false;
//		if (static_cast<double>(aabb1.max.y) < static_cast<double>(aabb2.min.y)) {// Case 4
//			tTmp = (static_cast<double>(aabb1.max.y) - static_cast<double>(aabb2.min.y)) / static_cast<double>(Vb.y);
//			tFirst = tTmp > tFirst ? tTmp : tFirst;
//		}
//		if (static_cast<double>(aabb1.min.y) < static_cast<double>(aabb2.max.y)) {// Case 4
//			tTmp = (static_cast<double>(aabb1.min.y) - static_cast<double>(aabb2.max.y)) / static_cast<double>(Vb.y);
//			tLast = tTmp < tLast ? tTmp : tLast;
//		}
//	}
//	if (static_cast<double>(Vb.y) > 0.0) {
//		if (static_cast<double>(aabb1.min.y) > static_cast<double>(aabb2.max.y)) {// Case 2
//			tTmp = (static_cast<double>(aabb1.min.y) - static_cast<double>(aabb2.max.y)) / static_cast<double>(Vb.y);
//			tFirst = tTmp > tFirst ? tTmp : tFirst;
//		}
//		if (static_cast<double>(aabb1.max.y) > static_cast<double>(aabb2.min.y)) {// Case 2
//			tTmp = (static_cast<double>(aabb1.max.y) - static_cast<double>(aabb2.min.y)) / static_cast<double>(Vb.y);
//			tLast = tTmp < tLast ? tTmp : tLast;
//		}
//		if (static_cast<double>(aabb1.max.y) < static_cast<double>(aabb2.min.y)) // Case 3
//			return false;
//	}
//	if (tFirst > tLast) // Case 5
//		return false;
//
//	return true;
//}
//
//bool Physics2DManager::CI_CirclevsCircle(const Transform& tData1, const Physics2D& pData1, const CircleCollider& cData1,
//	const Transform& tData2, const Physics2D& pData2, const CircleCollider& cData2) {
//	// Reduce problem by checking a static circle (pillar) and a moving point (ray/line)
//
//	// Find the relative velocity of both circles
//	//CSD1130::Vec2 relVel{ velA - velB };
//	glm::vec2 relVel{ (glm::vec2{glm::cos(pData1.moveDirection), glm::sin(pData1.moveDirection)} *pData1.speed * static_cast<float>(Helper::dt)) -
//					  (glm::vec2{glm::cos(pData2.moveDirection), glm::sin(pData2.moveDirection)} *pData2.speed * static_cast<float>(Helper::dt)) };
//
//	// Static check
//	//if (tDataRay.scale.x == 0) {
//
//	//}
//
//	//std::cout << "(" << relVel.x << ", " << relVel.y << ")" << std::endl;
//
//	// Create a third circle whos radius is the sum of the 2 circles and starts at circleB's position
//	//Circle circleC;
//	//circleC.m_center = circleB.m_center;
//	//circleC.m_radius = circleA.m_radius + circleB.m_radius;	
//	Transform tDataTmpCircle{ tData2 };
//	// Compute new collider radius; ignore translate and rotate
//	tDataTmpCircle.scale = tData1.scale * cData1.scaleOffset + tData2.scale * cData2.scaleOffset;
//	CircleCollider cDataTmpCircle{ cData2 };
//	cDataTmpCircle.scaleOffset = 1.f;
//
//	// Create a ray that starts from circleA's position and goes in the direction of the relative velocity
//	//Ray ray;
//	//ray.m_pt0 = circleA.m_center;
//	//ray.m_dir = relVel;
//	Transform tDataTmpRay{ tData1 };
//	tDataTmpRay.rotation = static_cast<float>(glm::acos(static_cast<double>(relVel.x) / static_cast<double>(glm::length(relVel))));
//	tDataTmpRay.scale.x = glm::length(relVel);
//
//	//// Check if collision will occur by calling the RayCircle collision function
//	//if (CollisionIntersection_RayCircle(ray, circleC, interTime)) {
//	//	// Calculate intersection points
//	//	interPtA = circleA.m_center + velA * interTime;
//	//	interPtB = circleB.m_center + velB * interTime;
//	//	// Return true (collision)
//	//	return 1;
//	//}
//	//else    // Otherwise, no collision happened
//	//	return 0;	// Return false
//	if (Physics2DManager::CI_RayvsStaticCircle(tDataTmpRay, tDataTmpCircle, cDataTmpCircle))
//		return true;
//	else
//		return false;
//}
//
//bool Physics2DManager::CI_RayvsStaticCircle(const Transform& tDataRay,
//	const Transform& tDataCircle, const CircleCollider& cDataCircle) {
//	// Dynamic check
//		// Find the normalised direction of the ray
//		//CSD1130::Vector2D v_normalized;
//		//CSD1130::Vector2DNormalize(v_normalized, ray.m_dir);
//	glm::vec2 rayDir{ glm::cos(tDataRay.rotation),
//					  glm::sin(tDataRay.rotation) };
//
//	// Calculate m and check if the ray is moving away from the circle
//	// And starts outside the circle
//	//float m{ CSD1130::Vector2DDotProduct(circle.m_center - ray.m_pt0, v_normalized) };
//	//if (m < 0.0f && CSD1130::Vector2DSquareLength(circle.m_center - ray.m_pt0) > circle.m_radius * circle.m_radius)
//	//	return 0;	// Case is true: Ray will never hit the circle; return false
//	double m{ static_cast<double>(glm::dot(((tDataCircle.translation + cDataCircle.centerOffset) - tDataRay.translation), rayDir)) };
//	if ((m < 0.0) &&
//		(static_cast<double>(glm::length((tDataCircle.translation + cDataCircle.centerOffset) - tDataRay.translation)) > (static_cast<double>(tDataCircle.scale.x) * static_cast<double>(cDataCircle.scaleOffset) / 2.0))
//		)
//		return false;
//	//double m{ static_cast<double>(glm::dot(((tDataCircle.translation + cDataCircle.centerOffset) - tDataRay.translation), rayDir)) };
//	//if ( (m < 0.0) &&
//	//	((tDataCircle.translation + cDataCircle.centerOffset) - tDataRay.translation) 
//	//	)
//
//	// Calculate and check if the closest distance to the circle is largest than the circle's radius
//	//float n2{ CSD1130::Vector2DSquareLength(circle.m_center - ray.m_pt0) - (m * m) };
//	//if (n2 > (circle.m_radius * circle.m_radius) )
//	//	return 0;	// Case is true: Ray will never hit the circle; return false
//	double n{ static_cast<double>(glm::length((tDataCircle.translation + cDataCircle.centerOffset) - tDataRay.translation)) - m };
//	if (n > (static_cast<double>(tDataCircle.scale.x) * static_cast<double>(cDataCircle.scaleOffset) / 2.0))
//		return false;
//
//	// Find the intersection time and take the minimum value
//	//float s{ sqrt((circle.m_radius * circle.m_radius) - n2) };
//	//float tmpIntertime1 = (m - s) / Vector2DLength(ray.m_dir);
//	//float tmpIntertime2 = (m + s) / Vector2DLength(ray.m_dir);
//	double s{ (static_cast<double>(tDataCircle.scale.x) * static_cast<double>(cDataCircle.scaleOffset) / 2.0) - n };
//	double tmpInterTime1{ (m - s) / static_cast<double>(tDataRay.scale.x) },
//		tmpInterTime2{ (m + s) / static_cast<double>(tDataRay.scale.x) };
//
//	//interTime = (tmpIntertime1 < tmpIntertime2) ? tmpIntertime1 : tmpIntertime2;
//	double interTime = (tmpInterTime1 < tmpInterTime2) ? tmpInterTime1 : tmpInterTime2;
//
//	// Check if the intersection time is within 1 second
//	//if (0.0f <= interTime && interTime <= 1.0f)
//	//	return 1;	// Case is true: Ray will intersect circle in this frame; return true
//	//else
//	//	return 0;	// Case is false; return false
//	if (0.0 <= interTime && interTime <= 1.0)
//		return true;
//	else
//		return false;
//}
