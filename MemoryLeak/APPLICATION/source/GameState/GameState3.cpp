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
#include "Application.h"

void GameState3::Load() {
    LOAD_TEXTURES("Background");
    LOAD_TEXTURES("Icons");
    LOAD_TEXTURES("Menu");
    LOAD_TEXTURES("Sprites");
    LOAD_TEXTURES("Spritesheets");
    for (size_t index = 0; index < GET_RESOURCES().size(); ++index)
        spriteManager->InitializeTexture(GET_TEXTURE_DATA(index));

	//serializationManager->LoadScene("SceneJPhysics");
}

void GameState3::Init() {
    //levelEditor->LevelEditor::Init(ptr_window, &window_width, &window_height);
    renderManager->RenderToFrameBuffer();
}

void GameState3::Update() {
    TRACK_PERFORMANCE("Physics");
    physics2DManager->Update(FPSManager::dt);
    END_TRACK("Physics");
    sheetAnimator->Animate();

    TRACK_PERFORMANCE("Editor");
    renderManager->RenderToFrameBuffer();
    levelEditor->LevelEditor::Window();
    levelEditor->LevelEditor::Update();
    END_TRACK("Editor");
}

void GameState3::Draw() {
    renderManager->Render();
}

void GameState3::Free() {
    ECS::DestroyAllEntities();
}

void GameState3::Unload() {
    //levelEditor->Exit();
    renderManager->RenderToScreen();
    renderManager->Clear();
    spriteManager->FreeTextures();
    FREE_RESOURCES();
}





