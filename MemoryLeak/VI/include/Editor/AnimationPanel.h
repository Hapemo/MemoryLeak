/*!*****************************************************************************
\file DialoguePanel.h
\author Huang Wei Jhin
\par DP email: h.weijhin@digipen.edu
\par Group: Memory Leak Studios
\date 20-10-2022
\brief
This file contains function declarations for a AnimationPanel Editor system that modifies
and Animation 
*******************************************************************************/
#pragma once
#include "ViewportPanel.h"

/*!*****************************************************************************
\brief
	This class encapsulates the functions for the Dialogue Panel Editor
*******************************************************************************/
class AnimationPanel : public ViewportPanel
{
public:
	
	void Init();
	void Update();
	void Free();
	
private:
	ImTextureID textureImage;
	bool isAnimationPaused;
};