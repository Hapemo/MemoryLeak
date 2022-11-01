/*!*****************************************************************************
/*!*****************************************************************************
\file WorldViewPanel.cpp
\author Huang Wei Jhin
\par DP email: h.weijhin@digipen.edu
\par Group: Memory Leak Studios
\date 20-10-2022
\brief
This file contains function definations for a WorldView Panel Editor system that displays the world scene
*******************************************************************************/
#include "WorldViewPanel.h"
#include <ECSManager.h>
int WorldViewPanel::newEntityCount =1;
/*!*****************************************************************************
\brief
	Initializes the WorldViewPanel editor

\return
None.
*******************************************************************************/
void WorldViewPanel::Init()
{
	viewportSize={ 0,0 };
	//camera = renderManager->GetWorldCamera();
}
/*!*****************************************************************************
\brief
	Updates the WorldViewPanel Panel editor

\return
None.
*******************************************************************************/
void WorldViewPanel::Update()
{
	ImGui::Begin("World View");
	
	//Calcualting the view port aspect ratio 
	SetViewportAspectRatio();
	
	Math::Vec2 pos = { (ImGui::GetWindowWidth() / 2.f) - 110.f, 30.f };
	ImGui::SetCursorPos(ImVec2(pos.x, pos.y));
	//if (ImGui::Button("Reset", buttonSize))
		//serializationManager->LoadScene("SceneTmp");
	//ImGui::SameLine(0.f,20.f);
	if (ImGui::Button("Play", buttonSize))
	{
		isScenePaused = false;
	}
	ImGui::SameLine(0.f, 20.f);
	if (ImGui::Button("Pause", buttonSize))
	{
		isScenePaused = true;
	}
	CalculateMousePos(E_CAMERA_TYPE::WORLD);
	fameBufferImage = (void*)(intptr_t)renderManager->GetWorldFBO();
	ImGui::SetCursorPos(ImVec2(viewportPos.x, viewportPos.y));
	ImGui::Image(fameBufferImage, { viewportSize.x, viewportSize.y }, ImVec2(0, 1), ImVec2(1, 0));
	if (ImGui::BeginDragDropTarget())
	{
		NewEntity();
		ImGui::EndDragDropTarget();
	}

	if (ImGui::IsWindowHovered())
	{
		if (IsMouseInScreen())
		{
			//Camera movement
			ArrowKeyMoveCam();
			MouseClickMoveCam();
			ScrollMoveCam();
			
		}
		if (Input::CheckKey(E_STATE::NOTPRESS, E_KEY::M_BUTTON_L))
			isSelected = 0;

		//object picking
		if (Input::CheckKey(E_STATE::PRESS, E_KEY::M_BUTTON_L) && IsMouseInScreen())
		{
			SetSelectedEntity();
		}
	
		if (selectedEntity != nullptr && (*selectedEntity).GetComponent<General>().tag != TAG::BACKGROUND)
		{
			e = *selectedEntity;
			if (SRT == 0)
			{
				MoveSelectedEntity();
			}
			else
			{
				UseGuizmo();
			}
		}
	}
	
	ImGui::End();
}
/*!*****************************************************************************
\brief
	Free the WorldViewPanel editor

\return
None.
*******************************************************************************/
void WorldViewPanel::Free()
{

}
void WorldViewPanel::ArrowKeyMoveCam()
{
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
}
void WorldViewPanel::MouseClickMoveCam()
{
	if (SRT == 0)
	{
		if (Input::CheckKey(E_STATE::PRESS, E_KEY::M_BUTTON_L) && !isSelected)
		{
			camOffset = camMousePos;
		}
		if (Input::CheckKey(E_STATE::HOLD, E_KEY::M_BUTTON_L) && !isSelected)
		{
			camPos = -(worldMousePos * renderManager->GetWorldCamera().GetZoom() - camOffset);
			renderManager->GetWorldCamera().SetPos(camPos);
		}
	}
}
void WorldViewPanel::ScrollMoveCam()
{
	if (Input::GetScroll() > 0.0) //scroll up   // zoon in
	{

		renderManager->GetWorldCamera() += worldMousePos * moveZoom;
		renderManager->GetWorldCamera() *= -moveZoom;
		//renderManager->GetWorldCamera() -= -mousePos;
	}
	else if (Input::GetScroll() < 0.0)  //scroll down //zoom out
	{
		renderManager->GetWorldCamera() -= worldMousePos * moveZoom;
		renderManager->GetWorldCamera() *= moveZoom;
		//renderManager->GetWorldCamera() += -mousePos;
	}
}
void WorldViewPanel::NewEntity()
{
	static const wchar_t* texpath = (const wchar_t*)"";
	if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("TEXTURES"))
	{
		LOG_INFO("Created new entity");
		Entity ne{ ECS::CreateEntity() };
		(*myEntities).insert(ne);
		ne.AddComponent(
			General{ "_NEW_DragDrop" + std::to_string(newEntityCount), TAG::OTHERS, SUBTAG::NOSUBTAG, true },
			Transform{ {150,150}, 0, camMousePos },
			Sprite{ Color{0,255,0,100}, SPRITE::TEXTURE, 0, highestLayer},
			RectCollider{ { 0.f, 0.f }, {1.f,1.f}, true });

		texpath = (const wchar_t*)payload->Data;
		std::string tp = (std::string)((const char*)texpath);
		spriteManager->SetTexture(ne, tp);
		newEntityCount++;
	}
}
void WorldViewPanel::SetSelectedEntity()
{
	int layer = 0;
	for (const Entity& e : *myEntities)
	{
		if (e.GetComponent<General>().tag == TAG::BACKGROUND)
			continue;
		if (e.HasComponent<Transform>() && e.HasComponent<Sprite>()) //||e.HasComponent<Text>()
		{
			Math::Vec2 scale = e.GetComponent<Transform>().scale;
			Math::Vec2 translation = e.GetComponent<Transform>().translation;
			Math::Vec2 distance = camMousePos - translation;
			if (abs(distance.x) < scale.x / 2 && abs(distance.y) < scale.y / 2)
			{
				LOG_INFO(e.GetComponent<General>().name + " Selected");
				if (e.GetComponent<Sprite>().layer >= layer)
				{
					selectedEntity = &e;
					layer = e.GetComponent<Sprite>().layer;
					objectOffset = distance;
					isSelected = 1;
				}
			}
		}
	}
}
void WorldViewPanel::MoveSelectedEntity()
{
	Math::Vec2 scale = e.GetComponent<Transform>().scale;
	Math::Vec2 translation = e.GetComponent<Transform>().translation;
	Math::Vec2 distance = camMousePos - translation;
	if (Input::CheckKey(E_STATE::HOLD, E_KEY::M_BUTTON_L) && (abs(distance.x) < scale.x / 2 && abs(distance.y) < scale.y / 2))
	{
		e.GetComponent<Transform>().translation = camMousePos - objectOffset;
		isSelected = 1;
	}
	if (Input::CheckKey(E_STATE::HOLD, E_KEY::M_BUTTON_L) && isSelected == 1)
	{
		e.GetComponent<Transform>().translation = camMousePos - objectOffset;
	}
}
void WorldViewPanel::UseGuizmo()
{
	
	ImGuizmo::SetOrthographic(true);
	ImGuizmo::SetDrawlist();
	ImGuizmo::SetRect(ImGui::GetWindowPos().x + viewportPos.x, ImGui::GetWindowPos().y + viewportPos.y,
		viewportSize.x, viewportSize.y);
	const float identity[16] = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };
	std::vector<float> trf = renderManager->GetImGuizmoMat4(e);
	float translate[16] = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };
	for (int i = 0; i < 16; ++i)
	{
		translate[i] = trf[i];
	}

	std::vector<float> cam = renderManager->GetWorldCamera().GetImGuizmoWorldToCam();
	float camera[16] = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };
	for (int i = 0; i < 16; ++i)
	{
		camera[i] = cam[i];
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
	ImGuizmo::Manipulate(&camera[0], &identity[0], opp, ImGuizmo::LOCAL, &translate[0]);
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
			e.GetComponent<Transform>().rotation = rotation;
		}
		else if (SRT == 3)
		{
			Math::Vec2 translation = { translate[12] * (float)(*mWindowWidth / 2), translate[13] * (float)(*mWindowHeight / 2) };
			e.GetComponent<Transform>().translation = translation;
		}
	}
}
