/*!*****************************************************************************
/*!*****************************************************************************
\file AnimationPanel.cpp
\author Huang Wei Jhin
\par DP email: h.weijhin@digipen.edu
\par Group: Memory Leak Studios
\date 20-10-2022
\brief
This file contains function definations for a Dialogue Panel Editor system that modifies
and view dialogues between a player and npc.
*******************************************************************************/
#include "AnimationPanel.h"
#include <ECSManager.h>

/*!*****************************************************************************
\brief
	Initializes the Dialogue Panel editor

\return
None.
*******************************************************************************/
void AnimationPanel::Init()
{
	
}
/*!*****************************************************************************
\brief
	Updates the Dialogue Panel editor

\return
None.
*******************************************************************************/
void AnimationPanel::Update()
{
	/*if (!active)
		return;*/
	

	ImGui::Begin("Animation Editor");
	if (selectedEntity != nullptr)
	{
		Entity e = *selectedEntity;
		if (e.HasComponent<Sprite>())
		{
			GLuint animation_texture = spriteManager->GetTexture(e);
			if (animation_texture)
			{
				ImTextureID textureImage = (void*)(intptr_t)animation_texture;
				ImGui::ImageButton(textureImage, ImVec2(100, 100), ImVec2(0, 1), ImVec2(1, 0));
			}
		}
	}
	ImGui::End();
}
/*!*****************************************************************************
\brief
	Free the Dialogue Panel editor

\return
None.
*******************************************************************************/
void AnimationPanel::Free()
{

}
