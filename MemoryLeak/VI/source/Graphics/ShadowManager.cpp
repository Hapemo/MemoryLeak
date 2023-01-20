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
#include <GameStateManager.h>

ShadowManager::ShadowManager() : mLightsource(0), mCastShadows(false) {}

void ShadowManager::Update()
{
	ClearVectors();

	mLightsource = renderManager->GetLightSource();

	if (!mLightsource.id)
	{
		mCastShadows = false;
		return;
	}
	if (!mLightsource.HasComponent<LightSource>()) return;

	mCastShadows = true;

	mCamera = GameStateManager::GetInstance()->mCurrentGameState->mCamera;

	CreateCameraVertices();

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
	Math::Vec2 lightPos = mLightsource.GetComponent<Transform>().translation
		+ mLightsource.GetComponent<LightSource>().centerOffset;

	float T1, T2;
	float smallestT1{};
	bool foundIntersection;

	for (const Edge& ray : mRayDirection)
	{
		smallestT1 = 1.f;
		foundIntersection = false;
		for (const Edge& segment : mObjectEdges)
		{
			T2 = (ray.dir.x * (segment.pos.y - ray.pos.y) + ray.dir.y * (ray.pos.x - segment.pos.x)) 
				/ (segment.dir.x * ray.dir.y - segment.dir.y * ray.dir.x);
			T1 = (segment.pos.x + segment.dir.x * T2 - ray.pos.x) / ray.dir.x;

			if (!(T1 > 0 && T2 > 0 && T2 < 1)) // no intersection
				continue;
			if (T1 >= smallestT1) // intersection is further than the closest
				continue;
			foundIntersection = true;
			smallestT1 = T1;
		}
		mRayEndPoints.push_back(ray.pos + smallestT1 * ray.dir);

		if (!foundIntersection) // intersection is at a point
		{
			float theta = 0.00001f;
			Math::Vec2 posDir{ ray.dir.x * cosf(theta) - ray.dir.y * sinf(theta), ray.dir.x * sinf(theta) + ray.dir.y * cosf(theta) };
			Math::Vec2 negDir{ ray.dir.x * cosf(-theta) - ray.dir.y * sinf(-theta), ray.dir.x * sinf(-theta) + ray.dir.y * cosf(-theta) };
			mExtendedRayDirection.push_back({ ray.pos, posDir });
			mExtendedRayDirection.push_back({ ray.pos, negDir });
		}
	}
	//sort!!!!
	//sort!!!!
	//sort!!!!
	//sort!!!!
	//sort!!!!
	//sort!!!!
	//sort!!!!
	//sort!!!!

	for (const Edge& ray : mExtendedRayDirection)
	{
		smallestT1 = std::numeric_limits<float>::max();
		for (const Edge& segment : mObjectEdges)
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
		mRayEndPoints.push_back(ray.pos + smallestT1 * ray.dir);
	}
}

void ShadowManager::CreateRays()
{
	Math::Vec2 lightPos = mLightsource.GetComponent<Transform>().translation
		+ mLightsource.GetComponent<LightSource>().centerOffset;

	Math::Vec2 i{ mCamera.scale.x / 2.f, 0 };
	Math::Vec2 j{ 0, mCamera.scale.y / 2.f };
	
	for (size_t k = 0; k < mObjectEdges.size(); ++k)
		mRayDirection.push_back({ lightPos, mObjectEdges[k].pos - lightPos });
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

	mObjectEdges.push_back({ xform.translation + i + j, -2.f * i });
	mObjectEdges.push_back({ xform.translation - i + j, -2.f * j });
	mObjectEdges.push_back({ xform.translation - i - j, 2 * i });
	mObjectEdges.push_back({ xform.translation + i - j, 2 * j });
}

void ShadowManager::ClearVectors()
{
	mObjectEdges.clear();
	mRayDirection.clear();
	mExtendedRayDirection.clear();
	mRayEndPoints.clear();
}

void ShadowManager::CreateCameraVertices()
{
	Math::Vec2 i{ mCamera.scale.x / 2.f, 0 };
	Math::Vec2 j{ 0, mCamera.scale.y / 2.f };
	mObjectEdges.push_back({ mCamera.translation + i + j, -2.f * i });
	mObjectEdges.push_back({ mCamera.translation - i + j, -2.f * j });
	mObjectEdges.push_back({ mCamera.translation - i - j, 2 * i });
	mObjectEdges.push_back({ mCamera.translation + i - j, 2 * j });
}
