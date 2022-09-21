/*!
file:	    Helper.cpp
author:	  Jazz Teoh Yu Jue
date:	    16/05/2022

email:	  j.teoh@digipen.edu

brief:	  Helper provides multiple useful but niche functionalities such as framerate
          tracking and printing system specs

All content © 2022 DigiPen Institute of Technology Singapore. All rights reserved.
*//*__________________________________________________________________________________*/

/*                                                                   includes
----------------------------------------------------------------------------- */
#include <iostream>
#include "Helper.h"
#include "Application.h"

/*                                                   objects with file scope
----------------------------------------------------------------------------- */
// static data members declared in Helper
GLdouble Helper::fps;
GLdouble Helper::dt;
double Helper::prev_time;

void Helper::CalcFPS(double fps_calc_interval) {
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
    Helper::fps = count / elapsed_time;
    start_time = curr_time;
    count = 0.0;
  }
}

void Helper::CalcDeltaTime() {
  dt = glfwGetTime() - prev_time;
  prev_time = glfwGetTime();
}

void Helper::print_specs() {
    GLubyte const* str = glGetString(GL_VENDOR);
    GLint intv{};

    std::cout << "GPU Vendor: " << str << std::endl;

    str = glGetString(GL_RENDERER);
    std::cout << "GPU Renderer: " << str << std::endl;

    glGetIntegerv(GL_MAJOR_VERSION, &intv);
    std::cout << "GPU Major Version: " << intv << std::endl;

    glGetIntegerv(GL_MINOR_VERSION, &intv);
    std::cout << "GPU Minor Version: " << intv << std::endl;

    std::cout << "Current OpenGL Context is double buffered\n";

    glGetIntegerv(GL_MAX_ELEMENTS_VERTICES, &intv);
    std::cout << "Maximum Vertex Count: " << intv << std::endl;

    glGetIntegerv(GL_MAX_ELEMENTS_INDICES, &intv);
    std::cout << "Maximum Indices Count: " << intv << std::endl;

    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &intv);
    std::cout << "GL Maximum texture size: " << intv << std::endl;
    
    GLint intv2[2]{};
    glGetIntegerv(GL_MAX_VIEWPORT_DIMS, intv2);
    std::cout << "Maximum Viewport Dimensions: " << intv2[0] << " x " << intv2[1] << std::endl;
}
