/*!*****************************************************************************
\file Helper.cpp
\author Jazz Teoh Yu Jue
\par DP email: j.teoh\@digipen.edu
\par Group: Memory Leak Studios
\date 24-09-2022
\brief
General helper class of application that calculates FPS and prints GLFW info
*******************************************************************************/
#include "Helper.h"

// static data members declared in Helper
GLdouble FPSManager::fps;
double FPSManager::dt;
double FPSManager::mPrevTime;
double FPSManager::mLimitFPS = 0;

void FPSManager::CalcFPS(double fps_calc_interval) {
  double curr_time = glfwGetTime();

  // fps calculations
  static double count = 0.0; // number of game loop iterations
  static double start_time = glfwGetTime();
  // get elapsed time since very beginning (in seconds) ...
  double elapsed_time = curr_time - start_time;

  ++count;

  // update fps at least every 10 seconds ...
  fps_calc_interval = (fps_calc_interval < 0.0) ? 0.0 : fps_calc_interval;
  fps_calc_interval = (fps_calc_interval > 10.0) ? 10.0 : fps_calc_interval;
  if (elapsed_time > fps_calc_interval) {
  FPSManager::fps = count / FPSManager::dt; // elapsed_time;
    start_time = curr_time;
    count = 0.0;
  }
}

void FPSManager::CalcDeltaTime() {
  dt = glfwGetTime() - mPrevTime;
  mPrevTime = glfwGetTime();
}

void FPSManager::LimitFPS() {
  if (!mLimitFPS) return;

  double targetedDT = 1 / mLimitFPS;
  while ((glfwGetTime() - mPrevTime) < targetedDT) {}
}
