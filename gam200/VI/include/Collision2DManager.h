#pragma once

#include "ECS_systems.h"

struct CollisionStore {

};

struct AABB {
	glm::vec2 min,
			  max;
};

class Collision2DManager : public System {
public:
// Manager functions
//	void Init();
//	void UpdateCollisionList();
//
//// Add / Remove Component
//	void AddRectColliderComponent(const Entity& e, const glm::vec2& _centerOffset = glm::vec2{ 0.f, 0.f }, const glm::vec2& _scaleOffset = glm::vec2{ 1.f, 1.f }, const bool& _renderFlag = false);
//	void AddCircleColliderComponent(const Entity& e, const glm::vec2& _centerOffset = glm::vec2{ 0.f, 0.f }, const float& _radiusOffset = 1.f, const bool& _renderFlag = false);
//	void AddEdgeColliderComponent(const Entity& e, const glm::vec2& _p0Offset = glm::vec2{ 0.f, 0.f }, const float& _rotationOffset = 0.f, const float& _scaleOffset = 0.f, const bool& _renderFlag = false);
//
//	// void RemoveRectCollider(const Entity &);
//	// void RemoveCircleCollider(const Entity &);
//
//
//// Collider Get / Set
//	bool HasCollider(const Entity& e);
//
//	// Circle
//	CircleCollider& GetCircleCollider(const Entity& e);
//	glm::vec2 GetCircleCenterOffset(const Entity& e);
//	void SetCircleCenterOffset(const Entity& e, const glm::vec2& _centerOffset);
//	float GetCircleRadiusOffset(const Entity& e);
//	void SetCircleRadiusOffset(const Entity& e, const float& _radiusOffset);
//	bool GetCircleRenderFlag(const Entity& e);
//	void SetCircleRenderFlag(const Entity& e, const bool& _renderFlag);
//
//	// Rect
//	RectCollider& GetRectCollider(const Entity& e);
//	glm::vec2 GetRectCenterOffset(const Entity& e);
//	void SetRectCenterOffset(const Entity& e, const glm::vec2& _centerOffset);
//	glm::vec2 GetRectScaleOffset(const Entity& e);
//	void SetRectScaleOffset(const Entity& e, const glm::vec2& _scaleOffset);
//	bool GetRectRenderFlag(const Entity& e);
//	void SetRectRenderFlag(const Entity& e, const bool& _renderFlag);
//
//	// Edge
//	Edge2DCollider& GetEdgeCollider(const Entity& e);
//	glm::vec2 GetEdgeP0Offset(const Entity& e);
//	void SetEdgeP0Offset(const Entity& e, const glm::vec2& _p0Offset);
//	float GetEdgeScaleOffset(const Entity& e);
//	void SetEdgeScaleOffset(const Entity& e, const float& _scaleOffset);
//	float GetEdgeRotationOffset(const Entity& e);
//	void SetEdgeRotationOffset(const Entity& e, const float& _rotationOffset);
//	bool GetEdgeRenderFlag(const Entity& e);
//	void SetEdgeRenderFlag(const Entity& e, const bool& _renderFlag);
//
//// Collision Checks / Response functions
//	
//	// May need to change
//	// {
//	//template<typename T>
//	//T GetCollider(const Entity &e);
//
//	//glm::vec2 GetColliderCenterOffset(const Entity &e);
//	//void SetColliderCenterOffset(const Entity &e, const glm::vec2 &_centerOffset);
//
//	//template<typename T>
//	//T GetColliderScaleOffset(const Entity &e);
//	//bool SetColliderScaleOffset(const Entity &e, const float &_scaleOffset);
//	//bool SetColliderScaleOffset(const Entity &e, const glm::vec2 &_scaleOffset);
//
//	//bool GetColliderRenderFlag(const Entity &e);
//	//void SetColliderRenderFlag(const Entity &e, const bool &_renderFlag);
//	// }
//
//	int CheckCollision(const Entity& obj1, const Entity& obj2);
//	void CollisionResponse(const Entity&, const Entity&, const int&);
//
//	bool CI_RectvsRect(const Transform& tData1, const Physics2D& pData1, const RectCollider& cData1,
//		const Transform& tData2, const Physics2D& pData2, const RectCollider& cData2);
//	bool CI_CirclevsCircle(const Transform& tData1, const Physics2D& pData1, const CircleCollider& cData1,
//		const Transform& tData2, const Physics2D& pData2, const CircleCollider& cData2);
//	bool CI_RayvsStaticCircle(const Transform& tDataRay,
//		const Transform& tDataCircle, const CircleCollider& cDataCircle);

private:
	
};
