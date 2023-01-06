/*!*****************************************************************************
\file ShadowManager.h
\author Kew Yu Jun
\par DP email: k.yujun\@digipen.edu
\par Group: Memory Leak Studios
\date 20-10-2022
\brief
This file contains a system to create shadows. As of now, shadows are defined 
as Sprites that are Squares. In the future, we will make a Shadow Component.
*******************************************************************************/
#pragma once
#include <ECS_systems.h>
#include "ECS_items.h"
#include "ECS_components.h"
#include <RenderManager.h>

/*!*****************************************************************************
\brief
ShadowManager Class that handles raycasting from entities with LightSource 
componenet onto entities with Shadow component (for now sprites with squares).
*******************************************************************************/
class ShadowManager : public System
{
public:
	ShadowManager() = default;
	/*!*****************************************************************************
	\brief
	Makes shadows based on the given Entity with lightsource, casting rays from the
	lightsource to all entities with Shadow component (for now sprites with squares).

	\param const Entity& _lightsource
	The lightsource to raycast from.

	\param std::shared_ptr<RenderManager> _renderMgr
	Sends the vertices of the raycast to the render manager.
	*******************************************************************************/
	void MakeShadows(const Entity& _lightsource, std::shared_ptr<RenderManager> _renderMgr);

private:
	/*!*****************************************************************************
	\brief
	Helper function for LOS check.

	\param const Math::Vec2& _p0
	First point of the line segment.

	\param const Math::Vec2& _p1
	Second point of the line segment.

	\param const Math::Vec2& _p
	Position of the light source.

	\param const Math::Vec2& _vtr
	The vector of the ray.

	\param const Math::Vec2& _normal
	The normal to the ray.

	\return 
	Return < 0 => in line of sight
	Return > 0 => not in line of sight
	*******************************************************************************/
	float LineOfSightCheck(const Math::Vec2& _p0, const Math::Vec2& _p1, const Math::Vec2& _p, const Math::Vec2& _vtr, const Math::Vec2& _normal);
	/*!*****************************************************************************
	\brief
	Finds the shortest distance of p to the line segment _p0 _p1.

	\param const Math::Vec2& _p
	The point to check its distance from the line segment.

	\param const Math::Vec2& _p0
	p0 of the line segment.

	\param const Math::Vec2& _p1
	p1 of the line segment.

	\return
	Returns the shortest distance of p to the line segment _p0 _p1.
	*******************************************************************************/
	float PointLineSegDist(const Math::Vec2& _p, const Math::Vec2& _p0, const Math::Vec2& _p1);
	/*!*****************************************************************************
	\brief
	Raycasts a single ray from the lightsource.

	\param const Transform& _xform
	The transform of the ray.

	\return
	Returns the point that the ray stopped at.
	*******************************************************************************/
	Math::Vec2 RayCast(const Transform& _xform);
	
};