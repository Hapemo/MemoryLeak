#pragma once

enum class ColliderType : int {
	RECT = 1,
	CIRCLE,
	MAXTYPESOFCOLLIDERS
};

//class ColliderBody {
//public:
//	ColliderBody(ColliderType _typeID) : typeID{_typeID} {}
//	virtual ~ColliderBody() {}
//
//	ColliderType typeID;
//
//};

//class RectCollider : ColliderBody {
//public:
//	RectCollider(ColliderType _typeID) : typeID(_typeID) {};
//	~RectCollider() override {};
//
//	Math::Vec2 centerOffset;
//	Math::Vec2 scaleOffset;
//};
//
//class CircleCollider : ColliderBody {
//public:
//	CircleCollider(ColliderType _typeID) : ColliderBody(_typeID) {};
//	~CircleCollider() override {};
//
//	Math::Vec2 centerOffset;
//	float scaleOffset;
//};
