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
#include "PrefabManager.h"

#include <vec2.h>
#include <filesystem>
#define _USE_MATH_DEFINES
#include <math.h>
#include <Input.h>
class Panel;
class Scene;
class GameState;
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
	void SetScenePaused(bool _paused) { isScenePaused = _paused; }
	using PrefabPtr = std::shared_ptr<Prefab>;

	Math::Vec2 GetEditorWorldMousePos();
	Math::Vec2 GetEditorGameMousePos();

private:
	static std::vector<Panel*> panels;
	
protected:
	//to remove
	//struct SceneData {
	//	std::string name = "";
	//	Transform camera = {};
	//	bool isActive = false;
	//	int layer = 0;
	//	int order = 0;;
	//	std::set<Entity> mEntities = {};
	//};

	////Data that a gamestate class should contain
	//struct GameStateData {
	//	std::string name = "";
	//	std::vector<SceneData> scenes = {};

	//};
	enum class E_PANELID
	{
		MENU,
		DEBUG,
		PERFORMANCE,
		ASSET,
		DIALOGUE,
		WEATHER,
		ANIMATION,
		PREFABS,
		HIERARCHY,
		INSPECTOR,
		WORLDVIEW,
		GAMEVIEW,
		END
	};
	void SceneReset();
	static bool GetPannelIsActive(E_PANELID _panel);
	static void SetPannelIsActive(E_PANELID _panel, bool _isActive);
	void SaveUndo(Entity const e, COMPONENT& old, COMPONENTID id);
	void Do();
	void Undo();
	void Redo();
	void Copy();
	void Cut();
	void Paste();
	Entity Clone(Entity e);
	GLFWwindow* mWindow;
	static int* mWindowWidth;
	static int* mWindowHeight;

	static std::set<Entity>* myEntities;
	static const Entity* selectedEntity;
	static Entity selEntity;
	static bool aspect;
	static PrefabPtr selectedPrefab;
	static int selectedType;


	static std::vector<GameState>* mGameStates;
	//static std::vector <GameStateData> GSList;
	//static std::vector<  std::pair<  std::string, std::vector<std::string> >> allNames;
	//static std::vector<std::vector<std::set<Entity>>> allEntities;
	static int selectedGameState;
	static int selectedScene;
	static int selectedPrevious;
	//static std::vector <Prefab*> mPrefabs;
	//static const void* selected;
	static int SRT;
	//undo/redo
	static std::vector<std::pair<Entity const, COMPONENT>> undoStack;
	static int stackPointer;
	static int highestLayer;
	//copy paste
	static std::pair<Entity, int> copyEntity;
	static float copyOffset;

	//prefab
	static float prefabOffset;

	static bool isScenePaused;
	static bool isAnimatorEditor;
	bool isAnimatorEditorFocused(){return isAnimatorEditor;}
	
	void NewScene();
	void NewGameState();


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