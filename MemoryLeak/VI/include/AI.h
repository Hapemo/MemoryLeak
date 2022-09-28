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

#define mapWidth 50
#define mapHeight 40
#define maxSizeX 5
#define maxSizeY 5
#define maxDirection 8
#define maxlocation 3

class AIManager : public System
{
public:
	void weatherAIinit();
	void weatherAIupdate();
	void updateAI();

private:
	void updateAIAllColors(const Entity&);
	void updateAITrafficLight(const Entity&);
	void updateAIUpDown(const Entity&, float speed = 1.0f, float range = 10.0f);
	void updateAILeftRight(const Entity&, float speed = 1.0f, float range = 10.0f);
	void updateAICircle(const Entity&, float speed = 1.0f, float range = 10.0f);
	void updateAISwing(const Entity&, float speed = 1.0f, float range = 10.0f);
	int map[mapWidth][mapHeight]{};
	int initialLoactionX[maxlocation]{};
	int initialLoactionY[maxlocation]{};
	int sizeX[maxlocation]{};
	int sizeY[maxlocation]{};
	int initialDirectionX[maxlocation]{};
	int initialDirectionY[maxlocation]{};
	int currentWeather[maxlocation]{};
};
enum WeatherType {
	SUNNUY,
	FOG,
	RAIN,
	WINDY
};