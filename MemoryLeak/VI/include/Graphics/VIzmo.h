#pragma once
#include <ECS_systems.h>
#include "ECS_items.h"
#include "ECS_components.h"
#include "VIzmoProps.h"

enum class GIZMO_BUTTON { SCALE_X, SCALE_Y, ROTATE, TRANSLATE, NONE };

class VIzmo
{
public:
	VIzmo();
	void Attach(const Entity& _e);
	Entity GetAttached();
	void Detach();
	void Update(const Math::Vec2& _mouseCoordinates);
private:
	Entity mAttached;
	GIZMO_BUTTON mSelected;
	std::unordered_map<GIZMO_BUTTON, Math::Vec2> mButtonPos;
};