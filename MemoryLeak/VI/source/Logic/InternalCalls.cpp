/*!*****************************************************************************
\file InternalCalls.cpp
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 22-11-2022
\brief
This file contains the function definitions of the class InternalCalls.
*******************************************************************************/

#include "InternalCalls.h"
#include "ECSManager.h"

bool InternalCalls::CheckKey(E_STATE _state, E_KEY _key) {
	return Input::CheckKey(_state, _key);
}

Math::Vec2 InternalCalls::GetWorldMousePos() {
	return editorManager->GetEditorWorldMousePos();
}

void InternalCalls::ApplyImpulse(const Entity& _e, const Math::Vec2& _impulse, const Math::Vec2& _rotation) {
	physics2DManager->ApplyImpulse(_e, _impulse, _rotation);
}
