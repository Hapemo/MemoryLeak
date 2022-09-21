/*!*****************************************************************************
\file LevelEditor.h
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
#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_glfw.h"
#include "../../imgui/imgui_impl_opengl3.h"
#include "../../imgui/imGuizmo.h"

#include <ECS_systems.h>
#include "ECS_items.h"
#include "ECS_components.h"
#include <Application.h>
#include "TransformManager.h"


class LevelEditor : public System
{
public:
	void Init();
	void Window();
	void Update();
	void Exit();

private:
	void SceneManager();
	void EntityManager();
	void AssetManager();
	void ViewPortManager();
	void ShowDebugInfo();
	
};