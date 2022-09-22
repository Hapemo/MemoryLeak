#pragma once
#include <ECS_systems.h>
#include "ECS_items.h"
#include "ECS_components.h"
class DialogManager : public System
{
public:
	DialogManager();
	~DialogManager();

private:
	std::vector<std::string> dialogs1;
	std::vector<std::string> dialogs2;
};