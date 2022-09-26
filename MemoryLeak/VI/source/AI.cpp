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
#define mapWidth 50
#define mapHeight 40
#define maxSizeX 5
#define maxSizeY 5
#define maxDirection 8
#define maxlocation 3
int map[mapWidth][mapHeight]{};
int initialLoactionX[maxlocation]{};
int initialLoactionY[maxlocation]{};
int sizeX[maxlocation]{};
int sizeY[maxlocation]{};
int initialDirectionX[maxlocation]{};
int initialDirectionY[maxlocation]{};
int currentWeather[maxlocation]{};
/*!*****************************************************************************
\brief
	Initialized the weather AI with initial random values

\return
None.
*******************************************************************************/
void weatherAIinit()
{
	int numWeatherLoc = 3;//(std::rand() % 3)+1;
	for (int i = 0; i < numWeatherLoc; i++)
	{
		sizeX[i] = (std::rand() % maxSizeX);
		sizeY[i] = (std::rand() % maxSizeY);
		currentWeather[i] = (std::rand() % 3) + 1;
		initialLoactionX[i] = std::rand() % mapWidth;
		initialLoactionY[i] = std::rand() % mapHeight;
		initialDirectionX[i] = (std::rand() % 3) - 1;
		initialDirectionY[i] = (std::rand() % 3) - 1;
		for (int h = initialLoactionY[i] - sizeY[i]; h <= initialLoactionY[i] + sizeY[i]; h++)
		{
			for (int w = initialLoactionX[i] - sizeX[i]; w <= initialLoactionX[i] + sizeX[i]; w++)
			{
				if(w>=0 && w< mapWidth&& h >= 0 && h < mapHeight)
					map[w][h] = currentWeather[i];
			}
		}
	}
	for (int h = 0; h < mapHeight; h++)
	{
		for (int w = 0; w < mapWidth ; w++)
		{
			std::cout<<map[w][h]<<" ";
		}
		std::cout << "\n ";
	}
	std::cout << "\n ";
	std::cout << "\n ";
}
/*!*****************************************************************************
\brief
	Update the Weatehr AI

\return
None.
*******************************************************************************/
void weatherAIupdate()
{
	
	int update = std::rand() % 100;
	if (update == 0)
	{
		for (int h = 0; h < mapHeight; h++)
		{
			for (int w = 0; w < mapWidth; w++)
			{
				map[w][h] = 0;
			}
		}
		int numWeatherLoc = 3;// std::rand() % 3;
		for (int i = 0; i < numWeatherLoc; i++)
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
					if (w >= 0 && w < mapWidth && h >= 0 && h < mapHeight)
					{
						map[w][h] = currentWeather[i];
						setted = 1;
					}
				}
			}
			if (setted == 0)
			{
				sizeX[i] = (std::rand() % maxSizeX);
				sizeY[i] = (std::rand() % maxSizeY);
				currentWeather[i] = (std::rand() % 3) + 1;
				initialLoactionX[i] = std::rand() % mapWidth;
				initialLoactionY[i] = std::rand() % mapHeight;
				initialDirectionX[i] = (std::rand() % 3) - 1;
				initialDirectionY[i] = (std::rand() % 3) - 1;
			}
		}
		for (int h = 0; h < mapHeight; h++)
		{
			for (int w = 0; w < mapWidth; w++)
			{
				std::cout << map[w][h] << " ";
			}
			std::cout << "\n ";
		}
		std::cout << "\n ";
	}
}

/*!*****************************************************************************
\brief
	AI to change colours of entities

\return
None.
*******************************************************************************/
void updateAIAllColors(const Entity& e)
{
	static double time = 0.0;
	//time += 1.f / Application::getTargetFPS() / 10.0; //deltatime
	time += FPSManager::dt;
	if (time > 2 * M_PI)
		time -= (2 * M_PI);
	GLubyte red = GLubyte((sin(time)		+ 1) / 2 *255.f);
	GLubyte green = GLubyte((sin(time * 4) + 1) / 2 * 255.f);
	GLubyte blue = GLubyte((sin(time * 8) + 1) / 2 * 255.f);
	Color clr{ red, green, blue , (GLubyte)255 };
	e.GetComponent<Sprite>().color = clr;
	//@weijhin
	//colorManager->SetColor(e, clr);
}

/*!*****************************************************************************
\brief
	AI to chnage a traffic light entity colour

\return
None.
*******************************************************************************/
void updateAITrafficLight(const Entity& e)
{
	static double time = 0.0;
	//time += 1.f / Application::getTargetFPS() /2.f;//deltatime
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

	Color clr{ (GLubyte)(red * 255), (GLubyte)(green * 255), (GLubyte)(blue*255) , (GLubyte)255};
	e.GetComponent<Sprite>().color = clr;
	//@weijhin
	//colorManager->SetColor(e, clr);
}

/*!*****************************************************************************
\brief
	AI to move an entity up and down

\return
None.
*******************************************************************************/
void updateAIUpDown(const Entity& e, float speed, float range)
{
	static double time = 0.0;
	//time += 1.f / Application::getTargetFPS() / 2.f;//deltatime
	static int state = 1;
	static float change = 0.0f;
	Math::Vec2 incrTranslation{};
	if (state)
	{
		incrTranslation.y = speed;
		change += speed;
	}
	else
	{
		incrTranslation.y = -speed;
		change -= speed;
	}
	if (change > range)
		state = 0;
	else if (change < -range)
		state = 1;
	e.GetComponent<Transform>().translation += incrTranslation;
	//@weijhin
	//transformManager->IncrTranslate(e, incrTranslation);
}

/*!*****************************************************************************
\brief
	AI to move an entity left and right

\return
None.
*******************************************************************************/
void updateAILeftRight(const Entity& e, float speed, float range)
{
	static double time = 0.0;
	//time += 1.f / Application::getTargetFPS() / 2.f;//deltatime
	static int state = 1;
	static float change = 0.0f;
	Math::Vec2 incrTranslation{};
	if (state)
	{
		incrTranslation.x = speed;
		change += speed;
	}
	else
	{
		incrTranslation.x = -speed;
		change -= speed;
	}
	if (change > range)
		state = 0;
	else if (change < -range)
		state = 1;
	e.GetComponent<Transform>().translation += incrTranslation;
	//@weijhin
	//transformManager->IncrTranslate(e, incrTranslation);
}

/*!*****************************************************************************
\brief
	AI to move an entity in circles

\return
None.
*******************************************************************************/
void updateAICircle(const Entity& e, float speed, float range)
{
	(void)range;
	static double time = 0.0;
	//time += 1.f / Application::getTargetFPS() / 2.f;//deltatime
	Math::Vec2 incrTranslation{};
	incrTranslation.x = (float)(sin(time * speed) * speed);
	incrTranslation.y = (float)(cos(time * speed) * speed);
	e.GetComponent<Transform>().translation += incrTranslation;
	//@weijhin
	//transformManager->IncrTranslate(e, incrTranslation);

}

/*!*****************************************************************************
\brief
	AI to roatate an entity

\return
None.
*******************************************************************************/
void updateAISwing(const Entity& e, float speed, float range)
{
	static double time = 0.0;
	//time += 1.f / Application::getTargetFPS() / 2.f;//deltatime
	float incrRotation{};
	static int state = 1;
	static float change = 0.0f;
	if (state)
	{
		incrRotation = (float)(speed / 100);
		change += speed;
	}
	else
	{
		incrRotation = -(float)(speed / 100);
		change -= speed;
	}
	if (change > range)
		state = 0;
	else if (change < -range)
		state = 1;
	e.GetComponent<Transform>().rotation += incrRotation;
	//@weijhin
	//transformManager->IncrRotation(e, incrRotation);
}