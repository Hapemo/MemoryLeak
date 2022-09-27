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
//#include <Application.h>
#include "Graphics/TransformManager.h"
#include <glm/glm.hpp>
#define _USE_MATH_DEFINES
#include <math.h>

void updateAIAllColors(const Entity&);
void updateAITrafficLight(const Entity&);

void updateAIUpDown(const Entity&, float speed =1.0f, float range = 10.0f );
void updateAILeftRight(const Entity&, float speed = 1.0f, float range = 10.0f);
void updateAICircle(const Entity&, float speed = 1.0f, float range = 10.0f);
void updateAISwing(const Entity&, float speed = 1.0f, float range = 10.0f);
void weatherAIinit();
void weatherAIupdate();

enum WeatherType {
	SUNNUY,
	FOG,
	RAIN,
	WINDY
};