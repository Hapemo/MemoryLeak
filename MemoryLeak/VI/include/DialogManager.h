/*!*****************************************************************************
\file DialogManager.h
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 26-09-2022
\brief
This file contains the class DialogManager and it's functions declaration.
The DialogManager manages the scripts and dialogues data.
*******************************************************************************/

#pragma once
#include <ECS_systems.h>
#include "ECS_items.h"
#include "ECS_components.h"

/*!*****************************************************************************
\brief
The struct for all the dialog's data.
*******************************************************************************/
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
	/*!*****************************************************************************
	\brief
	Constructor of the DialogManager.
	*******************************************************************************/
	DialogManager();

	/*!*****************************************************************************
	\brief
	Destructor of the DialogManager.
	*******************************************************************************/
	~DialogManager();

	/*!*****************************************************************************
	\brief
	Loads the dialog and it's data into the member vector mDialogs.

	\param Dialog _dialog
	The dialog data to be loaded into the vector.
	*******************************************************************************/
	void LoadDialog(Dialog _dialog);

	/*!*****************************************************************************
	\brief
	Prints all the dialog text in the member vector mDialogs.
	*******************************************************************************/
	void PrintDialogs();

	/*!*****************************************************************************
	\brief
	Gets the vector (mDialogs) filled with all the dialog data.

	\return
	Returns a vector of Dialog structs.
	*******************************************************************************/
	std::vector<Dialog> GetDialogs() { return mDialogs; }

	/*!*****************************************************************************
	\brief
	Checks if the dialog with a specific id has choices.

	\param int _id
	The id of the dialog to be checked.

	\return
	Returns true if the dialog has choices else returns false.
	*******************************************************************************/
	bool HasChoice(int _id);

	/*!*****************************************************************************
	\brief
	Retrieves the choices of the dialog with a specific id.

	\param int _id
	The id of the dialog to get the choices of.

	\return
	Returns a pair of integers with the choices of the dialog.
	*******************************************************************************/
	std::pair<int, int> GetChoices(int _id);

	/*!*****************************************************************************
	\brief
	Gets the speaker of the dialog with a specific id.

	\param int _id
	The id of the dialog to get the speaker of.

	\return
	Returns the speaker id.
	*******************************************************************************/
	int GetSpeaker(int _id);

	/*!*****************************************************************************
	\brief
	Retrieves the dialog text of the dialog with a specific id.

	\param int _id
	The id of the dialog to get.

	\return
	Returns the dialog text in string.
	*******************************************************************************/
	std::string GetDialogue(int _id);

	/*!*****************************************************************************
	\brief
	Retrieves the next dialog id.

	\param int _id
	The id of the current dialog.

	\return
	Returns the next dialog id.
	*******************************************************************************/
	int GetNext(int _id);
	int GetNext2(int _id);
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
	void CreateNewDialogue(int _id, std::string _text, int _speaker, int _next, int _next2 = -1);
	void EditDialogue(int _id, std::string _text);
	void EditChoice(int _id, int _choice, int _choice2);
	void RemoveDialog(int _id);
	void Clear();

private:
	/*!*****************************************************************************
	\brief
	The vector containing all the dialogs' data.
	*******************************************************************************/
	std::vector<Dialog> mDialogs;
};