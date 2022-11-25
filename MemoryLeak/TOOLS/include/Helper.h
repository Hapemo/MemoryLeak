/*!*****************************************************************************
\file Helper.h
\author Jazz Teoh Yu Jue
\par DP email: j.teoh\@digipen.edu
\par Group: Memory Leak Studios
\date 24-09-2022
\brief
General helper class of application that calculates FPS and prints GLFW info
*******************************************************************************/
#pragma once

#include "pch.h"

struct FPSManager
{
  /*!*****************************************************************************
  \brief
  This function must be called once per game loop. It uses GLFW's time
  functions to compute:
  1. the interval in seconds between each frame
  2. the frames per second every "fps_calc_interval" seconds

  \param double
  - the interval (in seconds) at which fps is to be calculated
  *******************************************************************************/
  static void CalcFPS(double = 1.0);

  /*!*****************************************************************************
  \brief
  Calculates the time taken for the previous frame to run
  *******************************************************************************/
  static void CalcDeltaTime();

  /*!*****************************************************************************
  \brief
  Limit the FPS. If limit fps is 0, fps will not be limited.
  *******************************************************************************/
  static void LimitFPS();

  static GLdouble fps;
  static double dt; // time taken to complete most recent game loop
  static double mPrevTime; // Time at beginning of game loop
  static double mLimitFPS;
};

class Helper {
public:
  static void Init(GLFWwindow* _winPtr);
  static void SetFullScreen(bool _fullscreen);
  


  static bool GetFullScreenFlag() { return fullscreenFlag; }
  static int GetScreenWidth() { return mWindowSize[0]; }
  static int GetScreenHeight() { return mWindowSize[1]; }

private:
  static GLFWwindow* mWindow;
  static GLFWmonitor* mMonitor;
  static std::array<int, 2> mWindowPos;
  static std::array<int, 2> mWindowSize;
  static bool fullscreenFlag;
};
