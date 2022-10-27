/*!*****************************************************************************
\file Application.h
\author Jazz Teoh Yu Jue
\par DP email: j.teoh\@digipen.edu
\par Group: Memory Leak Studios
\date 24-09-2022
\brief
Main application that gets called in the main loop. It handles the creation and 
start up of window and game system, also runs their update functions.
*******************************************************************************/
#pragma once
#include "pch.h"

struct GLFWwindow;

class Application {
public:
	/*!*****************************************************************************
	 \brief
	 Initialise the application and it's systems such as window, texture resources
	 and game engine systems
	*******************************************************************************/
	static void init();

	/*!*****************************************************************************
	 \brief
	 Start up the vital components for application. Should be called in Application
	 Init()
	*******************************************************************************/
	static void startup();

	/*!*****************************************************************************
	 \brief
	 initialise Game Engine ECS's systems
	*******************************************************************************/
	static void SystemInit();

	/*!*****************************************************************************
	 \brief
	 Update Game Engine ECS's systems, should be called every game loop
	*******************************************************************************/
	static void SystemUpdate();

	/*!*****************************************************************************
	 \brief
	 Initialisation before start of each game loop.
	*******************************************************************************/
	static void FirstUpdate();

	/*!*****************************************************************************
	 \brief
	 Clean up after end of each game loop.
	*******************************************************************************/
	static void SecondUpdate();

	/*!*****************************************************************************
	 \brief
	 Unload and clean up when exiting the application
	*******************************************************************************/
	static void exit();

	/*!*****************************************************************************
	 \brief
	 Unload and clean up when exiting the application
	*******************************************************************************/

	//------------------------------------------------------------------------------
	// Getter and Setters
	//------------------------------------------------------------------------------
	static GLFWwindow* getWindow() { return ptr_window; }
	static std::string getTitle() { return title; }
	static int getWindowWidth() { return window_width; }
	static int getWindowHeight() { return window_height; }
	static bool GetEditorMode() { return editorMode; }

private:
	static int window_width, window_height;
	static std::string title;
	static GLFWwindow* ptr_window;
	static bool editorMode;

	/*!*****************************************************************************
	 \brief
	 Load Config file into application
	 
	 \param std::string
	 - Path of config file
	*******************************************************************************/
	static void loadConfig(std::string);

	/*!*****************************************************************************
	 \brief
	 Print the window title bar

	 \param double
	 - Frequency of updating the title bar in seconds. eg. if 0.3, title bar will
	refresh evert 0.3 seconds
	*******************************************************************************/
	static void PrintTitleBar(double);

	/*!*****************************************************************************
	 \brief
	 Start up GLFW
	*******************************************************************************/
	static void GLFWStartUp();
	
	/*!*****************************************************************************
	 \brief
	 Start up GLEW
	*******************************************************************************/
	static void GlewStartUp();
	
	/*!*****************************************************************************
	 \brief
	 Callback function for GLFW errors

	 \param int _error
	 - Error code from GLFW

	 \param char const* _description
	 - Description of error
	*******************************************************************************/
	static void error_cb(int _error, char const* _description);

	/*!*****************************************************************************
	 \brief
	 Callback function for GLFW framebuffer

	 \param GLFWwindow* _ptrWin
	 - Pointer to window

	 \param _width
	 - Window width

	 \param _height
	 - Window height
	*******************************************************************************/
	static void fbsize_cb(GLFWwindow* _ptrWin, int _width, int _height);
};