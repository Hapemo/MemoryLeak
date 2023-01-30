/*!*****************************************************************************
\file InternalCalls.h
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 22-11-2022
\brief
This file contains the function declarations of the class InternalCalls.
InternalCalls are where all functions that scripts need to use from the engine
is being stored.
*******************************************************************************/

#pragma once
#include <mono/jit/jit.h>
#include "Singleton.h"
#include "Input.h"
#include "vec2.h"
#include "ECS_items.h"
//#include "Helper.h"
//#include "GameStateManager.h"
//#include "Scene.h"
//#include "DialogManager.h"

class Scene; 
class GameState;
struct Transform;

#define FUNC InternalCalls::GetInstance()

class InternalCalls : public Singleton<InternalCalls> {
private:
	static int* windowWidth;
	static int* windowHeight;

public:
	/*!*****************************************************************************
	\brief
	Test internal function for string.
	*******************************************************************************/
	static void TestArgString(MonoString* _thingToPrint);
	static MonoString* TestReturnString();

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
	static bool CheckKey(E_STATE _state, E_KEY _key);
	static bool CheckKeyPress(int _key);
	static bool CheckKeyHold(int _key);
	static bool CheckKeyRelease(int _key);
	static bool CheckKeyIdle(int _key);

	/*!*****************************************************************************
	\brief
	Get world mouse position.
	*******************************************************************************/
	static Math::Vec2 GetWorldMousePos();

	/*!*****************************************************************************
	\brief
	Get world mouse position x.
	*******************************************************************************/
	static float GetWorldMousePosX();

	/*!*****************************************************************************
	\brief
	Get world mouse position y.
	*******************************************************************************/
	static float GetWorldMousePosY();

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
	static void ApplyImpulseByEntity(const Entity& _e, const Math::Vec2& _impulse, const Math::Vec2& _rotation);
	static void ApplyImpulse(std::string const& _entityName, std::string const& _sceneName, const float _impulseX, const float _impulseY, const float _rotationX, const float _rotationY);

	/*!*****************************************************************************
	\brief
		Loads the dialogs from a json file to the dialog manager

	\return
	None.
	*******************************************************************************/
	static void LoadDialogs(std::string _filename);

	/*!*****************************************************************************
	\brief
	Retrieves the dialog text of the dialog with a specific id using function from
	DialogManager.

	\param int _id
	The id of the dialog to get.

	\return
	Returns the dialog text in string.
	*******************************************************************************/
	static std::string GetDialogue(int _id);

	/*!*****************************************************************************
	\brief
	Retrieves the next dialog id using function from DialogManager.

	\param int _id
	The id of the current dialog.

	\return
	Returns the next dialog id.
	*******************************************************************************/
	static int GetNextDialogueID(int _id);
	
	/*!*****************************************************************************
	\brief
	Checks if the dialog with a specific id has choices using function from
	DialogManager.

	\param int _id
	The id of the dialog to be checked.

	\return
	Returns true if the dialog has choices else returns false.
	*******************************************************************************/
	static bool HasChoice(int _id);

	/*!*****************************************************************************
	\brief
	Retrieves the choices of the dialog with a specific id using function from
	DialogManager.

	\param int _id
	The id of the dialog to get the choices of.

	\return
	Returns a pair of integers with the choices of the dialog.
	*******************************************************************************/
	static std::pair<int, int> GetChoices(int _id);

	/*!*****************************************************************************
	\brief
	Retrieves the next dialog id.

	\param int _id
	The id of the current dialog.

	\return
	Returns the next dialog id.
	*******************************************************************************/
	static int GetNext(int _id);

	/*!*****************************************************************************
	\brief
	Retrieves the next dialog id.

	\param int _id
	The id of the current dialog.

	\return
	Returns the next dialog id.
	*******************************************************************************/
	static int GetChoice1(int _id);

	/*!*****************************************************************************
	\brief
	Retrieves the second choice dialog id.

	\param int _id
	The id of the current dialog.

	\return
	Returns the second choice dialog id.
	*******************************************************************************/
	static int GetChoice2(int _id);

	/*!*****************************************************************************
	\brief
	Set the selected choice using function from DialogManager.

	\param int _id
	The id of the current dialog.

	\param int _selectedChoice
	The selected choice.
	*******************************************************************************/
	static void SetSelectedChoice(int _id, int _selectedChoice);

	/*!*****************************************************************************
	\brief
	Get current dialogue id using function from DialogManager.

	\param int _id
	The id of the current dialog.
	*******************************************************************************/
	static bool SetCurrentDialogueID(int _id);

	/*!*****************************************************************************
	\brief
	Get current dialogue id using function from DialogManager.

	\return
	The id of the current dialog.
	*******************************************************************************/
	static int GetCurrentDialogueID();

	/*!*****************************************************************************
	\brief
	Returns true if speaker is player using function from DialogManager.

	\param int _id
	The id of the current dialog.
	*******************************************************************************/
	static bool IsPlayerSpeaker(int _id);

	/*!*****************************************************************************
	\brief
	This function is called by user, to change the next game state
	*******************************************************************************/
	static void ChangeGameState(std::string const& _name);

	/*!*****************************************************************************
	\brief
	Gets an entity from scene.
	*******************************************************************************/
	static Entity GetEntity(std::string const& _entityName, std::string const& _sceneName);

	/*!*****************************************************************************
	\brief
	Checks if an entity from scene is active.
	*******************************************************************************/
	static bool EntityIsActive(std::string const& _entityName, std::string const& _sceneName);

	/*!*****************************************************************************
	\brief
	Activate an entity from scene.
	*******************************************************************************/
	static void EntityActivate(std::string const& _entityName, std::string const& _sceneName);

	/*!*****************************************************************************
	\brief
	Deactivate an entity from scene.
	*******************************************************************************/
	static void EntityDeactivate(std::string const& _entityName, std::string const& _sceneName);
	
	/*!*****************************************************************************
	\brief
	Gets parent name of an entity from scene.
	*******************************************************************************/
	static std::string EntityGetParent(std::string const& _entityName, std::string const& _sceneName);

	/*!*****************************************************************************
	\brief
	Gets parent id of an entity from scene.
	*******************************************************************************/
	static int EntityGetParentId(std::string const& _entityName, std::string const& _sceneName);

	/*!*****************************************************************************
	\brief
	Gets scene to pause or unpause the scene.
	*******************************************************************************/
	static Scene& SelectScene(std::string const& _name);

	/*!*****************************************************************************
	\brief
	Pause scene.
	*******************************************************************************/
	static void PauseScene(std::string const& _name);

	/*!*****************************************************************************
	\brief
	Unpause scene.
	*******************************************************************************/
	static void PlayScene(std::string const& _name);

	/*!*****************************************************************************
	\brief
	Get current game state
	*******************************************************************************/
	static GameState& CurrentGameState();
	static std::string GetCurrentGameStateName();

	/*!*****************************************************************************
	\brief
	Get current game state's camera
	*******************************************************************************/
	static Transform& CurrentCamera();

	/*!*****************************************************************************
	\brief
	Get current game state's camera X scale
	*******************************************************************************/
	static float GetCurrentCameraScaleX();

	/*!*****************************************************************************
	\brief
	Get current game state's camera Y scale
	*******************************************************************************/
	static float GetCurrentCameraScaleY();

	/*!*****************************************************************************
	\brief
	Get current game state's camera X pos
	*******************************************************************************/
	static float GetCurrentCameraPosX();

	/*!*****************************************************************************
	\brief
	Get current game state's camera Y pos
	*******************************************************************************/
	static float GetCurrentCameraPosY();

	/*!*****************************************************************************
	\brief
	Set current game state's camera X scale
	*******************************************************************************/
	static void SetCurrentCameraScaleX(float _x);

	/*!*****************************************************************************
	\brief
	Set current game state's camera Y scale
	*******************************************************************************/
	static void SetCurrentCameraScaleY(float _y);

	/*!*****************************************************************************
	\brief
	Set current game state's camera X pos
	*******************************************************************************/
	static void SetCurrentCameraPosX(float _x);

	/*!*****************************************************************************
	\brief
	Set current game state's camera Y pos
	*******************************************************************************/
	static void SetCurrentCameraPosY(float _y);

	/*!*****************************************************************************
	\brief
	Math vector functions
	*******************************************************************************/
	static float SqMagnitude(float _x, float _y);
	static float NormalizeX(float _x, float _y);
	static float NormalizeY(float _x, float _y);
	static float ArcTangent(float _x, float _y);
	static float Negate(float _value);

	/*!*****************************************************************************
	\brief
	Set current animation image speed
	*******************************************************************************/
	static void SetAnimationSpeed(std::string const& _entityName, std::string const& _sceneName, float _speed);

	/*!*****************************************************************************
	\brief
	Get current animation image speed
	*******************************************************************************/
	static float GetAnimationSpeed(std::string const& _entityName, std::string const& _sceneName);

	/*!*****************************************************************************
	\brief
	Set current animation image index by entity
	*******************************************************************************/
	static void SetSpriteSheetIndexByEntity(Entity _e, int _index);

	/*!*****************************************************************************
	\brief
	Get current animation image index by entity
	*******************************************************************************/
	static int GetSpriteSheetIndexByEntity(Entity _e);

	/*!*****************************************************************************
	\brief
	Set current animation image index
	*******************************************************************************/
	static void SetSpriteSheetIndex(std::string const& _entityName, std::string const& _sceneName, int _index);

	/*!*****************************************************************************
	\brief
	Get current animation image index
	*******************************************************************************/
	static int GetSpriteSheetIndex(std::string const& _entityName, std::string const& _sceneName);

	/*!*****************************************************************************
	\brief
	Set current animation image index
	*******************************************************************************/
	static void SetAnimationCurrentIndex(std::string const& _entityName, std::string const& _sceneName, int _index);

	/*!*****************************************************************************
	\brief
	Get current animation image index
	*******************************************************************************/
	static int GetAnimationCurrentIndex(std::string const& _entityName, std::string const& _sceneName);

	/*!*****************************************************************************
	\brief
	Get current animation total frame count
	*******************************************************************************/
	static int GetAnimationFrameCount(std::string const& _entityName, std::string const& _sceneName);

	/*!*****************************************************************************
	\brief
	Set current animation total frame count
	*******************************************************************************/
	static void SetAnimationFrameCount(std::string const& _entityName, std::string const& _sceneName, int _count);

	/*!*****************************************************************************
	\brief
	Sets the texture of an entity.
	*******************************************************************************/
	static void SetTextureByEntity(const Entity& _e, const std::string& _path);

	/*!*****************************************************************************
	\brief
	Retrieves the texture of an entity.
	*******************************************************************************/
	static std::string GetTextureByEntity(const Entity& _e);

	/*!*****************************************************************************
	\brief
	Sets the texture of an entity.
	*******************************************************************************/
	static void SetTexture(std::string const& _entityName, std::string const& _sceneName, const std::string& _path);

	/*!*****************************************************************************
	\brief
	Retrieves the texture of an entity.
	*******************************************************************************/
	static std::string GetTexture(std::string const& _entityName, std::string const& _sceneName);

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
	static bool EntitiesCollidedByEntity(const Entity& _e1, const Entity& _e2);
	static bool CheckCollisionByEntity(const Entity& _e1, const Entity& _e2, const bool& _dynamicCheck = false);

	/*!*****************************************************************************
	\brief
	EntitiesCollided function that checks if two given entities have collided by
	checking whether if a contact with the two entities exists
	\return bool
	Evaluated result of whether a collision happened between the two given entities
	*******************************************************************************/
	static bool EntitiesCollided(std::string const& _entityName1, std::string const& _entityName2, std::string const& _sceneName);
	static bool CheckCollision(std::string const& _entityName1, std::string const& _entityName2, std::string const& _sceneName, bool const& _dynamicCheck = false);

	/*!*****************************************************************************
	\brief
	Exits the game.
	*******************************************************************************/
	static void GameStateExit();

	/*!*****************************************************************************
	\brief
	Gets the delta time in double.
	*******************************************************************************/
	static double GetDeltaTime();

	/*!*****************************************************************************
	\brief
	Initialise the window width and height of the application using pointer.
	Should be called in application's init
	*******************************************************************************/
	static void InitScriptWindow(int* _windowWidth, int* _windowHeight);

	/*!*****************************************************************************
	\brief
		Stop a sound
	*******************************************************************************/
	static void StopSound(std::string const& _entityName, std::string const& _sceneName);

	/*!*****************************************************************************
	\brief
		Plays a sound on loop
	*******************************************************************************/
	static void PlaySoundOnLoop(std::string const& _entityName, std::string const& _sceneName);

	/*!*****************************************************************************
	\brief
		Plays a single background sound
	*******************************************************************************/
	static void PlayAnySound(std::string _name, int _channel);

	/*!*****************************************************************************
	\brief
	   Checks if a channel is playing
	*******************************************************************************/
	static bool IsPlaying(int _channel);

	/*!*****************************************************************************
	\brief
		Plays a single background sound
	*******************************************************************************/
	static void PlayBGSound(std::string _name, int _channel);

	/*!*****************************************************************************
	\brief
	Get X pos of an entity.
	*******************************************************************************/
	static float GetPosX(std::string const& _entityName, std::string const& _sceneName);

	/*!*****************************************************************************
	\brief
	Get Y pos of an entity.
	*******************************************************************************/
	static float GetPosY(std::string const& _entityName, std::string const& _sceneName);

	/*!*****************************************************************************
	\brief
	Set X pos of an entity.
	*******************************************************************************/
	static void SetPosX(std::string const& _entityName, std::string const& _sceneName, float _posX);

	/*!*****************************************************************************
	\brief
	Set Y pos of an entity.
	*******************************************************************************/
	static void SetPosY(std::string const& _entityName, std::string const& _sceneName, float _posY);

	/*!*****************************************************************************
	\brief
	Get X scale of an entity.
	*******************************************************************************/
	static float GetScaleX(std::string const& _entityName, std::string const& _sceneName);

	/*!*****************************************************************************
	\brief
	Get Y scale of an entity.
	*******************************************************************************/
	static float GetScaleY(std::string const& _entityName, std::string const& _sceneName);

	/*!*****************************************************************************
	\brief
	Set X scale of an entity.
	*******************************************************************************/
	static void SetScaleX(std::string const& _entityName, std::string const& _sceneName, float _posX);

	/*!*****************************************************************************
	\brief
	Set Y scale of an entity.
	*******************************************************************************/
	static void SetScaleY(std::string const& _entityName, std::string const& _sceneName, float _posY);

	/*!*****************************************************************************
	\brief
	Get rotation of an entity.
	*******************************************************************************/
	static float GetRotate(std::string const& _entityName, std::string const& _sceneName);

	/*!*****************************************************************************
	\brief
	Set rotation of an entity.
	*******************************************************************************/
	static void SetRotate(std::string const& _entityName, std::string const& _sceneName, float _rotate);

	/*!*****************************************************************************
	\brief
	This is for checking holding down button.
	*******************************************************************************/
	static bool ButtonClickedByEntity(const Entity& _e);
	static bool ButtonClicked(std::string const& _entityName, std::string const& _sceneName);

	/*!*****************************************************************************
	\brief
	This is for checking button is released. Plays sound if there is audio attached to it.
	*******************************************************************************/
	static bool ButtonReleasedByEntity(const Entity& _e);
	static bool ButtonReleased(std::string const& _entityName, std::string const& _sceneName);

	/*!*****************************************************************************
	\brief
	This is for checking if button is hovered.
	*******************************************************************************/
	static bool ButtonHoverByEntity(const Entity& _e);
	static bool ButtonHover(std::string const& _entityName, std::string const& _sceneName);

	/*!*****************************************************************************
	\brief
	Changing text component text.
	*******************************************************************************/
	static void UpdateTextByEntity(const Entity& _e, std::string const& _text);
	static void UpdateText(std::string const& _entityName, std::string const& _sceneName, std::string const& _text);
	static void SetTextOffset(std::string const& _entityName, std::string const& _sceneName, float _xoffset, float _yoffset);
	static int GetLineCount(std::string const& _entityName, std::string const& _sceneName);


	static void WeatherAIinit(float width = 1600, float height = 900);
	static int GetCurrentWeather(int index, float posX, float posY);
};
