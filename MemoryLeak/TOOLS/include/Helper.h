/*!*****************************************************************************
\file Helper.h
\author Jazz Teoh Yu Jue
\par DP email: j.teoh\@digipen.edu
\par Group: Memory Leak Studios
\date 24-09-2022
\brief

*******************************************************************************/

/*                                                                      guard
----------------------------------------------------------------------------- */
#pragma once

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "pch.h"

/*  _________________________________________________________________________ */
struct Helper
  /*! Helper structure to encapsulate initialization stuff ...
  */
{
  /***************************************************************************/
  /*!
    \brief
      This function must be called once per game loop. It uses GLFW's time
      functions to compute:
      1. the interval in seconds between each frame
      2. the frames per second every "fps_calc_interval" seconds

    \param double
      fps_calc_interval: the interval (in seconds) at which fps is to be
      calculated
  */
  /**************************************************************************/
  static void CalcFPS(double fpsCalcInt = 1.0);

  /***************************************************************************/
  /*!
    \brief
      Prints out the graphics and display specification of the system and
      graphics card
  */
  /**************************************************************************/
  static void print_specs();

  static void CalcDeltaTime();

  static GLdouble fps;
  static double dt; // time taken to complete most recent game loop
  static double prev_time;    // Time at beginning of game loop
};
