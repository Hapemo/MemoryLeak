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
	~DialogManager();

	void LoadDialog(Dialog _dialog);
	void PrintDialogs();

	std::vector<Dialog> GetDialogs() { return mDialogs; }

	bool IsChoice(int _id);
	std::pair<int, int> GetChoices(int _id);

	int GetSpeaker(int _id);
	std::string GetDialogue(int _id);
	int GetNext(int _id);
	
	void CreateNewDialogue(int _id, std::string _text, int _speaker, int _next, int _next2 = -1);

private:
	std::vector<Dialog> mDialogs;
};