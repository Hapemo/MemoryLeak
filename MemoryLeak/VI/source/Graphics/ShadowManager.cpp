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
#include <RenderProps.h>

ShadowManager::ShadowManager() : mCastShadows(false) {}

void ShadowManager::Update()
{
	ClearVectors();

	mLightsources = renderManager->GetLightSource();

	if (mLightsources.empty())
	{
		mCastShadows = false;
		return;
	}

	mCastShadows = true;

	for (Entity lightsource : mLightsources)
	{
		mCurrEntity = lightsource;
		CreateFOVVertices();

		for (Entity e : mEntities)
		{
			if (!e.ShouldRun()) continue;
			if (!e.HasComponent<ShadowCaster>()) continue;
			CreateObjectVertices(e);
		}
		CreateRays();
		RayCast();
		mObjectEdges.clear();
		mRayDirection.clear();
		mExtendedRayDirection.clear();
	}
}

void ShadowManager::RayCast()
{
	Math::Vec2 lightPos = GetLightPos();

	float T1, T2;
	float smallestT1{};
	bool foundIntersection;
	std::vector<Math::Vec2> rayPts;

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
			if (T1 >= smallestT1 - 0.0001f) // intersection is further than the closest
				continue;
			foundIntersection = true;
			smallestT1 = T1;
		}
		Math::Vec2 _ray = ray.pos + smallestT1 * ray.dir;
		rayPts.push_back(_ray);

		if (!foundIntersection) // intersection is at a point
		{
			float theta = 0.001f;
			Math::Vec2 posDir{ ray.dir.x * cosf(theta) - ray.dir.y * sinf(theta), ray.dir.x * sinf(theta) + ray.dir.y * cosf(theta) };
			Math::Vec2 negDir{ ray.dir.x * cosf(-theta) - ray.dir.y * sinf(-theta), ray.dir.x * sinf(-theta) + ray.dir.y * cosf(-theta) };
			mExtendedRayDirection.push_back({ ray.pos, posDir });
			mExtendedRayDirection.push_back({ ray.pos, negDir });
		}
	}

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
			if (T1 >= smallestT1 - 0.0001f) // intersection is further than the closest
				continue;
			smallestT1 = T1;
		}
		Math::Vec2 _ray = ray.pos + smallestT1 * ray.dir;
		rayPts.push_back(_ray);
	}
	std::sort(rayPts.begin(), rayPts.end(), CompareAngle);
	mRayEndPoints.push_back(rayPts);
}

void ShadowManager::CreateRays()
{
	Math::Vec2 lightPos = GetLightPos();
	for (size_t k = 0; k < mObjectEdges.size(); ++k)
		mRayDirection.push_back({ lightPos, mObjectEdges[k].pos - lightPos });
}

Math::Vec2 ShadowManager::GetLightPos()
{
	if (!mCurrEntity.id) return Math::Vec2();
	return mCurrEntity.GetComponent<Transform>().translation
		+ mCurrEntity.GetComponent<LightSource>().centerOffset;;
}

bool CompareAngle(const Math::Vec2& endPt1, const Math::Vec2& endPt2)
{
	return GetAngle(endPt1 - shadowManager->GetLightPos()) < GetAngle(endPt2 - shadowManager->GetLightPos());
}

float GetAngle(const Math::Vec2& endPt)
{
	if (endPt.y != 0.f && endPt.x >= 0.f)
	{
		float angle = atan2f(endPt.y, endPt.x);
		if (angle <= 0)
			angle = (float)Math::PI - abs(angle) + (float)Math::PI;
		return  angle;
	}
	if (endPt.y == 0.f && endPt.x > 0.f)
		return 0.f;
	if (endPt.y != 0.f && endPt.x < 0.f)
	{
		float angle = atan2f(endPt.y, endPt.x);
		if (angle <= 0)
			angle = (float)Math::PI - abs(angle) + (float)Math::PI;
		return  angle;
	}
	return (float)Math::PI;
}

void ShadowManager::CreateObjectVertices(Entity e)
{
	Math::Vec2 lightPos = GetLightPos();

	Transform xform = e.GetComponent<Transform>();
	ShadowCaster caster = e.GetComponent<ShadowCaster>();
	xform.translation += caster.centerOffset;
	xform.scale.x *= caster.scaleOffset.x;
	xform.scale.y *= caster.scaleOffset.y;
	Math::Vec2 i{ xform.scale.x * 0.5f, 0 };
	Math::Vec2 j{ 0, xform.scale.y * 0.5f };

	Math::Vec2 p0 = xform.translation + i + j;
	Math::Vec2 p1 = xform.translation - i + j;
	Math::Vec2 p2 = xform.translation - i - j;
	Math::Vec2 p3 = xform.translation + i - j;

	if (powf(p0.x - lightPos.x, 2.f) + powf(p0.y - lightPos.y, 2.f)
		< powf(mCurrEntity.GetComponent<LightSource>().radius, 2.f) ||
		powf(p1.x - lightPos.x, 2.f) + powf(p1.y - lightPos.y, 2.f)
		< powf(mCurrEntity.GetComponent<LightSource>().radius, 2.f) ||
		powf(p2.x - lightPos.x, 2.f) + powf(p2.y - lightPos.y, 2.f)
		< powf(mCurrEntity.GetComponent<LightSource>().radius, 2.f) ||
		powf(p3.x - lightPos.x, 2.f) + powf(p3.y - lightPos.y, 2.f)
		< powf(mCurrEntity.GetComponent<LightSource>().radius, 2.f))
	{
		mObjectEdges.push_back({ p0, -2.f * i });
		mObjectEdges.push_back({ p1, -2.f * j });
		mObjectEdges.push_back({ p2, 2 * i });
		mObjectEdges.push_back({ p3, 2 * j });
	}
}

void ShadowManager::ClearVectors()
{
	mObjectEdges.clear();
	mRayDirection.clear();
	mExtendedRayDirection.clear();
	mRayEndPoints.clear();
}

void ShadowManager::CreateFOVVertices()
{
	std::vector<Math::Vec2> circlePts;
	Math::Vec2 center = GetLightPos();
	Math::Vec2 vec = Math::Vec2(mCurrEntity.GetComponent<LightSource>().radius, 0.f);
	float theta = 2.f / CIRCLE_SLICES * static_cast<float>(Math::PI);


	for (int i = 0; i < CIRCLE_SLICES; ++i)
		circlePts.push_back(center + Math::Vec2(cosf(theta * i) * vec.x, sinf(theta * i) * vec.x));
	
	for (int i = 0; i < CIRCLE_SLICES - 1; ++i)
		mObjectEdges.push_back({ circlePts[i], circlePts[i + 1] - circlePts[i] });
	mObjectEdges.push_back({ circlePts.back(), circlePts[0] - circlePts.back() });
}
