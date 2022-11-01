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

Entity firstEntity{};
Entity secondEntity{};
//ScriptComponent testBaseScript;
TestScript firstTestScript;
TestScript2 secondTestScript;

void ScriptingDemo::Load() {
    LoadWithGUID(16673097090400516);
    renderManager->SetVectorLengthModifier(5.f);
    renderManager->SetDebug(true);
}

void ScriptingDemo::Init() {
    for (Scene* scenePtr : mScenes)
        scenePtr->Init();
    int i = 0;
    for (Entity e : mEntities)
    {
        if (i == 0)
        {
            e.AddComponent<Script>(Script({ "TestScript", &firstTestScript }));
        }
        else if (i == 1)
        {
            e.AddComponent<Script>(Script({ "TestScript2", &secondTestScript }));
        }
        i++;
    }
   /* firstEntity = ECS::CreateEntity();
    secondEntity = ECS::CreateEntity();

    firstEntity.AddComponent<General>(General{ "firstEntity", TAG::OTHERS, SUBTAG::OTHERS, true, false });
    firstEntity.AddComponent<Script>(Script({ "TestScript", &firstTestScript }));
    firstEntity.AddComponent<Transform>(Transform{ {200, 80}, 0, { 0, -100 } });
    firstEntity.AddComponent<Sprite>(Sprite{ Color{0, 255, 0, 255}, SPRITE::TEXTURE, 0, 10 });

    secondEntity.AddComponent<General>(General{ "secondEntity", TAG::OTHERS, SUBTAG::OTHERS, true, false });
    secondEntity.AddComponent<Script>(Script({ "TestScript2", &secondTestScript }));
    secondEntity.AddComponent<Transform>(Transform{ {200, 80}, 0, { 0, 100 } });
    secondEntity.AddComponent<Sprite>(Sprite{ Color{0, 255, 0, 255}, SPRITE::TEXTURE, 0, 10 });

    spriteManager->SetTexture(firstEntity, "Textures\\Icons\\backBtn.png");
    spriteManager->SetTexture(secondEntity, "Textures\\Icons\\backBtn.png");*/

    logicSystem->Init();
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
    for (auto& scenePtr : mScenes)
        scenePtr->Exit();
    logicSystem->Exit();
    firstEntity.Destroy();
    secondEntity.Destroy();
    ECS::DestroyAllEntities();
}

void ScriptingDemo::Unload() {
    renderManager->Clear();
    //spriteManager->FreeTextures();
    //FREE_RESOURCES();
}
