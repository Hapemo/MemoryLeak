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
DialogManager::DialogManager() {
	LOG_CUSTOM_CREATE("DIALOG");
}

/*!*****************************************************************************
\brief
Destructor of the DialogManager.
*******************************************************************************/
DialogManager::~DialogManager() {
	Clear();
}

/*!*****************************************************************************
\brief
Loads the dialog and it's data into the member map mDialogs.

\param Dialog _dialog
The dialog data to be loaded into the map.
*******************************************************************************/
void DialogManager::LoadDialog(int _id, Dialog _dialog) {
	mDialogs[_id] = _dialog;
}

/*!*****************************************************************************
\brief
Prints all the dialog text in the member map mDialogs.
*******************************************************************************/
void DialogManager::PrintDialogs() {
	for (std::pair<int, Dialog> dialog : mDialogs)
		LOG_CUSTOM("DIALOG", dialog.second.text.c_str());
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
	if (mDialogs.count(_id)) {
		if (mDialogs[_id].next2) return true;
		else return false;
	} else LOG_ERROR("Dialogue ID doesn't exist!");
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
	if(mDialogs.count(_id)) return mDialogs[_id].speaker;
	else LOG_ERROR("Dialogue ID doesn't exist!");
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
	if (mDialogs.count(_id)) return mDialogs[_id].text;
	else LOG_ERROR("Dialogue ID doesn't exist!");
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
	if (mDialogs.count(_id)) return mDialogs[_id].next;
	else LOG_ERROR("Dialogue ID doesn't exist!");
	return 0;
}

/*!*****************************************************************************
\brief
Retrieves the second choice dialog id.

\param int _id
The id of the current dialog.

\return
Returns the second choice dialog id.
*******************************************************************************/
int DialogManager::GetNext2(int _id) {
	if (mDialogs.count(_id)) return mDialogs[_id].next2;
	else LOG_ERROR("Dialogue ID doesn't exist!");
	return 0;
}

/*!*****************************************************************************
\brief
Retrieves the curently selected choice.

\param int _id
The id of the current dialog.
*******************************************************************************/
int DialogManager::GetSelectedChoice(int _id) {
	if (mDialogs.count(_id)) return mDialogs[_id].selectedChoice;
	else LOG_ERROR("Dialogue ID doesn't exist!");
	return 0;
}

/*!*****************************************************************************
\brief
Set the selected choice.

\param int _id
The id of the current dialog.

\param int _selectedChoice
The selected choice.
*******************************************************************************/
void DialogManager::SetSelectedChoice(int _id, int _selectedChoice) {
	if (mDialogs.count(_id)) mDialogs[_id].selectedChoice = _selectedChoice;
	else LOG_ERROR("Dialogue ID doesn't exist!");
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
	if (mDialogs.count(_id)) {
		if (!mDialogs[_id].next2) {
			LOG_ERROR("Dialogue doesn't have choices!");
			choices.first = choices.second = 0;
		}
		else {
			choices.first = mDialogs[_id].next;
			choices.second = mDialogs[_id].next2;
		}
	}
	else LOG_ERROR("Dialogue ID doesn't exist!");
	return choices;
}

/*!*****************************************************************************
\brief
Edit a certain dialog from the member map mDialogs.

\param int _id
The id of the current dialog.

\param int _text
The updated dialog string.
*******************************************************************************/
void DialogManager::EditDialogue(int _id, std::string _text) {
	if (mDialogs.count(_id))
		mDialogs[_id].text = _text;
}

/*!*****************************************************************************
\brief
Swap the 2 choices options in the member map mDialogs.

\param int _id
The id of the dialog choices to be swap.

\param int _choice
The first choice.

\param int _choice2
The second choice.
*******************************************************************************/
void DialogManager::EditChoice(int _id, int _choice, int _choice2) {
	if (mDialogs.count(_id)) {
		mDialogs[_id].next = _choice;
		mDialogs[_id].next2 = _choice2;
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
	if (mDialogs.count(_id))
		LOG_ERROR("Dialogue ID already exist!");
	else {
		Dialog newDialog;
		newDialog.text = _text;
		newDialog.speaker = _speaker;
		newDialog.next = _next;
		newDialog.next2 = _next2;
		mDialogs[_id] = newDialog;
	}
}

/*!*****************************************************************************
\brief
Clear the member map mDialogs.
*******************************************************************************/
void DialogManager::Clear() {
	mDialogs.clear();
}

/*!*****************************************************************************
\brief
Remove a certain dialog from the member map mDialogs.

\param int _id
The id of the current dialog.
*******************************************************************************/
void DialogManager::RemoveDialog(int _id) {
	if (mDialogs.count(_id)) mDialogs.erase(_id);
	else LOG_ERROR("Dialogue ID doesn't exist!");
}

