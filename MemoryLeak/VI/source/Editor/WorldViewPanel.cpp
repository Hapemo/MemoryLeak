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
#include "WorldViewPanel.h"
#include <ECSManager.h>
void WorldViewPanel::Init()
{

}
void WorldViewPanel::Update()
{
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoBackground;
	//bool open_ptr = true;
	//ImGui::Begin("View Port Manager", &open_ptr, window_flags);
	ImGui::Begin("World View");
	Math::Vec2 viewportSize = { ImGui::GetWindowSize().x,ImGui::GetWindowSize().y };
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
		renderManager->GetWorldCamera() *= 0.01f;
	}
	ImGui::SameLine(0.f, 20.f);
	if (ImGui::Button("Pause", { 100,25 }))
	{
		//isPaused = true;
	}
	static Math::Vec2 ScreenMousePos{};
	static Math::Vec2 WorldMousePos{};
	static Math::Vec2 CamMousePos{};
	pos = { (ImGui::GetWindowWidth() - viewportSize.x) * 0.5f, 60.f };
	ImGui::SetCursorPos(ImVec2(pos.x, pos.y));
	if (ImGui::IsWindowHovered())
	{
		ScreenMousePos = Input::CursorPos() - Math::Vec2{ ImGui::GetWindowPos().x,ImGui::GetWindowPos().y } - pos - viewportSize / 2;
		WorldMousePos = ScreenMousePos;
		WorldMousePos.y = -WorldMousePos.y;
		WorldMousePos.x = WorldMousePos.x / viewportSize.x * *mWindowWidth;
		WorldMousePos.y = WorldMousePos.y / viewportSize.y * *mWindowHeight;
		CamMousePos = WorldMousePos * renderManager->GetWorldCamera().GetZoom() + renderManager->GetWorldCamera().GetPos();
		const Math::Vec2 moveHorizontal{ 1, 0 };
		const Math::Vec2 moveVertical{ 0, 1 };
		const float zoom{ 0.1f };
		static Math::Vec2 camOffset{};
		static Math::Vec2 camPos{};
		static Math::Vec2 offset{};
		static int isSelected = 0;
		if (abs(ScreenMousePos.x) < viewportSize.x / 2 && abs(ScreenMousePos.y) < viewportSize.y / 2)
		{
			//Camera movement
			if (Input::CheckKey(E_STATE::HOLD, E_KEY::UP))
			{
				renderManager->GetWorldCamera() += moveVertical;
			}
			if (Input::CheckKey(E_STATE::HOLD, E_KEY::DOWN))
			{
				renderManager->GetWorldCamera() -= moveVertical;
			}
			if (Input::CheckKey(E_STATE::HOLD, E_KEY::RIGHT))
			{
				renderManager->GetWorldCamera() += moveHorizontal;
			}
			if (Input::CheckKey(E_STATE::HOLD, E_KEY::LEFT))
			{
				renderManager->GetWorldCamera() -= moveHorizontal;
			}
			if (Input::CheckKey(E_STATE::PRESS, E_KEY::M_BUTTON_L) && !isSelected)
			{
				camOffset = CamMousePos;
			}
			if (Input::CheckKey(E_STATE::HOLD, E_KEY::M_BUTTON_L) && !isSelected)
			{
				camPos = -(WorldMousePos * renderManager->GetWorldCamera().GetZoom() - camOffset);
				renderManager->GetWorldCamera().SetPos(camPos);
			}
			if (Input::GetScroll() > 0.0) //scroll up   // zoon in
			{

				renderManager->GetWorldCamera() += WorldMousePos * zoom;
				renderManager->GetWorldCamera() *= -zoom;
				//renderManager->GetWorldCamera() -= -mousePos;
			}
			else if (Input::GetScroll() < 0.0)  //scroll down //zoom out
			{
				renderManager->GetWorldCamera() -= WorldMousePos * zoom;
				renderManager->GetWorldCamera() *= zoom;
				//renderManager->GetWorldCamera() += -mousePos;
			}
		}
		if (Input::CheckKey(E_STATE::NOTPRESS, E_KEY::M_BUTTON_L))
			isSelected = 0;

		//object picking
		if (Input::CheckKey(E_STATE::PRESS, E_KEY::M_BUTTON_L) && (abs(ScreenMousePos.x) < viewportSize.x / 2 && abs(ScreenMousePos.y) < viewportSize.y / 2))
		{
			int layer = 0;
			for (const Entity& e : mEntities)/////////here////////////////////////////////////////////////here
			{
				if (e.GetComponent<General>().tag == TAG::BACKGROUND)
					continue;
				if (e.HasComponent<Transform>() && e.HasComponent<Sprite>())
				{
					Math::Vec2 scale = e.GetComponent<Transform>().scale;
					Math::Vec2 translation = e.GetComponent<Transform>().translation;
					Math::Vec2 distance = CamMousePos - translation;
					if (abs(distance.x) < scale.x / 2 && abs(distance.y) < scale.y / 2)
					{
						LOG_INFO(e.GetComponent<General>().name + " Selected");
						if (e.GetComponent<Sprite>().layer >= layer)
						{
							selectedEntity = &e;
							layer = e.GetComponent<Sprite>().layer;
							offset = distance;
							isSelected = 1;
						}
					}
				}
			}
		}

		if (selectedEntity != nullptr && (*selectedEntity).GetComponent<General>().tag != TAG::BACKGROUND)// && selectedEntityID <= (int)mEntities.size())
		{
			const Entity& e = *selectedEntity;
			if (SRT == 0)
			{
				Math::Vec2 scale = e.GetComponent<Transform>().scale;
				Math::Vec2 translation = e.GetComponent<Transform>().translation;
				Math::Vec2 distance = CamMousePos - translation;
				//if (Input::CheckKey(E_STATE::HOLD, E_KEY::M_BUTTON_L) && (abs(ScreenMousePos.x) < viewportSize.x / 2 && abs(ScreenMousePos.y) < viewportSize.y / 2))
				if (Input::CheckKey(E_STATE::HOLD, E_KEY::M_BUTTON_L) && (abs(distance.x) < scale.x / 2 && abs(distance.y) < scale.y / 2))
				{
					e.GetComponent<Transform>().translation = CamMousePos - offset;
					isSelected = 1;
				}
				if (Input::CheckKey(E_STATE::HOLD, E_KEY::M_BUTTON_L) && isSelected == 1)
				{
					e.GetComponent<Transform>().translation = CamMousePos - offset;
				}
			}
			else
			{
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
					//std::cout << translate[0] << " : " << translate[1] << "\n";
				}
				else if (SRT == 3)
				{
					opp = ImGuizmo::OPERATION::TRANSLATE;
				}
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
						if (rotation)
							LOG_INFO(std::to_string(rotation));
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
	}
	GLuint frameBuffer = renderManager->GetWorldFBO();
	ImTextureID fameBufferImage = (void*)(intptr_t)frameBuffer;
	ImGui::Image(fameBufferImage, { viewportSize.x, viewportSize.y }, ImVec2(0, 1), ImVec2(1, 0));
	static const wchar_t* texpath = (const wchar_t*)"";
	static int n{ 1 };
	if (ImGui::BeginDragDropTarget())
	{
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("TEXTURES"))
		{
			LOG_INFO("Created new entity");
			Entity e{ ECS::CreateEntity() };
			mEntities.insert(e);
			e.AddComponent(
				General{ "_NEW_DragDrop" + std::to_string(n), TAG::OTHERS, SUBTAG::NOSUBTAG, true },
				Transform{ {150,150}, 0, CamMousePos },
				Sprite{ Color{0,255,0,100}, SPRITE::TEXTURE, 0 },
				RectCollider{ { 0.f, 0.f }, {1.f,1.f}, true });

			texpath = (const wchar_t*)payload->Data;
			std::string tp = (std::string)((const char*)texpath);
			spriteManager->SetTexture(e, tp);
			n++;
		}
		ImGui::EndDragDropTarget();
	}
	ImGui::End();
}
void WorldViewPanel::Free()
{

}