#include <Lighting.h>
#include "Input.h"
#include <VertexFetcher.h>

constexpr Color black{ 0, 0, 0, 255 };
constexpr Color grey{ 50, 50, 50, 255 };
constexpr Color white{ 255, 255, 255, 255 };
Entity lightsource;

void Lighting::Load()
{
}

void Lighting::Init()
{
    renderManager->SetVectorLengthModifier(5.f);
    renderManager->SetDebug(true);
    renderManager->RenderToScreen();
    renderManager->SetClearColor(black);
    Entity e1{ ECS::CreateEntity() };
    mEntities.insert(e1);
    e1.AddComponent(Transform{ {400, 100}, 2, {100,250} },
        Sprite{ grey, SPRITE::SQUARE, 0, 1 },
        General{ "background", TAG::OTHERS, SUBTAG::NOSUBTAG, true, false });
    Entity e2{ ECS::CreateEntity() };
    mEntities.insert(e2);
    e2.AddComponent(Transform{ {100, 100}, 4, {-400,0} },
        Sprite{ grey, SPRITE::SQUARE, 0, 1 },
        General{ "background", TAG::OTHERS, SUBTAG::NOSUBTAG, true, false });
    Entity e3{ ECS::CreateEntity() };
    mEntities.insert(e3);
    e3.AddComponent(Transform{ {100, 200}, 1.7f, {400,-250} },
        Sprite{ grey, SPRITE::SQUARE, 0, 1 },
        General{ "background", TAG::OTHERS, SUBTAG::NOSUBTAG, true, false });
    Entity e4{ ECS::CreateEntity() };
    mEntities.insert(e4);
    e4.AddComponent(Transform{ {200, 200}, 2.8f, {650,50} },
        Sprite{ grey, SPRITE::SQUARE, 0, 1 },
        General{ "background", TAG::OTHERS, SUBTAG::NOSUBTAG, true, false });
    Entity e5{ ECS::CreateEntity() };
    mEntities.insert(e5);
    e5.AddComponent(Transform{ {100, 300}, 0.4f, {-650,200} },
        Sprite{ grey, SPRITE::SQUARE, 0, 1 },
        General{ "background", TAG::OTHERS, SUBTAG::NOSUBTAG, true, false });
    Entity e6{ ECS::CreateEntity() };
    mEntities.insert(e6);
    e6.AddComponent(Transform{ {300, 100}, 4.7f, {-400,-250} },
        Sprite{ grey, SPRITE::SQUARE, 0, 1 },
        General{ "background", TAG::OTHERS, SUBTAG::NOSUBTAG, true, false });
    Entity e7{ ECS::CreateEntity() };
    mEntities.insert(e7);
    e7.AddComponent(Transform{ {100, 100}, 4.7f, {500, 300} },
        Sprite{ grey, SPRITE::SQUARE, 0, 1 },
        General{ "background", TAG::OTHERS, SUBTAG::NOSUBTAG, true, false });
    Entity e8{ ECS::CreateEntity() };
    mEntities.insert(e8);
    e8.AddComponent(Transform{ {100, 100}, 0.5f, {-200, 250} },
        Sprite{ grey, SPRITE::SQUARE, 0, 1 },
        General{ "background", TAG::OTHERS, SUBTAG::NOSUBTAG, true, false });
    Entity e9{ ECS::CreateEntity() };
    mEntities.insert(e9);
    e9.AddComponent(Transform{ {100, 100}, 0.f, {0, -250} },
        Sprite{ grey, SPRITE::SQUARE, 0, 1 },
        General{ "background", TAG::OTHERS, SUBTAG::NOSUBTAG, true, false });
    lightsource = ECS::CreateEntity();
    lightsource.AddComponent(Transform{ {10, 10}, 0, {0,0} },
        Sprite{ {255, 0, 0, 255}, SPRITE::CIRCLE, 0, 240},
        General{ "background", TAG::OTHERS, SUBTAG::NOSUBTAG, true, false },
        LightSource{{0,0}});
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

void Lighting::Unload()
{
    renderManager->Clear();
    spriteManager->FreeTextures();
    FREE_RESOURCES();
}
