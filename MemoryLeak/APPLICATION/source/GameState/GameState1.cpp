/*!*****************************************************************************
\file GameState1.cpp
\author Jazz Teoh Yu Jue
\par DP email: j.teoh\@digipen.edu
\par Group: Memory Leak Studios
\date 24-09-2022
\brief
Game state for testing physics
*******************************************************************************/
#include "GameState1.h"
#include "Application.h"
void GameState1::Load() {
    LOAD_TEXTURES("Background");
    LOAD_TEXTURES("Icons");
    LOAD_TEXTURES("Menu");
    LOAD_TEXTURES("Sprites");
    LOAD_TEXTURES("Spritesheets");
    for (size_t index = 0; index < GET_RESOURCES().size(); ++index)
        spriteManager->InitializeTexture(GET_TEXTURE_DATA(index));
    renderManager->SetVectorLengthModifier(5.f);
    renderManager->SetDebug(true);
}

void GameState1::Init() {
    //serializationManager->LoadScene("SceneJPhysics");

    Entity e1{ ECS::CreateEntity() };
    e1.AddComponent(General{ "Rect1", TAG::PASSENGER, SUBTAG::NOSUBTAG, true });
    e1.AddComponent(Transform{ {150, 150}, 0, {0, 0} });
    e1.AddComponent(Sprite{ Color{0,255,0,255}, SPRITE::TEXTURE, 0, 10 });
    spriteManager->SetTexture(e1, "Textures\\Sprites\\mc.png");
    e1.AddComponent(Physics2D{ false, 100.0, true, 0.5, 1.0 / 0.5, 1.0, 1.0 / 1.0, 0.3, 0.3, 0.9, Math::Vec2{0.f, 0.f}, Math::Vec2{0.f, 0.f}, Math::Vec2{0.f, 0.f}, 0.0, 0.0, std::vector<Force>(), true });
    //physics2DManager->AddForce(e1, Math::Vec2{ 1.f, 0.f }, 50.0);
    //physics2DManager->AddForce(e1, Math::Vec2{ -1.f, 1.f }, 50.0);
}

void GameState1::Update() {
}

void GameState1::Draw() {
    renderManager->Render();
    //renderManager->RenderDebug();
}

void GameState1::Free() {
    ECS::DestroyAllEntities();
}

void GameState1::Unload() {
    renderManager->Clear();
    spriteManager->FreeTextures();
    FREE_RESOURCES();
}





