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

/*!*****************************************************************************
\brief
HasCollider function that checks if the given entity contains a collider

\param const Entity &
A reference to a read-only Entity to add collider to

\return bool
Evaluated result of whether the entity has a collider
*******************************************************************************/
bool Collision2DManager::HasCollider(const Entity& _e) {
	if (_e.HasComponent<RectCollider>() ||
		_e.HasComponent<CircleCollider>() ||
		_e.HasComponent<Edge2DCollider>() ||
		_e.HasComponent<Point2DCollider>())
		return true;
	else
		return false;
}

/*!*****************************************************************************
\brief
AddRectColliderComponent function that adds a rectangular collider to the given
entity of specified parameters

\param const Entity &
A reference to a read-only Entity to add collider to

\param const Math::Vec2 &
A reference to a read-only variable containing the position offset of the 
collider from the entity's position

\param const Math::Vec2 & 
A reference to a read-only variable containing the scale offset of the collider 
from the entity's scale

\param const bool &
A reference to a read-only variable containing the value of whether the collider
should be rendered

\return void
NULL
*******************************************************************************/
void Collision2DManager::AddRectColliderComponent(const Entity& _e, const Math::Vec2& _centerOffset, const Math::Vec2& _scaleOffset, const bool& _renderFlag) {
	// Check if the component already exists
	// If so, edit it
	if (!_e.HasComponent<RectCollider>())
		_e.AddComponent(RectCollider{ _centerOffset, _scaleOffset, _renderFlag });
	else {
		Collision2DManager::SetRectCenterOffset(_e, _centerOffset);
		Collision2DManager::SetRectScaleOffset(_e, _scaleOffset);
		Collision2DManager::SetRectRenderFlag(_e, _renderFlag);
	}
}

/*!*****************************************************************************
\brief
AddCircleColliderComponent function that adds a circular collider to the given
entity of specified parameters

\param const Entity &
A reference to a read-only Entity to add collider to

\param const Math::Vec2 &
A reference to a read-only variable containing the position offset of the
collider from the entity's position

\param const float &
A reference to a read-only variable containing the radius offset of the collider
from the entity's scale

\param const bool &
A reference to a read-only variable containing the value of whether the collider
should be rendered

\return void
NULL
*******************************************************************************/
void Collision2DManager::AddCircleColliderComponent(const Entity& _e, const Math::Vec2& _centerOffset, const float& _radiusOffset, const bool& _renderFlag) {
	// Check if the component already exists
	// If so, edit it
	if (!_e.HasComponent<CircleCollider>())
		_e.AddComponent(CircleCollider{ _centerOffset, _radiusOffset, _renderFlag });
	else {
		Collision2DManager::SetCircleCenterOffset(_e, _centerOffset);
		Collision2DManager::SetCircleRadiusOffset(_e, _radiusOffset);
		Collision2DManager::SetCircleRenderFlag(_e, _renderFlag);
	}
}

/*!*****************************************************************************
\brief
AddEdgeColliderComponent function that adds a circular collider to the given
entity of specified parameters

\param const Entity &
A reference to a read-only Entity to add collider to

\param const Math::Vec2 &
A reference to a read-only variable containing the position offset of the
collider from the entity's position

\param const float &
A reference to a read-only variable containing the rotation offset of the collider
from the entity's rotation

\param const float &
A reference to a read-only variable containing the scale offset of the collider
from the entity's scale

\param const bool &
A reference to a read-only variable containing the value of whether the collider
should be rendered

\return void
NULL
*******************************************************************************/
void Collision2DManager::AddEdgeColliderComponent(const Entity& _e, const Math::Vec2& _p0Offset, const float& _rotationOffset, const float& _scaleOffset, const bool& _renderFlag) {
	// Check if the component already exists
	// If so, edit it
	if (!_e.HasComponent<Edge2DCollider>())
		_e.AddComponent(Edge2DCollider{ _p0Offset, _rotationOffset, _scaleOffset, _renderFlag });
	else {
		Collision2DManager::SetEdgeP0Offset(_e, _p0Offset);
		Collision2DManager::SetEdgeScaleOffset(_e, _scaleOffset);
		Collision2DManager::SetEdgeRotationOffset(_e, _rotationOffset);
		Collision2DManager::SetEdgeRenderFlag(_e, _renderFlag);
	}
}

/*!*****************************************************************************
\brief
AddPointColliderComponent function that adds a point collider to the given
entity of specified parameters

\param const Entity &
A reference to a read-only Entity to add collider to

\param const Math::Vec2 &
A reference to a read-only variable containing the center offset of the
collider from the entity's position

\param const bool &
A reference to a read-only variable containing the value of whether the collider
should be rendered

\return void
NULL
*******************************************************************************/
void Collision2DManager::AddPointColliderComponent(const Entity& _e, const Math::Vec2& _centerOffset, const bool& _renderFlag) {
	// Check if the component already exists
	// If so, edit it
	if (!_e.HasComponent<Point2DCollider>())
		_e.AddComponent(Point2DCollider{ _centerOffset, _renderFlag });
	else {
		Collision2DManager::SetPointCenterOffset(_e, _centerOffset);
		Collision2DManager::SetPointRenderFlag(_e, _renderFlag);
	}
}

/*!*****************************************************************************
\brief
RemoveRectColliderComponent function that removes rectangular collider of the 
given entity

\param const Entity &
A reference to a read-only Entity to remove collider from

\return void
NULL
*******************************************************************************/
void Collision2DManager::RemoveRectColliderComponent(const Entity& _e) {
	if (_e.HasComponent<RectCollider>())
		_e.RemoveComponent<RectCollider>();
}

/*!*****************************************************************************
\brief
RemoveCircleColliderComponent function that removes circle collider of the
given entity

\param const Entity &
A reference to a read-only Entity to remove collider from

\return void
NULL
*******************************************************************************/
void Collision2DManager::RemoveCircleColliderComponent(const Entity& _e) {
	if (_e.HasComponent<CircleCollider>())
		_e.RemoveComponent<CircleCollider>();
}

/*!*****************************************************************************
\brief
RemoveEdgeColliderComponent function that removes edge collider of the
given entity

\param const Entity &
A reference to a read-only Entity to remove collider from

\return void
NULL
*******************************************************************************/
void Collision2DManager::RemoveEdgeColliderComponent(const Entity& _e) {
	if (_e.HasComponent<Edge2DCollider>())
		_e.RemoveComponent<Edge2DCollider>();
}

/*!*****************************************************************************
\brief
RemovePointColliderComponent function that removes point collider of the
given entity

\param const Entity &
A reference to a read-only Entity to remove collider from

\return void
NULL
*******************************************************************************/
void Collision2DManager::RemovePointColliderComponent(const Entity& _e) {
	if (_e.HasComponent<Point2DCollider>())
		_e.RemoveComponent<Point2DCollider>();
}

/*!*****************************************************************************
\brief
GetCircleCollider function that returns a reference to the given entity's circle
collider

\param const Entity &
A reference to a read-only Entity to get the circle collider of

\return CircleCollider&
A reference to the circle collider of the entity
*******************************************************************************/
CircleCollider& Collision2DManager::GetCircleCollider(const Entity& _e) {
	return _e.GetComponent<CircleCollider>();
}

/*!*****************************************************************************
\brief
GetCircleCenterOffset function that returns the value of the given entity's circle
collider's center offset

\param const Entity &
A reference to a read-only Entity to get the center offset of

\return Math::Vec2
Value of the circle collider's center offset
*******************************************************************************/
Math::Vec2 Collision2DManager::GetCircleCenterOffset(const Entity& _e) {
	return Collision2DManager::GetCircleCollider(_e).centerOffset;
}

/*!*****************************************************************************
\brief
SetCircleCenterOffset function that set the value of the given entity's circle
collider's center offset

\param const Entity &
A reference to a read-only Entity to set the center offset of

\param const Math::Vec2&
A reference to a read-only variable containing the center offset to set to

\return void
NULL
*******************************************************************************/
void Collision2DManager::SetCircleCenterOffset(const Entity& _e, const Math::Vec2& _centerOffset) {
	Collision2DManager::GetCircleCollider(_e).centerOffset = _centerOffset;
}

/*!*****************************************************************************
\brief
GetCircleRadiusOffset function that returns the value of the given entity's circle
collider's radius offset

\param const Entity &
A reference to a read-only Entity to get the radius offset of

\return float
Value of the circle collider's radius offset
*******************************************************************************/
float Collision2DManager::GetCircleRadiusOffset(const Entity& _e) {
	return Collision2DManager::GetCircleCollider(_e).scaleOffset;
}

/*!*****************************************************************************
\brief
SetCircleRadiusOffset function that set the value of the given entity's circle
collider's radius offset

\param const Entity &
A reference to a read-only Entity to set the radius offset of

\param const float &
A reference to a read-only variable containing the radius offset to set to

\return void
NULL
*******************************************************************************/
void Collision2DManager::SetCircleRadiusOffset(const Entity& _e, const float& _scaleOffset) {
	Collision2DManager::GetCircleCollider(_e).scaleOffset = _scaleOffset;
}

/*!*****************************************************************************
\brief
GetCircleRenderFlag function that returns the value of the given entity's circle
collider's render flag

\param const Entity &
A reference to a read-only Entity to get the render flag of

\return bool
Value of the circle collider's render flag
*******************************************************************************/
bool Collision2DManager::GetCircleRenderFlag(const Entity& _e) {
	return Collision2DManager::GetCircleCollider(_e).renderFlag;
}

/*!*****************************************************************************
\brief
SetCircleRenderFlag function that set the value of the given entity's circle
collider's render flag

\param const Entity &
A reference to a read-only Entity to set the render flag of

\param const bool &
A reference to a read-only variable containing the flag to set the render flag to

\return void
NULL
*******************************************************************************/
void Collision2DManager::SetCircleRenderFlag(const Entity& _e, const bool& _renderFlag) {
	Collision2DManager::GetCircleCollider(_e).renderFlag = _renderFlag;
}

/*!*****************************************************************************
\brief
GetRectCollider function that returns a reference to the given entity's rectangular
collider

\param const Entity &
A reference to a read-only Entity to get the rectangular collider of

\return RectCollider&
A reference to the rectangular collider of the entity
*******************************************************************************/
RectCollider& Collision2DManager::GetRectCollider(const Entity& _e) {
	return _e.GetComponent<RectCollider>();
}

/*!*****************************************************************************
\brief
GetRectCenterOffset function that returns the value of the given entity's 
rectangular collider's center offset

\param const Entity &
A reference to a read-only Entity to get the center offset of

\return Math::Vec2
Value of the rectangular collider's center offset
*******************************************************************************/
Math::Vec2 Collision2DManager::GetRectCenterOffset(const Entity& _e) {
	return Collision2DManager::GetRectCollider(_e).centerOffset;
}

/*!*****************************************************************************
\brief
SetRectCenterOffset function that set the value of the given entity's rectangular
collider's center offset

\param const Entity &
A reference to a read-only Entity to set the center offset of

\param const Math::Vec2&
A reference to a read-only variable containing the center offset to set to

\return void
NULL
*******************************************************************************/
void Collision2DManager::SetRectCenterOffset(const Entity& _e, const Math::Vec2& _centerOffset) {
	Collision2DManager::GetRectCollider(_e).centerOffset = _centerOffset;
}

/*!*****************************************************************************
\brief
GetRectScaleOffset function that returns the value of the given entity's 
rectangular collider's scale offset

\param const Entity &
A reference to a read-only Entity to get the scale offset of

\return Math::Vec2
Value of the rectangular collider's scale offset
*******************************************************************************/
Math::Vec2 Collision2DManager::GetRectScaleOffset(const Entity& _e) {
	return Collision2DManager::GetRectCollider(_e).scaleOffset;
}

/*!*****************************************************************************
\brief
SetRectScaleOffset function that set the value of the given entity's rectangular
collider's scale offset

\param const Entity &
A reference to a read-only Entity to set the scale offset of

\param const Math::Vec2 &
A reference to a read-only variable containing the scale offset to set to

\return void
NULL
*******************************************************************************/
void Collision2DManager::SetRectScaleOffset(const Entity& _e, const Math::Vec2& _scaleOffset) {
	Collision2DManager::GetRectCollider(_e).scaleOffset = _scaleOffset;
}

/*!*****************************************************************************
\brief
GetRectRenderFlag function that returns the value of the given entity's 
rectangular collider's render flag

\param const Entity &
A reference to a read-only Entity to get the render flag of

\return bool
Value of the rectangular collider's render flag
*******************************************************************************/
bool Collision2DManager::GetRectRenderFlag(const Entity& _e) {
	return Collision2DManager::GetRectCollider(_e).renderFlag;
}

/*!*****************************************************************************
\brief
SetRectRenderFlag function that set the value of the given entity's rectangular
collider's render flag

\param const Entity &
A reference to a read-only Entity to set the render flag of

\param const bool &
A reference to a read-only variable containing the flag to set the render flag to

\return void
NULL
*******************************************************************************/
void Collision2DManager::SetRectRenderFlag(const Entity& _e, const bool& _renderFlag) {
	Collision2DManager::GetRectCollider(_e).renderFlag = _renderFlag;
}

/*!*****************************************************************************
\brief
GetEdgeCollider function that returns a reference to the given entity's edge/line
collider

\param const Entity &
A reference to a read-only Entity to get the edge/line collider of

\return CircleCollider&
A reference to the edge/line collider of the entity
*******************************************************************************/
Edge2DCollider& Collision2DManager::GetEdgeCollider(const Entity& _e) {
	return _e.GetComponent<Edge2DCollider>();
}

/*!*****************************************************************************
\brief
GetEdgeP0Offset function that returns the value of the given entity's edge/line
collider's point offset

\param const Entity &
A reference to a read-only Entity to get the center offset of

\return Math::Vec2
Value of the edge/line collider's point offset
*******************************************************************************/
Math::Vec2 Collision2DManager::GetEdgeP0Offset(const Entity& _e) {
	return Collision2DManager::GetEdgeCollider(_e).p0Offset;
}

/*!*****************************************************************************
\brief
SetEdgeP0Offset function that set the value of the given entity's edge/line
collider's point offset

\param const Entity &
A reference to a read-only Entity to set the point offset of

\param const Math::Vec2&
A reference to a read-only variable containing the point offset to set to

\return void
NULL
*******************************************************************************/
void Collision2DManager::SetEdgeP0Offset(const Entity& _e, const Math::Vec2& _centerOffset) {
	Collision2DManager::GetEdgeCollider(_e).p0Offset = _centerOffset;
}

/*!*****************************************************************************
\brief
GetEdgeScaleOffset function that returns the value of the given entity's
edge/line collider's scale offset

\param const Entity &
A reference to a read-only Entity to get the scale offset of

\return Math::Vec2
Value of the edge/line collider's scale offset
*******************************************************************************/
float Collision2DManager::GetEdgeScaleOffset(const Entity& _e) {
	return Collision2DManager::GetEdgeCollider(_e).scaleOffset;
}

/*!*****************************************************************************
\brief
SetEdgeScaleOffset function that set the value of the given entity's edge/line
collider's scale offset

\param const Entity &
A reference to a read-only Entity to set the scale offset of

\param const Math::Vec2 &
A reference to a read-only variable containing the scale offset to set to

\return void
NULL
*******************************************************************************/
void Collision2DManager::SetEdgeScaleOffset(const Entity& _e, const float& _scaleOffset) {
	Collision2DManager::GetEdgeCollider(_e).scaleOffset = _scaleOffset;
}

/*!*****************************************************************************
\brief
GetEdgeRotationOffset function that returns the value of the given entity's
edge/line collider's rotation offset

\param const Entity &
A reference to a read-only Entity to get the rotation offset of

\return Math::Vec2
Value of the edge/line collider's rotation offset
*******************************************************************************/
float Collision2DManager::GetEdgeRotationOffset(const Entity& _e) {
	return Collision2DManager::GetEdgeCollider(_e).rotationOffset;
}

/*!*****************************************************************************
\brief
SetEdgeRotationOffset function that set the value of the given entity's edge/line
collider's rotation offset

\param const Entity &
A reference to a read-only Entity to set the rotation offset of

\param const float &
A reference to a read-only variable containing the rotation offset to set to

\return void
NULL
*******************************************************************************/
void Collision2DManager::SetEdgeRotationOffset(const Entity& _e, const float& _rotationOffset) {
	Collision2DManager::GetEdgeCollider(_e).rotationOffset = _rotationOffset;
}

/*!*****************************************************************************
\brief
GetEdgeRenderFlag function that returns the value of the given entity's
edge/line collider's render flag

\param const Entity &
A reference to a read-only Entity to get the render flag of

\return bool
Value of the edge/line collider's render flag
*******************************************************************************/
bool Collision2DManager::GetEdgeRenderFlag(const Entity& _e) {
	return Collision2DManager::GetEdgeCollider(_e).renderFlag;
}

/*!*****************************************************************************
\brief
SetEdgeRenderFlag function that set the value of the given entity's edge/line
collider's render flag

\param const Entity &
A reference to a read-only Entity to set the render flag of

\param const bool &
A reference to a read-only variable containing the flag to set the render flag to

\return void
NULL
*******************************************************************************/
void Collision2DManager::SetEdgeRenderFlag(const Entity& _e, const bool& _renderFlag) {
	Collision2DManager::GetEdgeCollider(_e).renderFlag = _renderFlag;
}

/*!*****************************************************************************
\brief
GetPointCollider function that returns a reference to the given entity's point
collider

\param const Entity &
A reference to a read-only Entity to get the point collider of

\return RectCollider&
A reference to the point collider of the entity
*******************************************************************************/
Point2DCollider& Collision2DManager::GetPointCollider(const Entity& _e) {
	return _e.GetComponent<Point2DCollider>();
}

/*!*****************************************************************************
\brief
GetPointCenterOffset function that returns the value of the given entity's
point collider's center offset

\param const Entity &
A reference to a read-only Entity to get the center offset of

\return Math::Vec2
Value of the point collider's center offset
*******************************************************************************/
Math::Vec2 Collision2DManager::GetPointCenterOffset(const Entity& _e) {
	return Collision2DManager::GetPointCollider(_e).centerOffset;
}

/*!*****************************************************************************
\brief
SetPointCenterOffset function that set the value of the given entity's point
collider's center offset

\param const Entity &
A reference to a read-only Entity to set the center offset of

\param const Math::Vec2&
A reference to a read-only variable containing the center offset to set to

\return void
NULL
*******************************************************************************/
void Collision2DManager::SetPointCenterOffset(const Entity& _e, const Math::Vec2& _centerOffset) {
	Collision2DManager::GetPointCollider(_e).centerOffset = _centerOffset;
}

/*!*****************************************************************************
\brief
GetPointRenderFlag function that returns the value of the given entity's
point collider's render flag

\param const Entity &
A reference to a read-only Entity to get the render flag of

\return bool
Value of the point collider's render flag
*******************************************************************************/
bool Collision2DManager::GetPointRenderFlag(const Entity& _e) {
	return Collision2DManager::GetPointCollider(_e).renderFlag;
}

/*!*****************************************************************************
\brief
SetPointRenderFlag function that set the value of the given entity's point
collider's render flag

\param const Entity &
A reference to a read-only Entity to set the render flag of

\param const bool &
A reference to a read-only variable containing the flag to set the render flag to

\return void
NULL
*******************************************************************************/
void Collision2DManager::SetPointRenderFlag(const Entity& _e, const bool& _renderFlag) {
	Collision2DManager::GetPointCollider(_e).renderFlag = _renderFlag;
}

/*!*****************************************************************************
\brief
ExistsInCollisionList function that checks and returns the whether if the given
entity pair is already in the collision entity pair container list

\param const Entity &
A reference to a read-only variable containing the 1st entity of the entity pair

\param const Entity &
A reference to a read-only variable containing the 2nd entity of the entity pair

\return bool
Evaluated result of whether the entity pair exists in container
*******************************************************************************/
bool Collision2DManager::ExistsInCollisionList(const Entity& e1, const Entity& e2) {
	// Nothing in container, does not exists
	if (mCollisionCheckList.size() == 0)
		return false;

	// Loop through the list and check if the pair exists
	for (const CollisionStore& cs : mCollisionCheckList) {
		if ((cs.obj1.id == e1.id && cs.obj2.id == e2.id) ||
			(cs.obj1.id == e2.id && cs.obj2.id == e1.id))
			return true;
	}

	// Loop completed, entity pair was not found
	return false;
}

/*!*****************************************************************************
\brief
UpdateCollisionList function that clears and updates the system's stored container
holding the entity pairs that need to be checked for collision

\param void
NULL

\return void
NULL
*******************************************************************************/
void Collision2DManager::UpdateCollisionList() {
	// Clear list from previous frame
	Collision2DManager::ClearCollisionList();

	// Loop through list
	for (const Entity& e1 : mEntities) {
		for (const Entity& e2 : mEntities) {
			// If entity looped is itself or either entities do not contain a collider, skip it
			if (e1.id == e2.id || !Collision2DManager::HasCollider(e1) || !Collision2DManager::HasCollider(e2))
				continue;

			// Check if the entity pair has yet to exists in the list
			// If so, add it to the container
			if (!Collision2DManager::ExistsInCollisionList(e1, e2))
				mCollisionCheckList.emplace_back(CollisionStore{ 0, e1, e2 });
		}
	}
}

/*!*****************************************************************************
\brief
ClearCollisionList function that clears the system's stored container

\param void
NULL

\return void
NULL
*******************************************************************************/
void Collision2DManager::ClearCollisionList() {
	mCollisionCheckList.clear();
}

/*!*****************************************************************************
\brief
Update function that calls function to update the system's container and loops 
through it and calls function to check for collision between the entity pair. 
If collision is detected, the function then calls another function to resolve
collision

\param const double &
A reference to a read-only variable that tells us the application's current
delta time

\return void
NULL
*******************************************************************************/
void Collision2DManager::Update(const double &_dt) {
	// Update container of entity pairs
	Collision2DManager::UpdateCollisionList();

	// Loop through the entity pairs and check for collision
	for (CollisionStore& cs : Collision2DManager::mCollisionCheckList) {
		if (Collision2DManager::CheckCollision(cs, _dt)) {
			Collision2DManager::ResolveCollision(cs, _dt);
		}
	}
}

/*!*****************************************************************************
\brief
CheckCollision function that calls the respective collision detection function
depending on the collider type of the given entity pair and returns the result 
of that function as its result

\param CollisionStore &
A reference to struct containing entity pair data to check

\param const double &
A reference to a read-only variable that tells us the application's current
delta time

\return bool
Evaluated result of whether collision has occurred between the given entity pair
*******************************************************************************/
bool Collision2DManager::CheckCollision(CollisionStore& _collisionData, const double &_dt) {
	// Rect vs Rect
	if (_collisionData.obj1.HasComponent<RectCollider>() && _collisionData.obj2.HasComponent<RectCollider>()) {
		_collisionData.collisionType = 1;
		return Collision2DManager::CI_RectvsRect(_collisionData, _dt);
	}

	// Rect vs Circle
	if (_collisionData.obj1.HasComponent<RectCollider>() && _collisionData.obj2.HasComponent<CircleCollider>()) {
		//return CollisionIntersection_RectvsCircle(CollisionData.obj1, CollisionData.obj2) ? 2 : 0;
	}
	if (_collisionData.obj1.HasComponent<CircleCollider>() && _collisionData.obj2.HasComponent<RectCollider>()) {
		//return CollisionIntersection_RectvsCircle(CollisionData.obj2, CollisionData.obj1) ? 3 :0;
	}

	// Rect vs Line
	// result = 4;
	// result = 5


	// Circle vs Circle
	if (_collisionData.obj1.HasComponent<CircleCollider>() && _collisionData.obj2.HasComponent<CircleCollider>()) {
		_collisionData.collisionType = 6;
		return Collision2DManager::CI_CirclevsCircle(_collisionData, _dt);
	}

	// Circle vs Line
	// result = 7;
	// result = 8

	// Line vs Line
	// result = 9


	// result = 0;
	return false;
}

/*!*****************************************************************************
\brief
ResolvesCollision function that calls the respective collision resolution function
depending on the collider type of the given entity pair

\param CollisionStore &
A reference to struct containing entity pair data to resolve

\param const double &
A reference to a read-only variable that tells us the application's current
delta time

\return void
NULL
*******************************************************************************/
void Collision2DManager::ResolveCollision(CollisionStore& _collisionData, const double& _dt) {
	// Change function call based on the resultant collision type in the stored data
	switch (_collisionData.collisionType) {
	case 1:	// Rect vs Rect
		Collision2DManager::CR_RectvsRect(_collisionData, _dt);
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
		Collision2DManager::CR_CirclevsCircle(_collisionData, _dt);
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

	// Log collision detection & resolution
	LOG_INFO("Collision between object detected. Resolved!");

	// For demonstration, if the object has audio, play it
	if (_collisionData.obj1.HasComponent<Audio>()) {
		_collisionData.obj1.GetComponent<Audio>().sound.toPlay = true;
	}

	// For demonstration, if the object has audio, play it
	if (_collisionData.obj2.HasComponent<Audio>()) {
		_collisionData.obj2.GetComponent<Audio>().sound.toPlay = true;
	}
}

/*!*****************************************************************************
\brief
CI_RectvsRect function that checks for collision between 2 rectangular
colliders using AABB

\param CollisionStore &
A reference to struct containing entity pair data to check

\param const double &
A reference to a read-only variable that tells us the application's current
delta time

\return bool
Evaluated result of whether collision has occurred between the given entity pair
*******************************************************************************/
bool Collision2DManager::CI_RectvsRect(CollisionStore& _collisionData, const double& _dt) {
	// Store center and scale of both entities
	Math::Vec2 center1{ Math::Vec2{_collisionData.obj1.GetComponent<Transform>().translation} + _collisionData.obj1.GetComponent<RectCollider>().centerOffset },
			   scale1{ static_cast<float>(static_cast<double>(_collisionData.obj1.GetComponent<Transform>().scale.x) * static_cast<double>(_collisionData.obj1.GetComponent<RectCollider>().scaleOffset.x) / 2.0),
				       static_cast<float>(static_cast<double>(_collisionData.obj1.GetComponent<Transform>().scale.y) * static_cast<double>(_collisionData.obj1.GetComponent<RectCollider>().scaleOffset.y) / 2.0) },
			   center2{ Math::Vec2{_collisionData.obj2.GetComponent<Transform>().translation} + _collisionData.obj2.GetComponent<RectCollider>().centerOffset },
		       scale2{ static_cast<float>(static_cast<double>(_collisionData.obj2.GetComponent<Transform>().scale.x) * static_cast<double>(_collisionData.obj2.GetComponent<RectCollider>().scaleOffset.x) / 2.0),
				       static_cast<float>(static_cast<double>(_collisionData.obj2.GetComponent<Transform>().scale.y) * static_cast<double>(_collisionData.obj2.GetComponent<RectCollider>().scaleOffset.y) / 2.0) };

	// Compute min and max of both entities
	Math::Vec2 aabb1min{ center1 - scale1 },
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
	if (_collisionData.obj2.HasComponent<Physics2D>() && _collisionData.obj1.HasComponent<Physics2D>())
		Vb = _collisionData.obj2.GetComponent<Physics2D>().velocity* static_cast<float>(_dt) - _collisionData.obj1.GetComponent<Physics2D>().velocity * static_cast<float>(_dt);
	else if (_collisionData.obj1.HasComponent<Physics2D>()) 
		Vb = _collisionData.obj1.GetComponent<Physics2D>().velocity * static_cast<float>(_dt);
	else if (_collisionData.obj2.HasComponent<Physics2D>()) 
		Vb = _collisionData.obj2.GetComponent<Physics2D>().velocity * static_cast<float>(_dt);

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
	_collisionData.interTime = tFirst;

	return true;
}

/*!*****************************************************************************
\brief
CI_CirclevsCircle function that checks for collision between 2 circular colliders 

\param CollisionStore &
A reference to struct containing entity pair data to check

\param const double &
A reference to a read-only variable that tells us the application's current
delta time

\return bool
Evaluated result of whether collision has occurred between the given entity pair
*******************************************************************************/
bool Collision2DManager::CI_CirclevsCircle(CollisionStore& _collisionData, const double& _dt) {
	// Find the relative velocity of both circles
	Math::Vec2 relVel{};
	if (_collisionData.obj2.HasComponent<Physics2D>() && _collisionData.obj1.HasComponent<Physics2D>())
		relVel = _collisionData.obj1.GetComponent<Physics2D>().velocity * static_cast<float>(_dt) - _collisionData.obj2.GetComponent<Physics2D>().velocity * static_cast<float>(_dt);
	else if (_collisionData.obj1.HasComponent<Physics2D>())
		relVel = _collisionData.obj1.GetComponent<Physics2D>().velocity * static_cast<float>(_dt);
	else if (_collisionData.obj2.HasComponent<Physics2D>())
		relVel = _collisionData.obj2.GetComponent<Physics2D>().velocity * static_cast<float>(_dt);



	// Store radius of both circles
	double  circle1Radius{ (_collisionData.obj1.GetComponent<Transform>().scale.x * _collisionData.obj1.GetComponent<CircleCollider>().scaleOffset) / 2.0},
			circle2Radius{ (_collisionData.obj2.GetComponent<Transform>().scale.x * _collisionData.obj2.GetComponent<CircleCollider>().scaleOffset) / 2.0};

// Static
	// Check if relVel is 0
	if (relVel == Math::Vec2{ 0.f, 0.f }) {
		// Check if there is a distance between the 2 circles
		if (abs(
			Math::SqDistance(_collisionData.obj1.GetComponent<Transform>().translation + _collisionData.obj1.GetComponent<CircleCollider>().centerOffset, _collisionData.obj2.GetComponent<Transform>().translation + _collisionData.obj2.GetComponent<CircleCollider>().centerOffset) -
			static_cast<float>(circle1Radius * circle1Radius + circle2Radius * circle2Radius)
			) > 0.f)
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
	double  tmpCircleRadius{ static_cast<double>(tDataTmpCircle.scale.x) / 2.0 };

	// Create a ray that starts from first object's position and goes in the direction of the relative velocity
	Transform tDataTmpRay{ _collisionData.obj1.GetComponent<Transform>() };
	tDataTmpRay.translation += _collisionData.obj1.GetComponent<CircleCollider>().centerOffset;
	tDataTmpRay.rotation = static_cast<float>(acos(static_cast<double>(relVel.x) / static_cast<double>(relVel.Magnitude())));
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
	double n2{ static_cast<double>((tDataTmpCircle.translation - tDataTmpRay.translation).SqMagnitude()) - (m * m)};
	if (n2 > tmpCircleRadius * tmpCircleRadius)
		return false;	// Ray  will never hit the circle

	// Find intersection time and take minimum value
	double s{ sqrt(tmpCircleRadius * tmpCircleRadius - n2) };
	double tmpInterTime1{ (m - s) / relVel.Magnitude()},
		   tmpInterTime2{ (m + s) / relVel.Magnitude() };
	double interTime = (tmpInterTime1 < tmpInterTime2) ? tmpInterTime1 : tmpInterTime2;

	// Check if the intersection time is within 1 unit
	if (0.0 <= interTime && interTime <= 1.0) {
		_collisionData.interTime = interTime;
		return true;
	}
	else
		return false;
}

/*!*****************************************************************************
\brief
CR_RectvsRect function that resolves collision between 2 entities of
rectangular collider

\param CollisionStore &
A reference to struct containing entity pair data to resolve

\param const double &
A reference to a read-only variable that tells us the application's current
delta time

\return void
NULL
*******************************************************************************/
void Collision2DManager::CR_RectvsRect(CollisionStore& _collisionData, const double& _dt) {
	// Get and store objects' current velocity
	Math::Vec2 velObj1{ _collisionData.obj1.HasComponent<Physics2D>() ? _collisionData.obj1.GetComponent<Physics2D>().velocity * static_cast<float>(_dt) : Math::Vec2{0.f, 0.f} },
			   velObj2{ _collisionData.obj2.HasComponent<Physics2D>() ? _collisionData.obj2.GetComponent<Physics2D>().velocity * static_cast<float>(_dt) : Math::Vec2{0.f, 0.f} };
	//double massObj1{ static_cast<double>(_collisionData.obj1.GetComponent<Physics2D>().mass) },
	//	     massObj2{ static_cast<double>(_collisionData.obj2.GetComponent<Physics2D>().mass) };

	// Compute and store objects' meeting point
	Math::Vec2 interPtObj1{ _collisionData.obj1.GetComponent<Transform>().translation + _collisionData.obj1.GetComponent<RectCollider>().centerOffset + velObj1 * static_cast<float>(_collisionData.interTime) },
		       interPtObj2{ _collisionData.obj2.GetComponent<Transform>().translation + _collisionData.obj2.GetComponent<RectCollider>().centerOffset + velObj2 * static_cast<float>(_collisionData.interTime) };

	// Set the entities' position at the meeting point
	//_collisionData.obj1.GetComponent<Transform>().translation = interPtObj1 - _collisionData.obj1.GetComponent<CircleCollider>().centerOffset;
	//_collisionData.obj2.GetComponent<Transform>().translation = interPtObj2 - _collisionData.obj2.GetComponent<CircleCollider>().centerOffset;

	// Stop their movement for now as a hack until bounce/slide can be figured out
	_collisionData.obj1.GetComponent<Physics2D>().speed = 
	_collisionData.obj2.GetComponent<Physics2D>().speed = 0.f;

	_collisionData.obj1.GetComponent<Physics2D>().velocity = 
	_collisionData.obj2.GetComponent<Physics2D>().velocity = Math::Vec2{ 0.f, 0.f };
}

/*!*****************************************************************************
\brief
CR_CirclevsCircle function that resolves collision between 2 entities of
circle collider

\param CollisionStore &
A reference to struct containing entity pair data to resolve

\param const double &
A reference to a read-only variable that tells us the application's current
delta time

\return void
NULL
*******************************************************************************/
void Collision2DManager::CR_CirclevsCircle(CollisionStore& _collisionData, const double& _dt) {
	// Compute and store objects' current velocity
	Math::Vec2 velObj1{ _collisionData.obj1.HasComponent<Physics2D>() ? _collisionData.obj1.GetComponent<Physics2D>().velocity * static_cast<float>(_dt) : Math::Vec2{0.f, 0.f} },
				velObj2{ _collisionData.obj2.HasComponent<Physics2D>() ? _collisionData.obj2.GetComponent<Physics2D>().velocity * static_cast<float>(_dt) : Math::Vec2{0.f, 0.f} };
	double massObj1{ static_cast<double>(_collisionData.obj1.GetComponent<Physics2D>().mass) },
		   massObj2{ static_cast<double>(_collisionData.obj2.GetComponent<Physics2D>().mass) };

	// Compute and store objects' meeting point
	Math::Vec2 interPtObj1{ _collisionData.obj1.GetComponent<Transform>().translation + velObj1 * static_cast<float>(_collisionData.interTime)},
			   interPtObj2{ _collisionData.obj2.GetComponent<Transform>().translation + velObj2 * static_cast<float>(_collisionData.interTime) };

	// Get normal to collision occurance
	Math::Vec2 normal{ (interPtObj1 - interPtObj2).Normalized()};
	double aA{ Math::Dot(velObj1, normal) },
		   aB{ Math::Dot(velObj2, normal) };

	// Compute objects' reflected velocity after collision
	Math::Vec2 reflectedVelObj1{ velObj1 - static_cast<float>( ( (2.0 * (aA - aB)) / (massObj1 + massObj2) * massObj2) ) * normal },
		       reflectedVelObj2{ velObj2 + static_cast<float>( ( (2.0 * (aA - aB)) / (massObj1 + massObj2) * massObj1) ) * normal };

	// Store the reflected velocity as the new velocity
	_collisionData.obj1.GetComponent<Physics2D>().velocity = reflectedVelObj1;
	_collisionData.obj2.GetComponent<Physics2D>().velocity = reflectedVelObj2;

	// Compute objects' velocity direction after collision
	_collisionData.obj1.GetComponent<Physics2D>().moveDirection = static_cast<float>(acos(static_cast<double>(reflectedVelObj1.x) / static_cast<double>(reflectedVelObj1.Magnitude())));
	_collisionData.obj2.GetComponent<Physics2D>().moveDirection = static_cast<float>(acos(static_cast<double>(reflectedVelObj2.x) / static_cast<double>(reflectedVelObj2.Magnitude())));

	// Compute objects' position the frame after the collision
	_collisionData.obj1.GetComponent<Transform>().translation = interPtObj1 + reflectedVelObj1 * static_cast<float>(_dt - _collisionData.interTime);
	_collisionData.obj2.GetComponent<Transform>().translation = interPtObj2 + reflectedVelObj2 * static_cast<float>(_dt - _collisionData.interTime);
}
