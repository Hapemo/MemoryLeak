/*!*****************************************************************************
\file ScriptingDemo.cpp
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 01-11-2022
\brief
Gamestate for testing scripting.
*******************************************************************************/

#include "ScriptingDemo.h"

void ScriptingDemo::Load() {
    serializationManager->LoadScene("Scene_Scripting");
    renderManager->SetDebug(true);
}

void ScriptingDemo::Init() {
    for (Scene* scenePtr : mScenes)
        scenePtr->Init();
    //logicSystem->Init();
}

void ScriptingDemo::Update() {
    for (Scene* scenePtr : mScenes)
        scenePtr->PrimaryUpdate();
    //logicSystem->Update();
}

void ScriptingDemo::Draw() {
    renderManager->Render();
}

void ScriptingDemo::Free() {
    //logicSystem->Exit();
    for (auto& scenePtr : mScenes)
        scenePtr->Exit();
}

void ScriptingDemo::Unload() {
    ECS::DestroyAllEntities();
}
