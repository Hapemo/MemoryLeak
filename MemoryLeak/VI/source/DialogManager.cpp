#include "DialogManager.h"

DialogManager::DialogManager()
{
	LOG_CUSTOM_CREATE("DIALOG");
}

DialogManager::~DialogManager()
{
}

void DialogManager::LoadDialog(Dialog _dialog) {
	mDialogs.push_back(_dialog);
}

void DialogManager::PrintDialogs() {
	for (Dialog dialog : mDialogs) {
		LOG_CUSTOM("DIALOG", dialog.text.c_str());
	}
}

bool DialogManager::IsChoice(int _id) {
	for (Dialog dialog : mDialogs)
		if (dialog.next2 != -1) return true;
	return false;
}

int DialogManager::GetSpeaker(int _id) {
	for (Dialog dialog : mDialogs)
		if (dialog.id == _id) return dialog.speaker;
	LOG_ERROR("Dialogue ID doesn't exist!");
	return -1;
}

std::string DialogManager::GetDialogue(int _id) {
	for (Dialog dialog : mDialogs)
		if (dialog.id == _id) return dialog.text;
	LOG_ERROR("Dialogue ID doesn't exist!");
	return "";
}

int DialogManager::GetNext(int _id) {
	for (Dialog dialog : mDialogs)
		if (dialog.id == _id) return dialog.next;
	LOG_ERROR("Dialogue ID doesn't exist!");
	return -1;
}

std::pair<int, int> DialogManager::GetChoices(int _id) {
	std::pair<int, int> choices;
	for (Dialog dialog : mDialogs) {
		if (dialog.id == _id) {
			if (dialog.next2 == -1) {
				LOG_ERROR("Dialogue doesn't have choices!");
				return choices;
			}
			else {
				choices.first = dialog.next;
				choices.second = dialog.next2;
				break;
			}
		}
	}
	return choices;
}

void DialogManager::CreateNewDialogue(int _id, std::string _text, int _speaker, int _next, int _next2) {
	for (Dialog dialog : mDialogs) {
		if (dialog.id == _id) {
			LOG_ERROR("Dialogue ID already exist!");
			return;
		}
	}
	Dialog newDialog;
	newDialog.id = _id;
	newDialog.text = _text;
	newDialog.speaker = _speaker;
	newDialog.next = _next;
	newDialog.next2 = _next2;
	mDialogs.push_back(newDialog);
}
