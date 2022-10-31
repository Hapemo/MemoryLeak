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
	
	//static COMPONENT tempComponent{};
	ImGui::Begin("Entity Manager");
	ImGui::BeginTabBar("Edit Entities ");
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
			if (e.HasComponent<PlayerTmp>())
			{
				PlayerTmpEditor();
			}
			

			//static int addComponentID;
			/*static const char* componentsList[]{ "General","Lifespan","Transform", "Sprite" ,"Animation","SheetAnimation","Physics2D",
				"RectCollider" , "CircleCollider" ,"Edge2DCollider" ,"Point2DCollider","Audio" ,"Text","AI", "Script", "Dialogue", "PlayerTmp"};*/
			ImGui::Combo("Select Component", &addComponentID, componentsList, IM_ARRAYSIZE(componentsList));
			if (ImGui::Button("Add Component"))
			{
				AddComponent();
				std::string add(componentsList[addComponentID]);
				LOG_INFO(add + "conponent added");
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
		ImGui::EndTabItem();

	}
	ImGui::EndTabBar();
	ImGui::End();
}
void InspectorPanel::Free()
{

}

void InspectorPanel::AddComponent()
{
	if (addComponentID == (int)COMPONENTID::GENERAL)
		e.AddComponent<General>({ "_new_", (TAG)0, (SUBTAG)0, true });
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
		e.AddComponent<Text>({ "CaviarDreams.ttf", "HEllO", Math::Vec2{0,0}, 1.f, Color{ 255,255,255,255 } });
	else if (addComponentID == (int)COMPONENTID::AI)
		e.AddComponent<AI>({});
	else if (addComponentID == (int)COMPONENTID::SCRIPT)
		e.AddComponent<Script>({});
	else if (addComponentID == (int)COMPONENTID::DIALOGUE)
		e.AddComponent<Dialogue>({});
	else if (addComponentID == (int)COMPONENTID::PLAYERTMP)
		e.AddComponent<PlayerTmp>({});
	
}
void InspectorPanel::DeleteEntity()
{
	e.Destroy();
	LOG_INFO("Entity deleated");
	selectedEntity = nullptr;
	e = *(static_cast<Entity*>(nullptr));
}
void InspectorPanel::GeneralEditor()
{
	if (ImGui::CollapsingHeader("General") || true) {
		ImGui::Text("General");

		ImGui::Checkbox("isActive", &e.GetComponent<General>().isActive); //isactive
		SaveUndo(e, tempComponent, COMPONENTID::GENERAL);

		ImGui::InputText("Name", const_cast<char*>(e.GetComponent<General>().name.c_str()), 30);
		SaveUndo(e, tempComponent, COMPONENTID::GENERAL);

		int tagID = (int)e.GetComponent<General>().tag;
		static const char* tag[]{ "PLAYER","PASSENGER", "ENEMY", "BUILDING","BACKGROUND", "OTHERS" };
		ImGui::Combo("Tag", &tagID, tag, IM_ARRAYSIZE(tag));
		e.GetComponent<General>().tag = (TAG)tagID;
		SaveUndo(e, tempComponent, COMPONENTID::GENERAL);

		int subtagID = (int)e.GetComponent<General>().subtag;
		static const char* subtag[]{ "NOSUBTAG", "PLAYER", "PASSENGER", "ENEMY", "BUILDING", "OTHERS" };
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

	if (ImGui::CollapsingHeader("Transform")) {
		//ImGui::Text("Transform Component");
		tmpVec2[0] = transformManager->GetScale(e).x;
		tmpVec2[1] = transformManager->GetScale(e).y;
		ImGui::DragFloat2("Set Scale", tmpVec2);
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
		static const char* shape[]{ "SQUARE", "CIRCLE", "TEXTURE","DEBUG_POINT" , "DEBUG_LINE","DEBUG_SQUARE","DEBUG_CIRCLE", "DEBUG_ARROW" };
		ImGui::Combo("Shape", &shapeID, shape, IM_ARRAYSIZE(shape));
		e.GetComponent<Sprite>().sprite = (SPRITE)shapeID;
		SaveUndo(e, tempComponent, COMPONENTID::SPRITE);

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
	if (ImGui::CollapsingHeader("SheetAnimation")) {
		//ImGui::Text("SheetAnimation");
		ImGui::InputInt("frameCount", (int*)&e.GetComponent<SheetAnimation>().frameCount);
		SaveUndo(e, tempComponent, COMPONENTID::SHEETANIMATION);
		ImGui::InputInt("currFrameIndex", (int*)&e.GetComponent<SheetAnimation>().currFrameIndex);
		SaveUndo(e, tempComponent, COMPONENTID::SHEETANIMATION);
		ImGui::InputFloat("timePerFrame", &e.GetComponent<SheetAnimation>().timePerFrame);
		SaveUndo(e, tempComponent, COMPONENTID::SHEETANIMATION);
		ImGui::InputFloat("timeToFrameSwap", &e.GetComponent<SheetAnimation>().timeToFrameSwap);
		SaveUndo(e, tempComponent, COMPONENTID::SHEETANIMATION);
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
		ImGui::Checkbox("gravityEnabled", &e.GetComponent<Physics2D>().gravityEnabled);

		//////
		ImGui::InputFloat("Mass", &e.GetComponent<Physics2D>().mass);
		SaveUndo(e, tempComponent, COMPONENTID::PHYSICS2D);
		ImGui::InputFloat("Speed", &e.GetComponent<Physics2D>().speed);
		SaveUndo(e, tempComponent, COMPONENTID::PHYSICS2D);
		ImGui::InputFloat("moveDirection", &e.GetComponent<Physics2D>().moveDirection);
		SaveUndo(e, tempComponent, COMPONENTID::PHYSICS2D);
		/////

		/*ImGui::InputDouble("gravityScale", &e.GetComponent<Physics2D>().gravityScale);

		ImGui::Checkbox("dynamicsEnabled", &e.GetComponent<Physics2D>().dynamicsEnabled);

		ImGui::InputDouble("Mass", &e.GetComponent<Physics2D>().mass);
		
		ImGui::InputDouble("invMass", &e.GetComponent<Physics2D>().invMass);

		ImGui::InputDouble("inertia", &e.GetComponent<Physics2D>().inertia);

		ImGui::InputFloat("invInertia", &e.GetComponent<Physics2D>().invInertia);

		ImGui::InputDouble("restitution", &e.GetComponent<Physics2D>().restitution);

		ImGui::InputDouble("friction", &e.GetComponent<Physics2D>().friction);

		ImGui::InputDouble("damping", &e.GetComponent<Physics2D>().damping);
				
		tmpVec2[0] = e.GetComponent<Physics2D>().accumulatedForce.x;
		tmpVec2[1] = e.GetComponent<Physics2D>().accumulatedForce.y;
		ImGui::InputFloat2("accumulatedForce", tmpVec2);
		e.GetComponent<Physics2D>().accumulatedForce = { tmpVec2[0] ,tmpVec2[1] };*/

		tmpVec2[0] = e.GetComponent<Physics2D>().velocity.x;
		tmpVec2[1] = e.GetComponent<Physics2D>().velocity.y;
		ImGui::InputFloat2("accumulatedForce", tmpVec2);
		e.GetComponent<Physics2D>().velocity = { tmpVec2[0] ,tmpVec2[1] };

		/*tmpVec2[0] = e.GetComponent<Physics2D>().acceleration.x;
		tmpVec2[1] = e.GetComponent<Physics2D>().acceleration.y;
		ImGui::InputFloat2("accumulatedForce", tmpVec2);
		e.GetComponent<Physics2D>().acceleration = { tmpVec2[0] ,tmpVec2[1] };

		ImGui::InputDouble("angularVelocity", &e.GetComponent<Physics2D>().angularVelocity);

		ImGui::InputDouble("angularTorque", &e.GetComponent<Physics2D>().angularTorque);*/

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
	if (ImGui::CollapsingHeader("Audio")) {
		//ImGui::Text("Audio");
		ImGui::InputText("Addsound", const_cast<char*>(e.GetComponent<Audio>().sound.path.c_str()), 30);
		SaveUndo(e, tempComponent, COMPONENTID::AUDIO);
		static const wchar_t* texpath = (const wchar_t*)"";
		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("AUDIO"))
			{
				texpath = (const wchar_t*)payload->Data;
				std::string tp = (std::string)((const char*)texpath);
				e.GetComponent<Audio>().sound.path = tp;
			}
			ImGui::EndDragDropTarget();
		}

		ImGui::Checkbox("Pause", &e.GetComponent<Audio>().sound.isPaused);
		SaveUndo(e, tempComponent, COMPONENTID::AUDIO);

		ImGui::Checkbox("Click to Play", &e.GetComponent<Audio>().sound.toPlay);
		SaveUndo(e, tempComponent, COMPONENTID::AUDIO);

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
		ImGui::InputText("Addtext", const_cast<char*>(e.GetComponent<Text>().text.c_str()), 30);
		SaveUndo(e, tempComponent, COMPONENTID::TEXT);

		ImGui::InputText("Addfont", const_cast<char*>(e.GetComponent<Text>().fontFile.c_str()), 30);
		SaveUndo(e, tempComponent, COMPONENTID::TEXT);

		tmpVec2[0] = e.GetComponent<Text>().offset.x;
		tmpVec2[1] = e.GetComponent<Text>().offset.y;
		ImGui::DragFloat2("Text Pos", tmpVec2);
		Math::Vec2 scale{ tmpVec2[0] ,tmpVec2[1] };
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
		static const char* colorChange[]{ "None","Smoothy","Traffic Light" };
		int colorChangeID = e.GetComponent<AI>().colorChange;
		ImGui::Combo("Select Color Change", &colorChangeID, colorChange, IM_ARRAYSIZE(colorChange));
		e.GetComponent<AI>().colorChange = colorChangeID;
		SaveUndo(e, tempComponent, COMPONENTID::AI);

		static const char* movement[]{ "None","UP-Down","Left-Right", "Swing", "Circle" };
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