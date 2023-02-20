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


void MovementAIManager::update()
{
	for (auto& e : mEntities) {
		if (e.GetComponent<MovementAI>().run)
		{
			if (e.GetComponent<MovementAI>().state == 0)//initialise
			{
				e.GetComponent<MovementAI>().currtime = e.GetComponent<MovementAI>().time;
				e.GetComponent<MovementAI>().targetTransform2 = e.GetComponent<Transform>();
				e.GetComponent<MovementAI>().state= 1;
			}
			else if (e.GetComponent<MovementAI>().state == 1)//move to target
			{
				Math::Vec2 scalediff = e.GetComponent<MovementAI>().targetTransform.scale - e.GetComponent<Transform>().scale;
				float rotationdiff = e.GetComponent<MovementAI>().targetTransform.rotation - e.GetComponent<Transform>().rotation;
				Math::Vec2 translationdiff = e.GetComponent<MovementAI>().targetTransform.translation - e.GetComponent<Transform>().translation;
				float timediff = e.GetComponent<MovementAI>().currtime / (float)FPSManager::dt;
				std::cout << "\ntimediff : " << timediff;
				std::cout << "\nscalediff : " << scalediff.x<<"\n";

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
				e.GetComponent<Transform>().scale = e.GetComponent<MovementAI>().targetTransform.scale;
				std::cout << "\n tgt scale : " << e.GetComponent<MovementAI>().targetTransform.scale.x << "\n";
				e.GetComponent<Transform>().rotation = e.GetComponent<MovementAI>().targetTransform.rotation;
				e.GetComponent<Transform>().translation = e.GetComponent<MovementAI>().targetTransform.translation;
				if (e.GetComponent<MovementAI>().loop)//move back to orgial if loop
				{
					e.GetComponent<MovementAI>().targetTransform = e.GetComponent<MovementAI>().targetTransform2;
				}
				else//end
				{
					e.GetComponent<MovementAI>().run = false;
				}
				e.GetComponent<MovementAI>().state = 0;
			}
		}
	}
}

