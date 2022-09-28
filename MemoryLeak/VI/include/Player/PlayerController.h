/*!*****************************************************************************
\file	PlayerController.h
\author Lee Hsien Wei, Joachim
\par	DP email: l.hsienweijoachim@digipen.edu
\par	Course: GAM200
\par	Group: Memory Leak Studios
\date	27-09-2022
\brief  This file contains the declaration of the Player Controller and its
		member functions which handles movement inpupt control of the player
*******************************************************************************/
#pragma once

// -----------------------------
// Include files
// -----------------------------
#include "ECSManager.h"

/*!*****************************************************************************
\brief PlayerController system class that handles movement input to move the
	   position of the player entities
*******************************************************************************/
class PlayerController : public System {
public:
// -----------------------------
// Controller functions
// -----------------------------
	/*!*****************************************************************************
	\brief
	Update function that checks for keyboard input to modify physics components values
	to move player entities

	\param void
	NULL

	\return void
	NULL
	*******************************************************************************/
	void Update();
private:
};