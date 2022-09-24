#pragma once
#include "pch.h"

struct GLFWwindow;

class Application {
public:
	static void init();
	static void startup();
	static void SystemInit();
	static void FirstUpdate();		// Called at the start of every game loop
	static void SecondUpdate();		// Called at the end of every game loop
	static void exit();

	static GLFWwindow* getWindow() { return ptr_window; }
	static std::string getTitle() { return title; }
	static int getWindowWidth() { return window_width; }
	static int getWindowHeight() { return window_height; }
	static float getTargetFPS() { return target_fps; }

private:
	static int window_width, window_height;
	static std::string title;
	static GLFWwindow* ptr_window;
	static float target_fps;

	static void loadConfig(std::string path);
	static void PrintTitleBar(double);
	static void glfwStartUp();
	static void glewStartUp();
	// Callbacks
	static void error_cb(int error, char const* description);
	static void fbsize_cb(GLFWwindow* ptr_win, int width, int height);
};