/*!*****************************************************************************
/*!*****************************************************************************
\file AnimationPanel.cpp
\author Huang Wei Jhin
\par DP email: h.weijhin@digipen.edu
\par Group: Memory Leak Studios
\date 20-10-2022
\brief
This file contains function definations for a AnimationPanel Editor system that modifies
and Animation 
*******************************************************************************/
#include "AnimationPanel.h"
#include <ECSManager.h>

/*!*****************************************************************************
\brief
	Initializes the Animation Panel editor

\return
None.
*******************************************************************************/
void AnimationPanel::Init()
{
	viewportSize = { 0,0 };
	isAnimationPaused = false;
}
/*!*****************************************************************************
\brief
	Updates the Animation Panel editor

\return
None.
*******************************************************************************/
void AnimationPanel::Update()
{
	/*if (!active)
		return;*/
	ImGui::Begin("Animation Editor");
	SetViewportAspectRatio();
	Math::Vec2 pos = { (ImGui::GetWindowWidth() / 2.f) - 110.f, 30.f };
	ImGui::SetCursorPos(ImVec2(pos.x, pos.y));
	if (ImGui::Button("Play", buttonSize))
	{
		isAnimationPaused = false;
	}
	ImGui::SameLine(0.f, 20.f);
	if (ImGui::Button("Pause", buttonSize))
	{
		isAnimationPaused = true;
	}
	if (ImGui::IsWindowFocused())
		isAnimatorEditor = true;
	else
	{
		isAnimatorEditor = false;
	}
	if (selectedEntity != nullptr)
	{
		Entity e = *selectedEntity;
		if (e.HasComponent<Sprite>())
		{
			float size = ImGui::GetWindowSize().y / 3.f;
			static int frame = 1;
			float ratio = e.GetComponent<Transform>().scale.x / e.GetComponent<Transform>().scale.x;
			ImVec2 imageSize = { size * ratio * frame,size * ratio };
			GLuint animation_texture = spriteManager->GetTexture(e);
			ImVec2 viewSize = { size * 16.f / 9.f,size  };
			if (animation_texture)
			{
				textureImage = (void*)(intptr_t)animation_texture;
				ImGui::Image(textureImage, imageSize, ImVec2(0, 1), ImVec2(1, 0));
				if (ImGui::BeginDragDropTarget())
				{
					static const wchar_t* texpath = (const wchar_t*)"";
					if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("TEXTURES"))
					{
						texpath = (const wchar_t*)payload->Data;
						std::string tp = (std::string)((const char*)texpath);
						e.GetComponent<Sprite>().sprite = SPRITE::TEXTURE;
						spriteManager->SetTexture(e, tp);
					}
					ImGui::EndDragDropTarget();
				}

			}
			if (e.HasComponent<SheetAnimation>())
			{
				
				//GLuint animated_texture = spriteManager->GetTexture(e);////// YU JUN get moving animated amimation
				//textureImage = (void*)(intptr_t)animated_texture;
				//ImGui::ImageButton(textureImage, ImVec2(200, 200), ImVec2(0, 1), ImVec2(1, 0));
				// 
				//Temp untill graphics return fame buffer for single animation entity
				frame = e.GetComponent<SheetAnimation>().frameCount;
				renderManager->GetAnimatorCamera().SetZoom(e.GetComponent<Transform>().scale.y / *mWindowHeight);
				renderManager->GetAnimatorCamera().SetPos(e.GetComponent<Transform>().translation);
				textureImage = (void*)(intptr_t)renderManager->GetAnimatorFBO();
				ImGui::Image(textureImage, viewSize, ImVec2(0, 1), ImVec2(1, 0));
				if (ImGui::BeginDragDropTarget())
				{
					ImGui::EndDragDropTarget();
				}
				if (!isAnimationPaused)
				{
					if (ImGui::IsWindowFocused())
						sheetAnimator->Animate();
				}
			}
			else
			{
				if (ImGui::Button("Add Animation Component", viewSize))
				{
					e.AddComponent<SheetAnimation>({});
				}
			}
		}
	}
	ImGui::End();
}
/*!*****************************************************************************
\brief
	Free the Animation Panel editor

\return
None.
*******************************************************************************/
void AnimationPanel::Free()
{

}

