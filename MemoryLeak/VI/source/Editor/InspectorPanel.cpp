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
#include "InspectorPanel.h"
#include <ECSManager.h>
void InspectorPanel::Init()
{

}
void InspectorPanel::Update()
{
	float tmpVec2[2];
	float tmpFloat;
	float tmpVec4[4];
	static COMPONENT tempComponent{};
	ImGui::Begin("Entity Manager");
	ImGui::BeginTabBar("Edit Entities ");
	if (ImGui::BeginTabItem("Edit Game: "))
	{
		if (selectedEntity != nullptr)
		{
			Entity e = *selectedEntity;

			if (e.HasComponent<General>())
			{
				if (ImGui::CollapsingHeader("General") || true) {
					ImGui::Text("General");
					ImGui::Checkbox("isActive", &e.GetComponent<General>().isActive); //isactive
					SaveUndo(const_cast<Entity*>(selectedEntity), tempComponent, COMPONENTID::GENERAL);
					ImGui::InputText("Name", const_cast<char*>(e.GetComponent<General>().name.c_str()), 30);
					SaveUndo(const_cast<Entity*>(selectedEntity), tempComponent, COMPONENTID::GENERAL);
					int tagID = (int)e.GetComponent<General>().tag;
					static const char* tag[]{ "PLAYER","PASSENGER", "ENEMY", "BUILDING","BACKGROUND", "OTHERS" };
					ImGui::Combo("Tag", &tagID, tag, IM_ARRAYSIZE(tag));
					SaveUndo(const_cast<Entity*>(selectedEntity), tempComponent, COMPONENTID::GENERAL);
					e.GetComponent<General>().tag = (TAG)tagID;
					int subtagID = (int)e.GetComponent<General>().subtag;
					static const char* subtag[]{ "NOSUBTAG", "PLAYER", "PASSENGER", "ENEMY", "BUILDING", "OTHERS" };
					ImGui::Combo("SubTag", &subtagID, subtag, IM_ARRAYSIZE(subtag));
					SaveUndo(const_cast<Entity*>(selectedEntity), tempComponent, COMPONENTID::GENERAL);
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
					static bool s = 0, r = 0, t = 0;
					ImGui::Checkbox("Scale Gizmo", &s);
					if (s) { SRT = 1; r = t = 0; }
					ImGui::Checkbox("Rotate", &r);
					if (r) { SRT = 2; s = t = 0; }
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
					SaveUndo(const_cast<Entity*>(selectedEntity), tempComponent, COMPONENTID::TRANSFORM);

					tmpVec2[0] = transformManager->GetTranslate(e).x;
					tmpVec2[1] = transformManager->GetTranslate(e).y;
					ImGui::DragFloat2("Set Position", tmpVec2);
					Math::Vec2 pos{ tmpVec2[0] ,tmpVec2[1] };
					transformManager->SetTranslate(e, pos);
					SaveUndo(const_cast<Entity*>(selectedEntity), tempComponent, COMPONENTID::TRANSFORM);

					tmpFloat = transformManager->GetRotation(e);
					tmpFloat = (float)(tmpFloat / M_PI * 180.f);
					ImGui::SliderFloat("Set Rotation", &tmpFloat, -360.f, 360.f);
					tmpFloat = (float)(tmpFloat * M_PI / 180.f);
					transformManager->SetRotation(e, tmpFloat);
					SaveUndo(const_cast<Entity*>(selectedEntity), tempComponent, COMPONENTID::TRANSFORM);
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
					tmpVec4[0] = e.GetComponent<Sprite>().color.r / 255.f;
					tmpVec4[1] = e.GetComponent<Sprite>().color.g / 255.f;
					tmpVec4[2] = e.GetComponent<Sprite>().color.b / 255.f;
					tmpVec4[3] = e.GetComponent<Sprite>().color.a / 255.f;
					ImGui::ColorEdit4("Color", tmpVec4);
					e.GetComponent<Sprite>().color.r = (GLubyte)(tmpVec4[0] * 255);
					e.GetComponent<Sprite>().color.g = (GLubyte)(tmpVec4[1] * 255);
					e.GetComponent<Sprite>().color.b = (GLubyte)(tmpVec4[2] * 255);
					e.GetComponent<Sprite>().color.a = (GLubyte)(tmpVec4[3] * 255);
					std::string tex{};
					if (e.GetComponent<Sprite>().sprite == SPRITE::TEXTURE)
						tex = spriteManager->GetTexturePath(spriteManager->GetTexture(e));
					else if (e.GetComponent<Sprite>().sprite == SPRITE::CIRCLE)
						tex = "CIRCLE";
					else if (e.GetComponent<Sprite>().sprite == SPRITE::SQUARE)
						tex = "SQUARE";

					int shapeID = (int)e.GetComponent<Sprite>().sprite;
					static const char* shape[]{ "SQUARE", "CIRCLE", "TEXTURE","DEBUG_POINT" , "DEBUG_LINE","DEBUG_SQUARE","DEBUG_CIRCLE", "DEBUG_ARROW" };
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
					static std::string  texadd = "Add image";
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
									texadd = (char*)texpath;
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
					e.GetComponent<RectCollider>().centerOffset = { tmpVec2[0] ,tmpVec2[1] };

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
					SaveUndo(const_cast<Entity*>(selectedEntity), tempComponent, COMPONENTID::CIRCLECOLLIDER);

					float scale = e.GetComponent<CircleCollider>().scaleOffset;
					ImGui::InputFloat("Circle scale Offset", &scale);
					e.GetComponent<CircleCollider>().scaleOffset = { scale };
					SaveUndo(const_cast<Entity*>(selectedEntity), tempComponent, COMPONENTID::CIRCLECOLLIDER);

					ImGui::Checkbox("Circle RenderFlag", &e.GetComponent<CircleCollider>().renderFlag);
					SaveUndo(const_cast<Entity*>(selectedEntity), tempComponent, COMPONENTID::CIRCLECOLLIDER);

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
				if (componentsID == 0)
					e.AddComponent<General>({ "_new_", (TAG)0, (SUBTAG)0, true });
				else if (componentsID == 1)
					e.AddComponent<Lifespan>({ 0,1000 });
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
				LOG_INFO(add + "conponent added");
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
void InspectorPanel::Free()
{

}