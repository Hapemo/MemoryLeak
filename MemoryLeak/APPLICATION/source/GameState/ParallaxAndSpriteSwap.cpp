/*!*****************************************************************************
\file ParallaxAndSpriteSwap.cpp
\author Kew Yu Jun
\par DP email: k.yujun\@digipen.edu
\par Group: Memory Leak Studios
\date 31-10-2022
\brief
Game state for testing background and sprite changes
*******************************************************************************/
#include "ParallaxAndSpriteSwap.h"
#include "ECSManager.h"
#include "Application.h"
#include "Input.h"
#include "Logger.h"

void ParallaxAndSpriteSwap::Load() {
    LoadWithGUID(16673599440027908);
}

void ParallaxAndSpriteSwap::Init() {
    for (Scene* scenePtr : mScenes)
        scenePtr->Init();
}

void ParallaxAndSpriteSwap::Update() {
    for (Scene* scenePtr : mScenes)
        scenePtr->PrimaryUpdate();
    static bool isjump = false;

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
    //collision2DManager->Update(mEntities);
}

void ParallaxAndSpriteSwap::Draw() {
    renderManager->Render();
}

void ParallaxAndSpriteSwap::Free() {
    for (auto& scenePtr : mScenes)
        scenePtr->Exit();
}

void ParallaxAndSpriteSwap::Unload() {}
