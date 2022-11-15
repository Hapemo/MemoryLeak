/*!*****************************************************************************
/*!*****************************************************************************
\file LevelEditor.cpp
\author Huang Wei Jhin
\par DP email: h.weijhin@digipen.edu
\par Group: Memory Leak Studios
\date 20-09-2022
\brief
This file contains function definations for a Inspector Panel Editor system that modifies
Entities and its Components.
*******************************************************************************/
#include "InspectorPanel.h"
#include <ECSManager.h>
#include "ScriptManager.h"
/*!*****************************************************************************
\brief
	Initializes the Inspector Panel editor

\return
None.
*******************************************************************************/
void InspectorPanel::Init()
{

}
/*!*****************************************************************************
\brief
	Update the Inspector Panel editor

\return
None.
*******************************************************************************/
void InspectorPanel::Update()
{
	if (ImGui::Begin("Inspector Manager"))
	{
		ImGui::BeginTabBar("Inspector ");
		if (ImGui::BeginTabItem("Edit Game: "))
		{
			if (selectedEntity != nullptr)
			{
				e = *selectedEntity;

				if (e.HasComponent<General>())
				{
					GeneralEditor();
				}
				if (e.HasComponent<Lifespan>())
				{
					LifespanEditor();
				}
				if (e.HasComponent<Transform>())
				{
					TransformEditor();
				}
				if (e.HasComponent<Sprite>())
				{
					SpriteEditor();
				}
				if (e.HasComponent<Animation>())
				{
					AnimationEditor();
				}
				if (e.HasComponent<SheetAnimation>())
				{
					SheetAnimationEditor();
				}
				if (e.HasComponent<Physics2D>())
				{
					Physics2DEditor();
				}
				if (e.HasComponent<RectCollider>())
				{
					RectColliderEditor();
				}
				if (e.HasComponent<LayerCollider>())
				{
					LayerColliderEditor();
				}
				if (e.HasComponent<CircleCollider>())
				{
					CircleColliderEditor();
				}
				if (e.HasComponent<Edge2DCollider>())
				{
					Edge2DColliderEditor();
				}
				if (e.HasComponent<Point2DCollider>())
				{
					Point2DColliderEditor();
				}
				if (e.HasComponent<Audio>())
				{
					AudioEditor();
				}
				if (e.HasComponent<Text>())
				{
					TextEditor();
				}
				if (e.HasComponent<AI>())
				{
					AIEditor();
				}
				if (e.HasComponent<Script>())
				{
					ScriptEditor();
				}
				if (e.HasComponent<Dialogue>())
				{
					DialogueEditor();
				}
				if (e.HasComponent<PlayerTmp>())
				{
					PlayerTmpEditor();
				}
				ImGui::Combo("Select Component", &addComponentID, componentsList, IM_ARRAYSIZE(componentsList));
				if (ImGui::Button("Add Component"))
				{
					AddComponent();
					std::string add(componentsList[addComponentID]);
					LOG_INFO(add + " conponent added");
				}
				if (ImGui::BeginPopupContextWindow(0, 1, false))
				{
					if (ImGui::MenuItem("Delete Entity"))
					{
						DeleteEntity();
					}
					ImGui::EndPopup();
				}
			}
			else if (selectedPrefab != nullptr)
			{
				p = selectedPrefab;
				PrefabEditor();
				ImGui::Combo("Select Prefab Component", &addComponentID, componentsList, IM_ARRAYSIZE(componentsList));
				if (ImGui::Button("Add Component to prefab"))
				{
					AddPrefabComponent();
					std::string add(componentsList[addComponentID]);
					LOG_INFO(add + " conponent added to prefab");
				}
			}
			ImGui::EndTabItem();
		}
		if (Input::CheckKey(E_STATE::PRESS, E_KEY::DELETE))
		{
			DeleteEntity();
		}
		ImGui::EndTabBar();
	}
	ImGui::End();
}
/*!*****************************************************************************
\brief
	Initializes the Inspector Panel editor

\return
None.
*******************************************************************************/
void InspectorPanel::Free()
{

}
/*!*****************************************************************************
\brief
	This function add a component to an entity

\return
None.
*******************************************************************************/
void InspectorPanel::AddComponent()
{
	if (addComponentID == (int)COMPONENTID::GENERAL)
		e.AddComponent<General>({ "_new_", (TAG)0, (SUBTAG)0, true , false});
	else if (addComponentID == (int)COMPONENTID::LIFESPAN)
		e.AddComponent<Lifespan>({ 0,1000 });
	else if (addComponentID == (int)COMPONENTID::TRANSFORM)
		e.AddComponent<Transform>({ {100,100}, 0, {0,0} });
	else if (addComponentID == (int)COMPONENTID::SPRITE)
		e.AddComponent<Sprite>({});
	else if (addComponentID == (int)COMPONENTID::ANIMATION)
		e.AddComponent<Animation>({});
	else if (addComponentID == (int)COMPONENTID::SHEETANIMATION)
		e.AddComponent<SheetAnimation>({});
	else if (addComponentID == (int)COMPONENTID::PHYSICS2D)
		e.AddComponent<Physics2D>({});
	else if (addComponentID == (int)COMPONENTID::RECTCOLLIDER)
		e.AddComponent<RectCollider>({ });
	else if (addComponentID == (int)COMPONENTID::CIRCLECOLLIDER)
		e.AddComponent<CircleCollider>({});
	else if (addComponentID == (int)COMPONENTID::EDGE2DCOLLIDER)
		e.AddComponent<Edge2DCollider>({});
	else if (addComponentID == (int)COMPONENTID::POINT2DCOLLIDER)
		e.AddComponent<Point2DCollider>({});
	else if (addComponentID == (int)COMPONENTID::AUDIO)
		e.AddComponent<Audio>({});
	else if (addComponentID == (int)COMPONENTID::TEXT)
		e.AddComponent<Text>({ "CaviarDreams", "PLAY", Math::Vec2{0,0}, 1.f, Color{ 255,255,255,255 } });
	else if (addComponentID == (int)COMPONENTID::AI)
		e.AddComponent<AI>({});
	else if (addComponentID == (int)COMPONENTID::SCRIPT)
		e.AddComponent<Script>({});
	else if (addComponentID == (int)COMPONENTID::DIALOGUE)
		e.AddComponent<Dialogue>({});
	else if (addComponentID == (int)COMPONENTID::PLAYERTMP)
		e.AddComponent<PlayerTmp>({});
	else if (addComponentID == (int)COMPONENTID::LAYERCOLLIDER)
		e.AddComponent<LayerCollider>({});
	
}
/*!*****************************************************************************
\brief
	This function add a component to an prefab

\return
None.
*******************************************************************************/
void InspectorPanel::AddPrefabComponent()
{
	if (p == nullptr)
		return;
	if (addComponentID == (int)COMPONENTID::GENERAL)
		p->UpdateComponent(General( "_new_", (TAG)7, (SUBTAG)0, true ));
		//p->AddComponent<General>({ "_new_", (TAG)0, (SUBTAG)0, true }); ///casuses memory leaks
	else if (addComponentID == (int)COMPONENTID::LIFESPAN)
		p->AddComponent<Lifespan>({ 0,1000 });
	else if (addComponentID == (int)COMPONENTID::TRANSFORM)
		p->AddComponent<Transform>({ {100,100}, 0, {0,0} });
	else if (addComponentID == (int)COMPONENTID::SPRITE)
		p->AddComponent<Sprite>({});
	else if (addComponentID == (int)COMPONENTID::ANIMATION)
		p->AddComponent<Animation>({});
	else if (addComponentID == (int)COMPONENTID::SHEETANIMATION)
		p->AddComponent<SheetAnimation>({});
	else if (addComponentID == (int)COMPONENTID::PHYSICS2D)
		p->AddComponent<Physics2D>({});
	else if (addComponentID == (int)COMPONENTID::RECTCOLLIDER)
		p->AddComponent<RectCollider>({ });
	else if (addComponentID == (int)COMPONENTID::CIRCLECOLLIDER)
		p->AddComponent<CircleCollider>({});
	else if (addComponentID == (int)COMPONENTID::EDGE2DCOLLIDER)
		p->AddComponent<Edge2DCollider>({});
	else if (addComponentID == (int)COMPONENTID::POINT2DCOLLIDER)
		p->AddComponent<Point2DCollider>({});
	else if (addComponentID == (int)COMPONENTID::AUDIO)
		p->AddComponent<Audio>({});
	else if (addComponentID == (int)COMPONENTID::TEXT)
		p->AddComponent<Text>({ "CaviarDreams", "PLAY", Math::Vec2{0,0}, 1.f, Color{ 255,255,255,255 } });
	else if (addComponentID == (int)COMPONENTID::AI)
		p->AddComponent<AI>({});
	else if (addComponentID == (int)COMPONENTID::SCRIPT)
		p->AddComponent<Script>({});
	else if (addComponentID == (int)COMPONENTID::DIALOGUE)
		p->AddComponent<Dialogue>({});
	else if (addComponentID == (int)COMPONENTID::PLAYERTMP)
		p->AddComponent<PlayerTmp>({});
}

/*!*****************************************************************************
\brief
	This function delete an entity

\return
None.
*******************************************************************************/
void InspectorPanel::DeleteEntity()
{
	GSList[selectedGameState].scenes[selectedScene].mEntities.erase(e);
	e.GetComponent<General>().isActive = false;
	e.GetComponent<General>().isPaused = true;
	//e.Destroy();
	LOG_INFO("Entity deleated");
	selectedEntity = nullptr;
	e = Entity{ 0 };
}
/*!*****************************************************************************
\brief
	This functions below onawards edits a particular component

\return
None.
*******************************************************************************/
void InspectorPanel::GeneralEditor()
{
	if (ImGui::CollapsingHeader("General") || true) {
		ImGui::Text("General");

		ImGui::Checkbox("isActive", &e.GetComponent<General>().isActive); //isactive
		SaveUndo(e, tempComponent, COMPONENTID::GENERAL);

		ImGui::InputText("Name", &e.GetComponent<General>().name);
		SaveUndo(e, tempComponent, COMPONENTID::GENERAL);

		int tagID = (int)e.GetComponent<General>().tag;
		//static const char* tag[]{ "PLAYER","PASSENGER", "ENEMY", "BUILDING","BACKGROUND", "ENVIRONMENT","EFFECTS","PREFABS","OTHERS" };
		ImGui::Combo("Tag", &tagID, tag, IM_ARRAYSIZE(tag));
		e.GetComponent<General>().tag = (TAG)tagID;
		SaveUndo(e, tempComponent, COMPONENTID::GENERAL);

		int subtagID = (int)e.GetComponent<General>().subtag;
		//static const char* subtag[]{ "NOSUBTAG", "PLAYER", "PASSENGER", "ENEMY", "BUILDING", "OTHERS" };
		ImGui::Combo("SubTag", &subtagID, subtag, IM_ARRAYSIZE(subtag));
		e.GetComponent<General>().subtag = (SUBTAG)subtagID;
		SaveUndo(e, tempComponent, COMPONENTID::GENERAL);
	}
}
void InspectorPanel::LifespanEditor()
{
	if (ImGui::CollapsingHeader("Lifespan")) {
		//ImGui::Text("Lifespan");
		SaveUndo(e, tempComponent, COMPONENTID::LIFESPAN);
		ImGui::InputFloat("Lifespan", &e.GetComponent<Lifespan>().limit);
		if (ImGui::Button("Remove Lifespan"))
		{
			e.RemoveComponent<Lifespan>();
			LOG_INFO("Lifespan component removed");
		}
	}
}
void InspectorPanel::TransformEditor()
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

	if (ImGui::CollapsingHeader("Transform") || true) {
		//ImGui::Text("Transform Component");
		if (ImGui::Button("Flip X", ImVec2(ImGui::GetWindowWidth()*0.32f, 18)))
			e.GetComponent<Transform>().scale.x *= -1.f;
		SaveUndo(e, tempComponent, COMPONENTID::TRANSFORM);
		ImGui::SameLine(0.f, 5.f);
		if (ImGui::Button("Flip Y", ImVec2(ImGui::GetWindowWidth() * 0.32f, 18)))
			e.GetComponent<Transform>().scale.y *= -1.f;
		SaveUndo(e, tempComponent, COMPONENTID::TRANSFORM);
		ImGui::SameLine(0.f, 5.f);
		ImGui::Checkbox("Aspect ratio", &aspect);
		tmpVec2[0] = transformManager->GetScale(e).x;
		tmpVec2[1] = transformManager->GetScale(e).y;
		SaveUndo(e, tempComponent, COMPONENTID::TRANSFORM);
		float ratio = tmpVec2[1] / tmpVec2[0];
		ImGui::DragFloat2("Set Scale", tmpVec2);
		if (aspect)
		{
			if (e.HasComponent<Sprite>() && e.GetComponent<Sprite>().sprite == SPRITE::TEXTURE)
				tmpVec2[1] = tmpVec2[0] * GET_ASPECT_RATIO(e.GetComponent<Sprite>().texture);
			else
				tmpVec2[1] = tmpVec2[0]*ratio;
		}
		Math::Vec2 scale{ tmpVec2[0] ,tmpVec2[1] };
		transformManager->SetScale(e, scale);
		SaveUndo(e, tempComponent, COMPONENTID::TRANSFORM);

		tmpVec2[0] = transformManager->GetTranslate(e).x;
		tmpVec2[1] = transformManager->GetTranslate(e).y;
		ImGui::DragFloat2("Set Position", tmpVec2);
		Math::Vec2 pos{ tmpVec2[0] ,tmpVec2[1] };
		transformManager->SetTranslate(e, pos);
		SaveUndo(e, tempComponent, COMPONENTID::TRANSFORM);

		tmpFloat = transformManager->GetRotation(e);
		tmpFloat = (float)(tmpFloat / M_PI * 180.f);
		ImGui::SliderFloat("Set Rotation", &tmpFloat, -360.f, 360.f);
		tmpFloat = (float)(tmpFloat * M_PI / 180.f);
		transformManager->SetRotation(e, tmpFloat);
		SaveUndo(e, tempComponent, COMPONENTID::TRANSFORM);
		/*if (ImGui::Button("Remove Transform"))
		{
			e.RemoveComponent<Transform>();
			LOG_INFO("Transform component removed");
		}*/
	}
}
void InspectorPanel::SpriteEditor()
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
		SaveUndo(e, tempComponent, COMPONENTID::SPRITE);

		std::string tex{};
		if (e.GetComponent<Sprite>().sprite == SPRITE::TEXTURE)
			tex = spriteManager->GetTexturePath(spriteManager->GetTexture(e));
		else if (e.GetComponent<Sprite>().sprite == SPRITE::CIRCLE)
			tex = "CIRCLE";
		else if (e.GetComponent<Sprite>().sprite == SPRITE::SQUARE)
			tex = "SQUARE";
		int shapeID = (int)e.GetComponent<Sprite>().sprite;
		//static const char* shape[]{ "SQUARE", "CIRCLE", "TEXTURE","DEBUG_POINT" , "DEBUG_LINE","DEBUG_SQUARE","DEBUG_CIRCLE", "DEBUG_ARROW" };
		ImGui::Combo("Shape", &shapeID, shape, IM_ARRAYSIZE(shape));
		e.GetComponent<Sprite>().sprite = (SPRITE)shapeID;
		SaveUndo(e, tempComponent, COMPONENTID::SPRITE);

		if ((SPRITE)shapeID != SPRITE::TEXTURE)
		{
			e.GetComponent<Sprite>().texture = 0;
		}
		if (e.GetComponent<Sprite>().sprite == SPRITE::TEXTURE)
		{
			ImGui::InputText("Sprite", &tex);
			spriteManager->SetTexture(e, tex);
			SaveUndo(e, tempComponent, COMPONENTID::SPRITE);

		}
		else
		{
			ImGui::Text(tex.c_str());
		}

		if (ImGui::BeginDragDropTarget())
		{
			static const wchar_t* texpath = (const wchar_t*)"";
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("TEXTURES"))
			{
				texpath = (const wchar_t*)payload->Data;
				std::string tp = (std::string)((const char*)texpath);
				e.GetComponent<Sprite>().sprite = SPRITE::TEXTURE;
				spriteManager->SetTexture(e, tp);
				COMPONENT _new;
				_new = e.GetComponent<Sprite>();
				undoStack.push_back(std::make_pair(e, _new));
				stackPointer = (int)undoStack.size();
			}
			ImGui::EndDragDropTarget();
		}
		ImGui::InputInt("Layer", &e.GetComponent<Sprite>().layer);
		SaveUndo(e, tempComponent, COMPONENTID::SPRITE);

		if (ImGui::Button("Remove Sprite"))
		{
			e.RemoveComponent<Sprite>();
			LOG_INFO("Sprite component removed");
		}
	}
}
void InspectorPanel::AnimationEditor()
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
			SaveUndo(e, tempComponent, COMPONENTID::ANIMATION);
		}
		if (ImGui::Button("Add Sprite"))
		{
			animator->AddImages(e, addImage);
		}
		SaveUndo(e, tempComponent, COMPONENTID::ANIMATION);
		ImGui::InputFloat("timePerImage", &e.GetComponent<Animation>().timePerImage);
		SaveUndo(e, tempComponent, COMPONENTID::ANIMATION);
		ImGui::InputFloat("timeToImageSwap", &e.GetComponent<Animation>().timeToImageSwap);
		SaveUndo(e, tempComponent, COMPONENTID::ANIMATION);
		ImGui::InputInt("currentImageIndex", &e.GetComponent<Animation>().currentImageIndex);
		SaveUndo(e, tempComponent, COMPONENTID::ANIMATION);
		if (ImGui::Button("Remove Animation"))
		{
			e.RemoveComponent<Animation>();
			LOG_INFO("Animation component removed");
		}
	}
}
void InspectorPanel::SheetAnimationEditor()
{
	if (ImGui::CollapsingHeader("SheetAnimation")||isAnimatorEditorFocused()) {
		//ImGui::Text("SheetAnimation");
		ImGui::InputInt("frameCount", &e.GetComponent<SheetAnimation>().frameCount);
		SaveUndo(e, tempComponent, COMPONENTID::SHEETANIMATION);
		ImGui::InputInt("currFrameIndex", (int*)&e.GetComponent<SheetAnimation>().currFrameIndex);
		SaveUndo(e, tempComponent, COMPONENTID::SHEETANIMATION);
		ImGui::InputFloat("timePerFrame", &e.GetComponent<SheetAnimation>().timePerFrame);
		SaveUndo(e, tempComponent, COMPONENTID::SHEETANIMATION);
		//ImGui::InputFloat("timeToFrameSwap", &e.GetComponent<SheetAnimation>().timeToFrameSwap);
		//SaveUndo(e, tempComponent, COMPONENTID::SHEETANIMATION);
		if (ImGui::Button("Remove SheetAnimation"))
		{
			e.RemoveComponent<SheetAnimation>();
			LOG_INFO("SheetAnimation component removed");
		}
	}
}
void InspectorPanel::Physics2DEditor()
{

	if (ImGui::CollapsingHeader("Physics2D")) {
		//ImGui::Text("Physics2D");
		// 
		// 
		//ImGui::Checkbox("gravityEnabled", &e.GetComponent<Physics2D>().gravityEnabled);

		////////
		//ImGui::InputFloat("Mass", &e.GetComponent<Physics2D>().mass);
		//SaveUndo(e, tempComponent, COMPONENTID::PHYSICS2D);
		//ImGui::InputFloat("Speed", &e.GetComponent<Physics2D>().speed);
		//SaveUndo(e, tempComponent, COMPONENTID::PHYSICS2D);
		//ImGui::InputFloat("moveDirection", &e.GetComponent<Physics2D>().moveDirection);
		//SaveUndo(e, tempComponent, COMPONENTID::PHYSICS2D);
		///////
		//ImGui::InputDouble("gravityScale", &e.GetComponent<Physics2D>().gravityScale);

		ImGui::Checkbox("dynamicsEnabled", &e.GetComponent<Physics2D>().dynamicsEnabled);
		SaveUndo(e, tempComponent, COMPONENTID::PHYSICS2D);

		ImGui::InputFloat("Mass", &e.GetComponent<Physics2D>().mass);
		SaveUndo(e, tempComponent, COMPONENTID::PHYSICS2D);

		ImGui::InputFloat("inertia", &e.GetComponent<Physics2D>().inertia);
		SaveUndo(e, tempComponent, COMPONENTID::PHYSICS2D);

		ImGui::InputFloat("restitution", &e.GetComponent<Physics2D>().restitution);
		SaveUndo(e, tempComponent, COMPONENTID::PHYSICS2D);

		ImGui::InputFloat("friction", &e.GetComponent<Physics2D>().friction);
		SaveUndo(e, tempComponent, COMPONENTID::PHYSICS2D);

		ImGui::InputFloat("damping", &e.GetComponent<Physics2D>().damping);
		SaveUndo(e, tempComponent, COMPONENTID::PHYSICS2D);

		tmpVec2[0] = e.GetComponent<Physics2D>().velocity.x;
		tmpVec2[1] = e.GetComponent<Physics2D>().velocity.y;
		ImGui::InputFloat2("velocity", tmpVec2);
		e.GetComponent<Physics2D>().velocity = { tmpVec2[0] ,tmpVec2[1] };
		SaveUndo(e, tempComponent, COMPONENTID::PHYSICS2D);

		tmpVec2[0] = e.GetComponent<Physics2D>().acceleration.x;
		tmpVec2[1] = e.GetComponent<Physics2D>().acceleration.y;
		ImGui::InputFloat2("acceleration", tmpVec2);
		e.GetComponent<Physics2D>().acceleration = { tmpVec2[0] ,tmpVec2[1] };
		SaveUndo(e, tempComponent, COMPONENTID::PHYSICS2D);

				
		tmpVec2[0] = e.GetComponent<Physics2D>().accumulatedForce.x;
		tmpVec2[1] = e.GetComponent<Physics2D>().accumulatedForce.y;
		ImGui::InputFloat2("accumulatedForce", tmpVec2);
		e.GetComponent<Physics2D>().accumulatedForce = { tmpVec2[0] ,tmpVec2[1] };
		SaveUndo(e, tempComponent, COMPONENTID::PHYSICS2D);


		ImGui::InputFloat("angularVelocity", &e.GetComponent<Physics2D>().angularVelocity);
		SaveUndo(e, tempComponent, COMPONENTID::PHYSICS2D);

		ImGui::InputFloat("angularTorque", &e.GetComponent<Physics2D>().angularTorque);
		SaveUndo(e, tempComponent, COMPONENTID::PHYSICS2D);

		ImGui::Checkbox("Physics RenderFlag", &e.GetComponent<Physics2D>().renderFlag);
		SaveUndo(e, tempComponent, COMPONENTID::PHYSICS2D);

		if (ImGui::Button("Remove Physics2D"))
		{
			e.RemoveComponent<Physics2D>();
			LOG_INFO("Physics2D component removed");
		}
	}
}
void InspectorPanel::RectColliderEditor()
{
	if (ImGui::CollapsingHeader("RectCollider")) {
		//ImGui::Text("RectCollider");
		tmpVec2[0] = e.GetComponent<RectCollider>().centerOffset.x;
		tmpVec2[1] = e.GetComponent<RectCollider>().centerOffset.y;
		ImGui::InputFloat2("Box position Offset", tmpVec2);
		e.GetComponent<RectCollider>().centerOffset = { tmpVec2[0] ,tmpVec2[1] };
		SaveUndo(e, tempComponent, COMPONENTID::RECTCOLLIDER);

		tmpVec2[0] = e.GetComponent<RectCollider>().scaleOffset.x;
		tmpVec2[1] = e.GetComponent<RectCollider>().scaleOffset.y;
		ImGui::InputFloat2("Box scale Offset", tmpVec2);
		e.GetComponent<RectCollider>().scaleOffset = { tmpVec2[0] ,tmpVec2[1] };
		SaveUndo(e, tempComponent, COMPONENTID::RECTCOLLIDER);

		ImGui::Checkbox("Rect RenderFlag", &e.GetComponent<RectCollider>().renderFlag);
		SaveUndo(e, tempComponent, COMPONENTID::RECTCOLLIDER);

		if (ImGui::Button("Remove RectCollider"))
		{
			e.RemoveComponent<RectCollider>();
			LOG_INFO("RectCollider component removed");
		}

	}
}
void InspectorPanel::LayerColliderEditor()
{
	if (ImGui::CollapsingHeader("LayerCollider")) {
		//ImGui::Text("LayerCollider");
		tmpVec2[0] = e.GetComponent<LayerCollider>().centerOffset.x;
		tmpVec2[1] = e.GetComponent<LayerCollider>().centerOffset.y;
		ImGui::InputFloat2("Box position Offset", tmpVec2);
		e.GetComponent<LayerCollider>().centerOffset = { tmpVec2[0] ,tmpVec2[1] };
		SaveUndo(e, tempComponent, COMPONENTID::LAYERCOLLIDER);

		tmpVec2[0] = e.GetComponent<LayerCollider>().scaleOffset.x;
		tmpVec2[1] = e.GetComponent<LayerCollider>().scaleOffset.y;
		ImGui::InputFloat2("Box scale Offset", tmpVec2);
		e.GetComponent<LayerCollider>().scaleOffset = { tmpVec2[0] ,tmpVec2[1] };
		SaveUndo(e, tempComponent, COMPONENTID::LAYERCOLLIDER);

		ImGui::Checkbox("Rect RenderFlag", &e.GetComponent<LayerCollider>().renderFlag);
		SaveUndo(e, tempComponent, COMPONENTID::LAYERCOLLIDER);

		if (ImGui::Button("Remove LayerCollider"))
		{
			e.RemoveComponent<LayerCollider>();
			LOG_INFO("LayerCollider component removed");
		}

	}
}
void InspectorPanel::CircleColliderEditor()
{
	if (ImGui::CollapsingHeader("CircleCollider")) {
		//ImGui::Text("CircleCollider");
		tmpVec2[0] = e.GetComponent<CircleCollider>().centerOffset.x;
		tmpVec2[1] = e.GetComponent<CircleCollider>().centerOffset.y;
		ImGui::InputFloat2("Circle position Offset", tmpVec2);
		e.GetComponent<CircleCollider>().centerOffset = { tmpVec2[0] ,tmpVec2[1] };
		SaveUndo(e, tempComponent, COMPONENTID::CIRCLECOLLIDER);

		float scale = e.GetComponent<CircleCollider>().scaleOffset;
		ImGui::InputFloat("Circle scale Offset", &scale);
		e.GetComponent<CircleCollider>().scaleOffset = { scale };
		SaveUndo(e, tempComponent, COMPONENTID::CIRCLECOLLIDER);

		ImGui::Checkbox("Circle RenderFlag", &e.GetComponent<CircleCollider>().renderFlag);
		SaveUndo(e, tempComponent, COMPONENTID::CIRCLECOLLIDER);

		if (ImGui::Button("Remove CircleCollider"))
		{
			e.RemoveComponent<CircleCollider>();
			LOG_INFO("CircleCollider component removed");
		}
	}
}
void InspectorPanel::Edge2DColliderEditor()
{
	if (ImGui::CollapsingHeader("Edge2DCollider")) {
		//ImGui::Text("Edge2DCollider");
		tmpVec2[0] = e.GetComponent<Edge2DCollider>().p0Offset.x;
		tmpVec2[1] = e.GetComponent<Edge2DCollider>().p0Offset.y;
		ImGui::InputFloat2("p0 Offset", tmpVec2);
		e.GetComponent<Edge2DCollider>().p0Offset = { tmpVec2[0] ,tmpVec2[1] };
		SaveUndo(e, tempComponent, COMPONENTID::EDGE2DCOLLIDER);

		ImGui::InputFloat("rotationOffset", &e.GetComponent<Edge2DCollider>().rotationOffset);
		SaveUndo(e, tempComponent, COMPONENTID::EDGE2DCOLLIDER);

		ImGui::InputFloat("scaleOffset", &e.GetComponent<Edge2DCollider>().scaleOffset);
		SaveUndo(e, tempComponent, COMPONENTID::EDGE2DCOLLIDER);

		ImGui::Checkbox("RenderFlag", &e.GetComponent<Edge2DCollider>().renderFlag);
		SaveUndo(e, tempComponent, COMPONENTID::EDGE2DCOLLIDER);
		
		if (ImGui::Button("Remove Edge2DCollider"))
		{
			e.RemoveComponent<Edge2DCollider>();
			LOG_INFO("Edge2DCollider component removed");
		}
	}
}
void InspectorPanel::Point2DColliderEditor()
{
	if (ImGui::CollapsingHeader("Point2DCollider")) {
		//ImGui::Text("Point2DCollider");
		tmpVec2[0] = e.GetComponent<Point2DCollider>().centerOffset.x;
		tmpVec2[1] = e.GetComponent<Point2DCollider>().centerOffset.y;
		ImGui::InputFloat2("centerOffset", tmpVec2);
		e.GetComponent<Point2DCollider>().centerOffset = { tmpVec2[0] ,tmpVec2[1] };
		SaveUndo(e, tempComponent, COMPONENTID::POINT2DCOLLIDER);

		ImGui::Checkbox("RenderFlag", &e.GetComponent<Point2DCollider>().renderFlag);
		SaveUndo(e, tempComponent, COMPONENTID::POINT2DCOLLIDER);

		if (ImGui::Button("Remove Point2DCollider"))
		{
			e.RemoveComponent<Point2DCollider>();
			LOG_INFO("Point2DCollider component removed");
		}
	}
}
void InspectorPanel::AudioEditor()
{
	if (ImGui::CollapsingHeader("Audio") || true) {
		//ImGui::Text("Audio");
		ImGui::InputText("Addsound", &e.GetComponent<Audio>().sound.path);
		SaveUndo(e, tempComponent, COMPONENTID::AUDIO);
		static const wchar_t* texpath = (const wchar_t*)"";
		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("AUDIO"))
			{
				texpath = (const wchar_t*)payload->Data;
				std::string tp = (std::string)((const char*)texpath);
				e.GetComponent<Audio>().sound.path = tp;
				COMPONENT _new;
				_new = e.GetComponent<Audio>();
				undoStack.push_back(std::make_pair(e, _new));
				stackPointer = (int)undoStack.size();
			}
			ImGui::EndDragDropTarget();
		}

		ImGui::Checkbox("Pause", &e.GetComponent<Audio>().sound.isPaused);
		SaveUndo(e, tempComponent, COMPONENTID::AUDIO);

		/*ImGui::Checkbox("Click to Play", &e.GetComponent<Audio>().sound.toPlay);
		SaveUndo(e, tempComponent, COMPONENTID::AUDIO);*/
		if (ImGui::Button("Play"))
		{
			audioManager->PlayAnySound(e.GetComponent<Audio>().sound.path, 17);
		}
		//ImGui::Checkbox("isLoop", &e.GetComponent<Audio>().sound.isLoop);
		if (ImGui::Button("Remove Audio"))
		{
			e.RemoveComponent<Audio>();
			LOG_INFO("Audio component removed");
		}
	}
}
void InspectorPanel::TextEditor()
{
	if (ImGui::CollapsingHeader("Text")) {
		//ImGui::Text("Text");
		//ImGuiInput
		ImGui::InputText("Add text", &e.GetComponent<Text>().text);
		SaveUndo(e, tempComponent, COMPONENTID::TEXT);
		ImGui::InputText("Add font", &e.GetComponent<Text>().fontFile);
		if (ImGui::BeginDragDropTarget())
		{
			static const wchar_t* texpath = (const wchar_t*)"";
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("FONT"))
			{
				texpath = (const wchar_t*)payload->Data;
				std::string tp = (std::string)((const char*)texpath);
				e.GetComponent<Text>().fontFile = tp;
			}
			ImGui::EndDragDropTarget();
		}
		SaveUndo(e, tempComponent, COMPONENTID::TEXT);

		tmpVec2[0] = e.GetComponent<Text>().offset.x;
		tmpVec2[1] = e.GetComponent<Text>().offset.y;
		ImGui::DragFloat2("Text Pos", tmpVec2);
		e.GetComponent<Text>().offset = Math::Vec2(tmpVec2[0], tmpVec2[1]);
		SaveUndo(e, tempComponent, COMPONENTID::TEXT);

		ImGui::DragFloat("Text Scale", &e.GetComponent<Text>().scale);
		SaveUndo(e, tempComponent, COMPONENTID::TEXT);

		tmpVec4[0] = e.GetComponent<Text>().color.r / 255.f;
		tmpVec4[1] = e.GetComponent<Text>().color.g / 255.f;
		tmpVec4[2] = e.GetComponent<Text>().color.b / 255.f;
		tmpVec4[3] = e.GetComponent<Text>().color.a / 255.f;
		ImGui::ColorEdit4("Text Color", tmpVec4);
		e.GetComponent<Text>().color.r = (GLubyte)(tmpVec4[0] * 255);
		e.GetComponent<Text>().color.g = (GLubyte)(tmpVec4[1] * 255);
		e.GetComponent<Text>().color.b = (GLubyte)(tmpVec4[2] * 255);
		e.GetComponent<Text>().color.a = (GLubyte)(tmpVec4[3] * 255);
		SaveUndo(e, tempComponent, COMPONENTID::TEXT);

		if (ImGui::Button("Remove Text"))
		{
			e.RemoveComponent<Text>();
			LOG_INFO("Text component removed");
		}
	}
}
void InspectorPanel::PlayerTmpEditor()
{
	if (ImGui::CollapsingHeader("PlayerTmp"))
	{
		ImGui::InputInt("HP", &e.GetComponent<PlayerTmp>().HP);
		SaveUndo(e, tempComponent, COMPONENTID::PLAYERTMP);
	}
}
void InspectorPanel::AIEditor()
{

	if (ImGui::CollapsingHeader("AI")) {
		//static const char* colorChange[]{ "None","Smoothy","Traffic Light" };
		int colorChangeID = e.GetComponent<AI>().colorChange;
		ImGui::Combo("Select Color Change", &colorChangeID, colorChange, IM_ARRAYSIZE(colorChange));
		e.GetComponent<AI>().colorChange = colorChangeID;
		SaveUndo(e, tempComponent, COMPONENTID::AI);

		//static const char* movement[]{ "None","UP-Down","Left-Right", "Swing", "Circle" };
		int movementID = e.GetComponent<AI>().movement;
		ImGui::Combo("Select Movement", &movementID, movement, IM_ARRAYSIZE(movement));
		e.GetComponent<AI>().movement = movementID;
		SaveUndo(e, tempComponent, COMPONENTID::AI);

		if (e.GetComponent<AI>().movement)
		{
			float speed = e.GetComponent<AI>().speed;
			ImGui::SliderFloat("Speed", &speed, 0.f, 15.f);
			e.GetComponent<AI>().speed = speed;
			SaveUndo(e, tempComponent, COMPONENTID::AI);
			if (e.GetComponent<AI>().movement < 4)
			{
				float range = e.GetComponent<AI>().range;
				ImGui::SliderFloat("Range", &range, 0.f, 400.f);
				e.GetComponent<AI>().range = range;
				SaveUndo(e, tempComponent, COMPONENTID::AI);
			}
		}
		if (ImGui::Button("Remove AI"))
		{
			e.RemoveComponent<AI>();
			LOG_INFO("AI component removed");
		}
	}
}
void InspectorPanel::ScriptEditor()
{
	if (ImGui::CollapsingHeader("Script")) {
		if (ImGui::InputText("Add script file name", &e.GetComponent<Script>().name))
		{
			//e.GetComponent<Script>().script = ScriptManager<ScriptComponent>::GetInstance()->GetScript(e.GetComponent<Script>().name);
		}
		if (ImGui::BeginDragDropTarget())
		{
			static const wchar_t* texpath = (const wchar_t*)"";
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("SCRIPT"))
			{
				texpath = (const wchar_t*)payload->Data;
				std::string tp = (std::string)((const char*)texpath);
				e.GetComponent<Script>().name = tp;
				//e.GetComponent<Script>().script = ScriptManager<ScriptComponent>::GetInstance()->GetScript(e.GetComponent<Script>().name);
			}
			ImGui::EndDragDropTarget();
		}
		if (ImGui::Button("Remove Script"))
		{
			e.RemoveComponent<Script>();
			LOG_INFO("Script component removed");
		}
	}
}
void InspectorPanel::DialogueEditor()
{
	if (ImGui::CollapsingHeader("Dialogue")) 
	{
		std::string dia = "Dialogue WIP";
		//ImGui:Text(dia.c_str());
		if (ImGui::Button("Remove Dialogue"))
		{
			e.RemoveComponent<Dialogue>();
			LOG_INFO("Dialogue component removed");
		}
	}
}

/*!*****************************************************************************
\brief
	This functions below onawards edits a particular component in a prefab

\return
None.
*******************************************************************************/
void InspectorPanel::PrefabEditor()
{
	if (p == nullptr)
		return;
	if (p->HasComponent<General>())
	{
		ImGui::InputText("Prefab Name", &p->Name());
		if (ImGui::CollapsingHeader("General") || true) {
			ImGui::Text("General");
			//General general = p->GetComponent<General>();
			//ImGui::Checkbox("isActive", &general.isActive); //isactive
			//
			////Should not chnage general name for all prefabees
			//ImGui::InputText("Name", &general.name);


			//int tagID = (int)general.tag;
			////static const char* tag[]{ "PLAYER","PASSENGER", "ENEMY", "BUILDING","BACKGROUND", "ENVIRONMENT","EFFECTS","PREFABS","OTHERS"};
			//ImGui::Combo("Tag", &tagID, tag, IM_ARRAYSIZE(tag));
			//general.tag = (TAG)tagID;


			//int subtagID = (int)general.subtag;
			////static const char* subtag[]{ "NOSUBTAG", "PLAYER", "PASSENGER", "ENEMY", "BUILDING", "OTHERS" };
			//ImGui::Combo("SubTag", &subtagID, subtag, IM_ARRAYSIZE(subtag));
			//general.subtag = (SUBTAG)subtagID;
			//p->UpdateComponent(general);
		}
	}
	if (p->HasComponent<Lifespan>())
	{
		if (ImGui::CollapsingHeader("Lifespan")) {
			//ImGui::Text("Lifespan");
			Lifespan lifespan = p->GetComponent<Lifespan>();
			ImGui::InputFloat("Lifespan", &lifespan.limit);
			p->UpdateComponent(lifespan);
			if (ImGui::Button("Remove Lifespan"))
			{
				p->RemoveComponent<Lifespan>();
				LOG_INFO("Lifespan component removed");
			}
		}
	}

	if (p->HasComponent<Transform>())
	{
		if (ImGui::CollapsingHeader("Transform")) {
			Transform transform = p->GetComponent<Transform>();
			//ImGui::Text("Transform Component");
			tmpVec2[0] = transform.scale.x;
			tmpVec2[1] = transform.scale.y;
			ImGui::DragFloat2("Set Scale", tmpVec2);
			transform.scale = { tmpVec2[0] ,tmpVec2[1] };

			tmpVec2[0] = transform.translation.x;
			tmpVec2[1] = transform.translation.y;
			ImGui::DragFloat2("Set Position", tmpVec2);
			transform.translation = { tmpVec2[0] ,tmpVec2[1] };

			tmpFloat = transform.rotation;
			tmpFloat = (float)(tmpFloat / M_PI * 180.f);
			ImGui::SliderFloat("Set Rotation", &tmpFloat, -360.f, 360.f);
			tmpFloat = (float)(tmpFloat * M_PI / 180.f);
			transform.rotation = tmpFloat;
			p->UpdateComponent(transform);
			if (ImGui::Button("Remove Transform"))
			{
				p->RemoveComponent<Transform>();
				LOG_INFO("Transform component removed");
			}
		}

	}

	if (p->HasComponent<Sprite>())
	{
		if (ImGui::CollapsingHeader("Sprite")) {
			//ImGui::Text("Sprite");
			Sprite sprite = p->GetComponent<Sprite>();
			tmpVec4[0] = sprite.color.r / 255.f;
			tmpVec4[1] = sprite.color.g / 255.f;
			tmpVec4[2] = sprite.color.b / 255.f;
			tmpVec4[3] = sprite.color.a / 255.f;
			ImGui::ColorEdit4("Color", tmpVec4);
			sprite.color.r = (GLubyte)(tmpVec4[0] * 255);
			sprite.color.g = (GLubyte)(tmpVec4[1] * 255);
			sprite.color.b = (GLubyte)(tmpVec4[2] * 255);
			sprite.color.a = (GLubyte)(tmpVec4[3] * 255);
			std::string tex{};
			if (sprite.sprite == SPRITE::TEXTURE)
				tex = spriteManager->GetTexturePath(sprite.texture);
			else if (sprite.sprite == SPRITE::CIRCLE)
				tex = "CIRCLE";
			else if (sprite.sprite == SPRITE::SQUARE)
				tex = "SQUARE";

			int shapeID = (int)sprite.sprite;
			//static const char* shape[]{ "SQUARE", "CIRCLE", "TEXTURE","DEBUG_POINT" , "DEBUG_LINE","DEBUG_SQUARE","DEBUG_CIRCLE", "DEBUG_ARROW" };
			ImGui::Combo("Shape", &shapeID, shape, IM_ARRAYSIZE(shape));
			sprite.sprite = (SPRITE)shapeID;
			if ((SPRITE)shapeID != SPRITE::TEXTURE)
			{
				sprite.texture = 0;
			}
			ImGui::Text(tex.c_str());

			static const wchar_t* texpath = (const wchar_t*)"";
			if (ImGui::BeginDragDropTarget())
			{
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("TEXTURES"))
				{
					texpath = (const wchar_t*)payload->Data;
					std::string tp = (std::string)((const char*)texpath);
					sprite.sprite = SPRITE::TEXTURE;
					sprite.texture = spriteManager->GetTextureID(tp);
				}
				ImGui::EndDragDropTarget();
			}
			ImGui::InputInt("Layer", &sprite.layer);
			p->UpdateComponent(sprite);
			if (ImGui::Button("Remove Sprite"))
			{
				p->RemoveComponent<Sprite>();
				LOG_INFO("Sprite component removed");
			}
		}
	}
	if (p->HasComponent<Animation>())
	{
		if (ImGui::CollapsingHeader("Animation")) {
			//ImGui::Text("Animation");
			Animation animation = p->GetComponent<Animation>();
			static GLuint addImage = {};
			static std::string  texadd = "Add image";
			for (size_t i = 0; i <= animation.images.size(); ++i)
			{
				std::string tex{};
				if (i != animation.images.size())
				{
					tex = spriteManager->GetTexturePath(animation.images[i]);
					ImGui::Text(tex.c_str());
				}
				else
				{
					ImGui::InputText("Addimage", &texadd);
					tex = texadd;
				}
				static const wchar_t* texpath = (const wchar_t*)"";
				if (ImGui::BeginDragDropTarget())
				{
					if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("TEXTURES"))
					{
						texpath = (const wchar_t*)payload->Data;
						if (i == p->GetComponent<Animation>().images.size())
							texadd = (char*)texpath;
						std::string  tp = (std::string)((const char*)texpath);
						if (i != animation.images.size())
							animation.images[i] = spriteManager->GetTextureID(tp);
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
			ImGui::InputFloat("timePerImage", &animation.timePerImage);
			ImGui::InputFloat("timeToImageSwap", &animation.timeToImageSwap);
			ImGui::InputInt("currentImageIndex", &animation.currentImageIndex);
			p->UpdateComponent<Animation>(animation);
			if (ImGui::Button("Remove Animation"))
			{
				p->RemoveComponent<Animation>();
				LOG_INFO("Animation component removed");
			}
		}
	}
	if (p->HasComponent<SheetAnimation>())
	{
		if (ImGui::CollapsingHeader("SheetAnimation")) {
			//ImGui::Text("SheetAnimation");
			SheetAnimation sheetAnimation = p->GetComponent<SheetAnimation>();
			ImGui::InputInt("frameCount", &sheetAnimation.frameCount);
			ImGui::InputInt("currFrameIndex", &sheetAnimation.currFrameIndex);
			ImGui::InputFloat("timePerFrame", &sheetAnimation.timePerFrame);
			ImGui::InputFloat("timeToFrameSwap", &sheetAnimation.timeToFrameSwap);
			p->UpdateComponent<SheetAnimation>(sheetAnimation);
			if (ImGui::Button("Remove SheetAnimation"))
			{
				p->RemoveComponent<SheetAnimation>();
				LOG_INFO("SheetAnimation component removed");
			}
		}
	}
	if (p->HasComponent<RectCollider>())
	{
		if (ImGui::CollapsingHeader("RectCollider")) {
			//ImGui::Text("RectCollider");
			RectCollider rectCollider = p->GetComponent<RectCollider>();
			tmpVec2[0] = p->GetComponent<RectCollider>().centerOffset.x;
			tmpVec2[1] = p->GetComponent<RectCollider>().centerOffset.y;
			ImGui::InputFloat2("Box position Offset", tmpVec2);
			rectCollider.centerOffset = { tmpVec2[0] ,tmpVec2[1] };

			tmpVec2[0] = rectCollider.scaleOffset.x;
			tmpVec2[1] = rectCollider.scaleOffset.y;
			ImGui::InputFloat2("Box scale Offset", tmpVec2);
			rectCollider.scaleOffset = { tmpVec2[0] ,tmpVec2[1] };

			ImGui::Checkbox("Rect RenderFlag", &rectCollider.renderFlag);
			p->UpdateComponent<RectCollider>(rectCollider);
			if (ImGui::Button("Remove RectCollider"))
			{
				p->RemoveComponent<RectCollider>();
				LOG_INFO("RectCollider component removed");
			}
		}
	}
	if (p->HasComponent<CircleCollider>())
	{
		if (ImGui::CollapsingHeader("CircleCollider")) {
			//ImGui::Text("CircleCollider");
			CircleCollider circleCollider = p->GetComponent<CircleCollider>();
			tmpVec2[0] = circleCollider.centerOffset.x;
			tmpVec2[1] = circleCollider.centerOffset.y;
			ImGui::InputFloat2("Circle position Offset", tmpVec2);
			circleCollider.centerOffset = { tmpVec2[0] ,tmpVec2[1] };

			float scale = circleCollider.scaleOffset;
			ImGui::InputFloat("Circle scale Offset", &scale);
			circleCollider.scaleOffset = { scale };

			ImGui::Checkbox("Circle RenderFlag", &circleCollider.renderFlag);

			p->UpdateComponent<CircleCollider>(circleCollider);
			if (ImGui::Button("Remove CircleCollider"))
			{
				p->RemoveComponent<CircleCollider>();
				LOG_INFO("CircleCollider component removed");
			}
		}
	}
	if (p->HasComponent<Edge2DCollider>())
	{
		if (ImGui::CollapsingHeader("Edge2DCollider")) {
			//ImGui::Text("Edge2DCollider");
			Edge2DCollider edge2DCollider = p->GetComponent<Edge2DCollider>();
			tmpVec2[0] = edge2DCollider.p0Offset.x;
			tmpVec2[1] = edge2DCollider.p0Offset.y;
			ImGui::InputFloat2("p0 Offset", tmpVec2);
			edge2DCollider.p0Offset = { tmpVec2[0] ,tmpVec2[1] };

			ImGui::InputFloat("rotationOffset", &edge2DCollider.rotationOffset);
			ImGui::InputFloat("scaleOffset", &edge2DCollider.scaleOffset);
			ImGui::Checkbox("RenderFlag", &edge2DCollider.renderFlag);
			p->UpdateComponent<Edge2DCollider>(edge2DCollider);
			if (ImGui::Button("Remove Edge2DCollider"))
			{
				p->RemoveComponent<Edge2DCollider>();
				LOG_INFO("Edge2DCollider component removed");
			}
		}
	}
	if (p->HasComponent<Point2DCollider>())
	{
		if (ImGui::CollapsingHeader("Point2DCollider")) {
			//ImGui::Text("Point2DCollider");
			Point2DCollider point2DCollider = p->GetComponent<Point2DCollider>();
			tmpVec2[0] = point2DCollider.centerOffset.x;
			tmpVec2[1] = point2DCollider.centerOffset.y;
			ImGui::InputFloat2("centerOffset", tmpVec2);
			point2DCollider.centerOffset = { tmpVec2[0] ,tmpVec2[1] };

			ImGui::Checkbox("RenderFlag", &point2DCollider.renderFlag);
			p->UpdateComponent<Point2DCollider>(point2DCollider);
			if (ImGui::Button("Remove Point2DCollider"))
			{
				p->RemoveComponent<Point2DCollider>();
				LOG_INFO("Point2DCollider component removed");
			}
		}
	}
	if (p->HasComponent<Physics2D>())
	{
		if (ImGui::CollapsingHeader("Physics2D")) {
			//ImGui::Text("Physics2D");
			Physics2D physics2D = p->GetComponent<Physics2D>();
			ImGui::Checkbox("dynamicsEnabled", &e.GetComponent<Physics2D>().dynamicsEnabled);
			ImGui::InputFloat("Mass", &physics2D.mass);
			ImGui::InputFloat("inertia", &physics2D.inertia);
			ImGui::InputFloat("restitution", &physics2D.restitution);
			ImGui::InputFloat("friction", &physics2D.friction);
			ImGui::InputFloat("damping", &physics2D.damping);

			tmpVec2[0] = physics2D.velocity.x;
			tmpVec2[1] = physics2D.velocity.y;
			ImGui::InputFloat2("velocity", tmpVec2);
			physics2D.velocity = { tmpVec2[0] ,tmpVec2[1] };

			tmpVec2[0] = physics2D.acceleration.x;
			tmpVec2[1] = physics2D.acceleration.y;
			ImGui::InputFloat2("acceleration", tmpVec2);
			physics2D.acceleration = { tmpVec2[0] ,tmpVec2[1] };


			tmpVec2[0] = physics2D.accumulatedForce.x;
			tmpVec2[1] = physics2D.accumulatedForce.y;
			ImGui::InputFloat2("accumulatedForce", tmpVec2);
			physics2D.accumulatedForce = { tmpVec2[0] ,tmpVec2[1] };

			ImGui::InputFloat("angularVelocity", &physics2D.angularVelocity);
			ImGui::InputFloat("angularTorque", &physics2D.angularTorque);
			ImGui::Checkbox("Physics RenderFlag", &physics2D.renderFlag);


			p->UpdateComponent<Physics2D>(physics2D);
			if (ImGui::Button("Remove Physics2D"))
			{
				p->RemoveComponent<Physics2D>();
				LOG_INFO("Physics2D component removed");
			}
		}
	}
	if (p->HasComponent<Audio>())
	{
		if (ImGui::CollapsingHeader("Audio")) {
			//ImGui::Text("Audio");
			Audio audio = p->GetComponent<Audio>();
			ImGui::InputText("Addsound", &audio.sound.path);
			ImGui::Checkbox("Pause", &audio.sound.isPaused);
			//ImGui::Checkbox("Click to Play", &audio.sound.toPlay);
			if (ImGui::Button("Play", ImVec2(50, 10)))
			{
				audioManager->PlayAnySound(audio.sound.path, 17);
			}
			//ImGui::Checkbox("isLoop", &audio.sound.isLoop);
			p->UpdateComponent<Audio>(audio);
			if (ImGui::Button("Remove Audio"))
			{
				p->RemoveComponent<Audio>();
				LOG_INFO("Audio component removed");
			}
		}
	}
	if (p->HasComponent<Text>())
	{
		if (ImGui::CollapsingHeader("Text")) {
			//ImGui::Text("Text");
			Text text = p->GetComponent<Text>();
			ImGui::InputText("Addstrtext", &text.text);
			ImGui::InputText("Addfont", &text.fontFile);

			tmpVec2[0] = text.offset.x;
			tmpVec2[1] = text.offset.y;
			ImGui::DragFloat2("Text Pos", tmpVec2);
			text.offset = Math::Vec2(tmpVec2[0], tmpVec2[1]);

			ImGui::DragFloat("Text Scale", &text.scale);

			tmpVec4[0] = text.color.r / 255.f;
			tmpVec4[1] = text.color.g / 255.f;
			tmpVec4[2] = text.color.b / 255.f;
			tmpVec4[3] = text.color.a / 255.f;
			ImGui::ColorEdit4("Text Color", tmpVec4);
			text.color.r = (GLubyte)(tmpVec4[0] * 255);
			text.color.g = (GLubyte)(tmpVec4[1] * 255);
			text.color.b = (GLubyte)(tmpVec4[2] * 255);
			text.color.a = (GLubyte)(tmpVec4[3] * 255);
			p->UpdateComponent<Text>(text);

			if (ImGui::Button("Remove Text"))
			{
				e.RemoveComponent<Text>();
				LOG_INFO("Text component removed");
			}
		}
	}
	if (p->HasComponent<AI>())
	{
		if (ImGui::CollapsingHeader("AI")) {
			AI ai = p->GetComponent<AI>();
			//static const char* colorChange[]{ "None","Smoothy","Traffic Light" };
			int colorChangeID = ai.colorChange;
			ImGui::Combo("Select Color Change", &colorChangeID, colorChange, IM_ARRAYSIZE(colorChange));
			ai.colorChange = colorChangeID;

			//static const char* movement[]{ "None","UP-Down","Left-Right", "Swing", "Circle" };
			int movementID = ai.movement;
			ImGui::Combo("Select Movement", &movementID, movement, IM_ARRAYSIZE(movement));
			ai.movement = movementID;

			if (ai.movement)
			{
				float speed = ai.speed;
				ImGui::SliderFloat("Speed", &speed, 0.f, 15.f);
				ai.speed = speed;
				if (ai.movement < 4)
				{
					float range = ai.range;
					ImGui::SliderFloat("Range", &range, 0.f, 400.f);
					ai.range = range;
				}
			}
			p->UpdateComponent<AI>(ai);
			if (ImGui::Button("Remove AI"))
			{
				p->RemoveComponent<AI>();
				LOG_INFO("AI component removed");
			}
		}
	}
	if (p->HasComponent<Script>())
	{
		if (ImGui::CollapsingHeader("Script")) {
			ImGui::InputText("Add script file name", &e.GetComponent<Script>().name);
			if (ImGui::Button("Remove Script"))
			{
				e.RemoveComponent<Script>();
				LOG_INFO("Script component removed");
			}
		}
	}
	if (p->HasComponent<Dialogue>())
	{
		if (ImGui::CollapsingHeader("Dialogue"))
		{
			std::string dia = "Dialogue WIP";
			//ImGui:Text(dia.c_str());
			if (ImGui::Button("Remove Dialogue"))
			{
				e.RemoveComponent<Dialogue>();
				LOG_INFO("Dialogue component removed");
			}
		}
	}

}