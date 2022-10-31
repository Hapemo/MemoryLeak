/*!*****************************************************************************
\file DialoguePanel.h
\author Huang Wei Jhin
\par DP email: h.weijhin@digipen.edu
\par Group: Memory Leak Studios
\date 20-10-2022
\brief
This file contains function declarations for a Dialogue Panel Editor system that modifies
and view dialogues between a player and npc.
*******************************************************************************/
#pragma once
#include "Panel.h"

/*!*****************************************************************************
\brief
	This class encapsulates the functions for the Dialogue Panel Editor
*******************************************************************************/
class AnimationPanel : public Panel
{
public:
	
	void Init();
	void Update();
	void Free();

	
private:
	
};