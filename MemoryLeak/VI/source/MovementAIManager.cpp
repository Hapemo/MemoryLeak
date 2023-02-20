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
#include "MovementAIManager.h"
#include <ECSManager.h>


void MovementAIManager::init()
{
	//for (auto& e : mEntities) {
		//addTransform(e, e.GetComponent<Transform>());
	//}
}
void MovementAIManager::update()
{
	for (auto& e : mEntities) {
		if (e.GetComponent<MovementAI>().run)
		{
			if (e.GetComponent<MovementAI>().targetTransforms.size() <=1)
				return;
			if (e.GetComponent<MovementAI>().state == 0)//initialise
			{

				if (e.GetComponent<MovementAI>().reverse)
				{
					e.GetComponent<MovementAI>().step--;
				}
				else
				{
					e.GetComponent<MovementAI>().step++;
				}
				if (e.GetComponent<MovementAI>().loop)
				{
					if (e.GetComponent<MovementAI>().step < 0)
					{
						e.GetComponent<MovementAI>().reverse = false;
						e.GetComponent<MovementAI>().step = 1;
					}
					else if (e.GetComponent<MovementAI>().step >= e.GetComponent<MovementAI>().targetTransforms.size())
					{
						e.GetComponent<MovementAI>().reverse = true;
						e.GetComponent<MovementAI>().step = (int)e.GetComponent<MovementAI>().targetTransforms.size() - 2;
					}
				}
				else
				{
					if (e.GetComponent<MovementAI>().step >= e.GetComponent<MovementAI>().targetTransforms.size())
					{
						e.GetComponent<MovementAI>().run = false;
						return;
					}
				}
				if (e.GetComponent<MovementAI>().step < 0)
				{
					e.GetComponent<MovementAI>().reverse = false;
					e.GetComponent<MovementAI>().step = 1;
				}

				e.GetComponent<MovementAI>().currtime = e.GetComponent<MovementAI>().time[e.GetComponent<MovementAI>().step];
				e.GetComponent<MovementAI>().state= 1;
			}
			else if (e.GetComponent<MovementAI>().state == 1)//move to target
			{
				Math::Vec2 scalediff = e.GetComponent<MovementAI>().targetTransforms[e.GetComponent<MovementAI>().step].scale - e.GetComponent<Transform>().scale;
				float rotationdiff = e.GetComponent<MovementAI>().targetTransforms[e.GetComponent<MovementAI>().step].rotation - e.GetComponent<Transform>().rotation;
				Math::Vec2 translationdiff = e.GetComponent<MovementAI>().targetTransforms[e.GetComponent<MovementAI>().step].translation - e.GetComponent<Transform>().translation;
				float timediff = e.GetComponent<MovementAI>().currtime / (float)FPSManager::dt;

				if (timediff >= 1.f)
				{
					scalediff /= timediff;
					rotationdiff /= timediff;
					translationdiff /= timediff;
					e.GetComponent<Transform>().scale += scalediff;
					e.GetComponent<Transform>().rotation += rotationdiff;
					e.GetComponent<Transform>().translation += translationdiff;
					e.GetComponent<MovementAI>().currtime -= (float)FPSManager::dt;
				}
				else
					e.GetComponent<MovementAI>().state = 2;
				if (e.GetComponent<MovementAI>().currtime < 0.f)
				{
					e.GetComponent<MovementAI>().state = 2;
				}
			}
			else if (e.GetComponent<MovementAI>().state == 2) //end
			{
				e.GetComponent<Transform>().scale = e.GetComponent<MovementAI>().targetTransforms[e.GetComponent<MovementAI>().step].scale;
				e.GetComponent<Transform>().rotation = e.GetComponent<MovementAI>().targetTransforms[e.GetComponent<MovementAI>().step].rotation;
				e.GetComponent<Transform>().translation = e.GetComponent<MovementAI>().targetTransforms[e.GetComponent<MovementAI>().step].translation;
				if (!e.GetComponent<MovementAI>().next)//move back to orgial if loop
				{
					e.GetComponent<MovementAI>().run = false;
				}
				e.GetComponent<MovementAI>().state = 0;
			}
		}
	}
}
void MovementAIManager::addTransform(Entity e, Transform t)
{
	e.GetComponent<MovementAI>().targetTransforms.push_back(t);
	e.GetComponent<MovementAI>().time.push_back(1.f);
}

