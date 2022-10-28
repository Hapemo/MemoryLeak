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
  //ResourceManager::GetInstance()->LoadAllResources();
  //for (size_t index = 0; index < GET_RESOURCES().size(); ++index)
  //  spriteManager->InitializeTexture(GET_TEXTURE_DATA(index));
  renderManager->SetVectorLengthModifier(5.f);
  renderManager->SetDebug(true);
  LoadWithGUID(16667121456447749);
}

void GameState1::Init() {
  for (Scene* scenePtr : mScenes)
    scenePtr->Init();
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
    
    TestScript::StartScript(const_cast<Entity*>(&(*(mEntities.begin()))));
}

void GameState1::Update() {
  for (Scene* scenePtr : mScenes)
    scenePtr->PrimaryUpdate();
  //if (Input::CheckKey(E_STATE::PRESS, E_KEY::P))
  //  for (auto const& e : mEntities) {
  //    Lifespan lifespan = e.GetComponent<Lifespan>();
  //    printf("Lifespan: %f, %f\n", lifespan.lifetime, lifespan.limit);
  //  }

  //if (Input::CheckKey(E_STATE::PRESS, E_KEY::U)) {
  //  Lifespan ls = (mEntities.begin())->GetComponent<Lifespan>();
  //  ls.lifetime += 1;
  //  ls.limit += 2;
  //  pref.UpdateComponent(ls);
  //}

  //if (Input::CheckKey(E_STATE::PRESS, E_KEY::D)) {
  //  ECS::DestroyEntity(11);
  //  mEntities.erase(Entity{ 11 });
  //}

}

void GameState1::Draw() {
  renderManager->Render();
  //renderManager->RenderDebug();
}

void GameState1::Free() {
  for (auto& scenePtr : mScenes)
    scenePtr->Exit();
}

void GameState1::Unload() {
  renderManager->Clear();
  UnloadWithGUID();
  //spriteManager->FreeTextures();
  //ResourceManager::GetInstance()->UnloadAllResources();
  //FREE_RESOURCES();
}





