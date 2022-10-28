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
#include "Input.h"
#include "TestScript.h"

void GameState1::Load() {
    LOAD_TEXTURES("Background");
    LOAD_TEXTURES("Icons");
    LOAD_TEXTURES("Menu");
    LOAD_TEXTURES("Sprites");
    LOAD_TEXTURES("Spritesheets");
    ResourceManager::GetInstance()->LoadAllResources();
    for (size_t index = 0; index < GET_RESOURCES().size(); ++index)
        spriteManager->InitializeTexture(GET_TEXTURE_DATA(index));
    renderManager->SetVectorLengthModifier(5.f);
    renderManager->SetDebug(true);
}

void GameState1::Init() {
    //serializationManager->LoadScene("SceneJPhysics");
    //pref.AddComponent<Lifespan>({ 10.f, 2.f });

    int entityCount{ 10 };
    while (entityCount--) {
      mEntities.insert(pref.CreatePrefabee());
    }
    
    Entity e1{ ECS::CreateEntity() };
    e1.AddComponent(Transform{ {100, 100}, 0, {200, 100} },
        Sprite{ Color{0,255,0,0}, SPRITE::SQUARE, 0, 1 },
        General{ "TEXTBOX", TAG::OTHERS, SUBTAG::NOSUBTAG, true },
        Text{ "CaviarDreams.ttf", "Hello World!", Math::Vec2{0,0}, 1, {255, 0, 0, 255}, 0, 0 });

    Entity e2{ ECS::CreateEntity() };
    e2.AddComponent(Transform{ {100, 100}, 0, {200, 100} },
        Sprite{ Color{0,255,0,0}, SPRITE::SQUARE, 0, 1 },
        General{ "TEXTBOX", TAG::OTHERS, SUBTAG::NOSUBTAG, true },
        Text{ "3Dumb.ttf", "Hello World!", Math::Vec2{100,0}, 1, {255, 0, 0, 255}, 0, 0 });
    
    //TestScript::StartScript(const_cast<Entity*>(&(*(mEntities.begin()))));

    Entity e3{ ECS::CreateEntity() };
    e3.AddComponent(General{ "Rect1", TAG::PASSENGER, SUBTAG::NOSUBTAG, true });
    e3.AddComponent(Transform{ {150, 150}, 0, {0, 0} });
    e3.AddComponent(Sprite{ Color{0,255,0,255}, SPRITE::TEXTURE, 0, 10 });
    spriteManager->SetTexture(e3, "Textures\\Sprites\\mc.png");
    e3.AddComponent(Physics2D{ false, 100.0, true, 0.5, 1.0 / 0.5, 1.0, 1.0 / 1.0, 0.3, 0.3, 0.9, Math::Vec2{0.f, 0.f}, Math::Vec2{0.f, 0.f}, Math::Vec2{0.f, 0.f}, 0.0, 0.0, std::vector<Force>(), true });
    //physics2DManager->AddForce(e3, Math::Vec2{ 1.f, 0.f }, 50.0);
    //physics2DManager->AddForce(e3, Math::Vec2{ -1.f, 1.f }, 50.0);
    e3.AddComponent(PlayerTmp{});
}

void GameState1::Update() {
  if (Input::CheckKey(E_STATE::PRESS, E_KEY::P)) 
    for (auto const& e : mEntities) {
      Lifespan lifespan = e.GetComponent<Lifespan>();
      printf("Lifespan: %f, %f\n", lifespan.lifetime, lifespan.limit);
    }

  if (Input::CheckKey(E_STATE::PRESS, E_KEY::U)) {
    Lifespan ls = (mEntities.begin())->GetComponent<Lifespan>();
    ls.lifetime += 1;
    ls.limit += 2;
    pref.UpdateComponent(ls);
  }

  if (Input::CheckKey(E_STATE::PRESS, E_KEY::D)) {
    ECS::DestroyEntity(11);
    mEntities.erase(Entity{ 11 });
  }

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
    ResourceManager::GetInstance()->UnloadAllResources();
    FREE_RESOURCES();
}





