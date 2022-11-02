/*!*****************************************************************************
\file Application.cpp
\author Jazz Teoh Yu Jue
\par DP email: j.teoh\@digipen.edu
\par Group: Memory Leak Studios
\date 24-09-2022
\brief
Main application that gets called in the main loop. It handles the creation and
start up of window and game system, also runs their update functions.
*******************************************************************************/
#include "Application.h"
//#include "Windows.h"
#include "Helper.h"
#include "Input.h"
#include "GameStateManager.h"
#include "ECSManager.h"
#include "Editor\EditorManager.h"
#include "PerformanceVisualiser.h"
#include "ResourceManager.h"

// Static variables
int Application::window_width{};
int Application::window_height{};
std::string Application::title{ "gam200" };
GLFWwindow* Application::ptr_window;
std::string Application::mCurrGameStateName{""};

void Application::startup() {
  loadConfig("../config.txt");
  GLFWStartUp();
  Input::Init(ptr_window);
  GlewStartUp();
  ECSManager::ECS_init();
  GameStateManager::GetInstance()->Init();
}

void Application::SystemInit() {
  editorManager->Load(ptr_window, &window_width, &window_height);
  audioManager->Init();
  logicSystem->Init();
  //aiManager->weatherAIinit();
  
  renderManager->Init(&window_width, &window_height);
  renderManager->RenderToFrameBuffer();
  // For render debug
  renderManager->SetVectorLengthModifier(5.f);
  renderManager->SetDebug(true);

  // Collision database initialization
  collision2DManager->SetupCollisionDatabase();

  ResourceManager::GetInstance()->LoadAllResources();
  for (size_t index = 0; index < GET_RESOURCES().size(); ++index)
    spriteManager->InitializeTexture(GET_TEXTURE_DATA(index));
}

void Application::SystemUpdate() {

  // AI
  TRACK_PERFORMANCE("AI");
  aiManager->updateAI();
  END_TRACK("AI");

  // Physics
  TRACK_PERFORMANCE("Physics");
  physics2DManager->Update(FPSManager::dt);
  END_TRACK("Physics");

  //Scripting
  TRACK_PERFORMANCE("Scripting");
  logicSystem->Update();

  END_TRACK("Scripting");

  // Animator
  TRACK_PERFORMANCE("Animation");
  sheetAnimator->Animate();
  animator->Animate();
  END_TRACK("Animation");

  // Audio
  TRACK_PERFORMANCE("Audio");
  audioManager->UpdateSound();
  END_TRACK("Audio");

  // Player
  playerManager->Update(); // Has error on gamestate3, maybe because player was not freed in gamestate1
}

void Application::init() {
  // Part 1
  startup();

  SystemInit();
 // audioManager->PlayBGSound("PIntro", 10);
  audioManager->PlayBGSound("MENUBG", 10);
}

void Application::FirstUpdate() {
  FPSManager::mPrevTime = glfwGetTime();

  // Part 1
  glfwPollEvents();
  
  // Part 2
  FPSManager::CalcFPS(0);
}

void Application::SecondUpdate() {
  PrintTitleBar(0.3);

  // Close the window if the close flag is triggered
  if (glfwWindowShouldClose(Application::getWindow())) GameStateManager::GetInstance()->NextGS(E_GS::EXIT);
  /////audioManager->UpdateSound();
  
  // Reset input
  Input::UpdatePrevKeyStates();
  // Part 2: swap buffers: front <-> back
  glfwSwapBuffers(Application::getWindow());

  FPSManager::LimitFPS();
  FPSManager::CalcDeltaTime();
}

void Application::exit() {
  editorManager->Unload();
  audioManager->Unload();
  spriteManager->FreeTextures();
  ResourceManager::GetInstance()->UnloadAllResources();
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
  ASSERT(!file.is_open(), "File " + path + " not found.\n");
  
  std::map<std::string, std::string> config = Util::TextFileToMap(file);

  // Applying configurations
#ifdef _DEBUG
  std::cout << "config file\n-----------\n";
#endif
  for (auto [key, value] : config) {
#ifdef _DEBUG
    std::cout << key << " | " << value << '\n';
#endif
    ASSERT(value.length() < 1, "Config error: " + key + " not found!\n");

    if (key == "window_width") window_width = stoi(value);
    else if (key == "window_height") window_height = stoi(value);
    else if (key == "title") title = value;
    else if (key == "fps_limit") FPSManager::mLimitFPS = static_cast<double>(stoi(value));
  }
#ifdef _DEBUG
  std::cout << "-----------\n";
#endif
}

// _s, time interval in updating titlebar, in seconds
void Application::PrintTitleBar(double _s) {
  static bool printDebug{ true };
  if (Input::CheckKey(HOLD, LEFT_ALT) && Input::CheckKey(HOLD, LEFT_SHIFT) && Input::CheckKey(PRESS, S)) printDebug = !printDebug;

  static double timeElapsed{};
  timeElapsed += FPSManager::dt;
  if (timeElapsed > _s) {
    timeElapsed = 0;

    // write window title with current fps ...
    std::stringstream sstr;


    sstr << std::fixed << std::setprecision(3) << Application::getTitle() << " | " 
                                               << "GameState: " << mCurrGameStateName << " | "
                                               << "fps: " << FPSManager::fps << " | "
                                               << "dt: " << FPSManager::dt << " | "
                                               << "Entity Count: " << Coordinator::GetInstance()->GetEntityCount() << " | ";

    if (printDebug) sstr << GET_SYSTEMS_PERFORMANCES();

    glfwSetWindowTitle(Application::getWindow(), sstr.str().c_str());
  }
}

void Application::GLFWStartUp() {
  // Part 1
  ASSERT(!glfwInit(), "GLFW init has failed - abort program!!!\n");
  
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
    glfwTerminate();
    ASSERT(!ptr_window, "GLFW unable to create OpenGL context - abort program");
  }

  glfwMakeContextCurrent(ptr_window);

  glfwSetFramebufferSizeCallback(ptr_window, fbsize_cb);
  glfwSwapInterval(0);
}

void Application::GlewStartUp() {
  // Part 2: Initialize entry points to OpenGL functions and extensions
  GLenum err = glewInit();

  std::stringstream string;
  string << "Unable to initialize GLEW - error " << glewGetErrorString(err) << " abort program\n";
  ASSERT(GLEW_OK, string.str());
}

void Application::error_cb(int error, char const* description) {
    (void)error;
    (void)description; // This function should only be called for debug mode
#ifdef _DEBUG
  std::cerr << "GLFW error " << error << ": " << description << std::endl;
#endif
}

void Application::fbsize_cb(GLFWwindow* ptr_win, int width, int height) {
#ifdef _DEBUG
  std::cout << "fbsize_cb getting called!!!" << std::endl;
#endif
  // use the entire framebuffer as drawing region
  glViewport(0, 0, width, height);
  (void)ptr_win;
  // later, if working in 3D, we'll have to set the projection matrix here ...
}