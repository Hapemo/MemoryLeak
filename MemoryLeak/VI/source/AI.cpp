/*!*****************************************************************************
\file AI.cpp
\author Huang Wei Jhin
\par DP email: h.weijhin@digipen.edu
\par Group: Memory Leak Studios
\date 20-09-2022
\brief
This file contains function definations for a AI system that modifies
Entities and its Components.
*******************************************************************************/
#include "AI.h"
#include <ECSManager.h>


/*!*****************************************************************************
\brief
	Initialize the weather AI with initial random values

\return
None.
*******************************************************************************/
void AIManager::weatherAIinit(float width, float height)
{
	mapMaxHeight = (int)(height/100);
	mapMaxWidth = (int)(width/100);
	/*for (int h = 0; h < weatherMap.size(); h++)
	{
		weatherMap[h].clear();
	}
	weatherMap.clear();*/
	weatherMap.resize(mapMaxWidth);
	for (int w = 0; w < mapMaxWidth; w++)
	{
		weatherMap[w].resize(mapMaxHeight);
	}
	for (int w = 0; w < mapMaxWidth; w++)
	{
		for (int h = 0; h < mapMaxHeight; h++)
		{
			weatherMap[w][h] = SUNNUY; //reset map
		}
	}
	//int numWeatherLoc = 3;//(std::rand() % 3)+1;
	for (int i = 0; i < weatherMaxLocation; i++)
	{
		sizeX[i] = (std::rand() % weatherMaxHeight);
		sizeY[i] = (std::rand() % weatherMaxWidth);
		currentWeather[i] = (std::rand() % 3) + 1;
		currentWeather[i] = (currentWeather[i] == 3 ? FOG : currentWeather[i]);
		initialLoactionY[i] = std::rand() % mapMaxHeight;
		initialLoactionX[i] = std::rand() % mapMaxWidth;
		initialDirectionX[i] = (std::rand() % 3) - 1;
		initialDirectionY[i] = (std::rand() % 3) - 1;
		for (int h = initialLoactionY[i] - sizeY[i]; h <= initialLoactionY[i] + sizeY[i]; h++)
		{
			for (int w = initialLoactionX[i] - sizeX[i]; w <= initialLoactionX[i] + sizeX[i]; w++)
			{
				if(w>=0 && w< mapMaxWidth && h >= 0 && h < mapMaxHeight)
					weatherMap[w][h] |= currentWeather[i];
			}
		}
	}
	
}
/*!*****************************************************************************
\brief
	Update the Weatehr AI

\return
None.
*******************************************************************************/
void AIManager::weatherAIupdate()
{
	if (mapMaxWidth == 0)
		return;
	if (mapMaxHeight == 0)
		return;
	int update = std::rand() % 20;
	if (update == 0)
	{
		for (int w = 0; w < mapMaxWidth; w++)
		{
			for (int h = 0; h < mapMaxHeight; h++)
			{
				weatherMap[w][h] = SUNNUY; //reset map
			}
		}
		//int numWeatherLoc = 3;// std::rand() % 3;
		for (int i = 0; i < weatherMaxLocation; i++)
		{
			//vary direction
			int directionX = (std::rand() % 3) - 1;
			int directionY = (std::rand() % 3) - 1;
			initialLoactionX[i] += directionX+initialDirectionX[i];
			initialLoactionY[i] += directionY+initialDirectionY[i];
			//very size
			if(sizeX[i] > 1)
				sizeX[i] += (std::rand() % 3) - 1;
			else
				sizeX[i] += (std::rand() % 3);
			if (sizeY[i] > 1)
				sizeY[i] += (std::rand() % 3) - 1;
			else
				sizeY[i] += (std::rand() % 3);
			int setted = 0;
			for (int h = initialLoactionY[i] - sizeY[i]; h <= initialLoactionY[i] + sizeY[i]; h++)
			{
				for (int w = initialLoactionX[i] - sizeX[i]; w <= initialLoactionX[i] + sizeX[i]; w++)
				{
					if (w >= 0 && w < mapMaxWidth && h >= 0 && h < mapMaxHeight)
					{
						weatherMap[w][h] |= currentWeather[i];
						setted = 1;
					}
				}
			}
			if (setted == 0)
			{
				//new weather location
				sizeX[i] = (std::rand() % weatherMaxWidth);
				sizeY[i] = (std::rand() % weatherMaxHeight);
				currentWeather[i] = (std::rand() % 3) + 1;
				currentWeather[i] = (currentWeather[i] == 3 ? FOG : currentWeather[i]);
				initialLoactionX[i] = std::rand() % mapMaxWidth;
				initialLoactionY[i] = std::rand() % mapMaxHeight;
				initialDirectionX[i] = (std::rand() % 3) - 1;
				initialDirectionY[i] = (std::rand() % 3) - 1;
			}
		}

		
	}
}
int AIManager::GetCurrentWeather(int index, float posX, float posY)
{
	int indexX = (int)((posX+mapMaxWidth*50)/100);
	int indexY = (int)(-(posY - mapMaxHeight*50)/100);
	indexX += (index % 5) - 2;
	indexY += (index / 5) - 2;
	return weatherMap[indexX][indexY];
}


/*!*****************************************************************************
\brief
	Update all the AI

\return
None.
*******************************************************************************/
void AIManager::updateAI()
{
	weatherAIupdate();
	for (auto& e : mEntities) {
		if (e.GetComponent<AI>().colorChange == 1)
			updateAIAllColors(e);
		else if (e.GetComponent<AI>().colorChange == 2)
			updateAITrafficLight(e);
		if (e.GetComponent<AI>().movement == 1)
			updateAIUpDown(e, e.GetComponent<AI>().speed, e.GetComponent<AI>().range);
		else if (e.GetComponent<AI>().movement == 2)
			updateAILeftRight(e, e.GetComponent<AI>().speed, e.GetComponent<AI>().range);
		else if (e.GetComponent<AI>().movement == 3)
			updateAISwing(e, e.GetComponent<AI>().speed, e.GetComponent<AI>().range);
		else if (e.GetComponent<AI>().movement == 4)
			updateAICircle(e, e.GetComponent<AI>().speed, e.GetComponent<AI>().range);
	}
}
/*!*****************************************************************************
\brief
	AI to change colours of entities
\param e
	entity to change
\return
None.
*******************************************************************************/
void AIManager::updateAIAllColors(const Entity& e)
{
	static double time = 0.0;
	time += FPSManager::dt/10.f;
	if (time > 2 * M_PI)
		time -= (2 * M_PI);
	GLubyte red = GLubyte((sin(time)		+ 1) / 2 *255.f);
	GLubyte green = GLubyte((sin(time * 4) + 1) / 2 * 255.f);
	GLubyte blue = GLubyte((sin(time * 8) + 1) / 2 * 255.f);
	Color clr{ red, green, blue , e.GetComponent<Sprite>().color.a };
	e.GetComponent<Sprite>().color = clr;
	//@weijhin
	//colorManager->SetColor(e, clr);
}

/*!*****************************************************************************
\brief
	AI to chnage a traffic light entity colour
\param e
	entity to change
\return
None.
*******************************************************************************/
void AIManager::updateAITrafficLight(const Entity& e)
{
	static double time = 0.0;
	time += FPSManager::dt;
	float red = 0.0f;
	float green = 0.0f;
	float blue = 0.0f;
	int state = (int)time % 10;
	if (state < 4)
	{
		green = 1.0f;
	}
	else if (state == 4)// && state < 4)
	{
		if ((int)(time * 10) % 2)
		{
			red = 1.0f;
			green = 0.6f;
		}
		else
		{
			red = 1.0f;
			green = 0.7f;
		}
	}
	else //if ((int)time % 3 > 4)
	{
		red = 1.0f;
	}

	Color clr{ (GLubyte)(red * 255), (GLubyte)(green * 255), (GLubyte)(blue*255) , e.GetComponent<Sprite>().color.a };
	e.GetComponent<Sprite>().color = clr;
}

/*!*****************************************************************************
\brief
	AI to move an entity up and down
\param e
	entity to change
\param speed
	speed to move
\param range
	range of movement
\return
None.
*******************************************************************************/
void AIManager::updateAIUpDown(const Entity& e, float speed, float range)
{
	float time = (float)FPSManager::dt*60.f;
	static int state = 1;
	static float change = 0.0f;
	Math::Vec2 incrTranslation{};
	if (state)
	{
		incrTranslation.y = speed* time;
		change += speed * time;
	}
	else
	{
		incrTranslation.y = -speed * time;
		change -= speed * time;
	}
	if (change > range)
		state = 0;
	else if (change < -range)
		state = 1;
	e.GetComponent<Transform>().translation += incrTranslation;
}

/*!*****************************************************************************
\brief
	AI to move an entity left and right
\param e
	entity to change
\param speed
	speed to move
\param range
	range of movement
\return
None.
*******************************************************************************/
void AIManager::updateAILeftRight(const Entity& e, float speed, float range)
{
	float time = (float)FPSManager::dt * 60.f;
	static int state = 1;
	static float change = 0.0f;
	Math::Vec2 incrTranslation{};
	if (state)
	{
		incrTranslation.x = speed * time;
		change += speed * time;
	}
	else
	{
		incrTranslation.x = -speed * time;
		change -= speed * time;
	}
	if (change > range)
		state = 0;
	else if (change < -range)
		state = 1;
	e.GetComponent<Transform>().translation += incrTranslation;
}

/*!*****************************************************************************
\brief
	AI to move an entity in circles
\param e
	entity to change
\param speed
	speed to move
\param range
	range of movement
\return
None.
*******************************************************************************/
void AIManager::updateAICircle(const Entity& e, float speed, float range)
{
	(void)range; //WIP
	static double time = 0.0;
	time += FPSManager::dt;
	Math::Vec2 incrTranslation{};
	incrTranslation.x = (float)(sin(time * speed) );
	incrTranslation.y = (float)(cos(time * speed) );
	e.GetComponent<Transform>().translation += incrTranslation;

}

/*!*****************************************************************************
\brief
	AI to roatate an entity
\param e
	entity to change
\param speed
	speed to move
\param range
	range of movement
\return
None.
*******************************************************************************/
void AIManager::updateAISwing(const Entity& e, float speed, float range)
{
	float time = (float)FPSManager::dt * 60.f;
	float incrRotation{};
	static int state = 1;
	static float change = 0.0f;
	if (state)
	{
		incrRotation = (float)(speed * time / 100);
		change += speed * time;
	}
	else
	{
		incrRotation = -(float)(speed * time / 100);
		change -= speed * time;
	}
	if (change > range)
		state = 0;
	else if (change < -range)
		state = 1;
	e.GetComponent<Transform>().rotation += incrRotation;
}