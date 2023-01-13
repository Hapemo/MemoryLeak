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

#include "InternalCalls.h"
#include "ECSManager.h"
#include "GameStateManager.h"
#include "Helper.h"

int* InternalCalls::windowWidth = nullptr;
int* InternalCalls::windowHeight = nullptr;

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

/*!*****************************************************************************
\brief
Get world mouse position.
*******************************************************************************/
Math::Vec2 InternalCalls::GetWorldMousePos() {
#ifdef _EDITOR
	return editorManager->GetEditorWorldMousePos();
#else 
	Math::Vec2 cursorPos = Math::Vec2(Input::CursorPos().x, -Input::CursorPos().y) + Math::Vec2(-*windowWidth / 2.f, *windowHeight / 2.f);
	//if (Input::CheckKey(PRESS, M_BUTTON_L)) std::cout << "cursorPos: " << cursorPos << '\n';

	return cursorPos;
#endif 
}

/*!*****************************************************************************
\brief
Get world mouse position x.
*******************************************************************************/
float InternalCalls::GetWorldMousePosX() {
	return FUNC->GetWorldMousePos().x;
}

/*!*****************************************************************************
\brief
Get world mouse position x.
*******************************************************************************/
float InternalCalls::GetWorldMousePosY() {
	return FUNC->GetWorldMousePos().y;
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
Retrieves the next dialog id.

\param int _id
The id of the current dialog.

\return
Returns the next dialog id.
*******************************************************************************/
int InternalCalls::GetNext(int _id) {
	return dialogManager->GetNext(_id);
}

/*!*****************************************************************************
\brief
Retrieves the next dialog id.

\param int _id
The id of the current dialog.

\return
Returns the next dialog id.
*******************************************************************************/
int InternalCalls::GetChoice1(int _id) {
	return dialogManager->GetNext(_id);
}

/*!*****************************************************************************
\brief
Retrieves the second choice dialog id.

\param int _id
The id of the current dialog.

\return
Returns the second choice dialog id.
*******************************************************************************/
int InternalCalls::GetChoice2(int _id) {
	return dialogManager->GetNext2(_id);
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
Checks if an entity from scene is active.
*******************************************************************************/
bool InternalCalls::EntityIsActive(std::string const& _entityName, std::string const& _sceneName) {
	return (FUNC->GetEntity(_entityName, _sceneName)).GetComponent<General>().isActive;
}

/*!*****************************************************************************
\brief
Activate an entity from scene.
*******************************************************************************/
void InternalCalls::EntityActivate(std::string const& _entityName, std::string const& _sceneName) {
	(FUNC->GetEntity(_entityName, _sceneName)).Activate();
}

/*!*****************************************************************************
\brief
Deactivate an entity from scene.
*******************************************************************************/
void InternalCalls::EntityDeactivate(std::string const& _entityName, std::string const& _sceneName) {
	(FUNC->GetEntity(_entityName, _sceneName)).Deactivate();
}

/*!*****************************************************************************
\brief
Gets parent name of an entity from scene.
*******************************************************************************/
std::string InternalCalls::EntityGetParent(std::string const& _entityName, std::string const& _sceneName) {
	return (FUNC->GetEntity(_entityName, _sceneName)).GetComponent<General>().parent.GetComponent<General>().name;
}

/*!*****************************************************************************
\brief
Gets parent id of an entity from scene.
*******************************************************************************/
int InternalCalls::EntityGetParentId(std::string const& _entityName, std::string const& _sceneName) {
	return (FUNC->GetEntity(_entityName, _sceneName)).GetComponent<General>().parent.id;
}

/*!*****************************************************************************
\brief
Gets scene to pause or unpause the scene.
*******************************************************************************/
Scene& InternalCalls::SelectScene(std::string const& _name) {
	return GameStateManager::GetInstance()->SelectScene(_name);
}

/*!*****************************************************************************
\brief
Get current game state
*******************************************************************************/
GameState& InternalCalls::CurrentGameState() {
	return *GameStateManager::GetInstance()->mCurrentGameState;
}

/*!*****************************************************************************
\brief
Pause scene.
*******************************************************************************/
void InternalCalls::PauseScene(std::string const& _name) {
	GameStateManager::GetInstance()->SelectScene(_name).Pause(true);
}

/*!*****************************************************************************
\brief
Unpause scene.
*******************************************************************************/
void InternalCalls::PlayScene(std::string const& _name) {
	GameStateManager::GetInstance()->SelectScene(_name).Pause(false);
}

/*!*****************************************************************************
\brief
Get current game state's camera
*******************************************************************************/
Transform& InternalCalls::CurrentCamera() {
	return CurrentGameState().mCamera;
}

/*!*****************************************************************************
\brief
Get current game state's camera X scale
*******************************************************************************/
float InternalCalls::GetCurrentCameraScaleX() {
	return CurrentGameState().mCamera.scale.x;
}

/*!*****************************************************************************
\brief
Get current game state's camera Y scale
*******************************************************************************/
float InternalCalls::GetCurrentCameraScaleY() {
	return CurrentGameState().mCamera.scale.y;
}

/*!*****************************************************************************
\brief
Get current game state's camera X pos
*******************************************************************************/
float InternalCalls::GetCurrentCameraPosX() {
	return CurrentGameState().mCamera.translation.x;
}

/*!*****************************************************************************
\brief
Get current game state's camera Y pos
*******************************************************************************/
float InternalCalls::GetCurrentCameraPosY() {
	return CurrentGameState().mCamera.translation.y;
}

/*!*****************************************************************************
\brief
Set current game state's camera X scale
*******************************************************************************/
void InternalCalls::SetCurrentCameraScaleX(float _x) {
	CurrentGameState().mCamera.scale.x = _x;
}

/*!*****************************************************************************
\brief
Set current game state's camera Y scale
*******************************************************************************/
void InternalCalls::SetCurrentCameraScaleY(float _y) {
	CurrentGameState().mCamera.scale.y = _y;
}

/*!*****************************************************************************
\brief
Set current game state's camera X pos
*******************************************************************************/
void InternalCalls::SetCurrentCameraPosX(float _x) {
	CurrentGameState().mCamera.translation.x = _x;
}

/*!*****************************************************************************
\brief
Set current game state's camera Y pos
*******************************************************************************/
void InternalCalls::SetCurrentCameraPosY(float _y) {
	CurrentGameState().mCamera.translation.y = _y;
}

/*!*****************************************************************************
\brief
Set current animation image index
*******************************************************************************/
void InternalCalls::SetCurrentImageIndex(std::string const& _entityName, std::string const& _sceneName, int _index) {
	animator->SetCurrentImageIndex(FUNC->GetEntity(_entityName, _sceneName), _index);
}

/*!*****************************************************************************
\brief
Set current animation image index
*******************************************************************************/
int InternalCalls::GetCurrentImageIndex(std::string const& _entityName, std::string const& _sceneName) {
	return animator->GetCurrentImageIndex(FUNC->GetEntity(_entityName, _sceneName));
}

/*!*****************************************************************************
\brief
Set current animation image index by entity
*******************************************************************************/
void InternalCalls::SetCurrentImageIndexByEntity(Entity _e, int _index) {
	animator->SetCurrentImageIndex(_e, _index);
}

/*!*****************************************************************************
\brief
Set current animation image index by entity
*******************************************************************************/
int InternalCalls::GetCurrentImageIndexByEntity(Entity _e) {
	return animator->GetCurrentImageIndex(_e);
}

/*!*****************************************************************************
\brief
Sets the texture of an entity.
*******************************************************************************/
void InternalCalls::SetTextureByEntity(const Entity& _e, const std::string& _path) {
	spriteManager->SetTexture(_e, _path);
}

/*!*****************************************************************************
\brief
Retrieves the texture of an entity.
*******************************************************************************/
std::string InternalCalls::GetTextureByEntity(const Entity& _e) {
	return spriteManager->GetTexturePath(spriteManager->GetTexture(_e));
}

/*!*****************************************************************************
\brief
Sets the texture of an entity.
*******************************************************************************/
void InternalCalls::SetTexture(std::string const& _entityName, std::string const& _sceneName, const std::string& _path) {
	spriteManager->SetTexture(FUNC->GetEntity(_entityName, _sceneName), _path);
}

/*!*****************************************************************************
\brief
Retrieves the texture of an entity.
*******************************************************************************/
std::string InternalCalls::GetTexture(std::string const& _entityName, std::string const& _sceneName) {
	return spriteManager->GetTexturePath(spriteManager->GetTexture(FUNC->GetEntity(_entityName, _sceneName)));
}

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
bool InternalCalls::EntitiesCollidedByEntity(const Entity& _e1, const Entity& _e2) {
	return collision2DManager->EntitiesCollided(_e1, _e2);
}

bool InternalCalls::CheckCollisionByEntity(const Entity& _e1, const Entity& _e2, bool const& _dynamicCheck) {
	return collision2DManager->CheckCollision(_e1, _e2, _dynamicCheck);
}

/*!*****************************************************************************
\brief
EntitiesCollided function that checks if two given entities have collided by
checking whether if a contact with the two entities exists
\return bool
Evaluated result of whether a collision happened between the two given entities
*******************************************************************************/
bool InternalCalls::EntitiesCollided(std::string const& _entityName1, std::string const& _entityName2, std::string const& _sceneName) {
	return collision2DManager->EntitiesCollided(FUNC->GetEntity(_entityName1, _sceneName), FUNC->GetEntity(_entityName2, _sceneName));
}

bool InternalCalls::CheckCollision(std::string const& _entityName1, std::string const& _entityName2, std::string const& _sceneName, bool const& _dynamicCheck) {
	return collision2DManager->CheckCollision(FUNC->GetEntity(_entityName1, _sceneName), FUNC->GetEntity(_entityName2, _sceneName), _dynamicCheck);
}

/*!*****************************************************************************
\brief
Exits the game.
*******************************************************************************/
void InternalCalls::GameStateExit() {
#ifdef _EDITOR
	editorManager->SetScenePaused(true);
	editorManager->SetFullScreen(false);
#else
	GameStateManager::GetInstance()->GameStateExit();
#endif // _EDITOR
}

/*!*****************************************************************************
\brief
Gets the delta time in double.
*******************************************************************************/
double InternalCalls::GetDeltaTime() {
	return FPSManager::dt;
}

/*!*****************************************************************************
\brief
Initialise the window width and height of the application using pointer.
Should be called in application's init
*******************************************************************************/
void InternalCalls::InitScriptWindow(int* _windowWidth, int* _windowHeight) {
	windowWidth = _windowWidth;
	windowHeight = _windowHeight;
}

/*!*****************************************************************************
\brief
	Plays a single background sound
*******************************************************************************/
void InternalCalls::PlayAnySound(std::string _name, int _channel) {
	audioManager->PlayAnySound(_name, _channel);
}

/*!*****************************************************************************
\brief
   Checks if a channel is playing
*******************************************************************************/
bool InternalCalls::IsPlaying(int _channel) {
	return audioManager->isPlaying(_channel);
}

/*!*****************************************************************************
\brief
	Plays a single background sound
*******************************************************************************/
void InternalCalls::PlayBGSound(std::string _name, int _channel) {
	audioManager->PlayBGSound(_name, _channel);
}

/*!*****************************************************************************
\brief
Get X pos of an entity.
*******************************************************************************/
float InternalCalls::GetPosX(std::string const& _entityName, std::string const& _sceneName) {
	return FUNC->GetEntity(_entityName, _sceneName).GetComponent<Transform>().translation.x;
}

/*!*****************************************************************************
\brief
Get Y pos of an entity.
*******************************************************************************/
float InternalCalls::GetPosY(std::string const& _entityName, std::string const& _sceneName) {
	return FUNC->GetEntity(_entityName, _sceneName).GetComponent<Transform>().translation.y;
}

/*!*****************************************************************************
\brief
Set X pos of an entity.
*******************************************************************************/
void InternalCalls::SetPosX(std::string const& _entityName, std::string const& _sceneName, float _posX) {
	FUNC->GetEntity(_entityName, _sceneName).GetComponent<Transform>().translation.x = _posX;
}

/*!*****************************************************************************
\brief
Set Y pos of an entity.
*******************************************************************************/
void InternalCalls::SetPosY(std::string const& _entityName, std::string const& _sceneName, float _posY) {
	FUNC->GetEntity(_entityName, _sceneName).GetComponent<Transform>().translation.y = _posY;
}

/*!*****************************************************************************
\brief
Set Y scale of an entity.
*******************************************************************************/
void InternalCalls::SetScaleY(std::string const& _entityName, std::string const& _sceneName, float _scaleY) {
	FUNC->GetEntity(_entityName, _sceneName).GetComponent<Transform>().scale.y = _scaleY;
}

/*!*****************************************************************************
\brief
Set Y scale of an entity.
*******************************************************************************/
void InternalCalls::SetScaleX(std::string const& _entityName, std::string const& _sceneName, float _scaleX) {
	FUNC->GetEntity(_entityName, _sceneName).GetComponent<Transform>().scale.x = _scaleX;
}

/*!*****************************************************************************
\brief
Get Y scale of an entity.
*******************************************************************************/
float InternalCalls::GetScaleY(std::string const& _entityName, std::string const& _sceneName) {
	return FUNC->GetEntity(_entityName, _sceneName).GetComponent<Transform>().scale.y;
}

/*!*****************************************************************************
\brief
Get X scale of an entity.
*******************************************************************************/
float InternalCalls::GetScaleX(std::string const& _entityName, std::string const& _sceneName) {
	return FUNC->GetEntity(_entityName, _sceneName).GetComponent<Transform>().scale.x;
}

/*!*****************************************************************************
\brief
Set rotation of an entity.
*******************************************************************************/
void InternalCalls::SetRotate(std::string const& _entityName, std::string const& _sceneName, float _rotate) {
	FUNC->GetEntity(_entityName, _sceneName).GetComponent<Transform>().rotation = _rotate;
}

/*!*****************************************************************************
\brief
Get rotation of an entity.
*******************************************************************************/
float InternalCalls::GetRotate(std::string const& _entityName, std::string const& _sceneName) {
	return FUNC->GetEntity(_entityName, _sceneName).GetComponent<Transform>().rotation;
}
