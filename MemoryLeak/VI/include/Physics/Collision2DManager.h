#pragma once

#include "ECS_systems.h"

struct CollisionStore {
	int collisionType;

	const Entity obj1,
		obj2;

	double interTime;
};

class Collision2DManager : public System {
public:
	// Manager functions
		//void Init();
	bool ExistsInCollisionList(const Entity& _e1, const Entity& _e2);
	void UpdateCollisionList();
	void UpdateCollisionList(const std::set<Entity>& _entityList);
	void Update();
	void Update(const std::set<Entity>& _entityList);


	// Add / Remove Component
	void AddRectColliderComponent(const Entity& _e, const glm::vec2& _centerOffset = glm::vec2{ 0.f, 0.f }, const glm::vec2& _scaleOffset = glm::vec2{ 1.f, 1.f }, const bool& _renderFlag = false);
	void AddCircleColliderComponent(const Entity& _e, const glm::vec2& _centerOffset = glm::vec2{ 0.f, 0.f }, const float& _radiusOffset = 1.f, const bool& _renderFlag = false);
	void AddEdgeColliderComponent(const Entity& _e, const glm::vec2& _p0Offset = glm::vec2{ 0.f, 0.f }, const float& _rotationOffset = 0.f, const float& _scaleOffset = 0.f, const bool& _renderFlag = false);

	// void RemoveRectColliderComponent(const Entity &);
	// void RemoveCircleColliderComponent(const Entity &);
	// void RemoveEdgeColliderComponent(const Entity &);

// Collider Get / Set
	bool HasCollider(const Entity& e);

	// Circle
	CircleCollider& GetCircleCollider(const Entity& _e);
	glm::vec2 GetCircleCenterOffset(const Entity& _e);
	void SetCircleCenterOffset(const Entity& _e, const glm::vec2& _centerOffset);
	float GetCircleRadiusOffset(const Entity& _e);
	void SetCircleRadiusOffset(const Entity& _e, const float& _radiusOffset);
	bool GetCircleRenderFlag(const Entity& _e);
	void SetCircleRenderFlag(const Entity& _e, const bool& _renderFlag);

	// Rect
	RectCollider& GetRectCollider(const Entity& _e);
	glm::vec2 GetRectCenterOffset(const Entity& _e);
	void SetRectCenterOffset(const Entity& _e, const glm::vec2& _centerOffset);
	glm::vec2 GetRectScaleOffset(const Entity& _e);
	void SetRectScaleOffset(const Entity& _e, const glm::vec2& _scaleOffset);
	bool GetRectRenderFlag(const Entity& _e);
	void SetRectRenderFlag(const Entity& _e, const bool& _renderFlag);

	// Edge
	Edge2DCollider& GetEdgeCollider(const Entity& _e);
	glm::vec2 GetEdgeP0Offset(const Entity& _e);
	void SetEdgeP0Offset(const Entity& _e, const glm::vec2& _p0Offset);
	float GetEdgeScaleOffset(const Entity& _e);
	void SetEdgeScaleOffset(const Entity& _e, const float& _scaleOffset);
	float GetEdgeRotationOffset(const Entity& _e);
	void SetEdgeRotationOffset(const Entity& _e, const float& _rotationOffset);
	bool GetEdgeRenderFlag(const Entity& _e);
	void SetEdgeRenderFlag(const Entity& _e, const bool& _renderFlag);

	// Collision Checks / Response functions

		// May need to change
		// {
		//template<typename T>
		//T GetCollider(const Entity &e);

		//glm::vec2 GetColliderCenterOffset(const Entity &e);
		//void SetColliderCenterOffset(const Entity &e, const glm::vec2 &_centerOffset);

		//template<typename T>
		//T GetColliderScaleOffset(const Entity &e);
		//bool SetColliderScaleOffset(const Entity &e, const float &_scaleOffset);
		//bool SetColliderScaleOffset(const Entity &e, const glm::vec2 &_scaleOffset);

		//bool GetColliderRenderFlag(const Entity &e);
		//void SetColliderRenderFlag(const Entity &e, const bool &_renderFlag);
		// }

	bool CheckCollision(CollisionStore& _collisionData);
	void ResolveCollision(CollisionStore& _collisionData);

	bool CI_RectvsRect(CollisionStore& _collisionData);
	bool CI_CirclevsCircle(CollisionStore& _collisionData);
	/*bool CI_RayvsStaticCircle(const Transform &tDataRay,
							  const Transform &tDataCircle, const CircleCollider &cDataCircle);*/
							  //bool CI_RectvsCircle(CollisionStore &_collisionData);

	void CR_RectvsRect(CollisionStore& _collisionData);
	void CR_CirclevsCircle(CollisionStore& _collisionData);
	//void CR_RectvsCircle(CollisionStore &_collisionData);

private:
	std::vector<CollisionStore> mCollisionCheckList;
};
