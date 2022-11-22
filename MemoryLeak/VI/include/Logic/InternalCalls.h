/*!*****************************************************************************
\file InternalCalls.h
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 22-11-2022
\brief
This file contains the function declarations of the class InternalCalls.
*******************************************************************************/

#pragma once
#include "Singleton.h"
#include "Input.h"
#include "vec2.h"
#include "ECS_items.h"

#define FUNC InternalCalls::GetInstance()

class InternalCalls : public Singleton<InternalCalls> {
private:

public:
	bool CheckKey(E_STATE _state, E_KEY _key);
	Math::Vec2 GetWorldMousePos();
	void ApplyImpulse(const Entity& _e, const Math::Vec2& _impulse, const Math::Vec2& _rotation);
};
