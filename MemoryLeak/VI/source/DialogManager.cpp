#include "DialogManager.h"

DialogManager::DialogManager()
{
	LOG_CUSTOM_CREATE("DIALOG");
}
void DialogManager::LoadDialog(Dialog _dialog) {
	mDialogs.push_back(_dialog);
}
void DialogManager::PrintDialogs() {
	for (Dialog dialog : mDialogs) {
		LOG_CUSTOM("DIALOG", dialog.text.c_str());
	}
}
DialogManager::~DialogManager()
{
}