/*!*****************************************************************************
\file ShadowManager.cpp
\author Kew Yu Jun
\par DP email: k.yujun\@digipen.edu
\par Group: Memory Leak Studios
\date 20-10-2022
\brief
This file contains a system to create shadows. As of now, shadows are defined
as Sprites that are Squares. In the future, we will make a Shadow Component.
*******************************************************************************/
#include <ShadowManager.h>
#include <Logger.h>
#include <ECSManager.h>

ShadowManager::ShadowManager() : lightsource(0) {}

void ShadowManager::Update()
{
	lightsource = renderManager->GetLightSource();
	if (!lightsource.id) return;

	for (Entity e : mEntities)
	{
		if (!e.ShouldRun()) continue;
		if (!e.HasComponent<ShadowCaster>()) continue;
		CreateObjectVertices(e);
	}
	CreateRays();
	RayCast();
}

void ShadowManager::RayCast()
{
	Math::Vec2 lightPos = lightsource.GetComponent<Transform>().translation
		+ lightsource.GetComponent<LightSource>().centerOffset;

	float T1, T2;
	float smallestT1{};

	for (const Math::Vec2& dir : rayDirection)
	{
		Edge ray{lightPos, dir};
		smallestT1 = 1.f;
		for (const Edge& segment : objectEdges)
		{
			T2 = (ray.dir.x * (segment.pos.y - ray.pos.y) + ray.dir.y * (ray.pos.x - segment.pos.x)) 
				/ (segment.dir.x * ray.dir.y - segment.dir.y * ray.dir.x);
			T1 = (segment.pos.x + segment.dir.x * T2 - ray.pos.x) / ray.dir.x;

			if (!(T1 > 0 && T2 > 0 && T2 < 1)) // no intersection
				continue;
			if (T1 > smallestT1) // intersection is further than the closest
				continue;
			smallestT1 = T1;
		}
		rayEndPoints.push_back(ray.pos + smallestT1 * ray.dir);
	}
	
	for (const Math::Vec2& pt : rayEndPoints)
		renderManager->CreateDebugPoint({ Math::Vec2(), 0.f, pt }, { 255, 255, 255, 255 });

	ClearVectors();
}

void ShadowManager::CreateRays()
{
	Math::Vec2 lightPos = lightsource.GetComponent<Transform>().translation
		+ lightsource.GetComponent<LightSource>().centerOffset;
	for (size_t i = 0; i < objectEdges.size(); ++i)
		rayDirection.push_back(objectEdges[i].pos - lightPos);
}

void ShadowManager::CreateObjectVertices(Entity e)
{
	Transform xform = e.GetComponent<Transform>();
	ShadowCaster caster = e.GetComponent<ShadowCaster>();
	xform.translation += caster.centerOffset;
	xform.scale.x *= caster.scaleOffset.x;
	xform.scale.y *= caster.scaleOffset.y;
	Math::Vec2 i{ xform.scale.x * 0.5f, 0 };
	Math::Vec2 j{ 0, xform.scale.y * 0.5f };

	objectEdges.push_back({ xform.translation + i + j, -2.f * i });
	objectEdges.push_back({ xform.translation - i + j, -2.f * j });
	objectEdges.push_back({ xform.translation - i - j, 2 * i });
	objectEdges.push_back({ xform.translation + i - j, 2 * j });
}

void ShadowManager::ClearVectors()
{
	objectEdges.clear();
	rayDirection.clear();
	rayEndPoints.clear();
}