/*!*****************************************************************************
\file GameState2.cpp
\author Jazz Teoh Yu Jue
\par DP email: j.teoh\@digipen.edu
\par Group: Memory Leak Studios
\date 24-09-2022
\brief
Game state for testing physics
*******************************************************************************/
#include "GameState2.h"
#include "ECSManager.h"



void GameState2::Load() {
    INIT_TEXTURES("Sprites");
    for (size_t index = 0; index < GET_RESOURCES().size(); ++index)
        spriteManager->InitializeTexture(GET_TEXTURE_DATA(index));
}

void GameState2::Init() {
    int i = 2500;
    while (i--)
    {
        Entity e1{ ECS::CreateEntity() };
        e1.AddComponent(Transform{ {64,64}, 0, {-100, 0} },
            Sprite{ Color{0,255,0,255}, SPRITE::TEXTURE, 0, 10 },
            General{ "count" + i, TAG::PASSENGER, SUBTAG::NOSUBTAG, true });
    }
}

void GameState2::Update() {

}

void GameState2::Draw() {

}

void GameState2::Free() {

}

void GameState2::Unload() {

}





