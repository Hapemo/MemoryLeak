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
    serializationManager->LoadScene("SceneJPhysics");
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





