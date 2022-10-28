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

#include <ECS_systems.h>
#include "ECS_items.h"
#include "ECS_components.h"
#include "Graphics/TransformManager.h"
//class Panel;

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


	bool IsEditorPaused() { return isPaused; };
	void UnpauseEditor() { isPaused = false; };
private:
	//std::vector<Panel> panels;
	
protected:
	void SceneManager();
	void EntityManager();
	void AssetManager();
	void ViewPortManager();
	void WorldViewPort();
	void CameraViewPort();
	void ShowDebugInfo();
	void DialogEditor();
	void SaveUndo(Entity * const e, COMPONENT& old, COMPONENTID id);
	void Undo();
	void Redo();
	GLFWwindow* mWindow;
	int* mWindowWidth;
	int* mWindowHeight;
	const Entity* selectedEntity;
	bool isPaused;
	int SRT;
	
	//std::vector<std::pair<Entity * const, Transform>> undoStack;
	std::vector<std::pair<Entity* const, COMPONENT>> undoStack;
	int stackPointer;
};