#pragma once
#include <ECS_systems.h>
#include "ECS_items.h"
#include "ECS_components.h"

struct Dialog {
	int id = -1;
	std::string text = "";
	int speaker = -1;
	int next = -1;
	int next2 = -1;
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