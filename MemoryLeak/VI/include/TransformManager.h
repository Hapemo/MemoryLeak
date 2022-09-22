#pragma once
#include <glm/glm.hpp>
#include <ECS_systems.h>
#include "ECS_items.h"
#include "ECS_components.h"

class TransformManager : public System
{
public:
	void			SetScale		(const Entity& e, const glm::vec2& scale);
	void			SetRotation		(const Entity& e, float rotation);
	void			SetTranslate	(const Entity& e, const glm::vec2& translation);

	glm::vec2		GetScale		(const Entity& e)		{ return e.GetComponent<Transform>().scale; }
	float			GetRotation		(const Entity& e)		{ return e.GetComponent<Transform>().rotation; }
	glm::vec2		GetTranslate	(const Entity& e)		{ return e.GetComponent<Transform>().translation; }
};									 