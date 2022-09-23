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
void updateAIAllColors(const Entity& e)
{
	static double time = 0.0;
	//time += 1.f / Application::getTargetFPS() / 10.0; //deltatime
	if (time > 2 * M_PI)
		time -= (2 * M_PI);
	float red = float((sin(time)		+ 1) / 2 );
	float green = float((sin(time * 4) + 1) / 2 );
	float blue = float((sin(time * 8) + 1) / 2 );
	glm::vec3 clr = glm::vec3(red, green, blue);
	//@weijhin
	//colorManager->SetColor(e, clr);
}

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
	glm::vec3 clr = glm::vec3(red, green, blue);
	//@weijhin
	//colorManager->SetColor(e, clr);
}

void updateAIUpDown(const Entity& e, float speed, float range)
{
	static double time = 0.0;
	//time += 1.f / Application::getTargetFPS() / 2.f;//deltatime
	static int state = 1;
	static float change = 0.0f;
	glm::vec2 incrTranslation{};
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
	//@weijhin
	//transformManager->IncrTranslate(e, incrTranslation);
}
void updateAILeftRight(const Entity& e, float speed, float range)
{
	static double time = 0.0;
	//time += 1.f / Application::getTargetFPS() / 2.f;//deltatime
	static int state = 1;
	static float change = 0.0f;
	glm::vec2 incrTranslation{};
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
	//@weijhin
	//transformManager->IncrTranslate(e, incrTranslation);
}
void updateAICircle(const Entity& e, float speed, float range)
{
	static double time = 0.0;
	//time += 1.f / Application::getTargetFPS() / 2.f;//deltatime
	glm::vec2 incrTranslation{};
	incrTranslation.x = (float)(sin(time * speed) * speed);
	incrTranslation.y = (float)(cos(time * speed) * speed);
	//@weijhin
	//transformManager->IncrTranslate(e, incrTranslation);

}
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
	//@weijhin
	//transformManager->IncrRotation(e, incrRotation);
}