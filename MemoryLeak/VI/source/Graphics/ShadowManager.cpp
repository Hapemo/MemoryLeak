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
#include <VertexFetcher.h>
#include <Logger.h>

/*!*****************************************************************************
\brief
Makes shadows based on the given Entity with lightsource, casting rays from the
lightsource to all entities with Shadow component (for now sprites with squares).

\param const Entity& _lightsource
The lightsource to raycast from.

\param std::shared_ptr<RenderManager> _renderMgr
Sends the vertices of the raycast to the render manager.
*******************************************************************************/
void ShadowManager::MakeShadows(const Entity& _lightsource, std::shared_ptr<RenderManager> _renderMgr)
{
    if (!_lightsource.HasComponent<LightSource>())
    {
        LOG_DEBUG("Entity does not have a LightSource Component!");
        return;
    }
    
    std::vector<Math::Vec2> points;
    Math::Vec2 pivot = _lightsource.GetComponent<Transform>().translation 
        + _lightsource.GetComponent<LightSource>().centreOffset;

    int rays = 360;

    for (int i = 0; i < rays; ++i)
    {
        Transform xform = _lightsource.GetComponent<Transform>();
        xform.translation = pivot;
        xform.rotation = (i / (float)rays) * 2.f * 3.14159f;
        points.push_back(RayCast(xform));
    }
    
    //loop and create triangles for shadows
    for (int i = 0; i < rays; ++i)
        _renderMgr->CreateLightingTriangle(pivot, points[i], points[(i + 1 == rays)? 0 : i + 1]);
}
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
float ShadowManager::LineOfSightCheck(const Math::Vec2& _p0, const Math::Vec2& _p1, 
    const Math::Vec2& _p, const Math::Vec2& _vtr, const Math::Vec2& _normal)
{
    float lineOfSightCheck(Math::Dot(_p0 - _p, _normal) * Math::Dot(_p1 - _p, _normal));
    return Math::Dot(_p0 - _p, _vtr) < 0 ? std::abs(lineOfSightCheck) : lineOfSightCheck;
}
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
float ShadowManager::PointLineSegDist(const Math::Vec2& _p, const Math::Vec2& _p0, const Math::Vec2& _p1)
{
    float lengthSq1 = Math::SqDistance(_p0, _p1);
    float t = std::max(0.f, std::min(1.f, Math::Dot(_p - _p0, _p1 - _p0) / lengthSq1));
    Math::Vec2 projection = _p0 + t * (_p1 - _p0);
    return Math::Distance(_p, projection);
}
/*!*****************************************************************************
\brief
Raycasts a single ray from the lightsource.

\param const Transform& _xform
The transform of the ray.

\return
Returns the point that the ray stopped at.
*******************************************************************************/
Math::Vec2 ShadowManager::RayCast(const Transform& _xform)
{
    Transform xform = _xform;
    float rot = _xform.rotation;

    Math::Vec2 vector{ cosf(rot), sinf(rot) };
    Math::Vec2 normal{ -vector.y, vector.x };
    std::pair<Math::Vec2, Math::Vec2> lineseg1;
    std::pair<Math::Vec2, Math::Vec2> lineseg2;
    std::pair<Math::Vec2, Math::Vec2> lineseg;
    float shortestDistance = 1600;

    //loop through all entities (FOR NOW)
    for (const Entity& _e : mEntities)
    {
        if (!_e.HasComponent<Sprite>() || _e.GetComponent<Sprite>().sprite != SPRITE::SQUARE) continue;


        std::vector<Math::Vec2> points = VertexFetcher::FetchVertices(_e);

        //check line of sight, if < 0 => in line of sight
        float p0p1 = LineOfSightCheck(points[0], points[1], xform.translation, vector, normal);
        float p1p2 = LineOfSightCheck(points[1], points[2], xform.translation, vector, normal);
        float p2p3 = LineOfSightCheck(points[2], points[3], xform.translation, vector, normal);
        float p3p0 = LineOfSightCheck(points[3], points[0], xform.translation, vector, normal);
        std::vector<float>pts{ p0p1, p1p2, p2p3, p3p0 };
        
        //if none in los, continue
        if (p0p1 >= 0 && p1p2 >= 0 && p2p3 >= 0 && p3p0 >= 0)
            continue;

        //find lineseg that intercepts
        for (size_t i = 0; i < pts.size(); ++i)
            if (pts[i] < 0)
            {
                lineseg1 = std::pair<Math::Vec2, Math::Vec2>(points[i], points[i == 3 ? 0 : i + 1]);
                break;
            }
        for (int i = (int)pts.size() - 1; i >= 0; --i)
            if (pts[i] < 0)
            {
                lineseg2 = std::pair<Math::Vec2, Math::Vec2>(points[i], points[i == 3 ? 0 : i + 1]);
                break;
            }

        //find shortest dist and cast it to that (FOR NOW)
        float dist1 = PointLineSegDist(xform.translation, lineseg1.first, lineseg1.second);
        float dist2 = PointLineSegDist(xform.translation, lineseg2.first, lineseg2.second);

        lineseg = dist1 < dist2 ? 
            (dist1 < shortestDistance ? shortestDistance = dist1, lineseg1 : lineseg)
            : (dist2 < shortestDistance ? shortestDistance = dist2, lineseg2 : lineseg);
    }
    Math::Vec2 linesegEqn = Math::Vec2(lineseg.second - lineseg.first);
    Math::Vec2 linesegNml{ linesegEqn.y, -linesegEqn.x };
    linesegNml.Normalize();
    float scale = std::abs(Math::Dot(linesegNml, lineseg.first - xform.translation) / Math::Dot(linesegNml, vector));
    //if nan, means that the rays do not collide with any line
    scale = std::isnan(scale) ? 1600 : scale;
    return xform.translation + scale * vector;
}