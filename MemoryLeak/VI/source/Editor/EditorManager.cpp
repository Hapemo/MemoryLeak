/*!*****************************************************************************
/*!*****************************************************************************
\file EditorManager.cpp
\author Huang Wei Jhin
\par DP email: h.weijhin@digipen.edu
\par Group: Memory Leak Studios
\date 20-09-2022
\brief
This file contains function definations for a Level Editor system that modifies
Entities and its Components.
*******************************************************************************/
#include "EditorManager.h"
#include <ECSManager.h>
//#include <Logger.h>
#include <Panel.h>
#include <HierarchyPanel.h>
#include <InspectorPanel.h>
#include <WorldViewPanel.h>
#include <GameViewPanel.h>
#include <DialoguePanel.h>
#include <DebugPanel.h>
#include <AssetPanel.h>
#include <MenuPanel.h>


std::vector<Panel*> EditorManager::panels{};


int* EditorManager::mWindowWidth = nullptr;
int* EditorManager::mWindowHeight = nullptr;
const Entity* EditorManager::selectedEntity = nullptr;
 Entity selEntity{};
int EditorManager::SRT{};
std::vector<std::pair<Entity const, COMPONENT>> EditorManager::undoStack{};
int EditorManager::stackPointer{-1};
std::set<Entity>* EditorManager::myEntities = nullptr;
bool EditorManager::isScenePaused = false;;
std::vector <Prefab> EditorManager::mPrefabs{};
/*!*****************************************************************************
\brief
	Initializes the level editor

\return
None.
*******************************************************************************/
void EditorManager::Load(GLFWwindow* _window, int* _windowWidth, int* _windowHeight)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigWindowsMoveFromTitleBarOnly = true;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(_window, true);
	ImGui_ImplOpenGL3_Init("#version 450");
	mWindowWidth = _windowWidth;
	mWindowHeight = _windowHeight;
	myEntities = &mEntities;
	//IM_ASSERT(ret);
	//weatherAIinit();
	static HierarchyPanel hierarchyPanel{};
	static InspectorPanel inspectorPanel{};
	static WorldViewPanel worldViewPanel{};
	static GameViewPanel gameViewPanel{};
	static DialoguePanel dialoguePanel{};
	static AssetPanel assetPanel{};
	static DebugPanel debugPanel{};
	static MenuPanel menuPanel{};
	panels.push_back(&hierarchyPanel);
	panels.push_back(&inspectorPanel);
	panels.push_back(&worldViewPanel);
	panels.push_back(&gameViewPanel);
	panels.push_back(&dialoguePanel);
	panels.push_back(&assetPanel);
	panels.push_back(&debugPanel);
	panels.push_back(&menuPanel);

	Init();
}
void EditorManager::Init()
{
	isScenePaused = true;
	selectedEntity = nullptr;
	SRT = 0;
	stackPointer = 0;

	for (size_t p = 0; p < panels.size(); p++)
	{
		panels[p]->Init();
		std::cout << p << "    init\n";
	}
	/*hierarchyPanel.Init();
	inspectorPanel.Init();
	worldViewPanel.Init();
	gameViewPanel.Init();
	dialoguePanel.Init();
	assetPanel.Init();
	debugPanel.Init();
	menuPanel.Init();*/
}

/*!*****************************************************************************
\brief
	Creates the level editor window

\return
None.
*******************************************************************************/
void EditorManager::Window()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	//ImGui::ShowDemoWindow();
}
/*!*****************************************************************************
\brief
	Updates the Level editor

\return
None.
*******************************************************************************/
void EditorManager::Update()
{
	Window();
	//weatherAIupdate();
	for (size_t p = 0; p < panels.size(); p++)
	{
			panels[p]->Update();
	}
	/*hierarchyPanel.Update();
	inspectorPanel.Update();
	worldViewPanel.Update();
	gameViewPanel.Update();
	dialoguePanel.Update();
	assetPanel.Update();
	debugPanel.Update();
	menuPanel.Update();*/

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}
	
}
/*!*****************************************************************************
\brief
	free

\return
None.
*******************************************************************************/
void EditorManager::Free()
{
	isScenePaused = false;
	for (size_t p = 0; p < panels.size(); p++)
	{
		panels[p]->Free();
	}
	/*hierarchyPanel.Free();
	inspectorPanel.Free();
	worldViewPanel.Free();
	gameViewPanel.Free();
	dialoguePanel.Free();
	assetPanel.Free();
	debugPanel.Free();
	menuPanel.Free();*/
}
/*!*****************************************************************************
\brief
	Shuts down Imgui, release all resources

\return
None.
*******************************************************************************/
void EditorManager::Unload()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void EditorManager::SaveUndo(Entity const e, COMPONENT& _old, COMPONENTID _id)
{
	static int lastID = -1;
	if (ImGui::IsItemActivated())
	{
		if (_id == COMPONENTID::GENERAL)
			_old = e.GetComponent<General>();
		else if (_id == COMPONENTID::LIFESPAN)
			_old = e.GetComponent<Lifespan>();
		else if (_id == COMPONENTID::TRANSFORM)
			_old = e.GetComponent<Transform>();
		else if (_id == COMPONENTID::SPRITE)
			_old = e.GetComponent<Sprite>();
		else if (_id == COMPONENTID::ANIMATION)
			_old = e.GetComponent<Animation>();
		else if (_id == COMPONENTID::SHEETANIMATION)
			_old = e.GetComponent<SheetAnimation>();
		else if (_id == COMPONENTID::PHYSICS2D)
			_old = e.GetComponent<Physics2D>();
		else if (_id == COMPONENTID::RECTCOLLIDER)
			_old = e.GetComponent<RectCollider>();
		else if (_id == COMPONENTID::CIRCLECOLLIDER)
			_old = e.GetComponent<CircleCollider>();
		else if (_id == COMPONENTID::EDGE2DCOLLIDER)
			_old = e.GetComponent<Edge2DCollider>();
		else if (_id == COMPONENTID::POINT2DCOLLIDER)
			_old = e.GetComponent<Point2DCollider>();
		else if (_id == COMPONENTID::AUDIO)
			_old = e.GetComponent<Audio>();
		else if (_id == COMPONENTID::TEXT)
			_old = e.GetComponent<Text>();
		else if (_id == COMPONENTID::AI)
			_old = e.GetComponent<AI>();
		else if (_id == COMPONENTID::SCRIPT)
			_old = e.GetComponent<Script>();
		else if (_id == COMPONENTID::DIALOGUE)
			_old = e.GetComponent<Dialogue>();
		else if (_id == COMPONENTID::PLAYERTMP)
			_old = e.GetComponent<PlayerTmp>();
	}
	if (ImGui::IsItemDeactivatedAfterEdit())
	{
		//undoStack.erase(undoStack.begin() + stackPointer-1);
		if (lastID != (int)_id)
		{
			undoStack.push_back(std::make_pair(e, _old));
			stackPointer = (int)undoStack.size();
		}
		COMPONENT _new;
		if (_id == COMPONENTID::GENERAL)
			_new = e.GetComponent<General>();
		else if (_id == COMPONENTID::LIFESPAN)
			_new = e.GetComponent<Lifespan>();
		else if (_id == COMPONENTID::TRANSFORM)
			_new = e.GetComponent<Transform>();
		else if (_id == COMPONENTID::SPRITE)
			_new = e.GetComponent<Sprite>();
		else if (_id == COMPONENTID::ANIMATION)
			_new = e.GetComponent<Animation>();
		else if (_id == COMPONENTID::SHEETANIMATION)
			_new = e.GetComponent<SheetAnimation>();
		else if (_id == COMPONENTID::PHYSICS2D)
			_new = e.GetComponent<Physics2D>();
		else if (_id == COMPONENTID::RECTCOLLIDER)
			_new = e.GetComponent<RectCollider>();
		else if (_id == COMPONENTID::CIRCLECOLLIDER)
			_new = e.GetComponent<CircleCollider>();
		else if (_id == COMPONENTID::EDGE2DCOLLIDER)
			_new = e.GetComponent<Edge2DCollider>();
		else if (_id == COMPONENTID::POINT2DCOLLIDER)
			_new = e.GetComponent<Point2DCollider>();
		else if (_id == COMPONENTID::AUDIO)
			_new = e.GetComponent<Audio>();
		else if (_id == COMPONENTID::TEXT)
			_new = e.GetComponent<Text>();
		else if (_id == COMPONENTID::AI)
			_new = e.GetComponent<AI>();
		else if (_id == COMPONENTID::SCRIPT)
			_new = e.GetComponent<Script>();
		else if (_id == COMPONENTID::DIALOGUE)
			_new = e.GetComponent<Dialogue>();
		else if (_id == COMPONENTID::PLAYERTMP)
			_new = e.GetComponent<PlayerTmp>();

		undoStack.push_back(std::make_pair(e, _new));
		stackPointer = (int)undoStack.size();
		lastID = (int)_id;
	}
}

void EditorManager::Do()
{
	if (undoStack[stackPointer].second.index() == (int)COMPONENTID::GENERAL)
		(undoStack[stackPointer].first).GetComponent<General>() = std::get<General>(undoStack[stackPointer].second);
	else if (undoStack[stackPointer].second.index() == (int)COMPONENTID::LIFESPAN)
		(undoStack[stackPointer].first).GetComponent<Lifespan>() = std::get<Lifespan>(undoStack[stackPointer].second);
	if (undoStack[stackPointer].second.index() == (int)COMPONENTID::TRANSFORM)
		(undoStack[stackPointer].first).GetComponent<Transform>() = std::get<Transform>(undoStack[stackPointer].second);
	else if (undoStack[stackPointer].second.index() == (int)COMPONENTID::SPRITE)
		(undoStack[stackPointer].first).GetComponent<Sprite>() = std::get<Sprite>(undoStack[stackPointer].second);
	else if (undoStack[stackPointer].second.index() == (int)COMPONENTID::ANIMATION)
		(undoStack[stackPointer].first).GetComponent<Animation>() = std::get<Animation>(undoStack[stackPointer].second);
	else if (undoStack[stackPointer].second.index() == (int)COMPONENTID::SHEETANIMATION)
		(undoStack[stackPointer].first).GetComponent<SheetAnimation>() = std::get<SheetAnimation>(undoStack[stackPointer].second);
	else if (undoStack[stackPointer].second.index() == (int)COMPONENTID::PHYSICS2D)
		(undoStack[stackPointer].first).GetComponent<Physics2D>() = std::get<Physics2D>(undoStack[stackPointer].second);
	else if (undoStack[stackPointer].second.index() == (int)COMPONENTID::RECTCOLLIDER)
		(undoStack[stackPointer].first).GetComponent<RectCollider>() = std::get<RectCollider>(undoStack[stackPointer].second);
	else if (undoStack[stackPointer].second.index() == (int)COMPONENTID::CIRCLECOLLIDER)
		(undoStack[stackPointer].first).GetComponent<CircleCollider>() = std::get<CircleCollider>(undoStack[stackPointer].second);
	else if (undoStack[stackPointer].second.index() == (int)COMPONENTID::EDGE2DCOLLIDER)
		(undoStack[stackPointer].first).GetComponent<Edge2DCollider>() = std::get<Edge2DCollider>(undoStack[stackPointer].second);
	else if (undoStack[stackPointer].second.index() == (int)COMPONENTID::POINT2DCOLLIDER)
		(undoStack[stackPointer].first).GetComponent<Point2DCollider>() = std::get<Point2DCollider>(undoStack[stackPointer].second);
	else if (undoStack[stackPointer].second.index() == (int)COMPONENTID::AUDIO)
		(undoStack[stackPointer].first).GetComponent<Audio>() = std::get<Audio>(undoStack[stackPointer].second);
	else if (undoStack[stackPointer].second.index() == (int)COMPONENTID::TEXT)
		(undoStack[stackPointer].first).GetComponent<Text>() = std::get<Text>(undoStack[stackPointer].second);
	else if (undoStack[stackPointer].second.index() == (int)COMPONENTID::AI)
		(undoStack[stackPointer].first).GetComponent<AI>() = std::get<AI>(undoStack[stackPointer].second);
	else if (undoStack[stackPointer].second.index() == (int)COMPONENTID::SCRIPT)
		(undoStack[stackPointer].first).GetComponent<Script>() = std::get<Script>(undoStack[stackPointer].second);
	else if (undoStack[stackPointer].second.index() == (int)COMPONENTID::DIALOGUE)
		(undoStack[stackPointer].first).GetComponent<Dialogue>() = std::get<Dialogue>(undoStack[stackPointer].second);
	else if (undoStack[stackPointer].second.index() == (int)COMPONENTID::PLAYERTMP)
		(undoStack[stackPointer].first).GetComponent<PlayerTmp>() = std::get<PlayerTmp>(undoStack[stackPointer].second);
}
void EditorManager::Undo()
{
	if(stackPointer == (int)undoStack.size())
		stackPointer--;
	stackPointer--;
	if (stackPointer >= 0)
	{
		Do();
	}
	else
	{
		LOG_ERROR("FK LA NO MORE UNDOO");
		stackPointer = 0;
	}
}
void EditorManager::Redo()
{
	stackPointer++;
	if (stackPointer < (int)undoStack.size())
	{
		Do();
	}
	else
	{
		LOG_ERROR("NO MORE REDOO");
		stackPointer = (int)undoStack.size();
	}
}
bool EditorManager::GetPannelIsActive(E_PANELID _panel)
{
	if ((int)_panel < panels.size())
		return panels[(int)_panel]->isActive();
	return false;
	/*if (_panel == E_PANELID::DIALOGUE)
	{
		return dialoguePanel.isActive();
	}
	else if (_panel == E_PANELID::DEBUG)
	{
		return debugPanel.isActive();
	}*/
}
void EditorManager::SetPannelIsActive(E_PANELID _panel, bool _isActive)
{
	if((int)_panel < panels.size())
		panels[(int)_panel]->setIsActive(_isActive);
	/*if (_panel == E_PANELID::DIALOGUE)
	{
		dialoguePanel.setIsActive(_isActive);
	}
	else if (_panel == E_PANELID::DEBUG)
	{
		debugPanel.setIsActive(_isActive);
	}*/
}




























/*!*****************************************************************************
\brief
	Debig logger pannel

\return
None.
*******************************************************************************/
//void EditorManager::ShowDebugInfo()
//{
	/*std::vector<std::pair<Logger::E_LOGLEVEL, std::string>> loggerStr = Logger::GetInstance()->GetLoggerStr();
	ImGui::Begin("Debug Logger");
	ImGui::BeginTabBar("DebugLogger ");
	if (ImGui::BeginTabItem("All Logs "))
	{
		for (auto str : loggerStr)
		{
			ImGui::Text(str.second.c_str());
		}
		ImGui::EndTabItem();
	}

	if (ImGui::BeginTabItem("Info Log "))
	{
		for (auto str : loggerStr)
		{
			if (str.first == Logger::E_LOGLEVEL::LOG_INFO)
				ImGui::Text(str.second.c_str());
		}
		ImGui::EndTabItem();
	}

	if (ImGui::BeginTabItem("Debug Log "))
	{
		
		for (auto str : loggerStr)
		{
			if (str.first == Logger::E_LOGLEVEL::LOG_DEBUG)
				ImGui::Text(str.second.c_str());
		}
		ImGui::EndTabItem();
	}

	if (ImGui::BeginTabItem("Warning Log "))
	{
		for (auto str : loggerStr)
		{
			if (str.first == Logger::E_LOGLEVEL::LOG_WARN)
				ImGui::Text(str.second.c_str());
		}
		ImGui::EndTabItem();
	}
	if (ImGui::BeginTabItem("Error Log "))
	{
		for (auto str : loggerStr)
		{
			if (str.first == Logger::E_LOGLEVEL::LOG_ERROR)
				ImGui::Text(str.second.c_str());
		}
		ImGui::EndTabItem();
	}
	if (ImGui::BeginTabItem("Custom Log "))
	{
		for (auto str : loggerStr)
		{
			if (str.first > Logger::E_LOGLEVEL::LOG_ASSERT)
				ImGui::Text(str.second.c_str());
		}
		ImGui::EndTabItem();
	}
	ImGui::Text("   ");
	ImGui::EndTabBar();
	ImGui::End();*/
//}
/*!*****************************************************************************
\brief
	Scene manager pannel

\return
None.
*******************************************************************************/
//void  EditorManager::SceneManager()
//{
	//static int n = 0;
	//ImGui::Begin("Scene Manager");
	//ImGui::BeginTabBar("Edit Scene ");
	//if (ImGui::BeginTabItem("Edit Game: "))
	//{
	//	std::vector<std::string> tag { "PLAYER","PASSENGER", "ENEMY", "BUILDING","BACKGROUND", "OTHERS" };
	//	for (int i = 0; i < (int)tag.size(); i++)
	//	{

	//		//if (ImGui::TreeNode(tag[i].c_str()))
	//		if(ImGui::CollapsingHeader(tag[i].c_str()))
	//		{
	//			int counter = 0;
	//			static bool first[20]{};
	//			for (const Entity& e : mEntities)
	//			{
	//				if (e.GetComponent<General>().tag != (TAG)i)
	//					continue;
	//				++counter;
	//				const char* lbl = e.GetComponent<General>().name.c_str();
	//				if (ImGui::TreeNode(lbl))
	//				{
	//					if (e.HasComponent<General>())
	//					{
	//						ImGui::Text("General");
	//						if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
	//						{
	//							selectedEntity = &e;
	//						}
	//					}
	//					if (e.HasComponent<Lifespan>())
	//					{
	//						ImGui::Text("Lifespan");
	//						if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
	//						{
	//							selectedEntity = &e;
	//						}
	//					}
	//					if (e.HasComponent<Transform>())
	//					{
	//						ImGui::Text("Transform");
	//						if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
	//						{
	//							selectedEntity = &e;
	//						}
	//					}
	//					if (e.HasComponent<Sprite>())
	//					{
	//						ImGui::Text("Sprite");
	//						if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
	//						{
	//							selectedEntity = &e;
	//						}
	//					}
	//					if (e.HasComponent<Animation>())
	//					{
	//						ImGui::Text("Animation");
	//						if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
	//						{
	//							selectedEntity = &e;
	//						}
	//					}
	//					if (e.HasComponent<SheetAnimation>())
	//					{
	//						ImGui::Text("SheetAnimation");
	//						if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
	//						{
	//							selectedEntity = &e;
	//						}
	//					}
	//					if (e.HasComponent<Physics2D>())
	//					{
	//						ImGui::Text("Physics2D");
	//						if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
	//						{
	//							selectedEntity = &e;
	//						}
	//					}
	//					if (e.HasComponent<RectCollider>())
	//					{
	//						ImGui::Text("RectCollider");
	//						if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
	//						{
	//							selectedEntity = &e;
	//						}
	//					}
	//					if (e.HasComponent<CircleCollider>())
	//					{
	//						ImGui::Text("CircleCollider");
	//						if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
	//						{
	//							selectedEntity = &e;
	//						}
	//					}
	//					if (e.HasComponent<Edge2DCollider>())
	//					{
	//						ImGui::Text("Edge2DCollider");
	//						if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
	//						{
	//							selectedEntity = &e;
	//						}
	//					}
	//					if (e.HasComponent<Stuff>())
	//					{
	//						ImGui::Text("Stuff");
	//						if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
	//						{
	//							selectedEntity = &e;
	//						}
	//					}
	//					if (e.HasComponent<Audio>())
	//					{
	//						ImGui::Text("Audio");
	//						if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
	//						{
	//							selectedEntity = &e;
	//						}
	//					}
	//					if (e.HasComponent<Stuff>())
	//					{
	//						ImGui::Text("AI");
	//						if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
	//						{
	//							selectedEntity = &e;
	//						}
	//					}
	//					ImGui::TreePop();

	//				}
	//			}
	//			//ImGui::TreePop();
	//			if (ImGui::BeginPopupContextWindow(0, 1, false))
	//			{
	//				if (ImGui::MenuItem(" Create Entity"))
	//				{
	//					Math::Vec2 campos = renderManager->GetWorldCamera().GetPos();
	//					LOG_INFO("Created new entity");
	//					Entity e{ ECS::CreateEntity() };
	//					mEntities.insert(e);
	//					e.AddComponent(
	//						General{ "_NEW_"+std::to_string(n), TAG::OTHERS, SUBTAG::NOSUBTAG, true},
	//						Transform{ {150,150}, 0, campos },
	//						Sprite{ Color{0,255,0,100}, SPRITE::CIRCLE, 0 },
	//						RectCollider{ { 0.f, 0.f }, {1.f,1.f}, true });
	//					n++;
	//				}
	//				ImGui::EndPopup();
	//			}

	//		}
	//	}
	//	/*if (ImGui::TreeNode("Scene 2"))
	//	{
	//		ImGui::Text("Nothing");
	//		ImGui::TreePop();
	//	}*/
	//	ImGui::EndTabItem();
	//	if (ImGui::Button("New object"))
	//	{
	//		Math::Vec2 campos = renderManager->GetWorldCamera().GetPos();
	//		LOG_INFO("Created new entity");
	//		Entity e{ ECS::CreateEntity() };
	//		mEntities.insert(e);
	//		e.AddComponent(
	//			General{"_NEW_" + std::to_string(n), TAG::OTHERS, SUBTAG::NOSUBTAG, true},
	//			Transform{ {150,150}, 0, campos },
	//			Sprite{ Color{0,255,0,100}, SPRITE::CIRCLE, 0 },
	//			RectCollider{ { 0.f, 0.f }, {1.f,1.f}, true });
	//		n++;
	//	}
	//}
	//ImGui::EndTabBar();
	//ImGui::End();
//}
/*!*****************************************************************************
\brief
	Entity Manager pannel

\return
None.
*******************************************************************************/
//void EditorManager::EntityManager()
//{
	//float tmpVec2[2];
	//float tmpFloat;
	//float tmpVec4[4];
	//static Transform old{};
	//static COMPONENT tempComponent{};
	//ImGui::Begin("Entity Manager");
	//ImGui::BeginTabBar("Edit Entities ");
	//if (ImGui::BeginTabItem("Edit Game: "))
	//{
	//	if (selectedEntity != nullptr)
	//	{
	//		Entity e = *selectedEntity;		

	//		if (e.HasComponent<General>())
	//		{
	//			if (ImGui::CollapsingHeader("General")||true) {
	//				ImGui::Text("General");
	//					ImGui::Checkbox("isActive", &e.GetComponent<General>().isActive); //isactive
	//					SaveUndo(const_cast<Entity*>(selectedEntity), tempComponent, COMPONENTID::GENERAL);
	//					ImGui::InputText("Name", const_cast<char*>(e.GetComponent<General>().name.c_str()), 30);
	//					SaveUndo(const_cast<Entity*>(selectedEntity), tempComponent, COMPONENTID::GENERAL);
	//					int tagID = (int)e.GetComponent<General>().tag;
	//					static const char* tag[]{ "PLAYER","PASSENGER", "ENEMY", "BUILDING","BACKGROUND", "OTHERS" };
	//					ImGui::Combo("Tag", &tagID, tag, IM_ARRAYSIZE(tag));
	//					SaveUndo(const_cast<Entity*>(selectedEntity), tempComponent, COMPONENTID::GENERAL);
	//					e.GetComponent<General>().tag = (TAG)tagID;
	//					int subtagID = (int)e.GetComponent<General>().subtag;
	//					static const char* subtag[]{ "NOSUBTAG", "PLAYER", "PASSENGER", "ENEMY", "BUILDING", "OTHERS" };
	//					ImGui::Combo("SubTag", &subtagID, subtag, IM_ARRAYSIZE(subtag));
	//					SaveUndo(const_cast<Entity*>(selectedEntity), tempComponent, COMPONENTID::GENERAL);
	//					e.GetComponent<General>().subtag = (SUBTAG)subtagID;
	//			}
	//		}
	//		if (e.HasComponent<Lifespan>())
	//		{
	//			if (ImGui::CollapsingHeader("Lifespan")) {
	//				//ImGui::Text("Lifespan");
	//				ImGui::InputFloat("Lifespan", &e.GetComponent<Lifespan>().limit);
	//				if (ImGui::Button("Remove Lifespan"))
	//				{
	//					e.RemoveComponent<Lifespan>();
	//					LOG_INFO("Lifespan component removed");
	//				}
	//			}
	//		}
	//		
	//		if (e.HasComponent<Transform>())
	//		{
	//			if (ImGui::CollapsingHeader("Transform Gizmo")) {
	//				//ImGui::Text("Transform Gizmo: ");
	//				static bool s = 0,r = 0,t = 0;
	//				ImGui::Checkbox("Scale Gizmo", &s);
	//				if (s) { SRT = 1; r = t = 0; }
	//				ImGui::Checkbox("Rotate", &r);
	//				if (r) { SRT = 2; s = t = 0; }
	//				ImGui::Checkbox("Translate Gizmo", &t);
	//				if (t) { SRT = 3; s = r = 0; }
	//				if (!s && !r && !t) SRT = 0;
	//			}

	//			if (ImGui::CollapsingHeader("Transform")) {
	//				//ImGui::Text("Transform Component");
	//				tmpVec2[0] = transformManager->GetScale(e).x;
	//				tmpVec2[1] = transformManager->GetScale(e).y;
	//				ImGui::DragFloat2("Set Scale", tmpVec2);
	//				Math::Vec2 scale{ tmpVec2[0] ,tmpVec2[1] };
	//				transformManager->SetScale(e, scale);
	//				SaveUndo(const_cast<Entity*>(selectedEntity), tempComponent, COMPONENTID::TRANSFORM);

	//				tmpVec2[0] = transformManager->GetTranslate(e).x;
	//				tmpVec2[1] = transformManager->GetTranslate(e).y;
	//				ImGui::DragFloat2("Set Position", tmpVec2);
	//				Math::Vec2 pos{ tmpVec2[0] ,tmpVec2[1] };
	//				transformManager->SetTranslate(e, pos);
	//				SaveUndo(const_cast<Entity*>(selectedEntity), tempComponent, COMPONENTID::TRANSFORM);

	//				tmpFloat = transformManager->GetRotation(e);
	//				tmpFloat = (float)(tmpFloat / M_PI * 180.f);
	//				ImGui::SliderFloat("Set Rotation", &tmpFloat, -360.f, 360.f);
	//				tmpFloat = (float)(tmpFloat * M_PI / 180.f);
	//				transformManager->SetRotation(e, tmpFloat);
	//				SaveUndo(const_cast<Entity*>(selectedEntity), tempComponent, COMPONENTID::TRANSFORM);
	//				/*if (ImGui::Button("Remove Transform"))
	//				{
	//					e.RemoveComponent<Transform>();
	//					LOG_INFO("Transform component removed");
	//				}*/
	//			}
	//			
	//		}
	//		
	//		if (e.HasComponent<Sprite>())
	//		{
	//			if (ImGui::CollapsingHeader("Sprite")) {
	//				//ImGui::Text("Sprite");
	//				tmpVec4[0] = e.GetComponent<Sprite>().color.r /255.f;
	//				tmpVec4[1] = e.GetComponent<Sprite>().color.g / 255.f;
	//				tmpVec4[2] = e.GetComponent<Sprite>().color.b / 255.f;
	//				tmpVec4[3] = e.GetComponent<Sprite>().color.a / 255.f;
	//				ImGui::ColorEdit4("Color", tmpVec4);
	//				e.GetComponent<Sprite>().color.r = (GLubyte)(tmpVec4[0] * 255);
	//				e.GetComponent<Sprite>().color.g = (GLubyte)(tmpVec4[1] * 255);
	//				e.GetComponent<Sprite>().color.b = (GLubyte)(tmpVec4[2] * 255);
	//				e.GetComponent<Sprite>().color.a = (GLubyte)(tmpVec4[3] * 255);
	//				std::string tex{};
	//				if(e.GetComponent<Sprite>().sprite == SPRITE::TEXTURE)
	//					tex = spriteManager->GetTexturePath(spriteManager->GetTexture(e));
	//				else if (e.GetComponent<Sprite>().sprite == SPRITE::CIRCLE)
	//					tex = "CIRCLE";
	//				else if (e.GetComponent<Sprite>().sprite == SPRITE::SQUARE)
	//					tex = "SQUARE";
	//			
	//				int shapeID = (int)e.GetComponent<Sprite>().sprite;
	//				static const char* shape[]{"SQUARE", "CIRCLE", "TEXTURE","DEBUG_POINT" , "DEBUG_LINE","DEBUG_SQUARE","DEBUG_CIRCLE", "DEBUG_ARROW"};
	//				ImGui::Combo("Shape", &shapeID, shape, IM_ARRAYSIZE(shape));
	//				e.GetComponent<Sprite>().sprite = (SPRITE)shapeID;
	//				if ((SPRITE)shapeID != SPRITE::TEXTURE)
	//				{
	//					e.GetComponent<Sprite>().texture = 0;
	//				}
	//				ImGui::Text(tex.c_str());

	//				static const wchar_t* texpath = (const wchar_t*)"";
	//				if (ImGui::BeginDragDropTarget())
	//				{
	//					if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("TEXTURES"))
	//					{
	//						texpath = (const wchar_t*)payload->Data;
	//						std::string tp = (std::string)((const char*)texpath);
	//						e.GetComponent<Sprite>().sprite = SPRITE::TEXTURE;
	//						spriteManager->SetTexture(e, tp);
	//					}
	//					ImGui::EndDragDropTarget();
	//				}
	//				ImGui::InputInt("Layer", &e.GetComponent<Sprite>().layer);
	//				if (ImGui::Button("Remove Sprite"))
	//				{
	//					e.RemoveComponent<Sprite>();
	//					LOG_INFO("Sprite component removed");
	//				}
	//			}
	//		}
	//		if (e.HasComponent<Animation>())
	//		{
	//			if (ImGui::CollapsingHeader("Animation")) {
	//				//ImGui::Text("Animation");
	//				static GLuint addImage = {};
	//				static std::string  texadd =  "Add image";
	//				for (size_t i = 0; i <= e.GetComponent<Animation>().images.size(); ++i)
	//				{
	//					std::string tex{};
	//					if (i != e.GetComponent<Animation>().images.size())
	//					{
	//						tex = spriteManager->GetTexturePath(e.GetComponent<Animation>().images[i]);
	//						ImGui::Text(tex.c_str());
	//					}
	//					else
	//					{
	//						ImGui::InputText("Addimage", const_cast<char*>(texadd.c_str()), texadd.size());
	//						tex = texadd;
	//					}
	//					static const wchar_t* texpath = (const wchar_t*)"";
	//					if (ImGui::BeginDragDropTarget())
	//					{
	//						if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("TEXTURES"))
	//						{
	//							texpath = (const wchar_t*)payload->Data;
	//							if (i == e.GetComponent<Animation>().images.size())
	//								texadd= (char*)texpath;
	//							std::string  tp = (std::string)((const char*)texpath);
	//							if (i != e.GetComponent<Animation>().images.size())
	//								e.GetComponent<Animation>().images[i] = spriteManager->GetTextureID(tp);
	//							else
	//								addImage = spriteManager->GetTextureID(tp);
	//						}
	//						ImGui::EndDragDropTarget();
	//					}
	//				}
	//				if (ImGui::Button("Add Sprite"))
	//				{
	//					animator->AddImages(e, addImage);
	//				}
	//				ImGui::InputFloat("timePerImage", &e.GetComponent<Animation>().timePerImage);
	//				ImGui::InputFloat("timeToImageSwap", &e.GetComponent<Animation>().timeToImageSwap);
	//				ImGui::InputInt("currentImageIndex", &e.GetComponent<Animation>().currentImageIndex);
	//				if (ImGui::Button("Remove Animation"))
	//				{
	//					e.RemoveComponent<Animation>();
	//					LOG_INFO("Animation component removed");
	//				}
	//			}
	//		}
	//		if (e.HasComponent<SheetAnimation>())
	//		{
	//			if (ImGui::CollapsingHeader("SheetAnimation")) {
	//				//ImGui::Text("SheetAnimation");
	//				ImGui::InputInt("frameCount", (int*)&e.GetComponent<SheetAnimation>().frameCount);
	//				ImGui::InputInt("currFrameIndex", (int*)&e.GetComponent<SheetAnimation>().currFrameIndex);
	//				ImGui::InputFloat("timePerFrame", &e.GetComponent<SheetAnimation>().timePerFrame);
	//				ImGui::InputFloat("timeToFrameSwap", &e.GetComponent<SheetAnimation>().timeToFrameSwap);
	//				if (ImGui::Button("Remove SheetAnimation"))
	//				{
	//					e.RemoveComponent<SheetAnimation>();
	//					LOG_INFO("SheetAnimation component removed");
	//				}
	//			}
	//		}
	//		if (e.HasComponent<RectCollider>())
	//		{
	//			if (ImGui::CollapsingHeader("RectCollider")) {
	//				//ImGui::Text("RectCollider");
	//				tmpVec2[0] = e.GetComponent<RectCollider>().centerOffset.x;
	//				tmpVec2[1] = e.GetComponent<RectCollider>().centerOffset.y;
	//				ImGui::InputFloat2("Box position Offset", tmpVec2);
	//				e.GetComponent<RectCollider>().centerOffset = { tmpVec2[0] ,tmpVec2[1]};

	//				tmpVec2[0] = e.GetComponent<RectCollider>().scaleOffset.x;
	//				tmpVec2[1] = e.GetComponent<RectCollider>().scaleOffset.y;
	//				ImGui::InputFloat2("Box scale Offset", tmpVec2);
	//				e.GetComponent<RectCollider>().scaleOffset = { tmpVec2[0] ,tmpVec2[1] };

	//				ImGui::Checkbox("Rect RenderFlag", &e.GetComponent<RectCollider>().renderFlag);
	//				if (ImGui::Button("Remove RectCollider"))
	//				{
	//					e.RemoveComponent<RectCollider>();
	//					LOG_INFO("RectCollider component removed");
	//				}
	//			}
	//		}
	//		if (e.HasComponent<CircleCollider>())
	//		{
	//			if (ImGui::CollapsingHeader("CircleCollider")) {
	//				//ImGui::Text("CircleCollider");
	//				tmpVec2[0] = e.GetComponent<CircleCollider>().centerOffset.x;
	//				tmpVec2[1] = e.GetComponent<CircleCollider>().centerOffset.y;
	//				ImGui::InputFloat2("Circle position Offset", tmpVec2);
	//				e.GetComponent<CircleCollider>().centerOffset = { tmpVec2[0] ,tmpVec2[1] };
	//				SaveUndo(const_cast<Entity*>(selectedEntity), tempComponent, COMPONENTID::CIRCLECOLLIDER);

	//				float scale = e.GetComponent<CircleCollider>().scaleOffset;
	//				ImGui::InputFloat("Circle scale Offset", &scale);
	//				e.GetComponent<CircleCollider>().scaleOffset = { scale };
	//				SaveUndo(const_cast<Entity*>(selectedEntity), tempComponent, COMPONENTID::CIRCLECOLLIDER);

	//				ImGui::Checkbox("Circle RenderFlag", &e.GetComponent<CircleCollider>().renderFlag);
	//				SaveUndo(const_cast<Entity*>(selectedEntity), tempComponent, COMPONENTID::CIRCLECOLLIDER);

	//				if (ImGui::Button("Remove CircleCollider"))
	//				{
	//					e.RemoveComponent<CircleCollider>();
	//					LOG_INFO("CircleCollider component removed");
	//				}
	//			}
	//		}
	//		if (e.HasComponent<Edge2DCollider>())
	//		{
	//			if (ImGui::CollapsingHeader("Edge2DCollider")) {
	//				//ImGui::Text("Edge2DCollider");
	//				tmpVec2[0] = e.GetComponent<Edge2DCollider>().p0Offset.x;
	//				tmpVec2[1] = e.GetComponent<Edge2DCollider>().p0Offset.y;
	//				ImGui::InputFloat2("p0 Offset", tmpVec2);
	//				e.GetComponent<Edge2DCollider>().p0Offset = { tmpVec2[0] ,tmpVec2[1] };

	//				ImGui::InputFloat("rotationOffset", &e.GetComponent<Edge2DCollider>().rotationOffset);
	//				ImGui::InputFloat("scaleOffset", &e.GetComponent<Edge2DCollider>().scaleOffset);
	//				ImGui::Checkbox("RenderFlag", &e.GetComponent<Edge2DCollider>().renderFlag);
	//				if (ImGui::Button("Remove Edge2DCollider"))
	//				{
	//					e.RemoveComponent<Edge2DCollider>();
	//					LOG_INFO("Edge2DCollider component removed");
	//				}
	//			}
	//		}
	//		if (e.HasComponent<Point2DCollider>())
	//		{
	//			if (ImGui::CollapsingHeader("Point2DCollider")) {
	//				//ImGui::Text("Point2DCollider");
	//				tmpVec2[0] = e.GetComponent<Point2DCollider>().centerOffset.x;
	//				tmpVec2[1] = e.GetComponent<Point2DCollider>().centerOffset.y;
	//				ImGui::InputFloat2("centerOffset", tmpVec2);
	//				e.GetComponent<Point2DCollider>().centerOffset = { tmpVec2[0] ,tmpVec2[1] };

	//				ImGui::Checkbox("RenderFlag", &e.GetComponent<Point2DCollider>().renderFlag);
	//				if (ImGui::Button("Remove Point2DCollider"))
	//				{
	//					e.RemoveComponent<Point2DCollider>();
	//					LOG_INFO("Point2DCollider component removed");	
	//				}
	//			}
	//		}
	//		if (e.HasComponent<Physics2D>())
	//		{
	//			if (ImGui::CollapsingHeader("Physics2D")) {
	//				//ImGui::Text("Physics2D");
	//				ImGui::InputFloat("Mass", &e.GetComponent<Physics2D>().mass);
	//				ImGui::InputFloat("Speed", &e.GetComponent<Physics2D>().speed);
	//				ImGui::InputFloat("moveDirection", &e.GetComponent<Physics2D>().moveDirection);
	//				ImGui::Checkbox("gravityEnabled", &e.GetComponent<Physics2D>().gravityEnabled);
	//				ImGui::Checkbox("Physics RenderFlag", &e.GetComponent<Physics2D>().renderFlag);
	//				if (ImGui::Button("Remove Physics2D"))
	//				{
	//					e.RemoveComponent<Physics2D>();
	//					LOG_INFO("Physics2D component removed");
	//				}
	//			}
	//		}
	//		if (e.HasComponent<Audio>())
	//		{
	//			if (ImGui::CollapsingHeader("Audio")) {
	//				//ImGui::Text("Audio");
	//				ImGui::InputText("Addsound", const_cast<char*>(e.GetComponent<Audio>().sound.path.c_str()), 30);
	//				ImGui::Checkbox("Pause", &e.GetComponent<Audio>().sound.isPaused);
	//				ImGui::Checkbox("Click to Play", &e.GetComponent<Audio>().sound.toPlay);
	//				//ImGui::Checkbox("isLoop", &e.GetComponent<Audio>().sound.isLoop);
	//				if (ImGui::Button("Remove Audio"))
	//				{
	//					e.RemoveComponent<Audio>();
	//					LOG_INFO("Audio component removed");
	//				}
	//			}
	//		}
	//		if (e.HasComponent<Stuff>())
	//		{
	//			if (ImGui::CollapsingHeader("AI")) {
	//				static const char* colorChange[]{ "None","Smoothy","Traffic Light" };
	//				int colorChangeID = e.GetComponent<Stuff>().colorChange;
	//				ImGui::Combo("Select Color Change", &colorChangeID, colorChange, IM_ARRAYSIZE(colorChange));
	//				e.GetComponent<Stuff>().colorChange = colorChangeID;

	//				static const char* movement[]{ "None","UP-Down","Left-Right", "Swing", "Circle" };
	//				int movementID = e.GetComponent<Stuff>().movement;
	//				ImGui::Combo("Select Movement", &movementID, movement, IM_ARRAYSIZE(movement));
	//				e.GetComponent<Stuff>().movement = movementID;

	//				if (e.GetComponent<Stuff>().movement)
	//				{
	//					float speed = e.GetComponent<Stuff>().speed;
	//					ImGui::SliderFloat("Speed", &speed, 0.f, 15.f);
	//					e.GetComponent<Stuff>().speed = speed;
	//					if (e.GetComponent<Stuff>().movement < 4)
	//					{
	//						float range = e.GetComponent<Stuff>().range;
	//						ImGui::SliderFloat("Range", &range, 0.f, 400.f);
	//						e.GetComponent<Stuff>().range = range;
	//					}
	//				}
	//				if (ImGui::Button("Remove AI"))
	//				{
	//					e.RemoveComponent<Stuff>();
	//					LOG_INFO("AI component removed");
	//				}
	//			}
	//		}

	//		static int componentsID;
	//		static const char* components[]{ "General","Lifespan","Transform", "Sprite" ,"Animation","SheetAnimation","Physics2D",
	//			"RectCollider" , "CircleCollider" ,"Edge2DCollider" ,"Audio" ,"AI" };
	//		ImGui::Combo("Select Component", &componentsID, components, IM_ARRAYSIZE(components));
	//		if (ImGui::Button("Add Component"))
	//		{
	//			if      (componentsID == 0)
	//				e.AddComponent<General>({ "_new_", (TAG)0, (SUBTAG)0, true});
	//			else if (componentsID == 1)
	//				e.AddComponent<Lifespan>({0,1000});
	//			else if (componentsID == 2)
	//				e.AddComponent<Transform>({ {100,100}, 0, {0,0} });
	//			else if (componentsID == 3)
	//				e.AddComponent<Sprite>({});
	//			else if (componentsID == 4)
	//				e.AddComponent<Animation>({});
	//			else if (componentsID == 5)
	//				e.AddComponent<SheetAnimation>({});
	//			else if (componentsID == 6)
	//				e.AddComponent<Physics2D>({});
	//			else if (componentsID == 7)
	//				e.AddComponent<RectCollider>({ });
	//			else if (componentsID == 8)
	//				e.AddComponent<CircleCollider>({});
	//			else if (componentsID == 9)
	//				e.AddComponent<Edge2DCollider>({});
	//			else if (componentsID == 10)
	//				e.AddComponent<Audio>({});
	//			else if (componentsID == 11)
	//				e.AddComponent<Stuff>({});
	//			std::string add(components[componentsID]);
	//			LOG_INFO(add+"conponent added");
	//		}
	//		if (ImGui::BeginPopupContextWindow(0, 1, false))
	//		{
	//			if (ImGui::MenuItem("Delete Entity"))
	//			{
	//				e.Destroy();
	//				LOG_INFO("Entity deleated");
	//				selectedEntity = nullptr;
	//				//selectedEntityID = 99;
	//			}
	//			ImGui::EndPopup();
	//		}
	//	}
	//	ImGui::EndTabItem();
	//	
	//}
	//ImGui::EndTabBar();
	//ImGui::End();
//}
/*!*****************************************************************************
\brief
	Asset manager pannel

\return
None.
*******************************************************************************/
//void  EditorManager::AssetManager()
//{
	//GLuint my_image_texture = spriteManager->GetTextureID("Textures\\Icons\\folderIcon.png");
	//GLuint my_image2_texture = 0;
	//std::string rootPath = "..\\resources";
	//ImVec2 buttonSize = { 100,100 };
	//ImGui::Begin("Asset Manager");
	//ImGui::BeginTabBar("Assets ");
	//if (ImGui::BeginTabItem("Content Browser")) {
	//	// switch to the newly selected tab
	//	static std::filesystem::path m_CurrentDirectory = std::filesystem::path(rootPath);
	//	if (m_CurrentDirectory != std::filesystem::path(rootPath))
	//	{
	//		if (ImGui::Button("<- BACK", buttonSize))
	//		{
	//			m_CurrentDirectory = m_CurrentDirectory.parent_path();
	//		}
	//	}
	//	for (auto& directory : std::filesystem::directory_iterator(m_CurrentDirectory))
	//	{
	//		const auto& path = directory.path();
	//		auto relativePath = std::filesystem::relative(path, rootPath);
	//		std::string filename = relativePath.filename().string();
	//		ImGui::Columns(3);

	//		ImTextureID folderIcon = (void*)(intptr_t)my_image_texture;
	//		if (directory.is_directory())
	//		{
	//			ImGui::ImageButton(folderIcon, buttonSize, ImVec2(0, 1), ImVec2(1, 0));
	//		}
	//		else
	//		{
	//			std::string texPath = directory.path().string();
	//			texPath = texPath.substr(13);
	//			my_image2_texture = spriteManager->GetTextureID(texPath);
	//			if (my_image2_texture)
	//			{
	//				ImTextureID textureImage = (void*)(intptr_t)my_image2_texture;
	//				ImGui::ImageButton(textureImage, buttonSize, ImVec2(0, 1), ImVec2(1, 0));
	//				if (ImGui::BeginDragDropSource())
	//				{
	//					const wchar_t* itemPath = (wchar_t*)texPath.c_str();
	//					ImGui::SetDragDropPayload("TEXTURES", itemPath, (wcslen(itemPath) + 1) * sizeof(wchar_t) , ImGuiCond_Once);
	//					ImGui::EndDragDropSource();
	//				}
	//			}
	//			else
	//				ImGui::Button(filename.c_str(), buttonSize);
	//		}
	//		if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
	//		{
	//			if (directory.is_directory())
	//				m_CurrentDirectory /= path.filename();
	//			else
	//			{
	//				std::string filename = directory.path().stem().string();
	//				std::cout << filename.substr(0, 7);
	//				if (filename.substr(0, 6) == "Dialog")
	//				{
	//					serializationManager->LoadDialogs(filename);
	//				}
	//				else if (filename.substr(0, 5) == "Scene")
	//				{
	//					serializationManager->LoadScene(filename);
	//				}

	//			}
	//		}
	//		ImGui::Text(filename.c_str());
	//		ImGui::NextColumn();
	//	}
	//	ImGui::Columns(1);
	//	ImGui::Text("   ");
	//	ImGui::EndTabItem();
	//}
	//ImGui::EndTabBar();
	//ImGui::End();
//}
/*!*****************************************************************************
\brief
	Viewport manager pannel

\return
None.
*******************************************************************************/
//void EditorManager::ViewPortManager()
//{
	//ImGui::Begin("View Port Manager");
	//WorldViewPort();
	//CameraViewPort();
	//ImGui::End();
//}
//void  EditorManager::WorldViewPort()
//{
	//ImGuiWindowFlags window_flags = 0;
	//window_flags |= ImGuiWindowFlags_NoBackground;
	////bool open_ptr = true;
	////ImGui::Begin("View Port Manager", &open_ptr, window_flags);
	//ImGui::Begin("World View");
	//Math::Vec2 viewportSize = { ImGui::GetWindowSize().x,ImGui::GetWindowSize().y };
	//viewportSize.y -= 70;
	////Calcualting the aspect ratio 
	//if (viewportSize.x / viewportSize.y > 16 / 9.0f) //wide screen
	//{
	//	viewportSize.x = viewportSize.y / 9 * 16;
	//}
	//else if (viewportSize.x / viewportSize.y < 16 / 9.0f) // tall screen
	//{
	//	viewportSize.y = viewportSize.x / 16 * 9;
	//}
	//Math::Vec2 pos = { (ImGui::GetWindowWidth() / 2.f) - 110.f, 30.f };
	//ImGui::SetCursorPos(ImVec2(pos.x, pos.y));
	////if (ImGui::Button("Reset", { 100,25 }))
	//	//serializationManager->LoadScene("SceneTmp");
	////ImGui::SameLine(0.f,20.f);
	//if (ImGui::Button("Play", { 100,25 }))
	//{
	//	//serializationManager->SaveScene("SceneTmp");
	//	//isPaused = false;
	//	renderManager->GetWorldCamera() *= 0.01f;
	//}
	//ImGui::SameLine(0.f, 20.f);
	//if (ImGui::Button("Pause", { 100,25 }))
	//	isPaused = true;
	//static Math::Vec2 ScreenMousePos{};
	//static Math::Vec2 WorldMousePos{};
	//static Math::Vec2 CamMousePos{};
	//pos = { (ImGui::GetWindowWidth() - viewportSize.x) * 0.5f, 60.f };
	//ImGui::SetCursorPos(ImVec2(pos.x, pos.y));
	//	ScreenMousePos = Input::CursorPos() - Math::Vec2{ ImGui::GetWindowPos().x,ImGui::GetWindowPos().y } - pos - viewportSize / 2;
	//	WorldMousePos = ScreenMousePos;
	//	WorldMousePos.y = -WorldMousePos.y;
	//	WorldMousePos.x = WorldMousePos.x / viewportSize.x * *mWindowWidth;
	//	WorldMousePos.y = WorldMousePos.y / viewportSize.y * *mWindowHeight;
	//	CamMousePos = WorldMousePos * renderManager->GetWorldCamera().GetZoom() + renderManager->GetWorldCamera().GetPos();
	//if (ImGui::IsWindowHovered())
	//{
	//	const Math::Vec2 moveHorizontal{ 1, 0 };
	//	const Math::Vec2 moveVertical{ 0, 1 };
	//	const float zoom{ 0.1f };
	//	static Math::Vec2 camOffset{};
	//	static Math::Vec2 camPos{};
	//	static Math::Vec2 offset{};
	//	static int isSelected = 0;
	//	if (abs(ScreenMousePos.x) < viewportSize.x / 2 && abs(ScreenMousePos.y) < viewportSize.y / 2)
	//	{
	//		//Camera movement
	//		if (Input::CheckKey(E_STATE::HOLD, E_KEY::UP))
	//		{
	//			renderManager->GetWorldCamera() += moveVertical;
	//		}
	//		if (Input::CheckKey(E_STATE::HOLD, E_KEY::DOWN))
	//		{
	//			renderManager->GetWorldCamera() -= moveVertical;
	//		}
	//		if (Input::CheckKey(E_STATE::HOLD, E_KEY::RIGHT))
	//		{
	//			renderManager->GetWorldCamera() += moveHorizontal;
	//		}
	//		if (Input::CheckKey(E_STATE::HOLD, E_KEY::LEFT))
	//		{
	//			renderManager->GetWorldCamera() -= moveHorizontal;
	//		}
	//		if (Input::CheckKey(E_STATE::PRESS, E_KEY::M_BUTTON_L) && !isSelected)
	//		{
	//			camOffset = CamMousePos;
	//		}
	//		if (Input::CheckKey(E_STATE::HOLD, E_KEY::M_BUTTON_L) && !isSelected)
	//		{
	//			camPos = -(WorldMousePos * renderManager->GetWorldCamera().GetZoom() - camOffset);
	//			renderManager->GetWorldCamera().SetPos(camPos);
	//		}
	//		if (Input::GetScroll() > 0.0) //scroll up   // zoon in
	//		{

	//			renderManager->GetWorldCamera() += WorldMousePos * zoom;
	//			renderManager->GetWorldCamera() *= -zoom;
	//			//renderManager->GetWorldCamera() -= -mousePos;
	//		}
	//		else if (Input::GetScroll() < 0.0)  //scroll down //zoom out
	//		{
	//			renderManager->GetWorldCamera() -= WorldMousePos * zoom;
	//			renderManager->GetWorldCamera() *= zoom;
	//			//renderManager->GetWorldCamera() += -mousePos;
	//		}
	//	}
	//	if (Input::CheckKey(E_STATE::NOTPRESS, E_KEY::M_BUTTON_L))
	//		isSelected = 0;

	//	//object picking
	//	if (Input::CheckKey(E_STATE::PRESS, E_KEY::M_BUTTON_L) && (abs(ScreenMousePos.x) < viewportSize.x / 2 && abs(ScreenMousePos.y) < viewportSize.y / 2))
	//	{
	//		int layer = 0;
	//		for (const Entity& e : mEntities)
	//		{
	//			if (e.GetComponent<General>().tag == TAG::BACKGROUND)
	//				continue;
	//			if (e.HasComponent<Transform>() && e.HasComponent<Sprite>())
	//			{
	//				Math::Vec2 scale = e.GetComponent<Transform>().scale;
	//				Math::Vec2 translation = e.GetComponent<Transform>().translation;
	//				Math::Vec2 distance = CamMousePos - translation;
	//				if (abs(distance.x) < scale.x / 2 && abs(distance.y) < scale.y / 2)
	//				{
	//					LOG_INFO(e.GetComponent<General>().name + " Selected");
	//					if (e.GetComponent<Sprite>().layer >= layer)
	//					{
	//						selectedEntity = &e;
	//						layer = e.GetComponent<Sprite>().layer;
	//						offset = distance;
	//						isSelected = 1;
	//					}
	//				}
	//			}
	//		}
	//	}

	//	if (selectedEntity != nullptr && (*selectedEntity).GetComponent<General>().tag != TAG::BACKGROUND)// && selectedEntityID <= (int)mEntities.size())
	//	{
	//		const Entity& e = *selectedEntity;
	//		if (SRT == 0)
	//		{
	//			Math::Vec2 scale = e.GetComponent<Transform>().scale;
	//			Math::Vec2 translation = e.GetComponent<Transform>().translation;
	//			Math::Vec2 distance = CamMousePos - translation;
	//			//if (Input::CheckKey(E_STATE::HOLD, E_KEY::M_BUTTON_L) && (abs(ScreenMousePos.x) < viewportSize.x / 2 && abs(ScreenMousePos.y) < viewportSize.y / 2))
	//			if (Input::CheckKey(E_STATE::HOLD, E_KEY::M_BUTTON_L) && (abs(distance.x) < scale.x / 2 && abs(distance.y) < scale.y / 2))
	//			{
	//				e.GetComponent<Transform>().translation = CamMousePos - offset;
	//				isSelected = 1;
	//			}
	//			if (Input::CheckKey(E_STATE::HOLD, E_KEY::M_BUTTON_L) && isSelected == 1)
	//			{
	//				e.GetComponent<Transform>().translation = CamMousePos - offset;
	//			}
	//		}
	//		else
	//		{
	//			//imguizmo
	//			ImGuizmo::SetOrthographic(true);
	//			ImGuizmo::SetDrawlist();
	//			ImGuizmo::SetRect(ImGui::GetWindowPos().x + pos.x, ImGui::GetWindowPos().y + pos.y,
	//				viewportSize.x, viewportSize.y);
	//			const float identity[16] = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };
	//			std::vector<float> trf = renderManager->GetImGuizmoMat4(e);
	//			float translate[16] = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };
	//			for (int i = 0; i < 16; ++i)
	//			{
	//				translate[i] = trf[i];
	//			}

	//			ImGuizmo::OPERATION opp{};
	//			if (SRT == 1)
	//			{
	//				opp = ImGuizmo::OPERATION::SCALE;
	//			}
	//			else if (SRT == 2)
	//			{
	//				opp = ImGuizmo::OPERATION::ROTATE;
	//				//std::cout << translate[0] << " : " << translate[1] << "\n";
	//			}
	//			else if (SRT == 3)
	//			{
	//				opp = ImGuizmo::OPERATION::TRANSLATE;
	//			}
	//			ImGuizmo::Manipulate(&identity[0], &identity[0], opp, ImGuizmo::LOCAL, &translate[0]);
	//			if (ImGuizmo::IsUsing())
	//			{
	//				if (SRT == 1)
	//				{
	//					Math::Vec2 scaleX = { translate[0] , translate[1] };
	//					Math::Vec2 scaleY = { translate[4] , translate[5] };
	//					Math::Vec2 scale = { scaleX.Magnitude() * (float)*mWindowWidth , scaleY.Magnitude() * (float)*mWindowHeight };
	//					e.GetComponent<Transform>().scale = scale;
	//				}
	//				else if (SRT == 2)
	//				{
	//					Math::Vec2 scale = { translate[0] , translate[1] };
	//					float rotation = (float)(acosf(scale.x / scale.Magnitude()));
	//					if (scale.y < 0.f)
	//					{
	//						rotation = -rotation;
	//					}
	//					/*float theta1 = atan2(translate[6], translate[10]);
	//					float c2 = scale.Magnitude();
	//					float theta2 = atan2(-translate[2], c2);
	//					float s1 = sin(theta1);
	//					float c1 = cos(theta1);
	//					float rotation = atan2(s1 * translate[8] - c1 * translate[4], c1 * translate[5] - s1 * translate[9]);*/

	//					/*rot.Normalize();
	//					float rotation{};
	//					if (rot.x == 0)
	//					{
	//						if (rot.y > 0)
	//							rotation = (float)Math::PI / 2;
	//						else if (rot.y < 0)
	//							rotation = 3 * (float)Math::PI / 2;
	//						else
	//							rotation = 0;
	//					}
	//					else
	//					{
	//						if (rot.y >= 0)
	//							rotation = atan2(rot.y, rot.x);
	//						else if (rot.y < 0)
	//							rotation = 2 * (float)Math::PI + atan2(rot.y, rot.x);
	//					}*/
	//					if (rotation)
	//						LOG_INFO(std::to_string(rotation));
	//					e.GetComponent<Transform>().rotation = rotation;
	//				}
	//				else if (SRT == 3)
	//				{
	//					Math::Vec2 translation = { translate[12] * (float)(*mWindowWidth / 2), translate[13] * (float)(*mWindowHeight / 2) };
	//					e.GetComponent<Transform>().translation = translation;
	//				}
	//			}
	//		}
	//	}
	//}
	//GLuint frameBuffer = renderManager->GetWorldFBO();
	//ImTextureID fameBufferImage = (void*)(intptr_t)frameBuffer;
	//ImGui::Image(fameBufferImage, { viewportSize.x, viewportSize.y }, ImVec2(0, 1), ImVec2(1, 0));
	//static const wchar_t* texpath = (const wchar_t*)"";
	//static int n{1};
	//if (ImGui::BeginDragDropTarget())
	//{
	//	if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("TEXTURES"))
	//	{
	//		LOG_INFO("Created new entity");
	//		Entity e{ ECS::CreateEntity() };
	//		mEntities.insert(e);
	//		e.AddComponent(
	//			General{ "_NEW_DragDrop" + std::to_string(n), TAG::OTHERS, SUBTAG::NOSUBTAG, true },
	//			Transform{ {150,150}, 0, CamMousePos },
	//			Sprite{ Color{0,255,0,100}, SPRITE::TEXTURE, 0 },
	//			RectCollider{ { 0.f, 0.f }, {1.f,1.f}, true});

	//		texpath = (const wchar_t*)payload->Data;
	//		std::string tp = (std::string)((const char*)texpath);
	//		spriteManager->SetTexture(e, tp);
	//		n++;
	//	}
	//	ImGui::EndDragDropTarget();
	//}
	//ImGui::End();
//}
///void  EditorManager::CameraViewPort()
//{
	//ImGui::Begin("Camera View");
	//Math::Vec2 viewportSize = { ImGui::GetWindowSize().x,ImGui::GetWindowSize().y };
	//viewportSize.y -= 70;
	////Calcualting the aspect ratio 
	//if (viewportSize.x / viewportSize.y > 16 / 9.0f) //wide screen
	//{
	//	viewportSize.x = viewportSize.y / 9 * 16;
	//}
	//else if (viewportSize.x / viewportSize.y < 16 / 9.0f) // tall screen
	//{
	//	viewportSize.y = viewportSize.x / 16 * 9;
	//}
	//Math::Vec2 pos = { (ImGui::GetWindowWidth() / 2.f) - 110.f, 30.f };
	//ImGui::SetCursorPos(ImVec2(pos.x, pos.y));
	////if (ImGui::Button("Reset", { 100,25 }))
	//	//serializationManager->LoadScene("SceneTmp");
	////ImGui::SameLine(0.f,20.f);
	//if (ImGui::Button("Play", { 100,25 }))
	//{
	//	//serializationManager->SaveScene("SceneTmp");
	//	isPaused = false;
	//	//renderManager->GetGameCamera() += Math::Vec2(10.f, 10.f);
	//}
	//ImGui::SameLine(0.f, 20.f);
	//if (ImGui::Button("Pause", { 100,25 }))
	//	isPaused = true;
	//
	//pos = { (ImGui::GetWindowWidth() - viewportSize.x) * 0.5f, 60.f };
	//ImGui::SetCursorPos(ImVec2(pos.x, pos.y));
	////
	//if (ImGui::IsWindowHovered())
	//{
	//	Math::Vec2 ScreenMousePos = Input::CursorPos() - Math::Vec2{ ImGui::GetWindowPos().x,ImGui::GetWindowPos().y } - pos - viewportSize / 2;
	//	Math::Vec2 WorldMousePos = ScreenMousePos;
	//	WorldMousePos.y = -WorldMousePos.y;
	//	WorldMousePos.x = WorldMousePos.x / viewportSize.x * *mWindowWidth;
	//	WorldMousePos.y = WorldMousePos.y / viewportSize.y * *mWindowHeight;
	//	Math::Vec2 CamMousePos = WorldMousePos * renderManager->GetGameCamera().GetZoom() + renderManager->GetGameCamera().GetPos();
	//	const Math::Vec2 moveHorizontal{ 1, 0 };
	//	const Math::Vec2 moveVertical{ 0, 1 };
	//	const float zoom{ 0.1f };
	//	static Math::Vec2 camOffset{};
	//	static Math::Vec2 camPos{};
	//	static Math::Vec2 offset{};
	//	static int isSelected = 0;
	//	if (abs(ScreenMousePos.x) < viewportSize.x / 2 && abs(ScreenMousePos.y) < viewportSize.y / 2)
	//	{
	//		//Camera movement
	//		if (Input::CheckKey(E_STATE::HOLD, E_KEY::UP))
	//		{
	//			renderManager->GetGameCamera() += moveVertical;
	//		}
	//		if (Input::CheckKey(E_STATE::HOLD, E_KEY::DOWN))
	//		{
	//			renderManager->GetGameCamera() -= moveVertical;
	//		}
	//		if (Input::CheckKey(E_STATE::HOLD, E_KEY::RIGHT))
	//		{
	//			renderManager->GetGameCamera() += moveHorizontal;
	//		}
	//		if (Input::CheckKey(E_STATE::HOLD, E_KEY::LEFT))
	//		{
	//			renderManager->GetGameCamera() -= moveHorizontal;
	//		}
	//		if (Input::CheckKey(E_STATE::PRESS, E_KEY::M_BUTTON_L) && !isSelected)
	//		{
	//			camOffset = CamMousePos;
	//		}
	//		if (Input::CheckKey(E_STATE::HOLD, E_KEY::M_BUTTON_L) && !isSelected)
	//		{
	//			camPos = -(WorldMousePos * renderManager->GetGameCamera().GetZoom() - camOffset);
	//			renderManager->GetGameCamera().SetPos(camPos);
	//		}
	//		if (Input::GetScroll() > 0.0) //scroll up   // zoon in
	//		{

	//			renderManager->GetGameCamera() += WorldMousePos * zoom;
	//			renderManager->GetGameCamera() *= -zoom;
	//			//renderManager->GetWorldCamera() -= -mousePos;
	//		}
	//		else if (Input::GetScroll() < 0.0)  //scroll down //zoom out
	//		{
	//			renderManager->GetGameCamera() -= WorldMousePos * zoom;
	//			renderManager->GetGameCamera() *= zoom;
	//			//renderManager->GetWorldCamera() += -mousePos;
	//		}
	//	}

	//}
	//GLuint frameBuffer = renderManager->GetGameFBO();
	//ImTextureID fameBufferImage = (void*)(intptr_t)frameBuffer;
	//ImGui::Image(fameBufferImage, { viewportSize.x, viewportSize.y }, ImVec2(0, 1), ImVec2(1, 0));
	//ImGui::End();
//}
//std::string& BreakString(std::string& _str, int _offset)
//{
//	int offset = 0;
//	while (_str.size() > _offset)
//	{
//		if (_str[_offset] == ' ')
//		{
//			_str.replace(_offset, 1, "\n");
//			_offset += 50;
//		}
//		else
//		{
//			offset = (int)_str.find("\n", _offset);
//			_offset += offset;
//		}
//	}
//	return _str;
//}
/*!*****************************************************************************
\brief
	Editor for game dialogs with options

\return
None.
*******************************************************************************/
//void EditorManager::DialogEditor()
//{
	//GLuint player_texture = spriteManager->GetTextureID("Textures\\Sprites\\mc.png");
	//ImTextureID playerIcon = (void*)(intptr_t)player_texture;
	//GLuint passenger_texture = spriteManager->GetTextureID("Textures\\Sprites\\girl.png");
	//ImTextureID npcIcon = (void*)(intptr_t)passenger_texture;
	//GLuint send_texture = spriteManager->GetTextureID("Textures\\Icons\\sendIcon.png");
	//ImTextureID sendIcon = (void*)(intptr_t)send_texture;
	//ImGui::Begin("Dialog Editor");
	//int id = 1;
	//int id2 = 0;
	//int prevID = 1;
	//static int selectedID = 0;
	//std::string dialog{};
	//std::string dialog2{};
	//static std::string dialogEdit{};
	//int wrapsize = int(ImGui::GetWindowWidth()/13);
	//ImVec2 iconSize = ImVec2(40, 40);
	////ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(100, 0, 0))); ImGui::PopStyleColor();
	//while (id)
	//{
	//	if (dialogManager->GetDialogs().size() == 0)
	//		break;
	//	dialog = dialogManager->GetDialogue(id);
	//	BreakString(dialog, wrapsize);
	//	
	//	if (dialogManager->GetSpeaker(id))// if right side convo (Player)
	//	{
	//		ImGui::NewLine();
	//		ImGui::SameLine(ImGui::GetWindowWidth()-70);
	//		ImGui::ImageButton(playerIcon, iconSize, ImVec2(0, 1), ImVec2(1, 0));
	//		ImGui::SameLine(ImGui::GetWindowWidth() - 77 -(dialog.find("\n") != std::string::npos ? dialog.find("\n") : dialog.size()) * 7.4f);
	//		if (dialogManager->GetSelectedChoice(prevID))//2nd choice selected
	//			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(220, 30, 58))); //unselected
	//		else//1st
	//			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(0, 128, 0))); //selected
	//	}
	//	else //left side (NPC)
	//	{
	//		//ImGui::Button("passenger", ImVec2(40,40));
	//		ImGui::ImageButton(npcIcon, iconSize, ImVec2(0, 1), ImVec2(1, 0));
	//		ImGui::SameLine();
	//		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(0, 136, 204))); //passenger
	//	}
	//	ImGui::Button(dialog.c_str());
	//	ImGui::PopStyleColor();
	//	if(ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0))
	//	{//edit text for 1st choice
	//		selectedID = id;
	//		dialogEdit = dialogManager->GetDialogue(selectedID);
	//		for (size_t i = dialogEdit.size(); i < 500; i++)
	//		{
	//			dialogEdit += " ";
	//		}
	//		BreakString(dialogEdit, wrapsize);
	//	}
	//	else if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(0))
	//	{//change selected to 1st choice
	//		dialogManager->SetSelectedChoice(prevID, 0);
	//	}
	//	if (id2) //if have 2nd choice
	//	{
	//		dialog2 = dialogManager->GetDialogue(id2);
	//		BreakString(dialog2, wrapsize);
	//		if (dialogManager->GetSpeaker(id2))
	//		{
	//			ImGui::NewLine();
	//			ImGui::SameLine(ImGui::GetWindowWidth() - 70);
	//			ImGui::ImageButton(playerIcon, iconSize, ImVec2(0, 1), ImVec2(1, 0));
	//			ImGui::SameLine(ImGui::GetWindowWidth() - 77-(dialog2.find("\n") != std::string::npos ? dialog2.find("\n") : dialog2.size()) * 7.4f);
	//			if (dialogManager->GetSelectedChoice(prevID))//2nd choice selected
	//				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(0, 128, 0))); //selected
	//			else//1st
	//				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(220, 30, 58))); //unselected
	//		}
	//		else //left side (NPC)
	//		{
	//			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(0, 136, 204)));
	//		}
	//		ImGui::Button(dialog2.c_str());
	//		ImGui::PopStyleColor();
	//		if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0))
	//		{//edit text for 2nd choice
	//			selectedID = id2;
	//			dialogEdit = dialogManager->GetDialogue(selectedID);
	//			for (size_t i = dialogEdit.size(); i < 500; i++)
	//			{
	//				dialogEdit += " ";
	//			}
	//			BreakString(dialogEdit, wrapsize);
	//		}
	//		else if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(0))
	//		{//change selected to 2nd choice
	//			dialogManager->SetSelectedChoice(prevID, 1);
	//		}
	//	}
	//	//Get new ID for net loop
	//	if (dialogManager->GetSelectedChoice(prevID))//2nd
	//		prevID = id2;
	//	else//1st
	//		prevID = id;
	//	id = dialogManager->GetNext(prevID);
	//	id2 = dialogManager->GetNext2(prevID);
	//	
	//		
	//	ImGui::NewLine();
	//}
	//ImGui::Separator();
	////LOG_INFO(std::to_string(ImGui::GetScrollY()));
	//
	//if (selectedID)
	//{
	//	ImGui::Button(" ", ImVec2(1, 150));
	//	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(ImColor(50, 50, 50)));
	//	ImGui::SetCursorPos(ImVec2(10, ImGui::GetWindowHeight() - 120 + ImGui::GetScrollY()));
	//	ImGui::BeginChild("yeet", ImVec2(ImGui::GetWindowWidth()-20, 100), true);
	//	ImGui::InputTextMultiline(" ", const_cast<char*>(dialogEdit.c_str()), 1000, 
	//		ImVec2(ImGui::GetWindowWidth()-100, 80));
	//	ImGui::SameLine();
	//	if(ImGui::ImageButton(sendIcon, ImVec2(50, 50), ImVec2(0, 1), ImVec2(1, 0)))
	//	{
	//		std::string editedDialog;
	//		std::string word;
	//		std::istringstream ss(dialogEdit);

	//		while (ss >> word) {
	//			if (!editedDialog.empty()) {
	//				editedDialog += ' ';
	//			}
	//			editedDialog += word;
	//		}
	//		dialogManager->EditDialogue(selectedID, editedDialog);
	//	}
	//	ImGui::EndChild();
	//	ImGui::PopStyleColor();
	//}

	//ImGui::End();
//}

