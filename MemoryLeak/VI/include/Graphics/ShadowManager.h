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

bool CompareAngle(const Math::Vec2& endPt1, const Math::Vec2& endPt2);

float GetAngle(const Math::Vec2& p0);

struct Edge
{
	Math::Vec2 pos;
	Math::Vec2 dir;
};

/*!*****************************************************************************
\brief
ShadowManager Class that handles raycasting from entities with LightSource 
componenet onto entities with Shadow component (for now sprites with squares).
*******************************************************************************/
class ShadowManager : public System
{
public:
	ShadowManager();
	void Update();
	Math::Vec2 GetLightPos();
	bool CastShadows() { return mCastShadows; }
	const std::vector <Math::Vec2>& GetRayEndPoints() { return mRayEndPoints; }
private:
	Entity mLightsource;
	bool mCastShadows;
	std::vector <Edge> mObjectEdges;
	std::vector <Edge> mRayDirection;
	std::vector <Edge> mExtendedRayDirection;
	std::vector <Math::Vec2> mRayEndPoints;
	Transform mCamera;

	void RayCast();
	void CreateRays();
	void ClearVectors();
	void CreateFOVVertices();
	void CreateObjectVertices(Entity e);
};