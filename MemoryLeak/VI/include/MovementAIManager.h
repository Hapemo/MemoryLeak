/*!*****************************************************************************
\file AI.h
\author Huang Wei Jhin
\par DP email: h.weijhin@digipen.edu
\par Group: Memory Leak Studios
\date 20-09-2022
\brief
This file contains function definations for a AI system that modifies
Entities and its Components.
*******************************************************************************/
#pragma once
#include <ECS_systems.h>
#include "ECS_items.h"
#include "ECS_components.h"

#define _USE_MATH_DEFINES
#include <math.h>
/*!*****************************************************************************
DEFINES
*******************************************************************************/

/*!*****************************************************************************
\brief
	This class encapsulates the functions for AI manager
*******************************************************************************/
class MovementAIManager : public System
{
public:
	void update();
	

private:
	

};
