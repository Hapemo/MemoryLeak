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
    Application::SetEditorMode(true);

	serializationManager->LoadScene("SceneJUX");
}

void GameState3::Init() {
    //levelEditor->LevelEditor::Init(ptr_window, &window_width, &window_height);
    renderManager->RenderToFrameBuffer();
    Application::SetEditorMode(true);
    //editorManager->UnpauseEditor(); // for this game state showing editor only
}

void GameState3::Update() {

}

void GameState3::Draw() {
    renderManager->Render();
}

void GameState3::Free() {
    //serializationManager->SaveScene("SceneJUX");
    ECS::DestroyAllEntities();
    Application::SetEditorMode(false);
}

void GameState3::Unload() {
    //levelEditor->Exit();
    renderManager->RenderToScreen();
    renderManager->Clear();
    spriteManager->FreeTextures();
    FREE_RESOURCES();
}





