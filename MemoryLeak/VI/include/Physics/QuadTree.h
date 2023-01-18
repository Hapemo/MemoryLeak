#pragma once

#include "pch.h"
#include "ECS_items.h"

const int MAX_OBJ_PER_NODE{ 5 };
const int MAX_SUBLEVELS{ 15 };

class QuadTree {
public:
	QuadTree(const int &_level = 0, const Math::Vec2 &_center = Math::Vec2{0.f, 0.f}, const Math::Vec2& _scale = Math::Vec2{0.f, 0.f});
	void UpdateQuadTreeSize(const Math::Vec2& _center, const Math::Vec2& _scale);
	void Clear();
	void DestroyTree();
	void Spilt();
	int GetQuadrant(const Entity& _e, const bool &_UseCollider = true);
	void Insert(const Entity& _e);
	void Retrieve(std::vector<Entity> &_returnList, const Entity& _e);
private:
	int mLevel;
	std::vector<Entity> mEntityList;
	Math::Vec2 mCenter;
	Math::Vec2 mScale;

	QuadTree* mLeaf[4];
};