#include <GL/glew.h> // for access to OpenGL API declarations
#include <iostream>
#include "Start.h"
#include "Input.h"

void Start::Load() {

}

void Start::Init() {

}

void Start::Update() {
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




