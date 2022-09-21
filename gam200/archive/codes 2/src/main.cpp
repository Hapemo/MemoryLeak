/*!
@file    main.cpp
@author  j.teoh@digipen.edu
@date    13/05/2022

This file uses functionality defined in types Helper and GLApp to initialize 
an OpenGL context and implement a game loop.

*//*__________________________________________________________________________*/

/*                                                                   includes
----------------------------------------------------------------------------- */
// Extension loader library's header must be included before GLFW's header!!!
#include <Helper.h>
#include <iostream>
#include "Application.h"
#include "GameStateManager.h"

/*                                                   type declarations
----------------------------------------------------------------------------- */


/*                                                      function definitions
----------------------------------------------------------------------------- */
/*  _________________________________________________________________________ */
/*! main

@param none

@return int

Indicates how the program existed. Normal exit is signaled by a return value of
0. Abnormal termination is signaled by a non-zero return value.
Note that the C++ compiler will insert a return 0 statement if one is missing.
*/
int main() {
  // Part 1
  Application::init();

  // Part 2
  while (!glfwWindowShouldClose(Application::getWindow())) {
    GameStateManager::getInstance()->Loop();
  }

  // Part 3
  Application::exit();
}

