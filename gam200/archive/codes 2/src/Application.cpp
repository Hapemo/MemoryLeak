#include "Application.h"
//#include "Windows.h"
#include <GL/glew.h> // for access to OpenGL API declarations 
#include <GLFW/glfw3.h>
#include "Helper.h"
#include "Input.h"
#include "Graphics.h"
#include "StartupException.h"
#include "GameStateManager.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
// Static variables
int Application::window_width{};
int Application::window_height{};
std::string Application::title{ "gam200" };
GLFWwindow* Application::ptr_window;
float Application::target_fps = 60.f;


void Application::startup() {
  
  try {
    loadConfig("../config.txt");
    glfwStartUp();
    Input::init();
    glewStartUp();
    GameStateManager::getInstance()->Init();
  }
  catch (StartUpException error) {
    std::cout << "Unable to create OpenGL context\n" << error.what() << '\n';
    std::exit(EXIT_FAILURE);
  }
}


void Application::init() {
  // Part 1
  startup();
  
  // Part 2
  Helper::print_specs();
  
  // Part 3
  Graphics::init();
}

void Application::FirstUpdate() {
  Helper::prev_time = glfwGetTime();

  // Part 1
  glfwPollEvents();
  
  // Part 2
  Helper::CalcFPS(2.0);
}

void Application::SecondUpdate() {
  // write window title with current fps ...
  std::stringstream sstr;
  sstr << std::fixed << std::setprecision(3) << Application::getTitle() << " | " << Helper::fps << " | " << Helper::dt;
  glfwSetWindowTitle(Application::getWindow(), sstr.str().c_str());

  // Close the window if the close flag is triggered
  if (glfwWindowShouldClose(Application::getWindow())) GameStateManager::getInstance()->nextGS(GS::EXIT);

  // Reset input
  Input::updatePrevKeyStates();

  // Part 2: swap buffers: front <-> back
  glfwSwapBuffers(Application::getWindow());
  
  // Calculate delta time
  //Sleep(1);
  while ((glfwGetTime() - Helper::prev_time) < (double)(1.0 / Application::getTargetFPS())) {}
  Helper::CalcDeltaTime();
}

void Application::exit() {
  // Part 1
  Graphics::cleanup();
  
  GameStateManager::getInstance()->Exit();
  SingletonManager::destroyAllSingletons();
  // Part 2
  glfwTerminate();
}



// Private helper functions
void Application::loadConfig(std::string path) {
  // Opening file
  std::fstream file;
  file.open(path, std::ios_base::in);
  std::vector<std::pair<std::string, std::string>> config;
  config.reserve(10);

  if (!file.is_open()) throw StartUpException("File " + path + " not found.");
  
  // Extracting config information
  std::string line{};
  while (std::getline(file, line)) {
    size_t midpoint{ line.find(':') };

    config.push_back({ line.substr(0, midpoint), line.substr(midpoint + 2, midpoint + 2 - line.length()) });
  }

  // Applying configurations
#ifdef _DEBUG
  std::cout << "config file\n-----------\n";
#endif
  for (auto [key, value] : config) {
#ifdef _DEBUG
    std::cout << key << " | " << value << '\n';
#endif
    
    if (value.length() <= 0) throw StartUpException("Config error: " + key + " not found!");

    if (key == "window_width") window_width = stoi(value);
    if (key == "window_height") window_height = stoi(value);
    if (key == "title") title = value;
  }
#ifdef _DEBUG
  std::cout << "-----------\n";
#endif
}

void Application::glfwStartUp() {
  // Part 1
  if (!glfwInit()) throw StartUpException("GLFW init has failed - abort program!!!");

  const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

  if (!window_width) window_width = mode->width;
  if (!window_height) window_height = mode->height;

  // In case a GLFW function fails, an error is reported to callback function
  glfwSetErrorCallback(error_cb);

   //Before asking GLFW to create an OpenGL context, we specify the minimum constraints
  // in that context:
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
  glfwWindowHint(GLFW_DEPTH_BITS, 24);
  glfwWindowHint(GLFW_RED_BITS, 8); glfwWindowHint(GLFW_GREEN_BITS, 8);
  glfwWindowHint(GLFW_BLUE_BITS, 8); glfwWindowHint(GLFW_ALPHA_BITS, 8);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); // window dimensions are static

  ptr_window = glfwCreateWindow(window_width, window_height, title.c_str(), NULL, NULL);
  if (!ptr_window) {
    throw StartUpException("GLFW unable to create OpenGL context - abort program");
    glfwTerminate();
  }

  glfwMakeContextCurrent(ptr_window);

  glfwSetFramebufferSizeCallback(ptr_window, fbsize_cb);
}

void Application::glewStartUp() {
  // Part 2: Initialize entry points to OpenGL functions and extensions
  GLenum err = glewInit();
  if (GLEW_OK != err) {
    std::stringstream string;
    string << "Unable to initialize GLEW - error " << glewGetErrorString(err) << " abort program";
    throw StartUpException(string.str());
  }
  if (GLEW_VERSION_4_5) {
    std::cout << "Using glew version: " << glewGetString(GLEW_VERSION) << std::endl;
    std::cout << "Driver supports OpenGL 4.5\n" << std::endl;
  }
  else throw StartUpException("Driver doesn't support OpenGL 4.5 - abort program");
}

void Application::error_cb(int error, char const* description) {
#ifdef _DEBUG
  std::cerr << "GLFW error: " << description << std::endl;
#endif
}

void Application::fbsize_cb(GLFWwindow* ptr_win, int width, int height) {
#ifdef _DEBUG
  std::cout << "fbsize_cb getting called!!!" << std::endl;
#endif
  // use the entire framebuffer as drawing region
  glViewport(0, 0, width, height);
  // later, if working in 3D, we'll have to set the projection matrix here ...
}