/*!*****************************************************************************
\file EditorManager.h
\author Huang Wei Jhin
\par DP email: h.weijhin@digipen.edu
\par Group: Memory Leak Studios
\date 20-09-2022
\brief
This file contains function declarations for a Level Editor system that modifies
Entities and its Components.
*******************************************************************************/
#pragma once
#include "pch.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imGuizmo.h"
#include "imgui_stdlib.h"

#include <ECS_systems.h>
#include "ECS_items.h"
#include "ECS_components.h"
//#include "Graphics/TransformManager.h"
#include <vec2.h>
#include <filesystem>
#define _USE_MATH_DEFINES
#include <math.h>
#include <Input.h>
class Panel;

/*!*****************************************************************************
\brief
	This class encapsulates the functions for the Level Editor
*******************************************************************************/
class EditorManager : public System
{
public:
	void Load(GLFWwindow*, int*, int*);
	void Init();
	void Window();
	void Update();
	void Free();
	void Unload();

	bool IsScenePaused() { return isScenePaused; }

	

	//bool IsEditorPaused() { return isPaused; };
	//void UnpauseEditor() { isPaused = false; };
private:
	static std::vector<Panel*> panels;
	
protected:
	enum class E_PANELID
	{
		HIERARCHY,
		INSPECTOR,
		WORLDVIEW,
		GAMEVIEW,
		DIALOGUE,
		ASSET,
		DEBUG,
		MENU
	};
	void SceneReset();
	static bool GetPannelIsActive(E_PANELID _panel);
	static void SetPannelIsActive(E_PANELID _panel, bool _isActive);
	void SaveUndo(Entity const e, COMPONENT& old, COMPONENTID id);
	void Do();
	void Undo();
	void Redo();
	static bool isScenePaused;
	GLFWwindow* mWindow;
	static int* mWindowWidth;
	static int* mWindowHeight;
	static std::set<Entity>* myEntities;
	static const Entity* selectedEntity;
	static Entity selEntity;
	static int SRT;
	static std::vector<std::pair<Entity const, COMPONENT>> undoStack;
	static int stackPointer;
	static int highestLayer;



	
	/*static bool isPaused;
	void SceneManager();
	void EntityManager();
	void AssetManager();
	void ViewPortManager();
	void WorldViewPort();
	void CameraViewPort();
	void ShowDebugInfo();
	void DialogEditor();*/
};