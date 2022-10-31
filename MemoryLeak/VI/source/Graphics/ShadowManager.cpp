#include <ShadowManager.h>
#include <VertexFetcher.h>
#include <Logger.h>

void ShadowManager::MakeShadows(const Entity& _lightsource, std::shared_ptr<RenderManager> _renderMgr)
{
    if (!_lightsource.HasComponent<LightSource>())
    {
        LOG_DEBUG("Entity does not have a LightSource Component!");
        return;
    }
    
    std::vector<Math::Vec2> points;
    Math::Vec2 pivot = _lightsource.GetComponent<Transform>().translation + _lightsource.GetComponent<LightSource>().centreOffset;

    int rays = 480;

    for (int i = 0; i < rays; ++i)
    {
        Transform xform = _lightsource.GetComponent<Transform>();
        xform.translation = pivot;
        xform.rotation = (i / (float)rays) * 2.f * 3.14159f;
        points.push_back(RayCast(xform));
    }
    
    for (int i = 0; i < rays; ++i)
        _renderMgr->CreateLightingTriangle(pivot, points[i], points[(i + 1 == rays)? 0 : i + 1]);
}

float ShadowManager::LineOfSightCheck(const Math::Vec2& p0, const Math::Vec2& p1, const Math::Vec2& p, const Math::Vec2& vtr, const Math::Vec2& normal)
{
    float lineOfSightCheck(Math::Dot(p0 - p, normal) * Math::Dot(p1 - p, normal));
    return Math::Dot(p0 - p, vtr) < 0 ? std::abs(lineOfSightCheck) : lineOfSightCheck;
}

float ShadowManager::PointLineSegDist(const Math::Vec2& p, const Math::Vec2& p0, const Math::Vec2& p1)
{
    float lengthSq1 = Math::SqDistance(p0, p1);
    float t = std::max(0.f, std::min(1.f, Math::Dot(p - p0, p1 - p0) / lengthSq1));
    Math::Vec2 projection = p0 + t * (p1 - p0);
    return Math::Distance(p, projection);
}

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

    for (const Entity& _e : mEntities)
    {
        if (!_e.HasComponent<Sprite>() || _e.GetComponent<Sprite>().sprite != SPRITE::SQUARE) continue;


        std::vector<Math::Vec2> points = VertexFetcher::FetchVertices(_e);

        float p0p1 = LineOfSightCheck(points[0], points[1], xform.translation, vector, normal);
        float p1p2 = LineOfSightCheck(points[1], points[2], xform.translation, vector, normal);
        float p2p3 = LineOfSightCheck(points[2], points[3], xform.translation, vector, normal);
        float p3p0 = LineOfSightCheck(points[3], points[0], xform.translation, vector, normal);
        std::vector<float>pts{ p0p1, p1p2, p2p3, p3p0 };
        if (p0p1 >= 0 && p1p2 >= 0 && p2p3 >= 0 && p3p0 >= 0)
            continue;

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
        float dist1 = PointLineSegDist(xform.translation, lineseg1.first, lineseg1.second);
        float dist2 = PointLineSegDist(xform.translation, lineseg2.first, lineseg2.second);

        lineseg = dist1 < dist2 ? (dist1 < shortestDistance ? shortestDistance = dist1, lineseg1 : lineseg)
            : (dist2 < shortestDistance ? shortestDistance = dist2, lineseg2 : lineseg);
    }
    Math::Vec2 linesegEqn = Math::Vec2(lineseg.second - lineseg.first);
    Math::Vec2 linesegNml{ linesegEqn.y, -linesegEqn.x };
    linesegNml.Normalize();
    float scale = std::abs(Math::Dot(linesegNml, lineseg.first - xform.translation) / Math::Dot(linesegNml, vector));
    scale = std::isnan(scale) ? 1600 : scale;
    return xform.translation + scale * vector;
}