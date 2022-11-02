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
        }
    }
}

void ParallaxAndSpriteSwap::Draw() {
    renderManager->Render();
}

void ParallaxAndSpriteSwap::Free() {
    for (auto& scenePtr : mScenes)
        scenePtr->Exit();
}

void ParallaxAndSpriteSwap::Unload() {}
