#pragma once
#include <ECS_systems.h>
#include "ECS_items.h"
#include "ECS_components.h"

struct Dialog {
	int id;
	std::string text;
	int speaker;
	int next;
	int next2;
};

class DialogManager : public System
{
public:
	DialogManager();
	void LoadDialog(Dialog _dialog);
	void PrintDialogs();
	~DialogManager();

private:
	std::vector<Dialog> mDialogs;
};