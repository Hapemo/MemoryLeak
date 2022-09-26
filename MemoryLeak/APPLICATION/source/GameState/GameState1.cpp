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

void GameState1::Load() {
    INIT_TEXTURES("Spritesheets");
    for (size_t index = 0; index < GET_RESOURCES().size(); ++index)
        spriteManager->InitializeTexture(GET_TEXTURE_DATA(index));
    renderManager->SetVectorLengthModifier(5.f);
    renderManager->SetDebug(true);
}

void GameState1::Init() {
    Entity e1{ ECS::CreateEntity() };
    mEntities.insert(e1);
    e1.AddComponent(Transform{ {64,64}, 0, {-100, 0} },
        Sprite{ Color{0,255,0,255}, SPRITE::TEXTURE, 0, 10 },
        SheetAnimation{ 4, 0, 0.1f },
        General{ "robot 1", TAG::PASSENGER, SUBTAG::NOSUBTAG, true },
        Audio{ Sound{"DAMAGE.wav", true}, false });

    spriteManager->SetTexture(e1, "Textures\\Spritesheets\\jumppadSheet.png");
    physics2DManager->AddPhysicsComponent(e1, 1.f, 50.f, 0.f, true);
    //collision2DManager->AddRectColliderComponent(e1, Math::Vec2{0.f, 0.f}, Math::Vec2{1.f, 1.f}, true);
    collision2DManager->AddCircleColliderComponent(e1, Math::Vec2{ 0.f, 0.f }, 1.f, true);
	
    Entity e2{ ECS::CreateEntity() };
    mEntities.insert(e2);
    e2.AddComponent(Transform{ {64,64}, 0, {100, 0} },
        Sprite{ Color{0,255,0,255}, SPRITE::TEXTURE, 0, 10 },
        SheetAnimation{ 6, 0, 0.1f },
        General{ "robot 2", TAG::PASSENGER, SUBTAG::NOSUBTAG, true },
        Audio{ Sound{"DAMAGE.wav", true}, false });
    spriteManager->SetTexture(e2, "Textures\\Spritesheets\\walkingSheet.png");
    physics2DManager->AddPhysicsComponent(e2, 10.f, 50.f, glm::pi<float>(), true);
    //collision2DManager->AddRectColliderComponent(e2, Math::Vec2{0.f, 0.f}, Math::Vec2{1.f, 1.f}, true);
    collision2DManager->AddCircleColliderComponent(e2, Math::Vec2{ 0.f, 0.f }, 1.f, true);
    
}

void GameState1::Update() {
    TRACK_PERFORMANCE("Physics");
    physics2DManager->Update(FPSManager::dt);
    collision2DManager->Update(mEntities);
    END_TRACK("Physics");
    sheetAnimator->Animate();
}

void GameState1::Draw() {
    renderManager->Render();
    //renderManager->RenderDebug();
}

void GameState1::Free() {
    physics2DManager->PhyObjListClear();
	
    for (auto& e : mEntities)
        e.Destroy();
    mEntities.clear();
}

void GameState1::Unload() {
    renderManager->Clear();
    spriteManager->FreeTextures();
    FREE_RESOURCES();
}





