#include <GL/glew.h> // for access to OpenGL API declarations
#include <iostream>
#include <iomanip>

#include "Start.h"
#include "Input.h"
#include "Helper.h"

void PrintOrResetEntityLifespan(std::set<Entity> entities, KEY key);

void Start::Load() {

}

void Start::Init() {
  for (Entity& e : someEntities) {
    e = Coordinator::GetInstance()->CreateEntity();

    Lifespan lifespan{0,120};
    Coordinator::GetInstance()->AddComponent<Lifespan>(e,lifespan);
    Coordinator::GetInstance()->AddComponent<IsActive>(e, { true });
  }
  for (size_t i = 0; i < 5; ++i) {
    Entity e{ Coordinator::GetInstance()->CreateEntity() };
    entitiesA.insert(e);

    Lifespan lifespan{ 0,5 };
    Coordinator::GetInstance()->AddComponent<Lifespan>(e, lifespan);
    Coordinator::GetInstance()->AddComponent<IsActive>(e, { true });
  }
  for (size_t i = 0; i < 5; ++i) {
    Entity e{ Coordinator::GetInstance()->CreateEntity() };
    entitiesB.insert(e);

    Lifespan lifespan{ 0,10 };
    Coordinator::GetInstance()->AddComponent<Lifespan>(e, lifespan);
    Coordinator::GetInstance()->AddComponent<IsActive>(e, { true });
  }
  for (size_t i = 0; i < 5; ++i) {
    Entity e{ Coordinator::GetInstance()->CreateEntity() };
    entitiesC.insert(e);

    Lifespan lifespan{ 0,15 };
    Coordinator::GetInstance()->AddComponent<Lifespan>(e, lifespan);
    Coordinator::GetInstance()->AddComponent<IsActive>(e, { true });
  }
}

void Start::Update() {

  lifespanManager->Update((float)Helper::dt);
  // Prints all someEntities
  if (Input::checkKey(PRESS, SPACE))
    for (const Entity& e : someEntities) {
      std::cout << "Entity: " << std::setw(4) << std::right << e;
      std::cout << " | Lifespan: " << std::setw(4) << std::right << Coordinator::GetInstance()->GetComponent<Lifespan>(e).lifetime;
      std::cout << " | isActive: " << Coordinator::GetInstance()->GetComponent<IsActive>(e).isActive << '\n';
    }

  PrintOrResetEntityLifespan(entitiesA, A);
  PrintOrResetEntityLifespan(entitiesB, B);
  PrintOrResetEntityLifespan(entitiesC, C);


  static bool reverse{ false };
  static float color[3]{ 0, 1, 0 };

  if (!reverse) {
    if (color[0] < 1) color[0] += 0.001f;
    else if (color[1] < 1) color[1] += 0.001f;
    else if (color[2] < 1) color[2] += 0.001f;
    else reverse = true;
  }
  else {
    if (color[0] > 0) color[0] -= 0.001f;
    else if (color[1] > 0) color[1] -= 0.001f;
    else if (color[2] > 0) color[2] -= 0.001f;
    else reverse = false;
  }

  glClearColor(color[0], color[1], color[2], 1.f);
  
}

void Start::Draw() {

}

void Start::Free() {

}

void Start::Unload() {

}


void PrintOrResetEntityLifespan (std::set<Entity> entities, KEY key) {
  // Prints entitiesA
  if (Input::checkKey(HOLD, key))
    if (Input::checkKey(PRESS, LEFT_SHIFT))
      lifespanManager->Reset(entities);
    else
      for (const Entity& e : entities) {
        std::cout << "Entity: " << std::setw(4) << std::right << e;
        std::cout << " | Lifespan: " << std::setw(4) << std::right << Coordinator::GetInstance()->GetComponent<Lifespan>(e).lifetime;
        std::cout << " | isActive: " << Coordinator::GetInstance()->GetComponent<IsActive>(e).isActive << '\n';
      }
}

