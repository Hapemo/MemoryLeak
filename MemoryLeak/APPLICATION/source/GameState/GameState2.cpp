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
#include "Application.h"



void GameState2::Load() {
    LOAD_TEXTURES("Sprites");
    for (size_t index = 0; index < GET_RESOURCES().size(); ++index)
        spriteManager->InitializeTexture(GET_TEXTURE_DATA(index));
}

void GameState2::Init() {
    //serializationManager->LoadScene("SceneJGraphics");
    int i = 4000;
    int width = Application::getWindowWidth() >> 1;
    int height = Application::getWindowHeight() >> 1;
    while (i--)
    {
        float tempx = (float)((-width + (std::rand() % (width * 2 + 1))));
        float tempy = (float)((-height + (std::rand() % (height * 2 + 1))));

        //if random number is outside of screen, crash
        //ensures that everything is rendered in the screen!!
        if (tempx > width || tempx < -width)
            std::exit(EXIT_FAILURE);
        if (tempy > height || tempy < -height)
            std::exit(EXIT_FAILURE);

        Entity e1{ ECS::CreateEntity() };
        e1.AddComponent(Transform{ {32,32}, 0, {tempx,tempy}},
            Sprite{ Color{0,255,0,255}, SPRITE::TEXTURE, 0, 10 },
            General{ "count" + i, TAG::PASSENGER, SUBTAG::NOSUBTAG, true });
        spriteManager->SetTexture(e1, "Textures\\Sprites\\jumppad1.png");
    }
}

void GameState2::Update() {

}

void GameState2::Draw() {
    renderManager->Render();
}

void GameState2::Free() {
    serializationManager->SaveScene("SceneJGraphics");
    ECS::DestroyAllEntities();
}

void GameState2::Unload() {
    renderManager->Clear();
    spriteManager->FreeTextures();
    FREE_RESOURCES();
}





