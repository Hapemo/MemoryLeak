#include "Application.h"
//#include "Windows.h"
#include "Helper.h"
#include "Input.h"
#include "StartupException.h"
#include "GameStateManager.h"
#include "ECSManager.h"
#include "LevelEditor.h"
#include "PerformanceVisualiser.h"
#include "ResourceManager.h"

// Static variables
int Application::window_width{};
int Application::window_height{};
std::string Application::title{ "gam200" };
GLFWwindow* Application::ptr_window;
float Application::target_fps = 60.f;
bool editorMode = false;

void Application::startup() {
  
  try {
    loadConfig("../config.txt");
    glfwStartUp();
    Input::init(ptr_window);
    glewStartUp();
    GameStateManager::GetInstance()->Init();
    ECSManager::ECS_init();
  }
  catch (StartUpException error) {
    std::cout << "Unable to create OpenGL context\n" << error.what() << '\n';
    std::exit(EXIT_FAILURE);
  }
}

void Application::SystemInit() {
  for (size_t index = 0; index < GET_RESOURCES().size(); ++index) {
    spriteManager->InitializeTexture(GET_TEXTURE(index));
  }

  //@weijhin
  levelEditor->LevelEditor::Init(ptr_window, &window_width, &window_height);
  audioManager->AudioManager::AudioManager();
  benchmarkManager->StartTime();
  renderManager->Init(&window_width, &window_height);
}


void Application::init() {
  // Part 1
  startup();

  INIT_TEXTURES("Background");
  INIT_TEXTURES("Icons");
  INIT_TEXTURES("Menu");
  INIT_TEXTURES("Sprites");
  INIT_TEXTURES("Spritesheets");

  // Part 2
  Helper::print_specs();
  SystemInit();
}

void Application::FirstUpdate() {
  Helper::prev_time = glfwGetTime();

  // Part 1
  glfwPollEvents();
  
  // Part 2
  Helper::CalcFPS(0);
}

void Application::SecondUpdate() {
  PrintTitleBar(0.3);

  // Close the window if the close flag is triggered
  if (glfwWindowShouldClose(Application::getWindow())) GameStateManager::GetInstance()->nextGS(GS::EXIT);

  // Update ImGui
  TRACK_PERFORMANCE("Editor");
  if (editorMode)
  {
      renderManager->RenderToFrameBuffer();
    levelEditor->LevelEditor::Window();
    levelEditor->LevelEditor::Update();
  }
  else
      renderManager->RenderToScreen();

  END_TRACK("Editor");

  if (Input::CheckKey(STATE::RELEASE, KEY::E))
  {
      editorMode = !editorMode;
  }
  // Reset input
  Input::updatePrevKeyStates();
  audioManager->UpdateSound();
  // Part 2: swap buffers: front <-> back
  glfwSwapBuffers(Application::getWindow());

  // Calculate delta time
  //Sleep(1);
  //while ((glfwGetTime() - Helper::prev_time) < (double)(1.0 / Application::getTargetFPS())) {}
  Helper::CalcDeltaTime();
  
}

void Application::exit() {
    //@weijhin
    levelEditor->Exit();
  GameStateManager::GetInstance()->Exit();
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

// _s, time interval in updating titlebar, in seconds
void Application::PrintTitleBar(double _s) {
  static double timeElapsed{};
  timeElapsed += Helper::dt;
  if (timeElapsed > _s) {
    timeElapsed = 0;

    // write window title with current fps ...
    std::stringstream sstr;
    sstr << std::fixed << std::setprecision(3) << Application::getTitle() << " | " << Helper::fps << " | " << Helper::dt << " | " << GET_SYSTEMS_PERFORMANCES();
    glfwSetWindowTitle(Application::getWindow(), sstr.str().c_str());
  }
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
  glfwSwapInterval(0);
}

void Application::glewStartUp() {
  // Part 2: Initialize entry points to OpenGL functions and extensions
  GLenum err = glewInit();
  if (GLEW_OK != err) {
    std::stringstream string;
    string << "Unable to initialize GLEW - error " << glewGetErrorString(err) << " abort program";
    throw StartUpException(string.str());
  }
  /*if (GLEW_VERSION_4_5) {
    std::cout << "Using glew version: " << glewGetString(GLEW_VERSION) << std::endl;
    std::cout << "Driver supports OpenGL 4.5\n" << std::endl;
  }
  else throw StartUpException("Driver doesn't support OpenGL 4.5 - abort program");*/
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