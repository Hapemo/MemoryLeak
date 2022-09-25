/*!*****************************************************************************
\file GameState3.cpp
\author Jazz Teoh Yu Jue
\par DP email: j.teoh\@digipen.edu
\par Group: Memory Leak Studios
\date 24-09-2022
\brief
Game state for testing physics
*******************************************************************************/
#include "GameState3.h"
#include "ECSManager.h"
#include "Application.h"
#include "Input.h"

void GameState3::Load() {
    INIT_TEXTURES("Background");
    INIT_TEXTURES("Spritesheets");
    for (size_t index = 0; index < GET_RESOURCES().size(); ++index)
        spriteManager->InitializeTexture(GET_TEXTURE_DATA(index));
}

void GameState3::Init() {
    float width = Application::getWindowWidth();
    float height = Application::getWindowHeight();
    Entity e1{ ECS::CreateEntity() };
    mEntities.insert(e1);
    e1.AddComponent(Transform{ {width, height}, 0, {0,0}},
        Sprite{ Color{0,255,0,255}, SPRITE::TEXTURE, 0, 0 },
        General{ "background", TAG::PASSENGER, SUBTAG::NOSUBTAG, true });
    spriteManager->SetTexture(e1, "Textures\\Background\\background.png");
    physics2DManager->AddPhysicsComponent(e1, 1.f, 50.f, 0.f, false);

    Entity e2{ ECS::CreateEntity() };
    mEntities.insert(e2);
    e2.AddComponent(Transform{ {width, height}, 0, {0,0} },
        Sprite{ Color{0,255,0,255}, SPRITE::TEXTURE, 0, 1 },
        General{ "middleground", TAG::PASSENGER, SUBTAG::NOSUBTAG, true });
    spriteManager->SetTexture(e2, "Textures\\Background\\middleground.png");
    physics2DManager->AddPhysicsComponent(e2, 1.f, 150.f, 0.f, false);

    Entity e3{ ECS::CreateEntity() };
    mEntities.insert(e3);
    e3.AddComponent(Transform{ {width, height}, 0, {0,0} },
        Sprite{ Color{0,255,0,255}, SPRITE::TEXTURE, 0, 2 },
        General{ "foreground", TAG::PASSENGER, SUBTAG::NOSUBTAG, true });
    spriteManager->SetTexture(e3, "Textures\\Background\\foreground.png");
    physics2DManager->AddPhysicsComponent(e3, 1.f, 300.f, 0.f, false);

    Entity e4{ ECS::CreateEntity() };
    mEntities.insert(e4);
    e4.AddComponent(Transform{ {width, height}, 0, {width,0} },
        Sprite{ Color{0,255,0,255}, SPRITE::TEXTURE, 0, 0 },
        General{ "background1", TAG::PASSENGER, SUBTAG::NOSUBTAG, true });
    spriteManager->SetTexture(e4, "Textures\\Background\\background.png");
    physics2DManager->AddPhysicsComponent(e4, 1.f, 50.f, 0.f, false);

    Entity e5{ ECS::CreateEntity() };
    mEntities.insert(e5);
    e5.AddComponent(Transform{ {width, height}, 0, {width,0} },
        Sprite{ Color{0,255,0,255}, SPRITE::TEXTURE, 0, 1 },
        General{ "middleground1", TAG::PASSENGER, SUBTAG::NOSUBTAG, true });
    spriteManager->SetTexture(e5, "Textures\\Background\\middleground.png");
    physics2DManager->AddPhysicsComponent(e5, 1.f, 150.f, 0.f, false);

    Entity e6{ ECS::CreateEntity() };
    mEntities.insert(e6);
    e6.AddComponent(Transform{ {width, height}, 0, {width,0} },
        Sprite{ Color{0,255,0,255}, SPRITE::TEXTURE, 0, 2 },
        General{ "foreground1", TAG::PASSENGER, SUBTAG::NOSUBTAG, true });
    spriteManager->SetTexture(e6, "Textures\\Background\\foreground.png");
    physics2DManager->AddPhysicsComponent(e6, 1.f, 300.f, 0.f, false);

    Entity e7{ ECS::CreateEntity() };
    mEntities.insert(e7);
    e7.AddComponent(Transform{ {96,96}, 0, {50, -100} },
        Sprite{ Color{0,255,0,255}, SPRITE::TEXTURE, 0, 10 },
        SheetAnimation{ 6, 0, 0.1f },
        General{ "spritesheet", TAG::PASSENGER, SUBTAG::NOSUBTAG, true });
    spriteManager->SetTexture(e7, "Textures\\Spritesheets\\Woodcutter_run.png");
}

void GameState3::Update() {
    static bool isjump = false;
    for (const Entity& e : mEntities)
    {
        if (e.GetComponent<Transform>().translation.x >= Application::getWindowWidth())
            e.GetComponent<Transform>().translation.x = -Application::getWindowWidth();

        if (e.GetComponent<General>().name == "spritesheet")
        {
            if (Input::CheckKey(STATE::PRESS, KEY::SPACE))
            {
                if (!isjump)
                {
                    spriteManager->SetTexture(e, "Textures\\Spritesheets\\Woodcutter_jump.png");
                    e.GetComponent<SheetAnimation>() = { 6,0,.1f };
                }
                else
                {
                    spriteManager->SetTexture(e, "Textures\\Spritesheets\\Woodcutter_run.png");
                    e.GetComponent<SheetAnimation>() = { 6,0,.1f };
                }
                isjump = !isjump;
            }
        }
    }
    physics2DManager->Update(FPSManager::dt);
    collision2DManager->Update(mEntities);
    sheetAnimator->Animate();
}

void GameState3::Draw() {
    renderManager->Render();
}

void GameState3::Free() {
    physics2DManager->PhyObjListClear();

    for (auto& e : mEntities)
        e.Destroy();
    mEntities.clear();
}

void GameState3::Unload() {
    renderManager->Clear();
    spriteManager->FreeTextures();
    FREE_RESOURCES();
}





