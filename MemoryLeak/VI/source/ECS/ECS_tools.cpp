/*!*****************************************************************************
\file ECS_tools.cpp
\author Jazz Teoh Yu Jue
\par DP email: j.teoh\@digipen.edu
\par Group: Memory Leak Studios
\date 24-09-2022
\brief
This file contains easier implementation of using the Coordinate in ECS.
The functions here calls the exact function in ECS using singleton Coordinate.
*******************************************************************************/
#include "ECS_tools.h"

Entity ECS::CreateEntity() { 
	return Entity{ Coordinator::GetInstance()->CreateEntity() };
}

void ECS::DestroyEntity(EntityID _entity) { Coordinator::GetInstance()->DestroyEntity(_entity); }

void ECS::DestroyAllEntities() { Coordinator::GetInstance()->DestroyAllEntities(); }

void ECS::DestroySomeEntites(const std::vector<EntityID>& _dontDestroy) { Coordinator::GetInstance()->DestroySomeEntites(_dontDestroy); }
