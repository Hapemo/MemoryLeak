/*!*****************************************************************************
\file GameState3.cpp
\author Jazz Teoh Yu Jue
\par DP email: j.teoh\@digipen.edu
\par Group: Memory Leak Studios
\date 24-09-2022
\brief
Game state for testing physics
*******************************************************************************/
#include "ParallaxAndSpriteSwap.h"
#include "ECSManager.h"
#include "Application.h"
#include "Input.h"
#include "Logger.h"

void ParallaxAndSpriteSwap::Load() {
    LOAD_TEXTURES("Background");
    LOAD_TEXTURES("Icons");
    LOAD_TEXTURES("Menu");
    LOAD_TEXTURES("Sprites");
    LOAD_TEXTURES("Spritesheets");
    for (size_t index = 0; index < GET_RESOURCES().size(); ++index)
        spriteManager->InitializeTexture(GET_TEXTURE_DATA(index));
}

void ParallaxAndSpriteSwap::Init() {
    float width = (float)Application::getWindowWidth();
    float height = (float)Application::getWindowHeight();

    /*************************************Parallax Start************************************/
    //background of parallax
    Entity e1{ ECS::CreateEntity() };
    mEntities.insert(e1);
    e1.AddComponent(Transform{ {width, height}, 0, {0,0} },
        Sprite{ Color{0,255,0,255}, SPRITE::TEXTURE, 0, 0 },
        General{ "background", TAG::PASSENGER, SUBTAG::NOSUBTAG, true });
    spriteManager->SetTexture(e1, "Textures\\Background\\background.png");
    physics2DManager->AddPhysicsComponent(e1, false, 1.f, 50.f);
    Entity e4{ ECS::CreateEntity() };
    mEntities.insert(e4);
    e4.AddComponent(Transform{ {width, height}, 0, {width,0} },
        Sprite{ Color{0,255,0,255}, SPRITE::TEXTURE, 0, 0 },
        General{ "background1", TAG::PASSENGER, SUBTAG::NOSUBTAG, true });
    spriteManager->SetTexture(e4, "Textures\\Background\\background.png");
    physics2DManager->AddPhysicsComponent(e4, false, 1.f, 50.f);

    //middleground of parallax
    Entity e2{ ECS::CreateEntity() };
    mEntities.insert(e2);
    e2.AddComponent(Transform{ {width, height}, 0, {0,0} },
        Sprite{ Color{0,255,0,255}, SPRITE::TEXTURE, 0, 1 },
        General{ "middleground", TAG::PASSENGER, SUBTAG::NOSUBTAG, true });
    spriteManager->SetTexture(e2, "Textures\\Background\\middleground.png");
    physics2DManager->AddPhysicsComponent(e2, false, 1.f, 150.f);
    Entity e5{ ECS::CreateEntity() };
    mEntities.insert(e5);
    e5.AddComponent(Transform{ {width, height}, 0, {width,0} },
        Sprite{ Color{0,255,0,255}, SPRITE::TEXTURE, 0, 1 },
        General{ "middleground1", TAG::PASSENGER, SUBTAG::NOSUBTAG, true });
    spriteManager->SetTexture(e5, "Textures\\Background\\middleground.png");
    physics2DManager->AddPhysicsComponent(e5, false, 1.f, 150.f);

    //foreground of parallax
    Entity e3{ ECS::CreateEntity() };
    mEntities.insert(e3);
    e3.AddComponent(Transform{ {width, height}, 0, {0,0} },
        Sprite{ Color{0,255,0,255}, SPRITE::TEXTURE, 0, 2 },
        General{ "foreground", TAG::PASSENGER, SUBTAG::NOSUBTAG, true });
    spriteManager->SetTexture(e3, "Textures\\Background\\foreground.png");
    physics2DManager->AddPhysicsComponent(e3, false, 1.f, 300.f);
    Entity e6{ ECS::CreateEntity() };
    mEntities.insert(e6);
    e6.AddComponent(Transform{ {width, height}, 0, {width,0} },
        Sprite{ Color{0,255,0,255}, SPRITE::TEXTURE, 0, 2 },
        General{ "foreground1", TAG::PASSENGER, SUBTAG::NOSUBTAG, true });
    spriteManager->SetTexture(e6, "Textures\\Background\\foreground.png");
    physics2DManager->AddPhysicsComponent(e6, false, 1.f, 300.f);
    /*************************************Parallax End************************************/

    /*************************************Spritesheet Multiple Animation Start************************************/
    //sprite changing 
    Entity e7{ ECS::CreateEntity() };
    mEntities.insert(e7);
    e7.AddComponent(Transform{ {96*2,96*2}, 0, {50, -100} },
        Sprite{ Color{0,255,0,255}, SPRITE::TEXTURE, 0, 10 },
        SheetAnimation{ 6, 0, 0.1f },
        General{ "spritesheet", TAG::PASSENGER, SUBTAG::NOSUBTAG, true },
        RectCollider{{0,0},{1,1},true});
    spriteManager->SetTexture(e7, "Textures\\Spritesheets\\Woodcutter_run.png");
    /*************************************Spritesheet Multiple Animation End************************************/

    /*************************************Debug Drawings Start************************************/
    Entity e8{ ECS::CreateEntity() };
    mEntities.insert(e8);
    e8.AddComponent(Transform{ {0, 0}, 0, {200, 200} },
        Sprite{ Color{0,255,0,255}, SPRITE::DEBUG_POINT, 0, 255 },
        General{ "point", TAG::OTHERS, SUBTAG::NOSUBTAG, true });

    Entity e9{ ECS::CreateEntity() };
    mEntities.insert(e9);
    e9.AddComponent(Transform{ {100, 0}, 0, {250, 200} },
        Sprite{ Color{0,255,0,255}, SPRITE::DEBUG_LINE, 0, 255 },
        General{ "line", TAG::OTHERS, SUBTAG::NOSUBTAG, true });

    Entity e10{ ECS::CreateEntity() };
    mEntities.insert(e10);
    e10.AddComponent(Transform{ {100, 100}, 0, {400, 200} },
        Sprite{ Color{0,255,0,255}, SPRITE::DEBUG_SQUARE, 0, 255 },
        General{ "square", TAG::OTHERS, SUBTAG::NOSUBTAG, true });

    Entity e11{ ECS::CreateEntity() };
    mEntities.insert(e11);
    e11.AddComponent(Transform{ {100, 100}, 0, {550, 200} },
        Sprite{ Color{0,255,0,255}, SPRITE::DEBUG_CIRCLE, 0, 255 },
        General{ "circle", TAG::OTHERS, SUBTAG::NOSUBTAG, true });
    /*************************************Debug Drawings End************************************/
}

void ParallaxAndSpriteSwap::Update() {
    static bool isjump = false;
    if (Input::CheckKey(E_STATE::PRESS, E_KEY::ENTER))
        ASSERT(1 == 1, "1 is equal to 1!!!");
    if (Input::CheckKey(E_STATE::PRESS, E_KEY::RIGHT_SHIFT))
        THROW(Logger::E_EXCEPTION::RUNTIME_ERR, "Right shift is pressed!!!");

    for (const Entity& e : mEntities)
    {
        if (e.GetComponent<Transform>().translation.x >= Application::getWindowWidth())
            e.GetComponent<Transform>().translation.x = (float)-Application::getWindowWidth();

        if (e.GetComponent<General>().name == "spritesheet")
        {
            /*************************************Multiple Animations Start************************************/
            if (Input::CheckKey(E_STATE::PRESS, E_KEY::SPACE))
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
            /*************************************Multiple Animations End************************************/

            /*************************************Scale and Rotate Sprite Start************************************/
            if (Input::CheckKey(E_STATE::HOLD, E_KEY::UP))
                e.GetComponent<Transform>().scale += 1.f;
            if (Input::CheckKey(E_STATE::HOLD, E_KEY::DOWN))
                e.GetComponent<Transform>().scale -= 1.f;
            if (Input::CheckKey(E_STATE::HOLD, E_KEY::LEFT))
                e.GetComponent<Transform>().rotation += 0.1f;
            if (Input::CheckKey(E_STATE::HOLD, E_KEY::RIGHT))
                e.GetComponent<Transform>().rotation -= 0.1f;
            /*************************************Scale and Rotate Sprite End************************************/

            /*************************************Collider Edit Start************************************/
            if (Input::CheckKey(E_STATE::HOLD, E_KEY::W))
                e.GetComponent<RectCollider>().centerOffset.y += 1.f;
            if (Input::CheckKey(E_STATE::HOLD, E_KEY::S))
                e.GetComponent<RectCollider>().centerOffset.y -= 1.f;
            if (Input::CheckKey(E_STATE::HOLD, E_KEY::A))
                e.GetComponent<RectCollider>().centerOffset.x -= 1.f;
            if (Input::CheckKey(E_STATE::HOLD, E_KEY::D))
                e.GetComponent<RectCollider>().centerOffset.x += 1.f;

            if (Input::CheckKey(E_STATE::HOLD, E_KEY::I))
                e.GetComponent<RectCollider>().scaleOffset.y += 0.02f;
            if (Input::CheckKey(E_STATE::HOLD, E_KEY::K))
                e.GetComponent<RectCollider>().scaleOffset.y -= 0.02f;
            if (Input::CheckKey(E_STATE::HOLD, E_KEY::J))
                e.GetComponent<RectCollider>().scaleOffset.x -= 0.02f;
            if (Input::CheckKey(E_STATE::HOLD, E_KEY::L))
                e.GetComponent<RectCollider>().scaleOffset.x += 0.02f;
            /*************************************Collider Edit End************************************/
        }
    }
    physics2DManager->Update(FPSManager::dt);
    //collision2DManager->Update(mEntities);
    sheetAnimator->Animate();
}

void ParallaxAndSpriteSwap::Draw() {
    renderManager->Render();
}

void ParallaxAndSpriteSwap::Free() {
    for (auto& e : mEntities)
        e.Destroy();
    mEntities.clear();
}

void ParallaxAndSpriteSwap::Unload() {
    renderManager->Clear();
    spriteManager->FreeTextures();
    FREE_RESOURCES();
}
