#pragma once

class ColliderBody {
public:
	ColliderBody(){}
	virtual ~ColliderBody() {}


};

class RectCollider : ColliderBody {
public:
	~RectCollider() override {}

	Math::Vec2 centerOffset;
	Math::Vec2 scaleOffset;
};

class CircleCollider : ColliderBody {
public:
	~CircleCollider() override {}

	Math::Vec2 centerOffset;
	float scaleOffset;
};
