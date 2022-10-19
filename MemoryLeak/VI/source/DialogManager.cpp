/*!*****************************************************************************
\file DialogManager.cpp
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 26-09-2022
\brief
This file contains the function definitions of the class DialogManager.
The DialogManager manages the scripts and dialogues data.
*******************************************************************************/

#include "DialogManager.h"

/*!*****************************************************************************
\brief
Constructor of the DialogManager.
*******************************************************************************/
DialogManager::DialogManager()
{
	LOG_CUSTOM_CREATE("DIALOG");
}

/*!*****************************************************************************
\brief
Destructor of the DialogManager.
*******************************************************************************/
DialogManager::~DialogManager()
{
	Clear();
}

/*!*****************************************************************************
\brief
Loads the dialog and it's data into the member vector mDialogs.

\param Dialog _dialog
The dialog data to be loaded into the vector.
*******************************************************************************/
void DialogManager::LoadDialog(Dialog _dialog) {
	mDialogs.push_back(_dialog);
}

/*!*****************************************************************************
\brief
Prints all the dialog text in the member vector mDialogs.
*******************************************************************************/
void DialogManager::PrintDialogs() {
	for (Dialog dialog : mDialogs) {
		LOG_CUSTOM("DIALOG", dialog.text.c_str());
	}
}

/*!*****************************************************************************
\brief
Checks if the dialog with a specific id has choices.

\param int _id
The id of the dialog to be checked.

\return
Returns true if the dialog has choices else returns false.
*******************************************************************************/
bool DialogManager::HasChoice(int _id) {
	for (Dialog dialog : mDialogs)
		if (dialog.id == _id && dialog.next2 != 0) return true;
	return false;
}

/*!*****************************************************************************
\brief
Gets the speaker of the dialog with a specific id.

\param int _id
The id of the dialog to get the speaker of.

\return
Returns the speaker id.
*******************************************************************************/
int DialogManager::GetSpeaker(int _id) {
	for (Dialog dialog : mDialogs)
		if (dialog.id == _id) return dialog.speaker;
	LOG_ERROR("Dialogue ID doesn't exist!");
	return -1;
}

/*!*****************************************************************************
\brief
Retrieves the dialog text of the dialog with a specific id.

\param int _id
The id of the dialog to get.

\return
Returns the dialog text in string.
*******************************************************************************/
std::string DialogManager::GetDialogue(int _id) {
	for (Dialog dialog : mDialogs)
		if (dialog.id == _id) return dialog.text;
	LOG_ERROR("Dialogue ID doesn't exist!");
	return "";
}

/*!*****************************************************************************
\brief
Retrieves the next dialog id.

\param int _id
The id of the current dialog.

\return
Returns the next dialog id.
*******************************************************************************/
int DialogManager::GetNext(int _id) {
	for (Dialog dialog : mDialogs)
		if (dialog.id == _id) return dialog.next;
	LOG_ERROR("Dialogue ID doesn't exist!");
	return 0;
}
int DialogManager::GetNext2(int _id) {
	for (Dialog dialog : mDialogs)
		if (dialog.id == _id) return dialog.next2;
	LOG_ERROR("Dialogue ID doesn't exist!");
	return 0;
}

/*!*****************************************************************************
\brief
Retrieves the choices of the dialog with a specific id.

\param int _id
The id of the dialog to get the choices of.

\return
Returns a pair of integers with the choices of the dialog.
*******************************************************************************/
std::pair<int, int> DialogManager::GetChoices(int _id) {
	std::pair<int, int> choices;
	for (Dialog dialog : mDialogs) {
		if (dialog.id == _id) {
			if (dialog.next2 == 0) {
				LOG_ERROR("Dialogue doesn't have choices!");
				choices.first = choices.second = 0;
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

void DialogManager::EditDialogue(int _id, std::string _text)
{
	for (Dialog& dialog : mDialogs)
	{
		if (dialog.id == _id)
		{
			dialog.text = _text;
			break;
		}
	}
}
void DialogManager::EditChoice(int _id, int _choice, int _choice2)
{
	for (Dialog& dialog : mDialogs)
	{
		if (dialog.id == _id)
		{
			dialog.next = _choice;
			dialog.next2 = _choice2;
			break;
		}
	}
}

/*!*****************************************************************************
\brief
Creates a new dialog item.

\param int _id
The id of the new dialog item.

\param std::string _text
The text of the new dialog item.

\param int _speaker
The speaker id of the new dialog item.

\param int _next
The dialog id of the next dialog item/first choice.

\param int _next2
The dialog id of the second choice.
*******************************************************************************/
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

/*!*****************************************************************************
\brief
Clear the member vector mDialogs.
*******************************************************************************/
void DialogManager::Clear() {
	mDialogs.clear();
}

/*!*****************************************************************************
\brief
Remove a certain dialog from the member vector mDialogs.

\param int _id
The id of the current dialog.

\return
Returns the next dialog id.
*******************************************************************************/
void DialogManager::RemoveDialog(int _id) {
	for (size_t index = 0; index < mDialogs.size(); ++index) {
		if (mDialogs[index].id == _id) {
			mDialogs.erase(std::next(mDialogs.begin(), index), std::next(mDialogs.begin(), index + 1));
			return;
		}
	}
	LOG_ERROR("Dialogue ID doesn't exist!");
}

