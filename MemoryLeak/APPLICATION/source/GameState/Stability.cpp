/*!*****************************************************************************
\file Stability.cpp
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 02-11-2022
\brief
\brief
Game state for testing 2500 objects stability.

*******************************************************************************/
#include "Stability.h"
#include "Application.h"

void Stability::Load() {
}

void Stability::Init() {
    /*************************************2550 Objects Start************************************/
     int entityCount = 1000;
     int width = Application::getWindowWidth() >> 1;
     int height = Application::getWindowHeight() >> 1;

     while (entityCount--)
     {
         float tempx = (float)((-width + (std::rand() % (width * 2 + 1))));
         float tempy = (float)((-height + (std::rand() % (height * 2 + 1))));

         /*******************if random number is outside of screen, crash**************/
         /*******************ensures that everything is rendered in the screen!!*******/
         if (tempx > width || tempx < -width)
             std::exit(EXIT_FAILURE);
         if (tempy > height || tempy < -height)
             std::exit(EXIT_FAILURE);

         Entity e1{ ECS::CreateEntity() };
         e1.AddComponent(Transform{ {200, 80}, 0, {tempx, tempy}},
             Sprite{ Color{0,255,0,255}, SPRITE::TEXTURE, 0, 10 },
             General{ "count " + std::to_string(entityCount), TAG::OTHERS, SUBTAG::NOSUBTAG, true });

         if (entityCount % 2)
             e1.AddComponent<Script>(Script({ "RotateScript", nullptr }));
         else if (entityCount % 2 == 0)
             e1.AddComponent<Script>(Script({ "ScaleScript", nullptr }));

         spriteManager->SetTexture(e1, "Textures\\Icons\\backBtn.png");
     }
    /*************************************2550 Objects End************************************/
     logicSystem->Init();
}

void Stability::Update() {
    logicSystem->Update();
}

void Stability::Draw() {
    renderManager->Render();
}

void Stability::Free() {
    logicSystem->Exit();
}

void Stability::Unload() {
}
