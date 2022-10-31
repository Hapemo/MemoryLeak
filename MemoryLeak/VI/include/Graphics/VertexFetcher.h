#pragma once
#include <pch.h>
#include <ECS_systems.h>
#include "ECS_items.h"
#include "ECS_components.h"

class VertexFetcher
{
public:
	static std::vector<Math::Vec2> FetchVertices(const Entity& _e);

	template <typename T>
	static std::vector<Math::Vec2> FetchColliderVertices(const Entity& _e);

private:
	static void PrintDebug(const std::string& _missingComponent);
};

template <typename T>
std::vector<Math::Vec2> VertexFetcher::FetchColliderVertices(const Entity& _e)
{
	if (!_e.HasComponent<Transform>())
	{
		PrintDebug("Transform");
		return std::vector<Math::Vec2>();
	}
	if (!_e.HasComponent<T>())
	{
		PrintDebug("Templated");
		return std::vector<Math::Vec2>();
	}
	
	Transform xform = _e.GetComponent<Transform>();
	Math::Vec2 pos = xform.translation;

	if (typeid(T) == typeid(Point2DCollider))
		return { pos + _e.GetComponent<T>().centreOffset };
	if (typeid(T) == typeid(Edge2DCollider))
	{
		Math::Vec2 scale = xform.scale * _e.GetComponent<T>().scaleOffset;
		float rotation = xform.rotation + _e.GetComponent<T>().rotationOffset;
		pos += _e.GetComponent<T>().p0Offset;
		Math::Vec2 i(cosf(rotation) * scale.x * 0.5f, sinf(rotation) * scale.x * 0.5f);

		return { pos, pos + i };
	}
	if (typeid(T) == typeid(RectCollider))
	{
		Math::Vec2 scale(xform.scale.x * _e.GetComponent<T>().scaleOffset.x, 
			xform.scale.y * _e.GetComponent<T>().scaleOffset.y);
		pos += _e.GetComponent<T>().centreOffset;
		Math::Vec2 i(scale.x * 0.5f, 0), j(0, scale.y * 0.5f);
		return { pos + i + j, pos - i + j, pos - i - j, pos + i - j };
	}
	if (typeid(T) == typeid(CircleCollider))
	{
		return { pos + _e.GetComponent<T>().centreOffset };
	}
}