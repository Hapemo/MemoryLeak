#pragma once
#include "pch.h"
#include <ECS_systems.h>
#include "ECS_items.h"
#include "ECS_components.h"
#include "Helper.h"

class SheetAnimator : public System
{
public:
	SheetAnimator();
	void Animate();
	void Animate(const Entity& e);
private:

};