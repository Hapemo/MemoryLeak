/*!*****************************************************************************
\file Start_1.cpp
\author Jazz Teoh Yu Jue
\par DP email: j.teoh\@digipen.edu
\par Group: Memory Leak Studios
\date 24-09-2022
\brief
First scene created.
*******************************************************************************/
#pragma once
#include "pch.h"
#include "Start_1.h"
#include "AI.h"
#include "Helper.h"
#include "PerformanceVisualiser.h"
Entity e8;
void Start_1::Init() {


  serializationManager->LoadScene("SceneJ");
    //Entity e{ ECS::CreateEntity() };
    //mEntities.insert(e);
    //e.AddComponent(Transform{ {150,150}, 0, {0,0} },
    //               Sprite{ Color{0,255,0,100}, SPRITE::CIRCLE, 0 , 18});
    //std::string name = "object " + std::to_string(1);
    //e.AddComponent(Stuff());
    //e.AddComponent<General>({ name, TAG::OTHERS, SUBTAG::NOSUBTAG, true });
    //Entity e1{ ECS::CreateEntity() };
    //mEntities.insert(e1);
    //e1.AddComponent(Transform{ {150,150}, 0, {0,100} },
    //    Sprite{ Color{255,0,0,255}, SPRITE::CIRCLE, 0 , 17 });
    //std::string name1 = "object " + std::to_string(2);
    //e1.AddComponent(Stuff());
    //e1.AddComponent<General>({ name1, TAG::OTHERS, SUBTAG::NOSUBTAG, true });
  //int count{ 2500 };
  //while (count--) {
    //Entity e{ ECS::CreateEntity() };
    //mEntities.insert(e);
    //e.AddComponent(Transform{ {150,150}, 0, {0,0} },
    //    Sprite{ Color{0,255,0,255}, SPRITE::SQUARE, 0 , 18 });
    //std::string name = "object " + std::to_string(1);
    //e.AddComponent(Stuff());
    //e.AddComponent<General>({ name, TAG::OTHERS, SUBTAG::NOSUBTAG, true });
    //
    //Entity e1{ ECS::CreateEntity() };
    //mEntities.insert(e1);
    //e1.AddComponent(Transform{ {150,150}, 2, {300,0} },
    //    Sprite{ Color{0,255,0,255}, SPRITE::SQUARE, 0 , 18 });
    //std::string name1 = "object " + std::to_string(1);
    //e1.AddComponent(Stuff());
    //e1.AddComponent<General>({ name1, TAG::OTHERS, SUBTAG::NOSUBTAG, true });
  //  //set one of the entities as texture!
  //}
  renderManager->SetVectorLengthModifier(5.f);
  renderManager->SetDebug(true);

  //Entity e1{ ECS::CreateEntity() };
  //mEntities.insert(e1);
  //e1.AddComponent(Transform{ {64,64}, 0, {-Application::getWindowWidth() / 2 + 32, Application::getWindowHeight()/2-32}},
  //    Sprite{ Color{0,255,0,255}, SPRITE::TEXTURE, 0, 10 },
  //    SheetAnimation{ 4, 0, 0.1f },
  //    General{ "robot yeet", TAG::PASSENGER, SUBTAG::NOSUBTAG, true },
  //    CircleCollider{ {0,0},1, true },
  //    RectCollider{ {0,0},{1,1}, true });
  //spriteManager->SetTexture(e1, "Textures\\Spritesheets\\jumppadSheet.png");
  //physics2DManager->AddPhysicsComponent(e1, 0.f, 60.f, 0.f, true);
  ////physics2DManager->AddRectColliderComponent(e1, glm::vec2{ 0.f, 0.f }, glm::vec2{ 1.f, 1.f }, true);
  ////physics2DManager->AddCircleColliderComponent(e1, glm::vec2{ 0.f, 0.f }, 1.f, true);

  //Entity e2{ ECS::CreateEntity() };
  //mEntities.insert(e2);
  //e2.AddComponent(Transform{ {64,64}, 0, {-Application::getWindowWidth() / 2 + 96, Application::getWindowHeight() / 2-32} },
  //    Sprite{ Color{0,255,0,255}, SPRITE::TEXTURE, 0, 10 },
  //    SheetAnimation{ 6, 0, 0.1f },
  //    General{ "robot 4", TAG::PASSENGER, SUBTAG::NOSUBTAG, true });
  //spriteManager->SetTexture(e2, "Textures\\Spritesheets\\walkingSheet.png");


  //Entity e3{ ECS::CreateEntity() };
  //mEntities.insert(e3);
  //e3.AddComponent(Transform{ {64,64}, 0, {-Application::getWindowWidth() / 2 + 96+64, Application::getWindowHeight() / 2-32} },
  //    Sprite{ Color{0,255,0,255}, SPRITE::TEXTURE, 0, 10 },
  //    SheetAnimation{ 4, 0, 0.1f },
  //    General{ "robot 4", TAG::PASSENGER, SUBTAG::NOSUBTAG, true });
  //spriteManager->SetTexture(e3, "Textures\\Spritesheets\\bridgeSheet.png");


  //Entity e4{ ECS::CreateEntity() };
  //mEntities.insert(e4);
  //e4.AddComponent(Transform{ {288,256}, 0, {-Application::getWindowWidth() / 2 + 200 + 175 + 256 + 144, Application::getWindowHeight() / 2 - 16 - 64 - 126} },
  //    Sprite{ Color{0,255,0,255}, SPRITE::TEXTURE, 0, 10 },
  //    SheetAnimation{ 22, 0, 0.1f },
  //    General{ "robot 4", TAG::PASSENGER, SUBTAG::NOSUBTAG, true });
  //spriteManager->SetTexture(e4, "Textures\\Spritesheets\\knight1.png");

  //Entity e5{ ECS::CreateEntity() };
  //mEntities.insert(e5);
  //e5.AddComponent(Transform{ {350,618}, 0, {-Application::getWindowWidth() / 2 + 200 + 175, Application::getWindowHeight() / 2 - 309} },
  //    Sprite{ Color{0,255,0,255}, SPRITE::TEXTURE, 0, 10 },
  //    SheetAnimation{ 8, 0, 0.1f },
  //    General{ "robot 4", TAG::PASSENGER, SUBTAG::NOSUBTAG, true });
  //spriteManager->SetTexture(e5, "Textures\\Spritesheets\\random1.png");

  //Entity e7{ ECS::CreateEntity() };
  //mEntities.insert(e7);
  //e7.AddComponent(Transform{ {288,256}, 0, {-Application::getWindowWidth() / 2 +200 + 175 + 256 +144, Application::getWindowHeight() / 2 - 16 - 64} },
  //    Sprite{ Color{0,255,0,255}, SPRITE::TEXTURE, 0, 10 },
  //    SheetAnimation{ 8, 0, 0.1f },
  //    General{ "robot 4", TAG::PASSENGER, SUBTAG::NOSUBTAG, true },
  //    RectCollider{ {0.f,0.f}, {1.f,1.f}, true });
  //spriteManager->SetTexture(e7, "Textures\\Spritesheets\\knight6.png");

  //e8= ECS::CreateEntity() ;
  //mEntities.insert(e8);
  //e8.AddComponent(Transform{ {288,256}, 0, {-Application::getWindowWidth() / 2 + 200 + 175 + 256 + 144+144, Application::getWindowHeight() / 2 - 16 - 64} },
  //    Sprite{ Color{0,255,0,255}, SPRITE::TEXTURE, 0, 10 },
  //    SheetAnimation{ 8, 0, 0.1f },
  //    General{ "robot 4", TAG::PASSENGER, SUBTAG::NOSUBTAG, true });
  //spriteManager->SetTexture(e8, "Textures\\Spritesheets\\knight6.png");

  //Entity e9 = ECS::CreateEntity();
  //mEntities.insert(e9);
  //e9.AddComponent(Transform{ {Application::getWindowWidth(),Application::getWindowHeight()}, 0, {0,0} },
  //    Sprite{ Color{0,255,0,255}, SPRITE::TEXTURE, 0, 0 },
  //    General{ "bgd 4", TAG::PASSENGER, SUBTAG::NOSUBTAG, true });
  //spriteManager->SetTexture(e9, "Textures\\Background\\background.png");

  //Entity e10 = ECS::CreateEntity();
  //mEntities.insert(e10);
  //e10.AddComponent(Transform{ {Application::getWindowWidth(),Application::getWindowHeight()}, 0, {0,0} },
  //    Sprite{ Color{0,255,0,255}, SPRITE::TEXTURE, 0, 1 },
  //    General{ "bgd 4", TAG::PASSENGER, SUBTAG::NOSUBTAG, true });
  //spriteManager->SetTexture(e10, "Textures\\Background\\middleground.png");

  //Entity e11 = ECS::CreateEntity();
  //mEntities.insert(e11);
  //e11.AddComponent(Transform{ {Application::getWindowWidth(),Application::getWindowHeight()}, 0, {0,0} },
  //    Sprite{ Color{0,255,0,255}, SPRITE::TEXTURE, 0, 2 },
  //    General{ "bgd 4", TAG::PASSENGER, SUBTAG::NOSUBTAG, true });
  //spriteManager->SetTexture(e11, "Textures\\Background\\foreground.png");
  //physics2DManager->AddPhysicsComponent(e2, 0.f, 60.f, glm::pi<float>(), true);
  ///*physics2DManager->AddRectColliderComponent(e2, glm::vec2{ 0.f, 0.f }, glm::vec2{ 1.f, 1.f }, true);
  //physics2DManager->AddCircleColliderComponent(e2, glm::vec2{ 0.f, 0.f }, 1.f, true);*/

  //levelEditor->LevelEditor::Init();
  /*transformManager->Init(); */

  Reset();
}

void Start_1::Update() {
  //for (auto& e : mEntities) {
  //    if (e.GetComponent<Stuff>().colorChange == 1)
  //      updateAIAllColors(e);
  //    else if (e.GetComponent<Stuff>().colorChange == 2)
  //      updateAITrafficLight(e);
  //    if (e.GetComponent<Stuff>().movement == 1)
  //      updateAIUpDown(e, e.GetComponent<Stuff>().speed, e.GetComponent<Stuff>().range);
  //    else if (e.GetComponent<Stuff>().movement == 2)
  //      updateAILeftRight(e, e.GetComponent<Stuff>().speed, e.GetComponent<Stuff>().range);
  //    else if (e.GetComponent<Stuff>().movement == 3)
  //      updateAISwing(e, e.GetComponent<Stuff>().speed, e.GetComponent<Stuff>().range);
  //    else if (e.GetComponent<Stuff>().movement == 4)
  //      updateAICircle(e, e.GetComponent<Stuff>().speed, e.GetComponent<Stuff>().range);
  //}

  /*static float timer = 0;
  timer += Helper::dt;
  if (timer >= 2.2f)
  {
      if (spriteManager->GetTexturePath(e8.GetComponent<Sprite>().texture) == "Textures\\Spritesheets\\knight6.png")
      {
          spriteManager->SetTexture(e8, "Textures\\Spritesheets\\knight1.png");
          e8.GetComponent<SheetAnimation>().frameCount = 22;
          e8.GetComponent<SheetAnimation>().currFrameIndex = 0;
      }
      else
      {
          spriteManager->SetTexture(e8, "Textures\\Spritesheets\\knight6.png");
          e8.GetComponent<SheetAnimation>().frameCount = 8;
          e8.GetComponent<SheetAnimation>().currFrameIndex = 0;

      }
      timer = 0;
  }*/
  //renderManager->Render();
  //renderManager->RenderDebug();
  //TRACK_PERFORMANCE("Physics");
  physics2DManager->Update(FPSManager::dt);
  //END_TRACK("Physics");

  ControlEntityLifespan(mEntities, A);
}

void Start_1::Reset() {
  std::cout << " Start_1 Reset() called\n";
}

void Start_1::Clear() {
    physics2DManager->PhyObjListClear();
    for (auto& e : mEntities)
        e.Destroy();
    //levelEditor->exit();
}

void Start_1::ControlEntityLifespan(std::set<Entity> entities, KEY key) {
  if (Input::CheckKey(HOLD, key)) {
    if (Input::CheckKey(PRESS, LEFT_SHIFT))
      lifespanManager->Reset(entities);
    else
      for (const Entity& e : entities) {
        std::cout << "EntityID: " << std::setw(4) << std::right << e.id;
        std::cout << " | Lifespan: " << std::setprecision(4) << std::setw(6) << std::right << e.GetComponent<Lifespan>().lifetime;
        std::cout << " | isActive: " << e.GetComponent<General>().isActive << '\n';
      }
  }
}



