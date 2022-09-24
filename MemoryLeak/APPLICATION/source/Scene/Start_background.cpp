#pragma once
#include "pch.h"
#include "Start_background.h"
#include "AI.h"
#include "Helper.h"

void Start_background::Init() {
  // Nothing for now

  Reset();
}

void Start_background::Update() {
  static bool reverse{ false };
  static float color[3]{ 0, 1, 0 };

  if (!reverse) {
    if (color[0] < 1) color[0] += 0.01f;
    else if (color[1] < 1) color[1] += 0.01f;
    else if (color[2] < 1) color[2] += 0.01f;
    else reverse = true;
  } else {
    if (color[0] > 0) color[0] -= 0.01f;
    else if (color[1] > 0) color[1] -= 0.01f;
    else if (color[2] > 0) color[2] -= 0.01f;
    else reverse = false;
  }

  glClearColor(color[0], color[1], color[2], 1.f);
}

void Start_background::Reset() {
  std::cout << " Start_background Reset() called\n";
}

void Start_background::Clear() {
  for (auto& e : mEntities)
    e.Destroy();
}



