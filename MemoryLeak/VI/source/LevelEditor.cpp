/*!*****************************************************************************
/*!*****************************************************************************
\file LevelEditor.cpp
\author Huang Wei Jhin
\par DP email: h.weijhin@digipen.edu
\par Group: Memory Leak Studios
\date 20-09-2022
\brief
This file contains function definations for a Level Editor system that modifies
Entities and its Components.
*******************************************************************************/
#include <LevelEditor.h>
#include <ECSManager.h>
//#include "Graphics/SpriteManager.h"
//#include <AI.h>
#include <Logger.h>
#include <vec2.h>
#include <filesystem>
#define _USE_MATH_DEFINES
#include <math.h>


/*!*****************************************************************************
\brief
	Initializes the level editor

\return
None.
*******************************************************************************/
void LevelEditor::Init(GLFWwindow* _window, int* _windowWidth, int* _windowHeight)
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

	//IM_ASSERT(ret);
	//weatherAIinit();
	Start();
}
void LevelEditor::Start()
{
	selectedEntity = nullptr;
	isPaused = true;
	SRT = 0;
	//serializationManager->SaveScene("SceneTemp");
}

/*!*****************************************************************************
\brief
	Creates the level editor window

\return
None.
*******************************************************************************/
void LevelEditor::Window()
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
void LevelEditor::Update()
{
	//weatherAIupdate();
	//ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
	//ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_AutoSelectNewTabs | ImGuiTabBarFlags_Reorderable;
	static bool showdebug = true;
	static char filenameS[30] = "Enter scene filename";
	static char filenameO[30] = "Enter scene filename";
	static char filenameS_Dialog[30] = "";
	static char filenameO_Dialog[30] = "";
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			ImGui::MenuItem("(menu)", NULL, false, false);
			ImGui::InputText("o", filenameO, 30);
			if (ImGui::MenuItem("Open", "Ctrl+O")) 
			{
				serializationManager->LoadScene(filenameO);
			}
			ImGui::Separator();
			ImGui::InputText("s", filenameS, 30);
			if (ImGui::MenuItem("Save", "Ctrl+S"))
			{
				serializationManager->SaveScene(filenameS);
			}
			ImGui::Separator();
			if (ImGui::MenuItem("Clear Scene"))
			{
				ECS::DestroyAllEntities();
				selectedEntity = nullptr;
			}
			ImGui::Separator();
			ImGui::MenuItem("Open Dialogue File", NULL, false, false);
			ImGui::InputText(".json ", filenameO_Dialog, 20);
			if (ImGui::MenuItem("Open", "Ctrl+D")) 
			{
				serializationManager->LoadDialogs(filenameO_Dialog);
			}
			ImGui::Separator();
			ImGui::MenuItem("Save Dialogue File As", NULL, false, false);
			ImGui::InputText(".json", filenameS_Dialog, 20);
			if (ImGui::MenuItem("Save As", "Ctrl+F"))
			{
				serializationManager->SaveDialogs(filenameS_Dialog);
			}
			ImGui::Separator();
			if (ImGui::MenuItem("Print Dialogs"))
			{
				dialogManager->PrintDialogs();
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Cut", "CTRL+X")) {}
			if (ImGui::MenuItem("Copy", "CTRL+C")) {}
			if (ImGui::MenuItem("Paste", "CTRL+V")) {}
			ImGui::Separator();
			if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
			if (ImGui::MenuItem("Redo", "CTRL+Y")) {}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Options"))
		{
			if (!showdebug && ImGui::MenuItem("Show Debug Info"))
			{
				showdebug = true;
			}
			if (showdebug && ImGui::MenuItem("Hide Debug Info"))
			{
				showdebug = false;
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
	
	SceneManager();
	EntityManager();
	AssetManager();
	ViewPortManager();
	if(showdebug)
		ShowDebugInfo();
	DialogEditor();
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
	Debig logger pannel

\return
None.
*******************************************************************************/
void LevelEditor::ShowDebugInfo()
{
	std::vector<std::pair<Logger::E_LOGLEVEL, std::string>> loggerStr = Logger::GetInstance()->GetLoggerStr();
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
	ImGui::End();
}
/*!*****************************************************************************
\brief
	Scene manager pannel

\return
None.
*******************************************************************************/
void  LevelEditor::SceneManager()
{
	static int n = 0;
	ImGui::Begin("Scene Manager");
	ImGui::BeginTabBar("Edit Scene ");
	if (ImGui::BeginTabItem("Edit Game: "))
	{
		std::vector<std::string> tag { "PLAYER","PASSENGER", "ENEMY", "BUILDING", "OTHERS" };
		for (int i = 0; i < (int)tag.size(); i++)
		{

			//if (ImGui::TreeNode(tag[i].c_str()))
			if(ImGui::CollapsingHeader(tag[i].c_str()))
			{
				int counter = 0;
				static bool first[20]{};
				for (const Entity& e : mEntities)
				{
					if (e.GetComponent<General>().tag != (TAG)i)
						continue;
					++counter;
					const char* lbl = e.GetComponent<General>().name.c_str();
					if (ImGui::TreeNode(lbl))
					{
						if (e.HasComponent<General>())
						{
							ImGui::Text("General");
							if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
							{
								selectedEntity = &e;
							}
						}
						if (e.HasComponent<Lifespan>())
						{
							ImGui::Text("Lifespan");
							if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
							{
								selectedEntity = &e;
							}
						}
						if (e.HasComponent<Transform>())
						{
							ImGui::Text("Transform");
							if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
							{
								selectedEntity = &e;
							}
						}
						if (e.HasComponent<Sprite>())
						{
							ImGui::Text("Sprite");
							if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
							{
								selectedEntity = &e;
							}
						}
						if (e.HasComponent<Animation>())
						{
							ImGui::Text("Animation");
							if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
							{
								selectedEntity = &e;
							}
						}
						if (e.HasComponent<SheetAnimation>())
						{
							ImGui::Text("SheetAnimation");
							if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
							{
								selectedEntity = &e;
							}
						}
						if (e.HasComponent<Physics2D>())
						{
							ImGui::Text("Physics2D");
							if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
							{
								selectedEntity = &e;
							}
						}
						if (e.HasComponent<RectCollider>())
						{
							ImGui::Text("RectCollider");
							if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
							{
								selectedEntity = &e;
							}
						}
						if (e.HasComponent<CircleCollider>())
						{
							ImGui::Text("CircleCollider");
							if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
							{
								selectedEntity = &e;
							}
						}
						if (e.HasComponent<Edge2DCollider>())
						{
							ImGui::Text("Edge2DCollider");
							if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
							{
								selectedEntity = &e;
							}
						}
						if (e.HasComponent<Stuff>())
						{
							ImGui::Text("Stuff");
							if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
							{
								selectedEntity = &e;
							}
						}
						if (e.HasComponent<Audio>())
						{
							ImGui::Text("Audio");
							if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
							{
								selectedEntity = &e;
							}
						}
						if (e.HasComponent<Stuff>())
						{
							ImGui::Text("AI");
							if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
							{
								selectedEntity = &e;
							}
						}
						ImGui::TreePop();

					}
				}
				//ImGui::TreePop();
				if (ImGui::BeginPopupContextWindow(0, 1, false))
				{
					if (ImGui::MenuItem(" Create Entity"))
					{
						LOG_INFO("Created new entity");
						Entity e{ ECS::CreateEntity() };
						mEntities.insert(e);
						e.AddComponent(
							General{ "_NEW_"+std::to_string(n), TAG::OTHERS, SUBTAG::NOSUBTAG, true},
							Transform{ {150,150}, 0, {0.f,0.f} },
							Sprite{ Color{0,255,0,100}, SPRITE::CIRCLE, 0 });
						n++;
					}
					ImGui::EndPopup();
				}

			}
		}
		/*if (ImGui::TreeNode("Scene 2"))
		{
			ImGui::Text("Nothing");
			ImGui::TreePop();
		}*/
		ImGui::EndTabItem();
		if (ImGui::Button("New object"))
		{
			LOG_INFO("Created new entity");
			Entity e{ ECS::CreateEntity() };
			mEntities.insert(e);
			e.AddComponent(
				General{"_NEW_" + std::to_string(n), TAG::OTHERS, SUBTAG::NOSUBTAG, true},
				Transform{ {150,150}, 0, {0.f,0.f} },
				Sprite{ Color{0,255,0,100}, SPRITE::CIRCLE, 0 });
			n++;
		}
	}
	ImGui::EndTabBar();
	ImGui::End();
}
/*!*****************************************************************************
\brief
	Entity Manager pannel

\return
None.
*******************************************************************************/
void LevelEditor::EntityManager()
{
	float tmpVec2[2];
	float tmpFloat;
	float tmpVec4[4];
	//int shape;
	ImGui::Begin("Entity Manager");
	ImGui::BeginTabBar("Edit Entities ");
	if (ImGui::BeginTabItem("Edit Game: "))
	{
		if (selectedEntity != nullptr)// && selectedEntityID <= (int)mEntities.size())
		{
			//++counter;
			//int counter = selectedEntityID;
			const Entity& e = *selectedEntity;
			//const char* lbl = e.GetComponent<General>().name.c_str();
			//ImGui::Text(lbl);
			if (e.HasComponent<General>())
			{
				if (ImGui::CollapsingHeader("General")||true) {
					ImGui::Text("General");
						ImGui::Checkbox("isActive", &e.GetComponent<General>().isActive); //isactive
						ImGui::InputText("Name", const_cast<char*>(e.GetComponent<General>().name.c_str()), 30);
						int tagID = (int)e.GetComponent<General>().tag;
						static const char* tag[]{ "PLAYER","PASSENGER", "ENEMY", "BUILDING", "OTHERS" };
						ImGui::Combo("Tag", &tagID, tag, IM_ARRAYSIZE(tag));
						e.GetComponent<General>().tag = (TAG)tagID;
						int subtagID = (int)e.GetComponent<General>().subtag;
						static const char* subtag[]{ "NOSUBTAG", "PLAYER", "PASSENGER", "ENEMY", "BUILDING", "OTHERS" };
						ImGui::Combo("SubTag", &subtagID, subtag, IM_ARRAYSIZE(subtag));
						e.GetComponent<General>().subtag = (SUBTAG)subtagID;
				}
			}
			if (e.HasComponent<Lifespan>())
			{
				if (ImGui::CollapsingHeader("Lifespan")) {
					//ImGui::Text("Lifespan");
					ImGui::InputFloat("Lifespan", &e.GetComponent<Lifespan>().limit);
					if (ImGui::Button("Remove Lifespan"))
					{
						e.RemoveComponent<Lifespan>();
						LOG_INFO("Lifespan component removed");
					}
				}
			}
			if (e.HasComponent<Transform>())
			{
				if (ImGui::CollapsingHeader("Transform Gizmo")) {
					//ImGui::Text("Transform Gizmo: ");
					static bool s = 0,r = 0,t = 0;
					ImGui::Checkbox("Scale Gizmo", &s);
					if (s) { SRT = 1; r = t = 0; }
					//ImGui::Checkbox("Rotate", &r);
					//if (r) { SRT = 2; s = t = 0; }
					ImGui::Checkbox("Translate Gizmo", &t);
					if (t) { SRT = 3; s = r = 0; }
					if (!s && !r && !t) SRT = 0;
				}

				if (ImGui::CollapsingHeader("Transform")) {
					//ImGui::Text("Transform Component");
					tmpVec2[0] = transformManager->GetScale(e).x;
					tmpVec2[1] = transformManager->GetScale(e).y;
					ImGui::DragFloat2("Set Scale", tmpVec2);
					Math::Vec2 scale{ tmpVec2[0] ,tmpVec2[1] };
					transformManager->SetScale(e, scale);

					tmpVec2[0] = transformManager->GetTranslate(e).x;
					tmpVec2[1] = transformManager->GetTranslate(e).y;
					ImGui::DragFloat2("Set Position", tmpVec2);
					Math::Vec2 pos{ tmpVec2[0] ,tmpVec2[1] };
					transformManager->SetTranslate(e, pos);

					tmpFloat = transformManager->GetRotation(e);
					tmpFloat = (float)(tmpFloat / M_PI * 180.f);
					ImGui::SliderFloat("Set Rotation", &tmpFloat, -360.f, 360.f);
					tmpFloat = (float)(tmpFloat * M_PI / 180.f);
					transformManager->SetRotation(e, tmpFloat);
					/*if (ImGui::Button("Remove Transform"))
					{
						e.RemoveComponent<Transform>();
						LOG_INFO("Transform component removed");
					}*/
				}
				
			}
			if (e.HasComponent<Sprite>())
			{
				if (ImGui::CollapsingHeader("Sprite")) {
					//ImGui::Text("Sprite");
					tmpVec4[0] = e.GetComponent<Sprite>().color.r /255.f;
					tmpVec4[1] = e.GetComponent<Sprite>().color.g / 255.f;
					tmpVec4[2] = e.GetComponent<Sprite>().color.b / 255.f;
					tmpVec4[3] = e.GetComponent<Sprite>().color.a / 255.f;
					ImGui::ColorEdit4("Color", tmpVec4);
					e.GetComponent<Sprite>().color.r = (GLubyte)(tmpVec4[0] * 255);
					e.GetComponent<Sprite>().color.g = (GLubyte)(tmpVec4[1] * 255);
					e.GetComponent<Sprite>().color.b = (GLubyte)(tmpVec4[2] * 255);
					e.GetComponent<Sprite>().color.a = (GLubyte)(tmpVec4[3] * 255);
					std::string tex{};
					if(e.GetComponent<Sprite>().sprite == SPRITE::TEXTURE)
						tex = spriteManager->GetTexturePath(spriteManager->GetTexture(e));
					else if (e.GetComponent<Sprite>().sprite == SPRITE::CIRCLE)
						tex = "CIRCLE";
					else if (e.GetComponent<Sprite>().sprite == SPRITE::SQUARE)
						tex = "SQUARE";
				
					int shapeID = (int)e.GetComponent<Sprite>().sprite;
					static const char* shape[]{"SQUARE", "CIRCLE", "TEXTURE","DEBUG_POINT" , "DEBUG_LINE","DEBUG_SQUARE","DEBUG_CIRCLE", "DEBUG_ARROW"};
					ImGui::Combo("Shape", &shapeID, shape, IM_ARRAYSIZE(shape));
					e.GetComponent<Sprite>().sprite = (SPRITE)shapeID;
					if ((SPRITE)shapeID != SPRITE::TEXTURE)
					{
						e.GetComponent<Sprite>().texture = 0;
					}
					ImGui::Text(tex.c_str());

					static const wchar_t* texpath = (const wchar_t*)"";
					if (ImGui::BeginDragDropTarget())
					{
						if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("TEXTURES"))
						{
							texpath = (const wchar_t*)payload->Data;
							std::string tp = (std::string)((const char*)texpath);
							e.GetComponent<Sprite>().sprite = SPRITE::TEXTURE;
							spriteManager->SetTexture(e, tp);
						}
						ImGui::EndDragDropTarget();
					}
					ImGui::InputInt("Layer", &e.GetComponent<Sprite>().layer);
					if (ImGui::Button("Remove Sprite"))
					{
						e.RemoveComponent<Sprite>();
						LOG_INFO("Sprite component removed");
					}
				}
			}
			if (e.HasComponent<Animation>())
			{
				if (ImGui::CollapsingHeader("Animation")) {
					//ImGui::Text("Animation");
					static GLuint addImage = {};
					static std::string  texadd =  "Add image";
					for (size_t i = 0; i <= e.GetComponent<Animation>().images.size(); ++i)
					{
						std::string tex{};
						if (i != e.GetComponent<Animation>().images.size())
						{
							tex = spriteManager->GetTexturePath(e.GetComponent<Animation>().images[i]);
							ImGui::Text(tex.c_str());
						}
						else
						{
							ImGui::InputText("Addimage", const_cast<char*>(texadd.c_str()), texadd.size());
							tex = texadd;
						}
						static const wchar_t* texpath = (const wchar_t*)"";
						if (ImGui::BeginDragDropTarget())
						{
							if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("TEXTURES"))
							{
								texpath = (const wchar_t*)payload->Data;
								if (i == e.GetComponent<Animation>().images.size())
									texadd= (char*)texpath;
								std::string  tp = (std::string)((const char*)texpath);
								if (i != e.GetComponent<Animation>().images.size())
									e.GetComponent<Animation>().images[i] = spriteManager->GetTextureID(tp);
								else
									addImage = spriteManager->GetTextureID(tp);
							}
							ImGui::EndDragDropTarget();
						}
					}
					if (ImGui::Button("Add Sprite"))
					{
						animator->AddImages(e, addImage);
					}
					ImGui::InputFloat("timePerImage", &e.GetComponent<Animation>().timePerImage);
					ImGui::InputFloat("timeToImageSwap", &e.GetComponent<Animation>().timeToImageSwap);
					ImGui::InputInt("currentImageIndex", &e.GetComponent<Animation>().currentImageIndex);
					if (ImGui::Button("Remove Animation"))
					{
						e.RemoveComponent<Animation>();
						LOG_INFO("Animation component removed");
					}
				}
			}
			if (e.HasComponent<SheetAnimation>())
			{
				if (ImGui::CollapsingHeader("SheetAnimation")) {
					//ImGui::Text("SheetAnimation");
					ImGui::InputInt("frameCount", (int*)&e.GetComponent<SheetAnimation>().frameCount);
					ImGui::InputInt("currFrameIndex", (int*)&e.GetComponent<SheetAnimation>().currFrameIndex);
					ImGui::InputFloat("timePerFrame", &e.GetComponent<SheetAnimation>().timePerFrame);
					ImGui::InputFloat("timeToFrameSwap", &e.GetComponent<SheetAnimation>().timeToFrameSwap);
					if (ImGui::Button("Remove SheetAnimation"))
					{
						e.RemoveComponent<SheetAnimation>();
						LOG_INFO("SheetAnimation component removed");
					}
				}
			}
			if (e.HasComponent<RectCollider>())
			{
				if (ImGui::CollapsingHeader("RectCollider")) {
					//ImGui::Text("RectCollider");
					tmpVec2[0] = e.GetComponent<RectCollider>().centerOffset.x;
					tmpVec2[1] = e.GetComponent<RectCollider>().centerOffset.y;
					ImGui::InputFloat2("Box position Offset", tmpVec2);
					e.GetComponent<RectCollider>().centerOffset = { tmpVec2[0] ,tmpVec2[1]};

					tmpVec2[0] = e.GetComponent<RectCollider>().scaleOffset.x;
					tmpVec2[1] = e.GetComponent<RectCollider>().scaleOffset.y;
					ImGui::InputFloat2("Box scale Offset", tmpVec2);
					e.GetComponent<RectCollider>().scaleOffset = { tmpVec2[0] ,tmpVec2[1] };

					ImGui::Checkbox("Rect RenderFlag", &e.GetComponent<RectCollider>().renderFlag);
					if (ImGui::Button("Remove RectCollider"))
					{
						e.RemoveComponent<RectCollider>();
						LOG_INFO("RectCollider component removed");
					}
				}
			}
			if (e.HasComponent<CircleCollider>())
			{
				if (ImGui::CollapsingHeader("CircleCollider")) {
					//ImGui::Text("CircleCollider");
					tmpVec2[0] = e.GetComponent<CircleCollider>().centerOffset.x;
					tmpVec2[1] = e.GetComponent<CircleCollider>().centerOffset.y;
					ImGui::InputFloat2("Circle position Offset", tmpVec2);
					e.GetComponent<CircleCollider>().centerOffset = { tmpVec2[0] ,tmpVec2[1] };

					float scale = e.GetComponent<CircleCollider>().scaleOffset;
					ImGui::InputFloat("Circle scale Offset", &scale);
					e.GetComponent<CircleCollider>().scaleOffset = { scale };

					ImGui::Checkbox("Circle RenderFlag", &e.GetComponent<CircleCollider>().renderFlag);
					if (ImGui::Button("Remove CircleCollider"))
					{
						e.RemoveComponent<CircleCollider>();
						LOG_INFO("CircleCollider component removed");
					}
				}
			}
			if (e.HasComponent<Edge2DCollider>())
			{
				if (ImGui::CollapsingHeader("Edge2DCollider")) {
					//ImGui::Text("Edge2DCollider");
					tmpVec2[0] = e.GetComponent<Edge2DCollider>().p0Offset.x;
					tmpVec2[1] = e.GetComponent<Edge2DCollider>().p0Offset.y;
					ImGui::InputFloat2("p0 Offset", tmpVec2);
					e.GetComponent<Edge2DCollider>().p0Offset = { tmpVec2[0] ,tmpVec2[1] };

					ImGui::InputFloat("rotationOffset", &e.GetComponent<Edge2DCollider>().rotationOffset);
					ImGui::InputFloat("scaleOffset", &e.GetComponent<Edge2DCollider>().scaleOffset);
					ImGui::Checkbox("RenderFlag", &e.GetComponent<Edge2DCollider>().renderFlag);
					if (ImGui::Button("Remove Edge2DCollider"))
					{
						e.RemoveComponent<Edge2DCollider>();
						LOG_INFO("Edge2DCollider component removed");
					}
				}
			}
			if (e.HasComponent<Point2DCollider>())
			{
				if (ImGui::CollapsingHeader("Point2DCollider")) {
					//ImGui::Text("Point2DCollider");
					tmpVec2[0] = e.GetComponent<Point2DCollider>().centerOffset.x;
					tmpVec2[1] = e.GetComponent<Point2DCollider>().centerOffset.y;
					ImGui::InputFloat2("centerOffset", tmpVec2);
					e.GetComponent<Point2DCollider>().centerOffset = { tmpVec2[0] ,tmpVec2[1] };

					ImGui::Checkbox("RenderFlag", &e.GetComponent<Point2DCollider>().renderFlag);
					if (ImGui::Button("Remove Point2DCollider"))
					{
						e.RemoveComponent<Point2DCollider>();
						LOG_INFO("Point2DCollider component removed");	
					}
				}
			}
			if (e.HasComponent<Physics2D>())
			{
				if (ImGui::CollapsingHeader("Physics2D")) {
					//ImGui::Text("Physics2D");
					ImGui::InputFloat("Mass", &e.GetComponent<Physics2D>().mass);
					ImGui::InputFloat("Speed", &e.GetComponent<Physics2D>().speed);
					ImGui::InputFloat("moveDirection", &e.GetComponent<Physics2D>().moveDirection);
					ImGui::Checkbox("gravityEnabled", &e.GetComponent<Physics2D>().gravityEnabled);
					ImGui::Checkbox("Physics RenderFlag", &e.GetComponent<Physics2D>().renderFlag);
					if (ImGui::Button("Remove Physics2D"))
					{
						e.RemoveComponent<Physics2D>();
						LOG_INFO("Physics2D component removed");
					}
				}
			}
			if (e.HasComponent<Audio>())
			{
				if (ImGui::CollapsingHeader("Audio")) {
					//ImGui::Text("Audio");
					ImGui::InputText("Addsound", const_cast<char*>(e.GetComponent<Audio>().sound.path.c_str()), 30);
					ImGui::Checkbox("Pause", &e.GetComponent<Audio>().sound.isPaused);
					ImGui::Checkbox("Click to Play", &e.GetComponent<Audio>().sound.toPlay);
					//ImGui::Checkbox("isLoop", &e.GetComponent<Audio>().sound.isLoop);
					if (ImGui::Button("Remove Audio"))
					{
						e.RemoveComponent<Audio>();
						LOG_INFO("Audio component removed");
					}
				}
			}
			if (e.HasComponent<Stuff>())
			{
				if (ImGui::CollapsingHeader("AI")) {
					static const char* colorChange[]{ "None","Smoothy","Traffic Light" };
					int colorChangeID = e.GetComponent<Stuff>().colorChange;
					ImGui::Combo("Select Color Change", &colorChangeID, colorChange, IM_ARRAYSIZE(colorChange));
					e.GetComponent<Stuff>().colorChange = colorChangeID;

					static const char* movement[]{ "None","UP-Down","Left-Right", "Swing", "Circle" };
					int movementID = e.GetComponent<Stuff>().movement;
					ImGui::Combo("Select Movement", &movementID, movement, IM_ARRAYSIZE(movement));
					e.GetComponent<Stuff>().movement = movementID;

					if (e.GetComponent<Stuff>().movement)
					{
						float speed = e.GetComponent<Stuff>().speed;
						ImGui::SliderFloat("Speed", &speed, 0.f, 15.f);
						e.GetComponent<Stuff>().speed = speed;
						if (e.GetComponent<Stuff>().movement < 4)
						{
							float range = e.GetComponent<Stuff>().range;
							ImGui::SliderFloat("Range", &range, 0.f, 400.f);
							e.GetComponent<Stuff>().range = range;
						}
					}
					if (ImGui::Button("Remove AI"))
					{
						e.RemoveComponent<Stuff>();
						LOG_INFO("AI component removed");
					}
				}
			}

			static int componentsID;
			static const char* components[]{ "General","Lifespan","Transform", "Sprite" ,"Animation","SheetAnimation","Physics2D",
				"RectCollider" , "CircleCollider" ,"Edge2DCollider" ,"Audio" ,"AI" };
			ImGui::Combo("Select Component", &componentsID, components, IM_ARRAYSIZE(components));
			if (ImGui::Button("Add Component"))
			{
				if      (componentsID == 0)
					e.AddComponent<General>({ "_new_", (TAG)0, (SUBTAG)0, true});
				else if (componentsID == 1)
					e.AddComponent<Lifespan>({0,1000});
				else if (componentsID == 2)
					e.AddComponent<Transform>({ {100,100}, 0, {0,0} });
				else if (componentsID == 3)
					e.AddComponent<Sprite>({});
				else if (componentsID == 4)
					e.AddComponent<Animation>({});
				else if (componentsID == 5)
					e.AddComponent<SheetAnimation>({});
				else if (componentsID == 6)
					e.AddComponent<Physics2D>({});
				else if (componentsID == 7)
					e.AddComponent<RectCollider>({ });
				else if (componentsID == 8)
					e.AddComponent<CircleCollider>({});
				else if (componentsID == 9)
					e.AddComponent<Edge2DCollider>({});
				else if (componentsID == 10)
					e.AddComponent<Audio>({});
				else if (componentsID == 11)
					e.AddComponent<Stuff>({});
				std::string add(components[componentsID]);
				LOG_INFO(add+"conponent added");
			}
			if (ImGui::BeginPopupContextWindow(0, 1, false))
			{
				if (ImGui::MenuItem("Delete Entity"))
				{
					e.Destroy();
					LOG_INFO("Entity deleated");
					selectedEntity = nullptr;
					//selectedEntityID = 99;
				}
				ImGui::EndPopup();
			}
		}
		ImGui::EndTabItem();
		
	}
	ImGui::EndTabBar();
	ImGui::End();
}



/*!*****************************************************************************
\brief
	Asset manager pannel

\return
None.
*******************************************************************************/
void  LevelEditor::AssetManager()
{
	GLuint my_image_texture = spriteManager->GetTextureID("Textures\\Icons\\folderIcon.png");
	GLuint my_image2_texture = 0;
	std::string rootPath = "..\\resources";
	ImVec2 buttonSize = { 100,100 };
	ImGui::Begin("Asset Manager");
	ImGui::BeginTabBar("Assets ");
	if (ImGui::BeginTabItem("Content Browser")) {
		// switch to the newly selected tab
		static std::filesystem::path m_CurrentDirectory = std::filesystem::path(rootPath);
		if (m_CurrentDirectory != std::filesystem::path(rootPath))
		{
			if (ImGui::Button("<- BACK", buttonSize))
			{
				m_CurrentDirectory = m_CurrentDirectory.parent_path();
			}
		}
		for (auto& directory : std::filesystem::directory_iterator(m_CurrentDirectory))
		{
			const auto& path = directory.path();
			auto relativePath = std::filesystem::relative(path, rootPath);
			std::string filename = relativePath.filename().string();
			ImGui::Columns(3);

			ImTextureID folderIcon = (void*)(intptr_t)my_image_texture;
			if (directory.is_directory())
			{
				ImGui::ImageButton(folderIcon, buttonSize, ImVec2(0, 1), ImVec2(1, 0));
			}
			else
			{
				std::string texPath = directory.path().string();
				texPath = texPath.substr(13);
				my_image2_texture = spriteManager->GetTextureID(texPath);
				if (my_image2_texture)
				{
					ImTextureID textureImage = (void*)(intptr_t)my_image2_texture;
					ImGui::ImageButton(textureImage, buttonSize, ImVec2(0, 1), ImVec2(1, 0));
					if (ImGui::BeginDragDropSource())
					{
						const wchar_t* itemPath = (wchar_t*)texPath.c_str();
						ImGui::SetDragDropPayload("TEXTURES", itemPath, (wcslen(itemPath) + 1) * sizeof(wchar_t) , ImGuiCond_Once);
						ImGui::EndDragDropSource();
					}
				}
				else
					ImGui::Button(filename.c_str(), buttonSize);
			}
			if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
			{
				if (directory.is_directory())
					m_CurrentDirectory /= path.filename();
			}
			ImGui::Text(filename.c_str());
			ImGui::NextColumn();
		}
		ImGui::Columns(1);
		ImGui::Text("   ");
		ImGui::EndTabItem();
	}
	ImGui::EndTabBar();
	ImGui::End();
}

/*!*****************************************************************************
\brief
	Viewport manager pannel

\return
None.
*******************************************************************************/
void LevelEditor::ViewPortManager()
{
	//ImGui::Begin("View Port Manager");
	WorldViewPort();
	CameraViewPort();
	//ImGui::End();
}
void  LevelEditor::WorldViewPort()
{
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoBackground;
	//bool open_ptr = true;
	//ImGui::Begin("View Port Manager", &open_ptr, window_flags);
	ImGui::Begin("World View");
	ImVec2 viewportSize = ImGui::GetWindowSize();
	viewportSize.y -= 70;
	//Calcualting the aspect ratio 
	if (viewportSize.x / viewportSize.y > 16 / 9.0f) //wide screen
	{
		viewportSize.x = viewportSize.y / 9 * 16;
	}
	else if (viewportSize.x / viewportSize.y < 16 / 9.0f) // tall screen
	{
		viewportSize.y = viewportSize.x / 16 * 9;
	}
	Math::Vec2 pos = { (ImGui::GetWindowWidth() / 2.f) - 110.f, 30.f };
	ImGui::SetCursorPos(ImVec2(pos.x, pos.y));
	//if (ImGui::Button("Reset", { 100,25 }))
		//serializationManager->LoadScene("SceneTmp");
	//ImGui::SameLine(0.f,20.f);
	if (ImGui::Button("Play", { 100,25 }))
	{
		//serializationManager->SaveScene("SceneTmp");
		//isPaused = false;
		renderManager->GetCamera() *= 0.01f;
	}
	ImGui::SameLine(0.f, 20.f);
	if (ImGui::Button("Pause", { 100,25 }))
		isPaused = true;
	GLuint frameBuffer = renderManager->GetFBO();
	pos = { (ImGui::GetWindowWidth() - viewportSize.x) * 0.5f, 60.f };
	ImGui::SetCursorPos(ImVec2(pos.x, pos.y));
	ImTextureID fameBufferImage = (void*)(intptr_t)frameBuffer;
	ImGui::Image(fameBufferImage, { viewportSize.x, viewportSize.y }, ImVec2(0, 1), ImVec2(1, 0));

	if (selectedEntity != nullptr)// && selectedEntityID <= (int)mEntities.size())
	{
		const Entity& e = *selectedEntity;
		//imguizmo
		ImGuizmo::SetOrthographic(true);
		ImGuizmo::SetDrawlist();
		ImGuizmo::SetRect(ImGui::GetWindowPos().x + pos.x, ImGui::GetWindowPos().y + pos.y,
			viewportSize.x, viewportSize.y);
		const float identity[16] = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };
		std::vector<float> trf = renderManager->GetImGuizmoMat4(e);
		float translate[16] = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };
		for (int i = 0; i < 16; ++i)
		{
			translate[i] = trf[i];
		}

		ImGuizmo::OPERATION opp{};
		if (SRT == 1)
		{
			opp = ImGuizmo::OPERATION::SCALE;
		}
		else if (SRT == 2)
		{
			opp = ImGuizmo::OPERATION::ROTATE;
		}
		else if (SRT == 3)
		{
			opp = ImGuizmo::OPERATION::TRANSLATE;
		}
		if (SRT != 0)
		{
			ImGuizmo::Manipulate(&identity[0], &identity[0], opp, ImGuizmo::LOCAL, &translate[0]);
			if (ImGuizmo::IsUsing())
			{
				if (SRT == 1)
				{
					Math::Vec2 scaleX = { translate[0] , translate[1] };
					Math::Vec2 scaleY = { translate[4] , translate[5] };
					Math::Vec2 scale = { scaleX.Magnitude() * (float)*mWindowWidth , scaleY.Magnitude() * (float)*mWindowHeight };
					e.GetComponent<Transform>().scale = scale;
				}
				else if (SRT == 2)
				{
					Math::Vec2 scale = { translate[0] , translate[1] };
					float rotation = (float)(acosf(scale.x / scale.Magnitude()));
					if (scale.y < 0.f)
					{
						rotation = -rotation;
					}
					//LOG_INFO(std::to_string(rotation));
					/*float theta1 = atan2(translate[6], translate[10]);
					float c2 = scale.Magnitude();
					float theta2 = atan2(-translate[2], c2);
					float s1 = sin(theta1);
					float c1 = cos(theta1);
					float rotation = atan2(s1 * translate[8] - c1 * translate[4], c1 * translate[5] - s1 * translate[9]);*/

					/*rot.Normalize();
					float rotation{};
					if (rot.x == 0)
					{
						if (rot.y > 0)
							rotation = (float)Math::PI / 2;
						else if (rot.y < 0)
							rotation = 3 * (float)Math::PI / 2;
						else
							rotation = 0;
					}
					else
					{
						if (rot.y >= 0)
							rotation = atan2(rot.y, rot.x);
						else if (rot.y < 0)
							rotation = 2 * (float)Math::PI + atan2(rot.y, rot.x);
					}*/
					e.GetComponent<Transform>().rotation = rotation;
				}
				else if (SRT == 3)
				{
					Math::Vec2 translation = { translate[12] * (float)(*mWindowWidth / 2), translate[13] * (float)(*mWindowHeight / 2) };
					e.GetComponent<Transform>().translation = translation;
				}
			}
		}
	}
	ImGui::End();
}
void  LevelEditor::CameraViewPort()
{
	ImGui::Begin("Camera View");
	ImVec2 viewportSize = ImGui::GetWindowSize();
	viewportSize.y -= 70;
	//Calcualting the aspect ratio 
	if (viewportSize.x / viewportSize.y > 16 / 9.0f) //wide screen
	{
		viewportSize.x = viewportSize.y / 9 * 16;
	}
	else if (viewportSize.x / viewportSize.y < 16 / 9.0f) // tall screen
	{
		viewportSize.y = viewportSize.x / 16 * 9;
	}
	Math::Vec2 pos = { (ImGui::GetWindowWidth() / 2.f) - 110.f, 30.f };
	ImGui::SetCursorPos(ImVec2(pos.x, pos.y));
	//if (ImGui::Button("Reset", { 100,25 }))
		//serializationManager->LoadScene("SceneTmp");
	//ImGui::SameLine(0.f,20.f);
	if (ImGui::Button("Play", { 100,25 }))
	{
		//serializationManager->SaveScene("SceneTmp");
		isPaused = false;
	}
	ImGui::SameLine(0.f, 20.f);
	if (ImGui::Button("Pause", { 100,25 }))
		isPaused = true;
	GLuint frameBuffer = renderManager->GetFBO();
	pos = { (ImGui::GetWindowWidth() - viewportSize.x) * 0.5f, 60.f };
	ImGui::SetCursorPos(ImVec2(pos.x, pos.y));
	ImTextureID fameBufferImage = (void*)(intptr_t)frameBuffer;
	ImGui::Image(fameBufferImage, { viewportSize.x, viewportSize.y }, ImVec2(0, 1), ImVec2(1, 0));

	
	ImGui::End();
}
std::string& BreakString(std::string& _str, int _offset)
{
	int offset = 0;
	while (_str.size() > _offset)
	{
		if (_str[_offset] == ' ')
		{
			_str.replace(_offset, 1, "\n");
			_offset += 50;
		}
		else
		{
			offset = (int)_str.find("\n", _offset);
			_offset += offset;
		}
	}
	return _str;
}
/*!*****************************************************************************
\brief
	Editor for game dialogs with options

\return
None.
*******************************************************************************/
void LevelEditor::DialogEditor()
{
	GLuint player_texture = spriteManager->GetTextureID("Textures\\Sprites\\mc.png");
	ImTextureID playerIcon = (void*)(intptr_t)player_texture;
	GLuint passenger_texture = spriteManager->GetTextureID("Textures\\Sprites\\girl.png");
	ImTextureID passengerIcon = (void*)(intptr_t)passenger_texture;
	GLuint send_texture = spriteManager->GetTextureID("Textures\\Icons\\sendIcon.png");
	ImTextureID sendIcon = (void*)(intptr_t)send_texture;
	ImGui::Begin("Dialog Editor");
	int id = 1;
	int id2 = 0;
	int prevID = 1;
	static int selectedID = 0;
	std::string dialog{};
	std::string dialog2{};
	static std::string editDialog{};
	int wrapsize = int(ImGui::GetWindowWidth()/13);
	ImVec2 iconSize = ImVec2(40, 40);
	//ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(100, 0, 0))); ImGui::PopStyleColor();
	while (id)
	{
		if (dialogManager->GetDialogs().size() == 0)
			break;
		dialog = dialogManager->GetDialogue(id);
		BreakString(dialog, wrapsize);
		
		if (dialogManager->GetSpeaker(id))// if right side convo (Player)
		{
			ImGui::NewLine();
			ImGui::SameLine(ImGui::GetWindowWidth()-70);
			ImGui::ImageButton(playerIcon, iconSize, ImVec2(0, 1), ImVec2(1, 0));
			ImGui::SameLine(ImGui::GetWindowWidth() - 77 -(dialog.find("\n") != std::string::npos ? dialog.find("\n") : dialog.size()) * 7.4f);
			if (dialogManager->GetSelectedChoice(prevID))//2nd choice selected
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(200, 0, 0))); //unselected
			else//1st
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(0, 200, 0))); //selected
		}
		else //left side (NPC)
		{
			//ImGui::Button("passenger", ImVec2(40,40));
			ImGui::ImageButton(passengerIcon, iconSize, ImVec2(0, 1), ImVec2(1, 0));
			ImGui::SameLine();
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(0, 0, 200))); 
		}
		ImGui::Button(dialog.c_str());
		ImGui::PopStyleColor();
		if(ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0))
		{//edit text for 1st choice
			selectedID = id;
			editDialog = dialogManager->GetDialogue(selectedID);
			BreakString(editDialog, wrapsize);
		}
		else if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(0))
		{//change selected to 1st choice
			dialogManager->SetSelectedChoice(prevID, 0);
		}
		if (id2) //if have 2nd choice
		{
			dialog2 = dialogManager->GetDialogue(id2);
			BreakString(dialog2, wrapsize);
			if (dialogManager->GetSpeaker(id2))
			{
				ImGui::NewLine();
				ImGui::SameLine(ImGui::GetWindowWidth() - 70);
				ImGui::ImageButton(playerIcon, iconSize, ImVec2(0, 1), ImVec2(1, 0));
				ImGui::SameLine(ImGui::GetWindowWidth() - 77-(dialog2.find("\n") != std::string::npos ? dialog2.find("\n") : dialog2.size()) * 7.4f);
				if (dialogManager->GetSelectedChoice(prevID))//2nd choice selected
					ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(0, 200, 0))); //selected
				else//1st
					ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(200, 0, 0))); //unselected
			}
			else //left side (NPC)
			{
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(0, 0, 200)));
			}
			ImGui::Button(dialog2.c_str());
			ImGui::PopStyleColor();
			if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0))
			{//edit text for 2nd choice
				selectedID = id2;
				editDialog = dialogManager->GetDialogue(selectedID);
				BreakString(editDialog, wrapsize);
			}
			else if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(0))
			{//change selected to 2nd choice
				dialogManager->SetSelectedChoice(prevID, 1);
			}
		}
		//Get new ID for net loop
		if (dialogManager->GetSelectedChoice(prevID))//2nd
			prevID = id2;
		else//1st
			prevID = id;
		id = dialogManager->GetNext(prevID);
		id2 = dialogManager->GetNext2(prevID);
		
			
		ImGui::NewLine();
	}
	ImGui::Separator();
	//LOG_INFO(std::to_string(ImGui::GetScrollY()));
	
	if (selectedID)
	{
		ImGui::Button("", ImVec2(1, 150));
		ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(ImColor(50, 50, 50)));
		ImGui::SetCursorPos(ImVec2(10, ImGui::GetWindowHeight() - 120 + ImGui::GetScrollY()));
		ImGui::BeginChild("yeet", ImVec2(ImGui::GetWindowWidth()-20, 100), true);
		ImGui::InputTextMultiline(" ", const_cast<char*>(editDialog.c_str()), 1000, 
			ImVec2(ImGui::GetWindowWidth()-100, 80));
		ImGui::SameLine();
		if(ImGui::ImageButton(sendIcon, ImVec2(50, 50), ImVec2(0, 1), ImVec2(1, 0)))
		{
			dialogManager->EditDialogue(selectedID, editDialog);
		}
		ImGui::EndChild();
		ImGui::PopStyleColor();
	}

	ImGui::End();
}









/*!*****************************************************************************
\brief
	Shuts down Imgui, release all resources

\return
None.
*******************************************************************************/
void LevelEditor::Exit()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

}
