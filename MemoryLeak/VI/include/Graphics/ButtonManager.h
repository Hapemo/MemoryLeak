#pragma once
#include "pch.h"
#include <ECS_systems.h>
#include "ECS_items.h"
#include "ECS_components.h"

class ButtonManager : public System
{
public:
	ButtonManager() : mWindowWidth(nullptr), mWindowHeight(nullptr) {};
	void Init(int* _windowWidth, int* _windowheight);
	void Update();
private:
	bool CheckHover(const Entity& _e);
	bool CheckClick(const Entity& _e);
	bool CheckActivate(const Entity& _e);
	int* mWindowWidth, *mWindowHeight;
};