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
    LoadWithGUID(16673097090400516);
    renderManager->SetVectorLengthModifier(5.f);
    renderManager->SetDebug(true);
}

void ScriptingDemo::Init() {
    for (Scene* scenePtr : mScenes)
        scenePtr->Init();

    size_t i = 0;
    for (Entity e : mEntities) {
        if (i == 0)
            e.AddComponent<Script>(Script({ "RotateScript", nullptr }));
        else if (i == 1)
            e.AddComponent<Script>(Script({ "ScaleScript", nullptr }));
        ++i;
    }
}

void ScriptingDemo::Update() {
    for (Scene* scenePtr : mScenes)
        scenePtr->PrimaryUpdate();
}

void ScriptingDemo::Draw() {
    renderManager->Render();
}

void ScriptingDemo::Free() {
    for (auto& scenePtr : mScenes)
        scenePtr->Exit();
}

void ScriptingDemo::Unload() {
}
