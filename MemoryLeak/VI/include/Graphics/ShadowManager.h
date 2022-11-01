#pragma once
#include <ECS_systems.h>
#include "ECS_items.h"
#include "ECS_components.h"
#include <RenderManager.h>

class ShadowManager : public System
{
public:
	ShadowManager() {};
	void MakeShadows(const Entity& _lightsource, std::shared_ptr<RenderManager> _renderMgr);

private:
	float LineOfSightCheck(const Math::Vec2& p0, const Math::Vec2& p1, const Math::Vec2& p, const Math::Vec2& vtr, const Math::Vec2& normal);
	float PointLineSegDist(const Math::Vec2& p, const Math::Vec2& p0, const Math::Vec2& p1);
	Math::Vec2 RayCast(const Transform& xform);
	
};