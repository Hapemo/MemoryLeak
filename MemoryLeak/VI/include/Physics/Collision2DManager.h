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

// ----------------------------------------
// CollisionStore struct
// ----------------------------------------
struct CollisionStore {
	int collisionType;	// Type of collision detected

	// Entity pair
	const Entity obj1,	// Entity object 1
				 obj2;	// Entity object 2	

	double interTime;	// Intersection time
};

// ----------------------------------------
// Collision Detection / Resolution System
// ----------------------------------------
class Collision2DManager : public System {
public:
// -----------------------------
// System functions
// -----------------------------
	/*!*****************************************************************************
	\brief
	Update function that calls function to update the system's container and loops
	through it and calls function to check for collision between the entity pair.
	If collision is detected, the function then calls another function to resolve
	collision

	\param const std::set<Entity> &
	A reference to a read-only container holding the list of entities to check against

	\return void
	NULL
	*******************************************************************************/
	void Update(const std::set<Entity>& _entityList);

// -----------------------------
// System object list functions
// -----------------------------
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
	bool ExistsInCollisionList(const Entity& _e1, const Entity& _e2);

	/*!*****************************************************************************
	\brief
	UpdateCollisionList function that clears and updates the system's stored container
	holding the entity pairs that need to be checked for collision

	\param const std::set<Entity> &
	A reference to a read-only container holding the list of entities to check against

	\return void
	NULL
	*******************************************************************************/
	void UpdateCollisionList(const std::set<Entity>& _entityList);

	/*!*****************************************************************************
	\brief
	ClearCollisionList function that clears the system's stored container

	\param void
	NULL

	\return void
	NULL
	*******************************************************************************/
	void ClearCollisionList();

// -----------------------------
// Component-related functions
// -----------------------------
	/*!*****************************************************************************
	\brief
	HasCollider function that checks if the given entity contains a collider

	\param const Entity &
	A reference to a read-only Entity to add collider to

	\return bool
	Evaluated result of whether the entity has a collider
	*******************************************************************************/
	bool HasCollider(const Entity& e);

// Add component
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
	void AddRectColliderComponent(const Entity& _e, const Math::Vec2& _centerOffset = Math::Vec2{ 0.f, 0.f }, const Math::Vec2& _scaleOffset = Math::Vec2{ 1.f, 1.f }, const bool& _renderFlag = false);

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
	void AddCircleColliderComponent(const Entity& _e, const Math::Vec2& _centerOffset = Math::Vec2{ 0.f, 0.f }, const float& _radiusOffset = 1.f, const bool& _renderFlag = false);
	
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
	void AddEdgeColliderComponent(const Entity& _e, const Math::Vec2& _p0Offset = Math::Vec2{ 0.f, 0.f }, const float& _rotationOffset = 0.f, const float& _scaleOffset = 0.f, const bool& _renderFlag = false);
	
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
	void AddPointColliderComponent(const Entity& _e, const Math::Vec2& _centerOffset = Math::Vec2{ 0.f, 0.f }, const bool& _renderFlag = false);

// Remove component
	/*!*****************************************************************************
	\brief
	RemoveRectColliderComponent function that removes rectangular collider of the
	given entity

	\param const Entity &
	A reference to a read-only Entity to remove collider from

	\return void
	NULL
	*******************************************************************************/
	void RemoveRectColliderComponent(const Entity& _e);
	
	/*!*****************************************************************************
	\brief
	RemoveCircleColliderComponent function that removes circle collider of the
	given entity

	\param const Entity &
	A reference to a read-only Entity to remove collider from

	\return void
	NULL
	*******************************************************************************/
	void RemoveCircleColliderComponent(const Entity& _e);

	/*!*****************************************************************************
	\brief
	RemoveEdgeColliderComponent function that removes edge collider of the
	given entity

	\param const Entity &
	A reference to a read-only Entity to remove collider from

	\return void
	NULL
	*******************************************************************************/
	void RemoveEdgeColliderComponent(const Entity& _e);

	/*!*****************************************************************************
	\brief
	RemovePointColliderComponent function that removes point collider of the
	given entity

	\param const Entity &
	A reference to a read-only Entity to remove collider from

	\return void
	NULL
	*******************************************************************************/
	void RemovePointColliderComponent(const Entity& _e);

// -----------------------------
// Get / Set functions
// -----------------------------
// Circle
	/*!*****************************************************************************
	\brief
	GetCircleCollider function that returns a reference to the given entity's circle
	collider

	\param const Entity &
	A reference to a read-only Entity to get the circle collider of

	\return CircleCollider&
	A reference to the circle collider of the entity
	*******************************************************************************/
	CircleCollider& GetCircleCollider(const Entity& _e);

	/*!*****************************************************************************
	\brief
	GetCircleCenterOffset function that returns the value of the given entity's circle
	collider's center offset

	\param const Entity &
	A reference to a read-only Entity to get the center offset of

	\return Math::Vec2
	Value of the circle collider's center offset
	*******************************************************************************/
	Math::Vec2 GetCircleCenterOffset(const Entity& _e);

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
	void SetCircleCenterOffset(const Entity& _e, const Math::Vec2& _centerOffset);

	/*!*****************************************************************************
	\brief
	GetCircleRadiusOffset function that returns the value of the given entity's circle
	collider's radius offset

	\param const Entity &
	A reference to a read-only Entity to get the radius offset of

	\return float
	Value of the circle collider's radius offset
	*******************************************************************************/
	float GetCircleRadiusOffset(const Entity& _e);

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
	void SetCircleRadiusOffset(const Entity& _e, const float& _radiusOffset);

	/*!*****************************************************************************
	\brief
	GetCircleRenderFlag function that returns the value of the given entity's circle
	collider's render flag

	\param const Entity &
	A reference to a read-only Entity to get the render flag of

	\return bool
	Value of the circle collider's render flag
	*******************************************************************************/
	bool GetCircleRenderFlag(const Entity& _e);

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
	void SetCircleRenderFlag(const Entity& _e, const bool& _renderFlag);

// Rect
	/*!*****************************************************************************
	\brief
	GetRectCollider function that returns a reference to the given entity's rectangular
	collider

	\param const Entity &
	A reference to a read-only Entity to get the rectangular collider of

	\return RectCollider&
	A reference to the rectangular collider of the entity
	*******************************************************************************/
	RectCollider& GetRectCollider(const Entity& _e);

	/*!*****************************************************************************
	\brief
	GetRectCenterOffset function that returns the value of the given entity's
	rectangular collider's center offset

	\param const Entity &
	A reference to a read-only Entity to get the center offset of

	\return Math::Vec2
	Value of the rectangular collider's center offset
	*******************************************************************************/
	Math::Vec2 GetRectCenterOffset(const Entity& _e);

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
	void SetRectCenterOffset(const Entity& _e, const Math::Vec2& _centerOffset);

	/*!*****************************************************************************
	\brief
	GetRectScaleOffset function that returns the value of the given entity's
	rectangular collider's scale offset

	\param const Entity &
	A reference to a read-only Entity to get the scale offset of

	\return Math::Vec2
	Value of the rectangular collider's scale offset
	*******************************************************************************/
	Math::Vec2 GetRectScaleOffset(const Entity& _e);

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
	void SetRectScaleOffset(const Entity& _e, const Math::Vec2& _scaleOffset);

	/*!*****************************************************************************
	\brief
	GetRectRenderFlag function that returns the value of the given entity's
	rectangular collider's render flag

	\param const Entity &
	A reference to a read-only Entity to get the render flag of

	\return bool
	Value of the rectangular collider's render flag
	*******************************************************************************/
	bool GetRectRenderFlag(const Entity& _e);

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
	void SetRectRenderFlag(const Entity& _e, const bool& _renderFlag);

// Edge
	/*!*****************************************************************************
	\brief
	GetEdgeCollider function that returns a reference to the given entity's edge/line
	collider

	\param const Entity &
	A reference to a read-only Entity to get the edge/line collider of

	\return CircleCollider&
	A reference to the edge/line collider of the entity
	*******************************************************************************/
	Edge2DCollider& GetEdgeCollider(const Entity& _e);

	/*!*****************************************************************************
	\brief
	GetEdgeP0Offset function that returns the value of the given entity's edge/line
	collider's point offset

	\param const Entity &
	A reference to a read-only Entity to get the center offset of

	\return Math::Vec2
	Value of the edge/line collider's point offset
	*******************************************************************************/
	Math::Vec2 GetEdgeP0Offset(const Entity& _e);

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
	void SetEdgeP0Offset(const Entity& _e, const Math::Vec2& _p0Offset);

	/*!*****************************************************************************
	\brief
	GetEdgeScaleOffset function that returns the value of the given entity's
	edge/line collider's scale offset

	\param const Entity &
	A reference to a read-only Entity to get the scale offset of

	\return Math::Vec2
	Value of the edge/line collider's scale offset
	*******************************************************************************/
	float GetEdgeScaleOffset(const Entity& _e);

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
	void SetEdgeScaleOffset(const Entity& _e, const float& _scaleOffset);

	/*!*****************************************************************************
	\brief
	GetEdgeRotationOffset function that returns the value of the given entity's
	edge/line collider's rotation offset

	\param const Entity &
	A reference to a read-only Entity to get the rotation offset of

	\return Math::Vec2
	Value of the edge/line collider's rotation offset
	*******************************************************************************/
	float GetEdgeRotationOffset(const Entity& _e);

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
	void SetEdgeRotationOffset(const Entity& _e, const float& _rotationOffset);

	/*!*****************************************************************************
	\brief
	GetEdgeRenderFlag function that returns the value of the given entity's
	edge/line collider's render flag

	\param const Entity &
	A reference to a read-only Entity to get the render flag of

	\return bool
	Value of the edge/line collider's render flag
	*******************************************************************************/
	bool GetEdgeRenderFlag(const Entity& _e);

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
	void SetEdgeRenderFlag(const Entity& _e, const bool& _renderFlag);

// Point
	/*!*****************************************************************************
	\brief
	GetPointCollider function that returns a reference to the given entity's point
	collider

	\param const Entity &
	A reference to a read-only Entity to get the point collider of

	\return RectCollider&
	A reference to the point collider of the entity
	*******************************************************************************/
	Point2DCollider& GetPointCollider(const Entity& _e);

	/*!*****************************************************************************
	\brief
	GetPointCenterOffset function that returns the value of the given entity's
	point collider's center offset

	\param const Entity &
	A reference to a read-only Entity to get the center offset of

	\return Math::Vec2
	Value of the point collider's center offset
	*******************************************************************************/
	Math::Vec2 GetPointCenterOffset(const Entity& _e);

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
	void SetPointCenterOffset(const Entity& _e, const Math::Vec2& _centerOffset);

	/*!*****************************************************************************
	\brief
	GetPointRenderFlag function that returns the value of the given entity's
	point collider's render flag

	\param const Entity &
	A reference to a read-only Entity to get the render flag of

	\return bool
	Value of the point collider's render flag
	*******************************************************************************/
	bool GetPointRenderFlag(const Entity& _e);

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
	void SetPointRenderFlag(const Entity& _e, const bool& _renderFlag);

	// Collision Checks / Response functions
// -----------------------------
// Collision Checks / Response functions
// -----------------------------
	/*!*****************************************************************************
	\brief
	CheckCollision function that calls the respective collision detection function
	depending on the collider type of the given entity pair and returns the result
	of that function as its result

	\param CollisionStore &
	A reference to struct containing entity pair data to check

	\return bool
	Evaluated result of whether collision has occurred between the given entity pair
	*******************************************************************************/
	bool CheckCollision(CollisionStore& _collisionData);

	/*!*****************************************************************************
	\brief
	ResolvesCollision function that calls the respective collision resolution function
	depending on the collider type of the given entity pair

	\param CollisionStore &
	A reference to struct containing entity pair data to resolve

	\return void
	NULL
	*******************************************************************************/
	void ResolveCollision(CollisionStore& _collisionData);

	/*!*****************************************************************************
	\brief
	CI_RectvsRect function that checks for collision between 2 rectangular
	colliders using AABB

	\param CollisionStore &
	A reference to struct containing entity pair data to check

	\return bool
	Evaluated result of whether collision has occurred between the given entity pair
	*******************************************************************************/
	bool CI_RectvsRect(CollisionStore& _collisionData);

	/*!*****************************************************************************
	\brief
	CI_CirclevsCircle function that checks for collision between 2 circular colliders

	\param CollisionStore &
	A reference to struct containing entity pair data to check

	\return bool
	Evaluated result of whether collision has occurred between the given entity pair
	*******************************************************************************/
	bool CI_CirclevsCircle(CollisionStore& _collisionData);
	/*bool CI_RayvsStaticCircle(const Transform &tDataRay,
							  const Transform &tDataCircle, const CircleCollider &cDataCircle);*/
	//bool CI_RectvsCircle(CollisionStore &_collisionData);

	/*!*****************************************************************************
	\brief
	CR_RectvsRect function that resolves collision between 2 entities of
	rectangular collider

	\param CollisionStore &
	A reference to struct containing entity pair data to resolve

	\return void
	NULL
	*******************************************************************************/
	void CR_RectvsRect(CollisionStore& _collisionData);

	/*!*****************************************************************************
	\brief
	CR_CirclevsCircle function that resolves collision between 2 entities of
	circle collider

	\param CollisionStore &
	A reference to struct containing entity pair data to resolve

	\return void
	NULL
	*******************************************************************************/
	void CR_CirclevsCircle(CollisionStore& _collisionData);
	//void CR_RectvsCircle(CollisionStore &_collisionData);

private:
	std::vector<CollisionStore> mCollisionCheckList;	// Entity pair collision list
};
