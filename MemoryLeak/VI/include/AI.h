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
//#define mapWidth 40
//#define mapHeight 50
//#define maxSizeX 5
//#define maxSizeY 5
//#define maxDirection 8
#define maxlocation 3
/*!*****************************************************************************
\brief
	This class encapsulates the functions for AI manager
*******************************************************************************/
class AIManager : public System
{
public:
	void weatherAIinit();
	void weatherAIupdate();
	void updateAI();

	//int weatherMap[mapWidth][mapHeight]{}; //to be shifted to provate after implementing proxy class for [] [] operator
	std::vector<std::vector<int>> getWeatherMap() { return weatherMap; }
	std::vector<std::vector<int>> weatherMap{};
private:
	void updateAIAllColors(const Entity&);
	void updateAITrafficLight(const Entity&);
	void updateAIUpDown(const Entity&, float speed = 1.0f, float range = 10.0f);
	void updateAILeftRight(const Entity&, float speed = 1.0f, float range = 10.0f);
	void updateAICircle(const Entity&, float speed = 1.0f, float range = 10.0f);
	void updateAISwing(const Entity&, float speed = 1.0f, float range = 10.0f);

	int mapMaxHeight= 50;
	int mapMaxWidth= 40;
	int weatherMaxHeight = 10;
	int weatherMaxWidth = 10;
	int weatherMaxLocation = 3;

	int initialLoactionX[maxlocation]{};
	int initialLoactionY[maxlocation]{};
	int sizeX[maxlocation]{};
	int sizeY[maxlocation]{};
	int initialDirectionX[maxlocation]{};
	int initialDirectionY[maxlocation]{};
	int currentWeather[maxlocation]{};
};
enum WeatherType {
	SUNNUY=0,
	RAIN=1,
	WINDY=2,
	FOG=4,
	ALL = 7
};