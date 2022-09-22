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
#include <SpriteManager.h>
#include <AI.h>
#include <Logger.h>

#include <filesystem>
#define _USE_MATH_DEFINES
#include <math.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


const Entity* selectedEntity;
int selectedEntityID = 0;
int SRT = 0;
// Simple helper function to load an image into a OpenGL texture with common settings
//bool LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height)
//{
//	 //Load from file
//	int image_width = 0;
//	int image_height = 0;
//	unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
//	if (image_data == NULL)
//		return false;
//
//	// Create a OpenGL texture identifier
//	GLuint image_texture;
//	glGenTextures(1, &image_texture);
//	glBindTexture(GL_TEXTURE_2D, image_texture);
//
//	// Setup filtering parameters for display
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same
//
//	// Upload pixels into texture
//#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
//	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
//#endif
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
//	stbi_image_free(image_data);
//
//	*out_texture = image_texture;
//	*out_width = image_width;
//	*out_height = image_height;
//
//	return true;
//	//return false;
//}
void LevelEditor::Init()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigWindowsMoveFromTitleBarOnly = true;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	//(void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(Application::getWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 450");
	
	//IM_ASSERT(ret);
	//weatherAIinit();
}
void LevelEditor::Window()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	//ImGui::ShowDemoWindow();
}
void LevelEditor::Update()
{
	//weatherAIupdate();
	//ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
	//ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_AutoSelectNewTabs | ImGuiTabBarFlags_Reorderable;
	static bool showdebug = true;
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			ImGui::MenuItem("(menu)", NULL, false, false);
			if (ImGui::MenuItem("New")) {}
			if (ImGui::MenuItem("Open", "Ctrl+O")) 
			{
				serializationManager->LoadScene();
			}
			if (ImGui::MenuItem("Clear Scene"))
			{
				for (const Entity& e : mEntities)
				{
					e.Destroy();
				}

			}
			if (ImGui::BeginMenu("Open Recent"))
			{
				ImGui::MenuItem("Scene1");
				ImGui::MenuItem("Scene2");
				ImGui::EndMenu();
			}
			if (ImGui::MenuItem("Save", "Ctrl+S")) 
			{
				serializationManager->SaveScene();
			}
			if (ImGui::MenuItem("Save As..")) {}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
			if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
			ImGui::Separator();
			if (ImGui::MenuItem("Cut", "CTRL+X")) {}
			if (ImGui::MenuItem("Copy", "CTRL+C")) {}
			if (ImGui::MenuItem("Paste", "CTRL+V")) {}
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
	//ImGui::End();
	

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
	ImGui::EndTabBar();
	ImGui::End();
}
void  LevelEditor::SceneManager()
{
	ImGui::Begin("Scene Manager");
	ImGui::BeginTabBar("Edit Scene ");
	if (ImGui::BeginTabItem("Edit Game: "))
	{
		std::vector<std::string> tag { "PLAYER","PASSENGER", "ENEMY", "BUILDING", "OTHERS" };
		for (int i = 0; i < (int)tag.size(); i++)
		{

			if (ImGui::TreeNode(tag[i].c_str()))
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
								selectedEntityID = counter;
							}
						}
						if (e.HasComponent<Lifespan>())
						{
							ImGui::Text("Lifespan");
							if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
							{
								selectedEntity = &e;
								selectedEntityID = counter;
							}
						}
						if (e.HasComponent<Transform>())
						{
							ImGui::Text("Transform");
							if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
							{
								selectedEntity = &e;
								selectedEntityID = counter;
							}
						}
						if (e.HasComponent<Sprite>())
						{
							ImGui::Text("Sprite");
							if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
							{
								selectedEntity = &e;
								selectedEntityID = counter;
							}
						}
						if (e.HasComponent<Animation>())
						{
							ImGui::Text("Animation");
							if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
							{
								selectedEntity = &e;
								selectedEntityID = counter;
							}
						}
						if (e.HasComponent<SheetAnimation>())
						{
							ImGui::Text("SheetAnimation");
							if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
							{
								selectedEntity = &e;
								selectedEntityID = counter;
							}
						}
						if (e.HasComponent<Physics2D>())
						{
							ImGui::Text("Physics2D");
							if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
							{
								selectedEntity = &e;
								selectedEntityID = counter;
							}
						}
						if (e.HasComponent<RectCollider>())
						{
							ImGui::Text("RectCollider");
							if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
							{
								selectedEntity = &e;
								selectedEntityID = counter;
							}
						}
						if (e.HasComponent<CircleCollider>())
						{
							ImGui::Text("CircleCollider");
							if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
							{
								selectedEntity = &e;
								selectedEntityID = counter;
							}
						}
						if (e.HasComponent<Edge2DCollider>())
						{
							ImGui::Text("Edge2DCollider");
							if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
							{
								selectedEntity = &e;
								selectedEntityID = counter;
							}
						}
						if (e.HasComponent<Stuff>())
						{
							ImGui::Text("Stuff");
							if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
							{
								selectedEntity = &e;
								selectedEntityID = counter;
							}
						}
						if (e.HasComponent<Audio>())
						{
							ImGui::Text("Audio");
							if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
							{
								selectedEntity = &e;
								selectedEntityID = counter;
							}
						}
						if (e.HasComponent<Benchmark>())
						{
							ImGui::Text("Benchmark");
							if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
							{
								selectedEntity = &e;
								selectedEntityID = counter;
							}
						}
						ImGui::TreePop();

					}
					/*else
						first[counter] = false;*/
				}
				ImGui::TreePop();
				if (ImGui::BeginPopupContextWindow(0, 1, false))
				{
					if (ImGui::MenuItem(" Create Entity"))
					{
						//LogInfo("Created new entity");
						Entity e{ ECS::CreateEntity() };
						mEntities.insert(e);
						e.AddComponent(Lifespan{ 0, 2000 },
							General{ "_NEW_", TAG::OTHERS, SUBTAG::NOSUBTAG, true },
							Transform{ {150,150}, 0, {(float)std::rand() / (float)RAND_MAX * 600,(float)std::rand() / (float)RAND_MAX * 400} },
							Sprite{ Color{0,255,0,100}, SPRITE::CIRCLE, 0 },
							RectCollider{ glm::vec2{0,0}, glm::vec2{1,1}, true });
					}
					ImGui::EndPopup();
				}

			}
		}
		if (ImGui::TreeNode("Scene 2"))
		{
			ImGui::Text("Nothing");
			ImGui::TreePop();
		}
		ImGui::EndTabItem();
		if (ImGui::Button("New object"))
		{
			//LogInfo("Created new entity");
			Entity e{ ECS::CreateEntity() };
			mEntities.insert(e);
			e.AddComponent(Lifespan{ 0, 2000 },
				General{"_NEW_", TAG::OTHERS, SUBTAG::NOSUBTAG, true},
				Transform{ {150,150}, 0, {(float)std::rand() / (float)RAND_MAX * 600,(float)std::rand() / (float)RAND_MAX * 400} },
				Sprite{ Color{0,255,0,100}, SPRITE::CIRCLE, 0 },
				RectCollider{ glm::vec2{0,0}, glm::vec2{1,1}, true });
		}
	}
	ImGui::EndTabBar();
	ImGui::End();
}
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
		if (selectedEntity != nullptr && selectedEntityID <= (int)mEntities.size())
		{
			//++counter;
			int counter = selectedEntityID;
			const Entity& e = *selectedEntity;
			//const char* lbl = e.GetComponent<General>().name.c_str();
			//ImGui::Text(lbl);
			if (e.HasComponent<General>())
			{
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
			if (e.HasComponent<Lifespan>())
			{
				ImGui::Text("Lifespan");
				ImGui::InputFloat("Lifespan", &e.GetComponent<Lifespan>().limit);
			}
			if (e.HasComponent<Transform>())
			{
				ImGui::Text("Transform");


				static bool s = 0,r = 0,t = 0;
				ImGui::Checkbox("Scale", &s);
				if (s) { SRT = 1; r = t = 0; }
				ImGui::Checkbox("Rotate", &r);
				if (r) { SRT = 2; s = t = 0; }
				ImGui::Checkbox("translate", &t);
				if (t) { SRT = 3; s = r = 0; }
				if (!s && !r && !t) SRT = 0;

				tmpVec2[0] = transformManager->GetScale(e).x;
				tmpVec2[1] = transformManager->GetScale(e).y;
				ImGui::DragFloat2("Set Scale", tmpVec2);
				glm::vec2 scale{ tmpVec2[0] ,tmpVec2[1] };
				transformManager->SetScale(e, scale);

				tmpVec2[0] = transformManager->GetTranslate(e).x;
				tmpVec2[1] = transformManager->GetTranslate(e).y;
				ImGui::DragFloat2("Set Position", tmpVec2);
				glm::vec2 pos{ tmpVec2[0] ,tmpVec2[1] };
				transformManager->SetTranslate(e, pos);

				tmpFloat = transformManager->GetRotation(e);
				tmpFloat = (float)(tmpFloat / M_PI * 180.f);
				ImGui::SliderFloat("Set Rotation", &tmpFloat, -360.f, 360.f);
				tmpFloat = (float)(tmpFloat * M_PI / 180.f);
				transformManager->SetRotation(e, tmpFloat);

				
			}
			if (e.HasComponent<Sprite>())
			{
				ImGui::Text("Sprite");
				//float shipColor[4];
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

			}
			if (e.HasComponent<Animation>())
			{
				ImGui::Text("Animation");
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
			}
			if (e.HasComponent<SheetAnimation>())
			{
				ImGui::Text("SheetAnimation");
				ImGui::InputInt("frameCount", (int*)&e.GetComponent<SheetAnimation>().frameCount);
				ImGui::InputInt("currFrameIndex", (int*)&e.GetComponent<SheetAnimation>().currFrameIndex);
				ImGui::InputFloat("timePerFrame", &e.GetComponent<SheetAnimation>().timePerFrame);
				ImGui::InputFloat("timeToFrameSwap", &e.GetComponent<SheetAnimation>().timeToFrameSwap);
			}
			if (e.HasComponent<RectCollider>())
			{
				ImGui::Text("RectCollider");
				tmpVec2[0] = e.GetComponent<RectCollider>().centerOffset.x;
				tmpVec2[1] = e.GetComponent<RectCollider>().centerOffset.y;
				ImGui::InputFloat2("Box position Offset", tmpVec2);
				e.GetComponent<RectCollider>().centerOffset = { tmpVec2[0] ,tmpVec2[1]};

				tmpVec2[0] = e.GetComponent<RectCollider>().scaleOffset.x;
				tmpVec2[1] = e.GetComponent<RectCollider>().scaleOffset.y;
				ImGui::InputFloat2("Box scale Offset", tmpVec2);
				e.GetComponent<RectCollider>().scaleOffset = { tmpVec2[0] ,tmpVec2[1] };

				ImGui::Checkbox("Box RenderFlag", &e.GetComponent<RectCollider>().renderFlag);
			}
			if (e.HasComponent<CircleCollider>())
			{
				ImGui::Text("CircleCollider");
				tmpVec2[0] = e.GetComponent<CircleCollider>().centerOffset.x;
				tmpVec2[1] = e.GetComponent<CircleCollider>().centerOffset.y;
				ImGui::InputFloat2("Circle position Offset", tmpVec2);
				e.GetComponent<CircleCollider>().centerOffset = { tmpVec2[0] ,tmpVec2[1] };

				float scale = e.GetComponent<CircleCollider>().scaleOffset;
				ImGui::InputFloat("Circle scale Offset", &scale);
				e.GetComponent<CircleCollider>().scaleOffset = { scale };

				ImGui::Checkbox("Circle RenderFlag", &e.GetComponent<CircleCollider>().renderFlag);
			}
			if (e.HasComponent<Edge2DCollider>())
			{
				ImGui::Text("Edge2DCollider");
				tmpVec2[0] = e.GetComponent<Edge2DCollider>().p0Offset.x;
				tmpVec2[1] = e.GetComponent<Edge2DCollider>().p0Offset.y;
				ImGui::InputFloat2("p0 Offset", tmpVec2);
				e.GetComponent<Edge2DCollider>().p0Offset = { tmpVec2[0] ,tmpVec2[1] };

				ImGui::InputFloat("rotationOffset", &e.GetComponent<Edge2DCollider>().rotationOffset);
				ImGui::InputFloat("scaleOffset", &e.GetComponent<Edge2DCollider>().scaleOffset);
				ImGui::Checkbox("RenderFlag", &e.GetComponent<Edge2DCollider>().renderFlag);
			}
			if (e.HasComponent<Point2DCollider>())
			{
				ImGui::Text("Point2DCollider");
				tmpVec2[0] = e.GetComponent<Point2DCollider>().centerOffset.x;
				tmpVec2[1] = e.GetComponent<Point2DCollider>().centerOffset.y;
				ImGui::InputFloat2("centerOffset", tmpVec2);
				e.GetComponent<Point2DCollider>().centerOffset = { tmpVec2[0] ,tmpVec2[1] };

				ImGui::Checkbox("RenderFlag", &e.GetComponent<Point2DCollider>().renderFlag);
			}
			if (e.HasComponent<Physics2D>())
			{
				ImGui::Text("Physics2D");
				ImGui::InputFloat("Mass", &e.GetComponent<Physics2D>().mass);
				ImGui::InputFloat("Speed", &e.GetComponent<Physics2D>().speed);
				ImGui::InputFloat("moveDirection", &e.GetComponent<Physics2D>().moveDirection);
				ImGui::Checkbox("Physics RenderFlag", &e.GetComponent<Physics2D>().renderFlag);
			}
			if (e.HasComponent<Audio>())
			{
				ImGui::Text("Audio");
				ImGui::InputText("Addsound", const_cast<char*>(e.GetComponent<Audio>().sound.path.c_str()), 30);
				ImGui::Checkbox("Pause", &e.GetComponent<Audio>().sound.isPaused);
			}
			if (e.HasComponent<Stuff>())
			{
				ImGui::Text("Stuff");
				/*static const char* colorChange[]{ "None","Smoothy","Traffic Light" };
				eid = "Select Color Change" + std::to_string(counter);
				strcpy(lbl, eid.c_str());
				int colorChangeID = e.GetComponent<Stuff>().colorChange;
				ImGui::Combo(lbl, &colorChangeID, colorChange, IM_ARRAYSIZE(colorChange));
				e.GetComponent<Stuff>().colorChange = colorChangeID;

				static const char* movement[]{ "None","UP-Down","Left-Right", "Swing", "Circle" };
				eid = "Select Movement" + std::to_string(counter);
				strcpy(lbl, eid.c_str());
				int movementID = e.GetComponent<Stuff>().movement;
				ImGui::Combo(lbl, &movementID, movement, IM_ARRAYSIZE(movement));
				e.GetComponent<Stuff>().movement = movementID;

				if (e.GetComponent<Stuff>().movement)
				{
					eid = "Speed" + std::to_string(counter);
					strcpy(lbl, eid.c_str());
					float speed = e.GetComponent<Stuff>().speed;
					ImGui::SliderFloat(lbl, &speed, 0.f, 15.f);
					e.GetComponent<Stuff>().speed = speed;
					if (e.GetComponent<Stuff>().movement < 4)
					{
						eid = "Range" + std::to_string(counter);
						strcpy(lbl, eid.c_str());
						float range = e.GetComponent<Stuff>().range;
						ImGui::SliderFloat(lbl, &range, 0.f, 400.f);
						e.GetComponent<Stuff>().range = range;
					}
				}*/

			}
			if (e.HasComponent<Benchmark>())
			{
				ImGui::Text("Benchmark");
			}

			static int componentsID;
			static const char* components[]{ "General","Lifespan","Transform", "Sprite" ,"Animation","SheetAnimation","Physics2D",
				"RectCollider" , "CircleCollider" ,"Edge2DCollider" ,"Audio" ,"Stuff" };
			ImGui::Combo("Select Component", &componentsID, components, IM_ARRAYSIZE(components));
			if (ImGui::Button("Add Component"))
			{
				if      (componentsID == 0)
					e.AddComponent<General>({ "_new_", (TAG)0, (SUBTAG)0, true});
				else if (componentsID == 1)
					e.AddComponent<Lifespan>({0,1000});
				else if (componentsID == 2)
					e.AddComponent<Transform>({ {200,100}, 0, {0,0} });
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
			}
			if (ImGui::BeginPopupContextWindow(0, 1, false))
			{
				if (ImGui::MenuItem("Delete Entity"))
				{
					e.Destroy();
					selectedEntity = nullptr;
					selectedEntityID = 99;
				}
				ImGui::EndPopup();
			}
		}
		ImGui::EndTabItem();
		
	}
	ImGui::EndTabBar();
	ImGui::End();
}




void  LevelEditor::AssetManager()
{
	GLuint my_image_texture = spriteManager->GetTextureID("Textures\\Icons\\folderIcon.png");
	GLuint my_image2_texture = 0;
	std::string rootPath = "resources";
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
			{std::string texPath = directory.path().string();
				texPath = texPath.substr(10);
				my_image2_texture = spriteManager->GetTextureID(texPath);
				if (my_image2_texture)
				{
				ImGui::ImageButton((ImTextureID)my_image2_texture, buttonSize, ImVec2(0, 1), ImVec2(1, 0));
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
		ImGui::EndTabItem();
	}
	ImGui::EndTabBar();
	ImGui::End();
}
void LevelEditor::ViewPortManager()
{
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoBackground;
	bool open_ptr = true;
	//ImGui::Begin("View Port Manager", &open_ptr, window_flags);
	ImGui::Begin("View Port Manager");
	ImGui::SameLine(300.f, 0.f);
	ImGui::Button("Reset", {100,25});
	ImGui::SameLine(0.f,20.f);
	ImGui::Button("Play", {100,25});
	ImGui::SameLine(0.f, 20.f);
	ImGui::Button("Pause", { 100,25 });
	GLuint frameBuffer = renderManager->GetFBO();
	ImVec2 viewportSize = ImGui::GetWindowSize();
	viewportSize.y -=70;
	//Calcualting the aspect ratio 
	if (viewportSize.x / viewportSize.y > 16 / 9.0f) //wide screen
	{
		viewportSize.x = viewportSize.y / 9 * 16;
	}
	else if (viewportSize.x / viewportSize.y < 16 / 9.0f) // tall screen
	{
		viewportSize.y = viewportSize.x / 16 * 9;
	}
	ImGui::SetCursorPos(ImVec2((ImGui::GetWindowWidth()- viewportSize.x)*0.5, 60));
	ImGui::Image((ImTextureID)frameBuffer, { viewportSize.x, viewportSize.y}, ImVec2(0, 1), ImVec2(1, 0));

	if (selectedEntity != nullptr && selectedEntityID <= (int)mEntities.size())
	{
		//++counter;
		int counter = selectedEntityID;
		const Entity& e = *selectedEntity;
		//imguizmo
		ImGuizmo::SetOrthographic(true);
		ImGuizmo::SetDrawlist();
		ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y,
			ImGui::GetWindowWidth(), ImGui::GetWindowHeight());
		/*ImGuizmo::SetRect(0, 0,
			ImGui::GetWindowWidth(), ImGui::GetWindowHeight());*/
		glm::mat4 iii = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };
		glm::mat4 view = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };
		view[3][0] /= (float)Application::getWindowWidth() / 2.f;
		view[3][1] /= (float)Application::getWindowHeight() / 2.f;
		//glm::mat4 trans = renderManager->GetTransform(e);
		//glm::mat4 trans2 = glm::inverse(renderManager->GetTransform(e));
		glm::mat4 trans{
		transformManager->GetScale(e).x, 0								,0,transformManager->GetTranslate(e).x,
		0								,transformManager->GetScale(e).y,0,transformManager->GetTranslate(e).y,
		0								,			0					,1,0,
		0								,			0					,0,1};
		
		ImGuizmo::OPERATION opp{};
		if (SRT == 1)
		{
			opp = ImGuizmo::OPERATION::SCALE;
			view[0][0] /= (float)Application::getWindowWidth() / 2.f;
			view[0][1] /= (float)Application::getWindowHeight() / 2.f;
			view[1][0] /= (float)Application::getWindowWidth() / 2.f;
			view[1][1] /= (float)Application::getWindowHeight() / 2.f;
			
		}
		if (SRT == 2)
		{
			opp = ImGuizmo::OPERATION::ROTATE;
		}
		if (SRT == 3)
		{
			opp = ImGuizmo::OPERATION::TRANSLATE;
		}
		if (SRT != 0)
		{
			ImGuizmo::Manipulate(glm::value_ptr(view), glm::value_ptr(iii),
				opp, ImGuizmo::LOCAL, glm::value_ptr(trans));
			if (ImGuizmo::IsUsing())
			{
				if(SRT==3)
					transformManager->SetTranslate(e, { trans[3][0]* (float)Application::getWindowWidth() / 2.f,
						trans[3][1]* (float)Application::getWindowHeight() / 2.f });
				if(SRT==1)
					transformManager->SetScale(e, { glm::length(trans[0]),glm::length(trans[1]) }	);
			}
			//glm::decompose();
		}
		


	}

	
	
	

	ImGui::End();
}





void LevelEditor::Exit()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

}
