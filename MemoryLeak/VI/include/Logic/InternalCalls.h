/*!*****************************************************************************
\file InternalCalls.h
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 22-11-2022
\brief
This file contains the function declarations of the class InternalCalls.
*******************************************************************************/

#pragma once
#include "Singleton.h"
#include "Input.h"
#include "vec2.h"
#include "ECS_items.h"
//#include "Helper.h"
//#include "GameStateManager.h"
//#include "Scene.h"
//#include "DialogManager.h"

class Scene; 

#define FUNC InternalCalls::GetInstance()

class InternalCalls : public Singleton<InternalCalls> {
private:
	int* windowWidth = nullptr;
	int* windowHeight = nullptr;

public:
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
	bool CheckKey(E_STATE _state, E_KEY _key);

	/*!*****************************************************************************
	\brief
	Get world mouse position.
	*******************************************************************************/
	Math::Vec2 GetWorldMousePos();

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
	void ApplyImpulse(const Entity& _e, const Math::Vec2& _impulse, const Math::Vec2& _rotation);

	/*!*****************************************************************************
	\brief
		Loads the dialogs from a json file to the dialog manager

	\return
	None.
	*******************************************************************************/
	void LoadDialogs(std::string _filename);

	/*!*****************************************************************************
	\brief
	Retrieves the dialog text of the dialog with a specific id using function from
	DialogManager.

	\param int _id
	The id of the dialog to get.

	\return
	Returns the dialog text in string.
	*******************************************************************************/
	std::string GetDialogue(int _id);

	/*!*****************************************************************************
	\brief
	Retrieves the next dialog id using function from DialogManager.

	\param int _id
	The id of the current dialog.

	\return
	Returns the next dialog id.
	*******************************************************************************/
	int GetNextDialogueID(int _id);
	
	/*!*****************************************************************************
	\brief
	Checks if the dialog with a specific id has choices using function from
	DialogManager.

	\param int _id
	The id of the dialog to be checked.

	\return
	Returns true if the dialog has choices else returns false.
	*******************************************************************************/
	bool HasChoice(int _id);

	/*!*****************************************************************************
	\brief
	Retrieves the choices of the dialog with a specific id using function from
	DialogManager.

	\param int _id
	The id of the dialog to get the choices of.

	\return
	Returns a pair of integers with the choices of the dialog.
	*******************************************************************************/
	std::pair<int, int> GetChoices(int _id);

	/*!*****************************************************************************
	\brief
	Set the selected choice using function from DialogManager.

	\param int _id
	The id of the current dialog.

	\param int _selectedChoice
	The selected choice.
	*******************************************************************************/
	void SetSelectedChoice(int _id, int _selectedChoice);

	/*!*****************************************************************************
	\brief
	Get current dialogue id using function from DialogManager.

	\param int _id
	The id of the current dialog.
	*******************************************************************************/
	bool SetCurrentDialogueID(int _id);

	/*!*****************************************************************************
	\brief
	Get current dialogue id using function from DialogManager.

	\return
	The id of the current dialog.
	*******************************************************************************/
	int GetCurrentDialogueID();

	/*!*****************************************************************************
	\brief
	This function is called by user, to change the next game state
	*******************************************************************************/
	void ChangeGameState(std::string const& _name);

	/*!*****************************************************************************
	\brief
	Gets an entity from scene.
	*******************************************************************************/
	Entity GetEntity(std::string const& _entityName, std::string const& _sceneName);

	/*!*****************************************************************************
	\brief
	Gets scene to pause or unpause the scene.
	*******************************************************************************/
	Scene& SelectScene(std::string const& _name);

	/*!*****************************************************************************
	\brief
	Sets the texture of an entity.
	*******************************************************************************/
	void SetTexture(const Entity& _e, const std::string& _path);

	/*!*****************************************************************************
	\brief
	EntitiesCollided function that checks if two given entities have collided by
	checking whether if a contact with the two entities exists
	\param const Entity &
	A reference to a read-only entity to compare with
	\param const Entity &
	A reference to a read-only entity to compare against
	\return bool
	Evaluated result of whether a collision happened between the two given entities
	*******************************************************************************/
	bool EntitiesCollided(const Entity& _e1, const Entity& _e2);

	/*!*****************************************************************************
	\brief
	Exits the game.
	*******************************************************************************/
	void GameStateExit();

	/*!*****************************************************************************
	\brief
	Gets the delta time in double.
	*******************************************************************************/
	double GetDeltaTime();

	/*!*****************************************************************************
	\brief
	Initialise the window width and height of the application using pointer.
	Should be called in application's init
	*******************************************************************************/
	void InitScriptWindow(int* _windowWidth, int* _windowHeight);
};
