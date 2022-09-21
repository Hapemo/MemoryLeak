/*!
file:	    Helper.h
author:	  Jazz Teoh Yu Jue
date:	    16/05/2022

email:	  j.teoh@digipen.edu

brief:	  Helper provides multiple useful but niche functionalities such as framerate
          tracking and printing system specs

All content © 2022 DigiPen Institute of Technology Singapore. All rights reserved.
*//*__________________________________________________________________________________*/

/*                                                                      guard
----------------------------------------------------------------------------- */
#pragma once

/*                                                                   includes
----------------------------------------------------------------------------- */
#include <GL/glew.h> // for access to OpenGL API declarations 
#include <GLFW/glfw3.h>
#include <string>

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
