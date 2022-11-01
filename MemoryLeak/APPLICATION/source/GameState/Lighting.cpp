#include <Lighting.h>
#include "Input.h"
#include <VertexFetcher.h>
#include "Helper.h"

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
    e1.AddComponent(Transform{ {400, 100}, 1.f, {100,250} },
        Sprite{ grey, SPRITE::SQUARE, 0, 1 },
        General{ "background", TAG::OTHERS, SUBTAG::NOSUBTAG, true, false },
        Text{ "3Dumb", "Wall", {-50, 0}, 1.f, {255, 0, 0, 255} });
    Entity e2{ ECS::CreateEntity() };
    mEntities.insert(e2);
    e2.AddComponent(Transform{ {100, 100}, 4, {-400,0} },
        Sprite{ grey, SPRITE::SQUARE, 0, 1 },
        General{ "background", TAG::OTHERS, SUBTAG::NOSUBTAG, true, false },
        Text{ "3Dumb", "Wall", {-50, 0}, 1.f, {255, 0, 0, 255} });
    Entity e3{ ECS::CreateEntity() };
    mEntities.insert(e3);
    e3.AddComponent(Transform{ {100, 200}, 1.7f, {400,-250} },
        Sprite{ grey, SPRITE::SQUARE, 0, 1 },
        General{ "background", TAG::OTHERS, SUBTAG::NOSUBTAG, true, false },
        Text{ "3Dumb", "Wall", {-50, 0}, 1.f, {255, 0, 0, 255} });
    Entity e4{ ECS::CreateEntity() };
    mEntities.insert(e4);
    e4.AddComponent(Transform{ {200, 200}, 2.8f, {650,50} },
        Sprite{ grey, SPRITE::SQUARE, 0, 1 },
        General{ "background", TAG::OTHERS, SUBTAG::NOSUBTAG, true, false },
        Text{ "3Dumb", "Wall", {-50, 0}, 1.f, {255, 0, 0, 255} });
    Entity e5{ ECS::CreateEntity() };
    mEntities.insert(e5);
    e5.AddComponent(Transform{ {100, 300}, 0.4f, {-650,200} },
        Sprite{ grey, SPRITE::SQUARE, 0, 1 },
        General{ "background", TAG::OTHERS, SUBTAG::NOSUBTAG, true, false },
        Text{ "3Dumb", "Wall", {-50, 0}, 1.f, {255, 0, 0, 255} });
    Entity e6{ ECS::CreateEntity() };
    mEntities.insert(e6);
    e6.AddComponent(Transform{ {300, 100}, 4.7f, {-400,-250} },
        Sprite{ grey, SPRITE::SQUARE, 0, 1 },
        General{ "background", TAG::OTHERS, SUBTAG::NOSUBTAG, true, false },
        Text{ "3Dumb", "Wall", {-50, 0}, 1.f, {255, 0, 0, 255} });
    Entity e7{ ECS::CreateEntity() };
    mEntities.insert(e7);
    e7.AddComponent(Transform{ {100, 100}, 0, {500, 300} },
        Sprite{ grey, SPRITE::SQUARE, 0, 1 },
        General{ "background", TAG::OTHERS, SUBTAG::NOSUBTAG, true, false },
        Text{ "3Dumb", "Wall", {-50, 0}, 1.f, {255, 0, 0, 255} });
    Entity e8{ ECS::CreateEntity() };
    mEntities.insert(e8);
    e8.AddComponent(Transform{ {100, 100}, 0.5f, {-200, 250} },
        Sprite{ grey, SPRITE::SQUARE, 0, 1 },
        General{ "background", TAG::OTHERS, SUBTAG::NOSUBTAG, true, false },
        Text{ "3Dumb", "Wall", {-50, 0}, 1.f, {255, 0, 0, 255} });
    Entity e9{ ECS::CreateEntity() };
    mEntities.insert(e9);
    e9.AddComponent(Transform{ {100, 100}, 0.f, {0, -250} },
        Sprite{ grey, SPRITE::SQUARE, 0, 1 },
        General{ "background", TAG::OTHERS, SUBTAG::NOSUBTAG, true, false },
        Text{ "3Dumb", "Wall", {-50, 0}, 1.f, {255, 0, 0, 255} });
    lightsource = ECS::CreateEntity();
    lightsource.AddComponent(Transform{ {10, 10}, 0, {0,0} },
        Sprite{ {255, 0, 0, 255}, SPRITE::CIRCLE, 0, 240},
        General{ "background", TAG::OTHERS, SUBTAG::NOSUBTAG, true, false },
        LightSource{{0,0}},
        Text{ "CaviarDreams", "Lightsource", {-120, 0}, 1.f, {255, 0, 0, 255} });
    mEntities.insert(lightsource);
}

void Lighting::Update()
{
    if (Input::CheckKey(E_STATE::HOLD, E_KEY::UP))
        lightsource.GetComponent<Transform>().translation.y += 200.f * (float)FPSManager::dt;
    if (Input::CheckKey(E_STATE::HOLD, E_KEY::DOWN))
        lightsource.GetComponent<Transform>().translation.y -= 200.f * (float)FPSManager::dt;
    if (Input::CheckKey(E_STATE::HOLD, E_KEY::LEFT))
        lightsource.GetComponent<Transform>().translation.x -= 200.f * (float)FPSManager::dt;
    if (Input::CheckKey(E_STATE::HOLD, E_KEY::RIGHT))
        lightsource.GetComponent<Transform>().translation.x += 200.f * (float)FPSManager::dt;

    
    renderManager->GetGameCamera().SetPos(lightsource.GetComponent<Transform>().translation);
    for (const Entity& e : mEntities)
    {
        e.GetComponent<Text>().offset = -renderManager->GetGameCamera().GetPos();
        e.GetComponent<Text>().offset.x -= 50;
    }
    shadowManager->MakeShadows(lightsource, renderManager);
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
