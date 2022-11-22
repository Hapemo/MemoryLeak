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
//#include "ECSManager.h"
#include "Singleton.h"

class InternalCalls : public Singleton<InternalCalls> {
private:

public:
	InternalCalls() = default;
	~InternalCalls() = default;

	/*
	bool CheckKey(E_STATE _state, E_KEY _key) { return Input::CheckKey(_state, _key); }
	Math::Vec2 GetWorldMousePos() { return editorManager->GetEditorWorldMousePos(); }

	void ApplyImpulse(const Entity& _e, const Math::Vec2& _impulse, const Math::Vec2& _rotation) {
		physics2DManager->ApplyImpulse(_e, _impulse, _rotation);
	}
	*/
};
