/*!*****************************************************************************
\file TransformManager.cpp
\author Kew Yu Jun
\par DP email: k.yujun\@digipen.edu
\par Group: Memory Leak Studios
\date 20-09-2022
\brief
This file contains function definitions for a TransformManager system to 
manipulate its components.
*******************************************************************************/
#include "Graphics/TransformManager.h"

void TransformManager::SetScale(const Entity& e, const Math::Vec2& _scale)
{
	e.GetComponent<Transform>().scale = _scale;
}

void TransformManager::SetRotation(const Entity& e, float _rotation)
{
	e.GetComponent<Transform>().rotation = _rotation;
}

void TransformManager::SetTranslate(const Entity& e, const Math::Vec2& _translation)
{
	e.GetComponent<Transform>().translation = _translation;
}
