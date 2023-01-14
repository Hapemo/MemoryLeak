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

private:
	Entity lightsource;
	std::vector <Edge> objectEdges;
	std::vector <Math::Vec2> rayDirection;
	std::vector <Math::Vec2> rayEndPoints;

	void RayCast();
	void CreateRays();
	void ClearVectors();
	void CreateObjectVertices(Entity e);
};