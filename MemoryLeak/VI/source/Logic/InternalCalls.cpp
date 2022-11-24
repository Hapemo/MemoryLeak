/*!*****************************************************************************
\file InternalCalls.cpp
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 22-11-2022
\brief
This file contains the function definitions of the class InternalCalls.
*******************************************************************************/

#include "InternalCalls.h"
#include "ECSManager.h"
#include "GameStateManager.h"

/*!*****************************************************************************
\brief
Checks for the state of certain key
\param STATE
- State of the key pressed
\param KEY
- Key to check the state of
\return bool
- Returns true if inputted state matches current state of specified key
*******************************************************************************/
bool InternalCalls::CheckKey(E_STATE _state, E_KEY _key) {
	return Input::CheckKey(_state, _key);
}

Math::Vec2 InternalCalls::GetWorldMousePos() {
	return editorManager->GetEditorWorldMousePos();
}

/*!*****************************************************************************
\brief
ApplyImpulse function that adds a velocity impulse to the entity
\param const Entity &
A reference to a read-only Entity to
\param const Math::Vec2 &
A reference to a read-only variable containing the velocity impulse
\param const Math::Vec2 &
A reference to a read-only variable containing the rotation impulse
calculation
\return void
NULL
*******************************************************************************/
void InternalCalls::ApplyImpulse(const Entity& _e, const Math::Vec2& _impulse, const Math::Vec2& _rotation) {
	physics2DManager->ApplyImpulse(_e, _impulse, _rotation);
}

/*!*****************************************************************************
\brief
	Loads the dialogs from a json file to the dialog manager

\return
None.
*******************************************************************************/
void InternalCalls::LoadDialogs(std::string _filename) {
	LOG_INFO("Loading Dialog: " + _filename);
	serializationManager->LoadDialogs(_filename);
}

/*!*****************************************************************************
\brief
Retrieves the dialog text of the dialog with a specific id using function from
DialogManager.

\param int _id
The id of the dialog to get.

\return
Returns the dialog text in string.
*******************************************************************************/
std::string InternalCalls::GetDialogue(int _id) {
	return dialogManager->GetDialogue(_id);
}

/*!*****************************************************************************
\brief
Retrieves the next dialog id using function from DialogManager.

\param int _id
The id of the current dialog.

\return
Returns the next dialog id.
*******************************************************************************/
int InternalCalls::GetNextDialogueID(int _id) {
	return dialogManager->GetNext(_id);
}

/*!*****************************************************************************
\brief
Checks if the dialog with a specific id has choices using function from
DialogManager.

\param int _id
The id of the dialog to be checked.

\return
Returns true if the dialog has choices else returns false.
*******************************************************************************/
bool InternalCalls::HasChoice(int _id) {
	return dialogManager->HasChoice(_id);
}

/*!*****************************************************************************
\brief
Retrieves the choices of the dialog with a specific id using function from
DialogManager.

\param int _id
The id of the dialog to get the choices of.

\return
Returns a pair of integers with the choices of the dialog.
*******************************************************************************/
std::pair<int, int> InternalCalls::GetChoices(int _id) {
	return dialogManager->GetChoices(_id);
}

/*!*****************************************************************************
\brief
Set the selected choice using function from DialogManager.

\param int _id
The id of the current dialog.

\param int _selectedChoice
The selected choice.
*******************************************************************************/
void InternalCalls::SetSelectedChoice(int _id, int _selectedChoice) {
	dialogManager->SetSelectedChoice(_id, _selectedChoice);
}

/*!*****************************************************************************
\brief
Get current dialogue id using function from DialogManager.

\param int _id
The id of the current dialog.
*******************************************************************************/
bool InternalCalls::SetCurrentDialogueID(int _id) {
	return dialogManager->SetCurrentDialogueID(_id);
}

/*!*****************************************************************************
\brief
Get current dialogue id using function from DialogManager.

\return
The id of the current dialog.
*******************************************************************************/
int InternalCalls::GetCurrentDialogueID() {
	return dialogManager->GetCurrentDialogueID();
}

/*!*****************************************************************************
\brief
This function is called by user, to change the next game state
*******************************************************************************/
void InternalCalls::ChangeGameState(std::string const& _name) {
	GameStateManager::GetInstance()->ChangeGameState(_name);
}

/*!*****************************************************************************
\brief
Gets an entity from scene.
*******************************************************************************/
Entity InternalCalls::GetEntity(std::string const& _entityName, std::string const& _sceneName) {
	return GameStateManager::GetInstance()->GetEntity(_entityName, _sceneName);
}

/*!*****************************************************************************
\brief
Gets scene to pause or unpause the scene.
*******************************************************************************/
Scene& InternalCalls::SelectScene(std::string const& _name) {
	return GameStateManager::GetInstance()->SelectScene(_name);
}
