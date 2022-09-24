#pragma once
#include <glm/glm.hpp>
#include <ECS_systems.h>
#include "ECS_items.h"
#include "ECS_components.h"

class TransformManager : public System
{
public:
	void			SetScale		(const Entity& _e, const Math::Vec2& _scale);
	void			SetRotation		(const Entity& _e, float _rotation);
	void			SetTranslate	(const Entity& _e, const Math::Vec2& _translation);

	Math::Vec2		GetScale		(const Entity& _e)		{ return _e.GetComponent<Transform>().scale; }
	float			GetRotation		(const Entity& _e)		{ return _e.GetComponent<Transform>().rotation; }
	Math::Vec2		GetTranslate	(const Entity& _e)		{ return _e.GetComponent<Transform>().translation; }
};									 