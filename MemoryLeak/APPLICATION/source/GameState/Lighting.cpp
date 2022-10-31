#include <Lighting.h>
#include "Input.h"

constexpr Color black{ 0, 0, 0, 255 };
constexpr Color grey{ 50, 50, 50, 255 };
constexpr Color white{ 255, 255, 255, 255 };
Entity lightsource;

float LineLine(const Math::Vec2& p0, const Math::Vec2& p1, const Math::Vec2& p, const Math::Vec2& normal)
{
    return (Math::Dot(p0 - p, normal) * Math::Dot(p1 - p, normal));
}

void Lighting::Load() {}

void Lighting::Init()
{
    renderManager->SetVectorLengthModifier(5.f);
    renderManager->SetDebug(true);
    renderManager->RenderToScreen();
    renderManager->SetClearColor(black);
    Entity e1{ ECS::CreateEntity() };
    mEntities.insert(e1);
    e1.AddComponent(Transform{ {400, 100}, 0, {100,250} },
        Sprite{ grey, SPRITE::SQUARE, 0, 1 },
        General{ "background", TAG::OTHERS, SUBTAG::NOSUBTAG, true });
    Entity e2{ ECS::CreateEntity() };
    mEntities.insert(e2);
    e2.AddComponent(Transform{ {100, 100}, 0, {-400,0} },
        Sprite{ grey, SPRITE::SQUARE, 0, 1 },
        General{ "background", TAG::OTHERS, SUBTAG::NOSUBTAG, true });
    Entity e3{ ECS::CreateEntity() };
    mEntities.insert(e3);
    e3.AddComponent(Transform{ {100, 200}, 0, {400,-250} },
        Sprite{ grey, SPRITE::SQUARE, 0, 1 },
        General{ "background", TAG::OTHERS, SUBTAG::NOSUBTAG, true });
    Entity e4{ ECS::CreateEntity() };
    mEntities.insert(e4);
    e4.AddComponent(Transform{ {200, 200}, 0, {650,50} },
        Sprite{ grey, SPRITE::SQUARE, 0, 1 },
        General{ "background", TAG::OTHERS, SUBTAG::NOSUBTAG, true });
    Entity e5{ ECS::CreateEntity() };
    mEntities.insert(e5);
    e5.AddComponent(Transform{ {100, 300}, 0, {-650,200} },
        Sprite{ grey, SPRITE::SQUARE, 0, 1 },
        General{ "background", TAG::OTHERS, SUBTAG::NOSUBTAG, true });
    Entity e6{ ECS::CreateEntity() };
    mEntities.insert(e6);
    e6.AddComponent(Transform{ {300, 100}, 0, {-400,-250} },
        Sprite{ grey, SPRITE::SQUARE, 0, 1 },
        General{ "background", TAG::OTHERS, SUBTAG::NOSUBTAG, true });
    lightsource = ECS::CreateEntity();
    lightsource.AddComponent(Transform{ {50, 50}, 0, {0,0} },
        Sprite{ white, SPRITE::CIRCLE, 0, 0 },
        General{ "background", TAG::OTHERS, SUBTAG::NOSUBTAG, true },
        Edge2DCollider{ {0,0}, 0, 10000, true });
}

void Lighting::Update()
{
    if (Input::CheckKey(E_STATE::HOLD, E_KEY::UP))
        lightsource.GetComponent<Transform>().translation.y += 1.f;
    if (Input::CheckKey(E_STATE::HOLD, E_KEY::DOWN))
        lightsource.GetComponent<Transform>().translation.y -= 1.f;
    if (Input::CheckKey(E_STATE::HOLD, E_KEY::LEFT))
        lightsource.GetComponent<Transform>().translation.x -= 1.f;
    if (Input::CheckKey(E_STATE::HOLD, E_KEY::RIGHT))
        lightsource.GetComponent<Transform>().translation.x += 1.f;

    if (Input::CheckKey(E_STATE::HOLD, E_KEY::Q))
        lightsource.GetComponent<Edge2DCollider>().rotationOffset += 0.001f;
    if (Input::CheckKey(E_STATE::HOLD, E_KEY::E))
        lightsource.GetComponent<Edge2DCollider>().rotationOffset -= 0.001f;

    float rot = lightsource.GetComponent<Edge2DCollider>().rotationOffset;

    Math::Vec2 vector{ cosf(rot), sinf(rot) };
    Math::Vec2 normal{ -vector.y, vector.x };

    for (const Entity& e : mEntities)
    {
        if (!(e.HasComponent<Sprite>() && e.GetComponent<Sprite>().sprite == SPRITE::SQUARE)) continue;

        float halfwidth = 0.5f * e.GetComponent<Transform>().scale.x;
        float halfheight = 0.5f * e.GetComponent<Transform>().scale.y;
        Math::Vec2 centre = e.GetComponent<Transform>().translation;
        Math::Vec2 p0{ centre.x - halfwidth, centre.y - halfheight };
        Math::Vec2 p1{ centre.x + halfwidth, centre.y - halfheight };
        Math::Vec2 p2{ centre.x + halfwidth, centre.y + halfheight };
        Math::Vec2 p3{ centre.x - halfwidth, centre.y + halfheight };
        float p0p1 = LineLine(p0, p1, lightsource.GetComponent<Transform>().translation, normal);
        float p1p2 = LineLine(p1, p2, lightsource.GetComponent<Transform>().translation, normal);
        float p2p3 = LineLine(p2, p3, lightsource.GetComponent<Transform>().translation, normal);
        float p3p0 = LineLine(p3, p0, lightsource.GetComponent<Transform>().translation, normal);
        if (p0p1 >= 0 && p1p2 >= 0 && p2p3 >= 0 && p3p0 >= 0)
            continue;
        std::pair<Math::Vec2, Math::Vec2> lineseg;
        if (p0p1 < 0)
            lineseg = std::pair<Math::Vec2, Math::Vec2>(p0,p1);
        else if (p1p2 < 0)
            lineseg = std::pair<Math::Vec2, Math::Vec2>(p1, p2);
        else if (p2p3 < 0)
            lineseg = std::pair<Math::Vec2, Math::Vec2>(p2, p3);
        else 
            lineseg = std::pair<Math::Vec2, Math::Vec2>(p3, p0);
        lightsource.GetComponent<Edge2DCollider>().scaleOffset = std::abs(Math::Dot(lineseg.first - centre, vector));
    }

}

void Lighting::Draw()
{
    renderManager->Render();
}

void Lighting::Free()
{
    ECS::DestroyAllEntities();
}

void Lighting::Unload() {}
