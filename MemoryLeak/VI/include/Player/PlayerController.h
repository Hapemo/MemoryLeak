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

// -----------------------------
// Player Controller
// -----------------------------
class PlayerController : public System {
public:
	// -----------------------------
	// Controller functions
	// -----------------------------
		/*!*****************************************************************************
		\brief
		Update function that checks for keyboard input to modify physics components values
		to move player entities
		\param const double &
		A reference to a read-only variable that tells us the application's current
		delta time
		\return void
		NULL
		*******************************************************************************/
	void Update(double _dt);
private:
};