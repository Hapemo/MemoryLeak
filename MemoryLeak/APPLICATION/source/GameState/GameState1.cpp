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
//    serializationManager->LoadScene("SceneJPhysics");
//    float entityTransformPosY{ static_cast<float>(Application::getWindowHeight()) / 2.f - 128.f };
//// -----------------------------
//// Rect vs Rect Collision Test
//// -----------------------------
//    Entity e1{ ECS::CreateEntity() };
//    //mEntities.insert(e1);
//// Modify entity position scale and rotation here
//    e1.AddComponent(Transform{ Math::Vec2{64,64}, 0, Math::Vec2{-100, entityTransformPosY} },
//        Sprite{ Color{0,255,0,255}, SPRITE::TEXTURE, 0, 10 },
//        SheetAnimation{ 4, 0, 0.1f },
//        General{ "Rect1", TAG::PASSENGER, SUBTAG::NOSUBTAG, true },
//        Audio{ Sound{"DAMAGE.wav", true}, false });
//    spriteManager->SetTexture(e1, "Textures\\Spritesheets\\jumppadSheet.png");
//    e1.AddComponent<Physics2D>({ false,  1.f, 50.f, 0.f, Math::Vec2{0, 0}, Math::Vec2{0, 0}, true });
//    e1.AddComponent<RectCollider>({ Math::Vec2{0.f, 0.f}, Math::Vec2{1.f, 1.f}, true });
//// Modify physics / collision components here
//    //physics2DManager->AddPhysicsComponent(e1, false, 1.f, 50.f, 0.f, true);
//    //collision2DManager->AddRectColliderComponent(e1, Math::Vec2{0.f, 0.f}, Math::Vec2{1.f, 1.f}, true);
//    
//    Entity e2{ ECS::CreateEntity() };
//    //mEntities.insert(e2);
//// Modify entity position scale and rotation here
//    e2.AddComponent(Transform{ Math::Vec2{64,64}, 0, Math::Vec2{100, entityTransformPosY} },
//        Sprite{ Color{0,255,0,255}, SPRITE::TEXTURE, 0, 10 },
//        SheetAnimation{ 6, 0, 0.1f },
//        General{ "Rect2", TAG::PASSENGER, SUBTAG::NOSUBTAG, true },
//        Audio{ Sound{"DAMAGE.wav", true}, false });
//    spriteManager->SetTexture(e2, "Textures\\Spritesheets\\walkingSheet.png");
//    e2.AddComponent<Physics2D>({ false, 5.f, 50.f, glm::pi<float>(), Math::Vec2{0, 0}, Math::Vec2{0, 0}, true });
//    e2.AddComponent<RectCollider>({ Math::Vec2{0.f, 0.f}, Math::Vec2{1.f, 1.f}, true });
//// Modify physics / collision components here
//    //physics2DManager->AddPhysicsComponent(e2, false, 5.f, 50.f, glm::pi<float>(), true);
//    //collision2DManager->AddRectColliderComponent(e2, Math::Vec2{0.f, 0.f}, Math::Vec2{1.f, 1.f}, true);
//
//    entityTransformPosY = static_cast<float>(Application::getWindowHeight()) / 2.f - 128.f * 2.f;
//// ---------------------------------
//// Circle vs Circle Collision Test
//// ---------------------------------
//    Entity e3{ ECS::CreateEntity() };
//    //mEntities.insert(e3);
//// Modify entity position scale and rotation here
//    e3.AddComponent(Transform{ Math::Vec2{64,64}, 0, Math::Vec2{-100, entityTransformPosY} },
//        Sprite{ Color{0,255,0,255}, SPRITE::TEXTURE, 0, 10 },
//        SheetAnimation{ 4, 0, 0.1f },
//        General{ "Circle1", TAG::PASSENGER, SUBTAG::NOSUBTAG, true },
//        Audio{ Sound{"DAMAGE.wav", true}, false });
//    spriteManager->SetTexture(e3, "Textures\\Spritesheets\\jumppadSheet.png");
//
//// Modify physics / collision components here
//    physics2DManager->AddPhysicsComponent(e3, false, 1.f, 50.f, 0.f, true);
//    collision2DManager->AddCircleColliderComponent(e3, Math::Vec2{ 0.f, 0.f }, 1.f, true);
//    
//    Entity e4{ ECS::CreateEntity() };
//    //mEntities.insert(e4);
//// Modify entity position scale and rotation here
//    e4.AddComponent(Transform{ Math::Vec2{64,64}, 0, Math::Vec2{100, entityTransformPosY} },
//        Sprite{ Color{0,255,0,255}, SPRITE::TEXTURE, 0, 10 },
//        SheetAnimation{ 6, 0, 0.1f },
//        General{ "Circle2", TAG::PASSENGER, SUBTAG::NOSUBTAG, true },
//        Audio{ Sound{"DAMAGE.wav", true}, false });
//    spriteManager->SetTexture(e4, "Textures\\Spritesheets\\walkingSheet.png");
//
//// Modify physics / collision components here
//    physics2DManager->AddPhysicsComponent(e4, false, 5.f, 50.f, glm::pi<float>(), true);
//    collision2DManager->AddCircleColliderComponent(e4, Math::Vec2{ 0.f, 0.f }, 1.f, true);
//    
// -----------------------------
// Player Movement Test
// -----------------------------
    Entity e5{ ECS::CreateEntity() };
    //mEntities.insert(e5);
// Modify entity position scale and rotation here
    e5.AddComponent(Transform{ Math::Vec2{64,64}, 0, Math::Vec2{0, 0} },
                    Sprite{ Color{0,255,0,255}, SPRITE::TEXTURE, 0, 10 },
                    SheetAnimation{ 6, 0, 0.1f },
                    General{ "Player", TAG::PASSENGER, SUBTAG::NOSUBTAG, true },
                    Audio{ Sound{"DAMAGE.wav", true}, false });
    spriteManager->SetTexture(e5, "Textures\\Spritesheets\\walkingSheet.png");
    physics2DManager->AddPhysicsComponent(e5, false, 1.f, 0.f, 0.f, true);
    e5.AddComponent(PlayerTmp{ 0 });

    //serializationManager->SaveScene("SceneJPhysics");
}

void GameState1::Update() {
        playerManager->Update(FPSManager::dt);
        TRACK_PERFORMANCE("Physics");
        physics2DManager->Update(FPSManager::dt);
        END_TRACK("Physics");
        sheetAnimator->Animate();
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





