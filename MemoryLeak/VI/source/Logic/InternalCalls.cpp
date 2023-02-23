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

/*!*****************************************************************************
\brief
Test internal function for string.
*******************************************************************************/
void InternalCalls::TestArgString(MonoString* _thingToPrint) {
	std::cout << "TestArgString: " << mono_string_to_utf8(_thingToPrint) << "\n";
}
MonoString* InternalCalls::TestReturnString() {
	std::cout << "Calling internal call TestReturnString() success!\n";
	return mono_string_new(mono_domain_get(), "Hello from TestReturnString()!");
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
Checks for the state of certain key
\param STATE
- State of the key pressed
\param KEY
- Key to check the state of
\return bool
- Returns true if inputted state matches current state of specified key
*******************************************************************************/
bool InternalCalls::iInput::CheckKey(E_STATE _state, E_KEY _key) {
	return Input::CheckKey(_state, _key);
}
bool InternalCalls::iInput::iKey::Press(int _key) {
	return Input::CheckKey(E_STATE::PRESS, (E_KEY)_key);
}
bool InternalCalls::iInput::iKey::Hold(int _key) {
	return Input::CheckKey(E_STATE::HOLD, (E_KEY)_key);
}
bool InternalCalls::iInput::iKey::Release(int _key) {
	return Input::CheckKey(E_STATE::RELEASE, (E_KEY)_key);
}
bool InternalCalls::iInput::iKey::Idle(int _key) {
	return Input::CheckKey(E_STATE::NOTPRESS, (E_KEY)_key);
}

/*!*****************************************************************************
\brief
This is for checking button activity.
*******************************************************************************/
bool InternalCalls::iInput::iButton::Clicked(const Entity& _e) {
	return _e.GetComponent<Button>().isClick;
}
bool InternalCalls::iInput::iButton::Clicked(const int _eId) {
	return VI::iInput::iButton::Clicked(Entity(_eId));
}
bool InternalCalls::iInput::iButton::Clicked(std::string const& _entityName, std::string const& _sceneName) {
	return VI::iInput::iButton::Clicked(VI::iEntity::GetEntity(_entityName, _sceneName));
}
bool InternalCalls::iInput::iButton::Released(const Entity& _e) {
	return _e.GetComponent<Button>().activated;
}
bool InternalCalls::iInput::iButton::Released(const int _eId) {
	return VI::iInput::iButton::Released(Entity(_eId));
}
bool InternalCalls::iInput::iButton::Released(std::string const& _entityName, std::string const& _sceneName) {
	return VI::iInput::iButton::Released(VI::iEntity::GetEntity(_entityName, _sceneName));
}
bool InternalCalls::iInput::iButton::Hover(const Entity& _e) {
	return _e.GetComponent<Button>().isHover;
}
bool InternalCalls::iInput::iButton::Hover(const int _eId) {
	return VI::iInput::iButton::Hover(Entity(_eId));
}
bool InternalCalls::iInput::iButton::Hover(std::string const& _entityName, std::string const& _sceneName) {
	return VI::iInput::iButton::Hover(VI::iEntity::GetEntity(_entityName, _sceneName));
}

/*!*****************************************************************************
\brief
Get world mouse position.
*******************************************************************************/
Math::Vec2 InternalCalls::iInput::iMouse::GetWorldPos() {
#ifdef _EDITOR
	return editorManager->GetEditorWorldMousePos();
#else 
	Math::Vec2 cursorPos = Math::Vec2(Input::CursorPos().x, -Input::CursorPos().y) + Math::Vec2(-Helper::GetScreenWidth() / 2.f, Helper::GetScreenHeight() / 2.f);
	//if (Input::CheckKey(PRESS, M_BUTTON_L)) std::cout << "cursorPos: " << cursorPos << '\n';
	return cursorPos;
#endif 
}
float InternalCalls::iInput::iMouse::GetWorldPosX() {
	return VI::iInput::iMouse::GetWorldPos().x;
}
float InternalCalls::iInput::iMouse::GetWorldPosY() {
	return VI::iInput::iMouse::GetWorldPos().y;
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
void InternalCalls::iPhysics::ApplyImpulse(const Entity& _e, const Math::Vec2& _impulse, const Math::Vec2& _rotation) {
	physics2DManager->ApplyImpulse(_e, _impulse, _rotation);
}
void InternalCalls::iPhysics::ApplyImpulse(const int _eId, const float _impulseX, const float _impulseY, const float _rotationX, const float _rotationY) {
	Math::Vec2 impulse = { _impulseX, _impulseY };
	Math::Vec2 rotate = { _rotationX, _rotationY };
	VI::iPhysics::ApplyImpulse(Entity(_eId), impulse, rotate);
}
void InternalCalls::iPhysics::ApplyImpulse(std::string const& _entityName, std::string const& _sceneName, const float _impulseX, const float _impulseY, const float _rotationX, const float _rotationY) {
	Math::Vec2 impulse = { _impulseX, _impulseY };
	Math::Vec2 rotate = { _rotationX, _rotationY };
	VI::iPhysics::ApplyImpulse(VI::iEntity::GetEntity(_entityName, _sceneName), impulse, rotate);
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
bool InternalCalls::iPhysics::EntitiesCollided(const Entity& _e1, const Entity& _e2) {
	return collision2DManager->EntitiesCollided(_e1, _e2);
}
bool InternalCalls::iPhysics::EntitiesCollided(const int _eId1, const int _eId2) {
	return VI::iPhysics::EntitiesCollided(Entity(_eId1), Entity(_eId2));
}
bool InternalCalls::iPhysics::EntitiesCollided(std::string const& _entityName1, std::string const& _entityName2, std::string const& _sceneName) {
	return VI::iPhysics::EntitiesCollided(VI::iEntity::GetEntity(_entityName1, _sceneName), VI::iEntity::GetEntity(_entityName2, _sceneName));
}
bool InternalCalls::iPhysics::CheckCollision(const Entity& _e1, const Entity& _e2, bool const& _dynamicCheck) {
	return collision2DManager->CheckCollision(_e1, _e2, _dynamicCheck);
}
bool InternalCalls::iPhysics::CheckCollision(const int _eId1, const int _eId2, bool const& _dynamicCheck) {
	return VI::iPhysics::CheckCollision(Entity(_eId1), Entity(_eId2), _dynamicCheck);
}
bool InternalCalls::iPhysics::CheckCollision(std::string const& _entityName1, std::string const& _entityName2, std::string const& _sceneName, bool const& _dynamicCheck) {
	return VI::iPhysics::CheckCollision(VI::iEntity::GetEntity(_entityName1, _sceneName), VI::iEntity::GetEntity(_entityName2, _sceneName), _dynamicCheck);
}

/*!*****************************************************************************
\brief
	Loads the dialogs from a json file to the dialog manager

\return
None.
*******************************************************************************/
void InternalCalls::iDialogue::LoadScript(std::string _filename) {
	LOG_INFO("Loading Dialogue File: " + _filename);
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
std::string InternalCalls::iDialogue::GetLine(int _id) {
	return dialogManager->GetLine(_id);
}

/*!*****************************************************************************
\brief
Retrieves the next dialog id using function from DialogManager.

\param int _id
The id of the current dialog.

\return
Returns the next dialog id.
*******************************************************************************/
int InternalCalls::iDialogue::GetNextId(int _id) {
	return dialogManager->GetNext(_id);
}
std::string InternalCalls::iDialogue::GetNext(int _id) {
	return dialogManager->GetLine(dialogManager->GetNext(_id));
}

/*!*****************************************************************************
\brief
Checks if/Get the dialog with a specific id has choices using function from
DialogManager.

\param int _id
The id of the dialog to be checked.

\return
Returns true if the dialog has choices else returns false.
*******************************************************************************/
bool InternalCalls::iDialogue::HaveChoices(int _id) {
	return dialogManager->HaveChoices(_id);
}
std::pair<int, int> InternalCalls::iDialogue::GetChoices(int _id) {
	return dialogManager->GetChoices(_id);
}
int InternalCalls::iDialogue::GetChoice1(int _id) {
	return dialogManager->GetNext(_id);
}
int InternalCalls::iDialogue::GetChoice2(int _id) {
	return dialogManager->GetNext2(_id);
}

/*!*****************************************************************************
\brief
Set/Get the selected choice using function from DialogManager.

\param int _id
The id of the current dialog.

\param int _selectedChoice
The selected choice.
*******************************************************************************/
void InternalCalls::iDialogue::SetSelectedChoice(int _selectedChoice) {
	dialogManager->SetSelectedChoice(VI::iDialogue::GetCurrentId(), _selectedChoice);
}
int InternalCalls::iDialogue::GetSelectedChoice(int _id) {
	return dialogManager->GetSelectedChoice(_id);
}
int InternalCalls::iDialogue::GetCurrentSelectedChoice() {
	return dialogManager->GetSelectedChoice(VI::iDialogue::GetCurrentId());
}

/*!*****************************************************************************
\brief
Get/Set current dialogue id using function from DialogManager.

\param int _id
The id of the current dialog.
*******************************************************************************/
bool InternalCalls::iDialogue::SetCurrentId(int _id) {
	return dialogManager->SetCurrentDialogueID(_id);
}
int InternalCalls::iDialogue::GetCurrentId() {
	return dialogManager->GetCurrentDialogueID();
}

/*!*****************************************************************************
\brief
Returns true if speaker is player using function from DialogManager.

\param int _id
The id of the current dialog.
*******************************************************************************/
bool InternalCalls::iDialogue::IsPlayerSpeaker(int _id) {
	return dialogManager->GetSpeaker(_id);
}

/*!*****************************************************************************
\brief
This function is called by user, to change the next game state
*******************************************************************************/
void InternalCalls::iGameState::ChangeGameState(std::string const& _name) {
	GameStateManager::GetInstance()->ChangeGameState(_name);
}

/*!*****************************************************************************
\brief
Get current game state
*******************************************************************************/
GameState& InternalCalls::iGameState::CurrentGameState() {
	return *GameStateManager::GetInstance()->mCurrentGameState;
}
std::string InternalCalls::iGameState::GetCurrentGameStateName() {
	return GameStateManager::GetInstance()->mCurrentGameState->mName;
}

/*!*****************************************************************************
\brief
Exits the game.
*******************************************************************************/
void InternalCalls::iGameState::GameStateExit() {
#ifdef _EDITOR
	editorManager->SetScenePaused(true);
	editorManager->SetFullScreen(false);
#else
	GameStateManager::GetInstance()->GameStateExit();
#endif // _EDITOR
}

/*!*****************************************************************************
\brief
Gets entity id.
*******************************************************************************/
int InternalCalls::iEntity::GetId(const Entity& _e) {
	return _e.id;
}
int InternalCalls::iEntity::GetId(std::string _entityName, std::string _sceneName) {
	return GameStateManager::GetInstance()->GetEntity(_entityName, _sceneName).id;
}

/*!*****************************************************************************
\brief
Gets an entity.
*******************************************************************************/
Entity InternalCalls::iEntity::GetEntity(const int _eId) {
	return Entity(_eId);
}
Entity InternalCalls::iEntity::GetEntity(std::string const& _entityName, std::string const& _sceneName) {
	return GameStateManager::GetInstance()->GetEntity(_entityName, _sceneName);
}

/*!*****************************************************************************
\brief
Checks if/Sets an entity is active.
*******************************************************************************/
bool InternalCalls::iEntity::IsActive(const Entity& _e) {
	return _e.GetComponent<General>().isActive;
}
bool InternalCalls::iEntity::IsActive(const int _eId) {
	return VI::iEntity::IsActive(Entity(_eId));
}
bool InternalCalls::iEntity::IsActive(std::string const& _entityName, std::string const& _sceneName) {
	return VI::iEntity::IsActive(VI::iEntity::GetEntity(_entityName, _sceneName));
}

void InternalCalls::iEntity::SetIsActive(const Entity& _e, bool _active) {
	_e.GetComponent<General>().isActive = _active;
}
void InternalCalls::iEntity::SetIsActive(const int _eId, bool _active) {
	VI::iEntity::SetIsActive(Entity(_eId), _active);
}
void InternalCalls::iEntity::SetIsActive(std::string const& _entityName, std::string const& _sceneName, bool _active) {
	VI::iEntity::SetIsActive(VI::iEntity::GetEntity(_entityName, _sceneName), _active);
}

/*!*****************************************************************************
\brief
Activate/Deactivate an entity from scene.
*******************************************************************************/
void InternalCalls::iEntity::Activate(const Entity& _e) {
	_e.Activate();
}
void InternalCalls::iEntity::Activate(const int _eId) {
	VI::iEntity::Activate(Entity(_eId));
}
void InternalCalls::iEntity::Activate(std::string const& _entityName, std::string const& _sceneName) {
	VI::iEntity::Activate(VI::iEntity::GetEntity(_entityName, _sceneName));
}

void InternalCalls::iEntity::Deactivate(const Entity& _e) {
	_e.Deactivate();
}
void InternalCalls::iEntity::Deactivate(const int _eId) {
	VI::iEntity::Deactivate(Entity(_eId));
}
void InternalCalls::iEntity::Deactivate(std::string const& _entityName, std::string const& _sceneName) {
	VI::iEntity::Deactivate(VI::iEntity::GetEntity(_entityName, _sceneName));
}

/*!*****************************************************************************
\brief
Gets parent name/id of an entity from scene.
*******************************************************************************/
std::string InternalCalls::iEntity::GetParent(const Entity& _e) {
	return _e.GetComponent<General>().parent.GetComponent<General>().name;
}
std::string InternalCalls::iEntity::GetParent(const int _eId) {
	return VI::iEntity::GetParent(Entity(_eId));
}
std::string InternalCalls::iEntity::GetParent(std::string const& _entityName, std::string const& _sceneName) {
	return VI::iEntity::GetParent(VI::iEntity::GetEntity(_entityName, _sceneName));
}

int InternalCalls::iEntity::GetParentId(const Entity& _e) {
	return _e.GetComponent<General>().parent.id;
}
int InternalCalls::iEntity::GetParentId(const int _eId) {
	return VI::iEntity::GetParentId(Entity(_eId));
}
int InternalCalls::iEntity::GetParentId(std::string const& _entityName, std::string const& _sceneName) {
	return VI::iEntity::GetParentId(VI::iEntity::GetEntity(_entityName, _sceneName));
}

/*!*****************************************************************************
\brief
Gets scene to pause or unpause the scene.
*******************************************************************************/
Scene& InternalCalls::iScene::Select(std::string const& _name) {
	return GameStateManager::GetInstance()->SelectScene(_name);
}
void InternalCalls::iScene::Pause(std::string const& _name) {
	GameStateManager::GetInstance()->SelectScene(_name).Pause(true);
}
void InternalCalls::iScene::Play(std::string const& _name) {
	GameStateManager::GetInstance()->SelectScene(_name).Pause(false);
}

/*!*****************************************************************************
\brief
Get/Set current game state's camera
*******************************************************************************/
Transform& InternalCalls::iCamera::CurrentCamera() {
	return VI::iGameState::CurrentGameState().mCamera;
}
float InternalCalls::iCamera::GetScaleX() {
	return VI::iGameState::CurrentGameState().mCamera.scale.x;
}
float InternalCalls::iCamera::GetScaleY() {
	return VI::iGameState::CurrentGameState().mCamera.scale.y;
}
float InternalCalls::iCamera::GetPosX() {
	return VI::iGameState::CurrentGameState().mCamera.translation.x;
}
float InternalCalls::iCamera::GetPosY() {
	return VI::iGameState::CurrentGameState().mCamera.translation.y;
}
void InternalCalls::iCamera::SetScaleX(float _x) {
	VI::iGameState::CurrentGameState().mCamera.scale.x = _x;
}
void InternalCalls::iCamera::SetScaleY(float _y) {
	VI::iGameState::CurrentGameState().mCamera.scale.y = _y;
}
void InternalCalls::iCamera::SetPosX(float _x) {
	VI::iGameState::CurrentGameState().mCamera.translation.x = _x;
}
void InternalCalls::iCamera::SetPosY(float _y) {
	VI::iGameState::CurrentGameState().mCamera.translation.y = _y;
}

/*!*****************************************************************************
\brief
	Math vector functions
*******************************************************************************/
float InternalCalls::iMath::SqMagnitude(float _x, float _y) {
	Math::Vec2 temp = { _x, _y };
	return temp.SqMagnitude();
}
float InternalCalls::iMath::NormalizeX(float _x, float _y) {
	Math::Vec2 temp = { _x, _y };
	return temp.Normalize().x;
}
float InternalCalls::iMath::NormalizeY(float _x, float _y) {
	Math::Vec2 temp = { _x, _y };
	return temp.Normalize().y;
}
float InternalCalls::iMath::ArcTangent(float _x, float _y) {
	return atan2f(_x, _y);
}
float InternalCalls::iMath::Negate(float _value) {
	return (_value < 0 ? -_value : _value);
}

/*!*****************************************************************************
\brief
Set/Get current animation image speed
*******************************************************************************/
void InternalCalls::iAnimation::SetSpeed(const Entity& _e, float _speed) {
	_e.GetComponent<SheetAnimation>().timePerFrame = _speed;
}
float InternalCalls::iAnimation::GetSpeed(const Entity& _e) {
	return _e.GetComponent<SheetAnimation>().timePerFrame;
}
void InternalCalls::iAnimation::SetSpeed(const int _eId, float _speed) {
	VI::iAnimation::SetSpeed(Entity(_eId), _speed);
}
float InternalCalls::iAnimation::GetSpeed(const int _eId) {
	return VI::iAnimation::GetSpeed(Entity(_eId));
}
void InternalCalls::iAnimation::SetSpeed(std::string const& _entityName, std::string const& _sceneName, float _speed) {
	VI::iAnimation::SetSpeed(VI::iEntity::GetEntity(_entityName, _sceneName), _speed);
}
float InternalCalls::iAnimation::GetSpeed(std::string const& _entityName, std::string const& _sceneName) {
	return VI::iAnimation::GetSpeed(VI::iEntity::GetEntity(_entityName, _sceneName));
}

/*!*****************************************************************************
\brief
Set/Get current sprite sheet image index
*******************************************************************************/
void InternalCalls::iAnimation::SetSheetIndex(const Entity& _e, int _index) {
	animator->SetCurrentImageIndex(_e, _index);
}
int InternalCalls::iAnimation::GetSheetIndex(const Entity& _e) {
	return animator->GetCurrentImageIndex(_e);
}
void InternalCalls::iAnimation::SetSheetIndex(const int _eId, int _index) {
	VI::iAnimation::SetSheetIndex(Entity(_eId), _index);
}
int InternalCalls::iAnimation::GetSheetIndex(const int _eId) {
	return VI::iAnimation::GetSheetIndex(Entity(_eId));
}
void InternalCalls::iAnimation::SetSheetIndex(std::string const& _entityName, std::string const& _sceneName, int _index) {
	VI::iAnimation::SetSheetIndex((VI::iEntity::GetEntity(_entityName, _sceneName)), _index);
}
int InternalCalls::iAnimation::GetSheetIndex(std::string const& _entityName, std::string const& _sceneName) {
	return VI::iAnimation::GetSheetIndex(VI::iEntity::GetEntity(_entityName, _sceneName));
}

/*!*****************************************************************************
\brief
Set current animation image index
*******************************************************************************/
void InternalCalls::iAnimation::SetCurrentFrame(const Entity& _e, int _index) {
	_e.GetComponent<SheetAnimation>().currFrameIndex = _index;
}
int InternalCalls::iAnimation::GetCurrentFrame(const Entity& _e) {
	return _e.GetComponent<SheetAnimation>().currFrameIndex;
}
void InternalCalls::iAnimation::SetCurrentFrame(const int _eId, int _index) {
	VI::iAnimation::SetCurrentFrame(Entity(_eId), _index);
}
int InternalCalls::iAnimation::GetCurrentFrame(const int _eId) {
	return VI::iAnimation::GetCurrentFrame(Entity(_eId));
}
void InternalCalls::iAnimation::SetCurrentFrame(std::string const& _entityName, std::string const& _sceneName, int _index) {
	VI::iAnimation::SetCurrentFrame(VI::iEntity::GetEntity(_entityName, _sceneName), _index);
}
int InternalCalls::iAnimation::GetCurrentFrame(std::string const& _entityName, std::string const& _sceneName) {
	return VI::iAnimation::GetCurrentFrame(VI::iEntity::GetEntity(_entityName, _sceneName));
}

/*!*****************************************************************************
\brief
Get/Set current animation total frame count
*******************************************************************************/
void InternalCalls::iAnimation::SetFrameCount(const Entity& _e, int _count) {
	_e.GetComponent<SheetAnimation>().frameCount = _count;
}
int InternalCalls::iAnimation::GetFrameCount(const Entity& _e) {
	return _e.GetComponent<SheetAnimation>().frameCount;
}
void InternalCalls::iAnimation::SetFrameCount(const int _eId, int _count) {
	VI::iAnimation::SetFrameCount(Entity(_eId), _count);
}
int InternalCalls::iAnimation::GetFrameCount(const int _eId) {
	return VI::iAnimation::GetFrameCount(Entity(_eId));
}
void InternalCalls::iAnimation::SetFrameCount(std::string const& _entityName, std::string const& _sceneName, int _count) {
	VI::iAnimation::SetFrameCount(VI::iEntity::GetEntity(_entityName, _sceneName), _count);
}
int InternalCalls::iAnimation::GetFrameCount(std::string const& _entityName, std::string const& _sceneName) {
	return VI::iAnimation::GetFrameCount(VI::iEntity::GetEntity(_entityName, _sceneName));
}

/*!*****************************************************************************
\brief
Movement animation
*******************************************************************************/
void InternalCalls::iAnimation::Start(int _eId) {
	movementAIManager->StartAnimation(Entity(_eId));
}
bool InternalCalls::iAnimation::SetNext(int _eId, int _i) { // return true if successful (withing 0 to the vector MAX)
	return movementAIManager->SetNextStep(Entity(_eId), _i);
}
void InternalCalls::iAnimation::Stop(int _eId, bool _next) {
	movementAIManager->StopAfterThisAnimation(Entity(_eId), _next);
}
void InternalCalls::iAnimation::StopAfterEndLoop(int _eId, bool _loop) {
	movementAIManager->StopAfterEndofAnimationLoop(Entity(_eId), _loop);
}
void InternalCalls::iAnimation::ReverseOrder(int _eId, bool _reverse) {
	movementAIManager->ReverseOrderAfterNextAnimation(Entity(_eId), _reverse);
}
void InternalCalls::iAnimation::SetLoopCycle(int _eId, bool _cycle) {
	movementAIManager->SetAnimationLoopToCycle(Entity(_eId), _cycle);
}
void InternalCalls::iAnimation::AddTransform(int _eId, float _scaleX, float _scaleY, float _rot, float _posX, float _posY, float _time) {
	Transform trans{ {_scaleX, _scaleY}, _rot, { _posX, _posY} };
	movementAIManager->AddTransform(Entity(_eId), trans);
}
void InternalCalls::iAnimation::AddTransformDifference(int _eId, float _scaleX, float _scaleY, float _rot, float _posX, float _posY, float _time) {
	Transform trans{ {_scaleX, _scaleY}, _rot, { _posX, _posY} };
	movementAIManager->AddTransformDifference(Entity(_eId), trans);
}
void InternalCalls::iAnimation::SetCalculatedTimeFromPosition(int _eId, float _posX, float _posY, int _step) {
	movementAIManager->SetCalculatedTimeFromPosition(Entity(_eId), { _posX, _posY }, _step);
}
void InternalCalls::iAnimation::SetCalculatedTimeFromRotation(int _eId, float _rot, int _step) {
	movementAIManager->SetCalculatedTimeFromRotation(Entity(_eId), _rot, _step);
}
void InternalCalls::iAnimation::SetCalculatedTimeFromScale(int _eId, float _scaleX, float _scaleY, int _step) {
	movementAIManager->SetCalculatedTimeFromScale(Entity(_eId), { _scaleX, _scaleY }, _step);
}

/*!*****************************************************************************
\brief
Set/Get the texture of an entity.
*******************************************************************************/
void InternalCalls::iTexture::SetTexture(const Entity& _e, const std::string& _path) {
	spriteManager->SetTexture(_e, _path);
}
std::string InternalCalls::iTexture::GetTexture(const Entity& _e) {
	return spriteManager->GetTexturePath(spriteManager->GetTexture(_e));
}
void InternalCalls::iTexture::SetTexture(const int _eId, const std::string& _path) {
	VI::iTexture::SetTexture(Entity(_eId), _path);
}
std::string InternalCalls::iTexture::GetTexture(const int _eId) {
	return VI::iTexture::GetTexture(Entity(_eId));
}
void InternalCalls::iTexture::SetTexture(std::string const& _entityName, std::string const& _sceneName, const std::string& _path) {
	VI::iTexture::SetTexture(VI::iEntity::GetEntity(_entityName, _sceneName), _path);
}
std::string InternalCalls::iTexture::GetTexture(std::string const& _entityName, std::string const& _sceneName) {
	return VI::iTexture::GetTexture(VI::iEntity::GetEntity(_entityName, _sceneName));
}

/*!*****************************************************************************
\brief
	Plays sound
*******************************************************************************/
void InternalCalls::iAudio::Play(const Entity& _e) {
	_e.GetComponent<Audio>().sound.toPlay = true;
	//(FUNC->GetEntity(_entityName, _sceneName)).GetComponent<Audio>().sound.volume = 1.f;
	//audioManager->PlaySound((FUNC->GetEntity(_entityName, _sceneName)));
}
void InternalCalls::iAudio::Play(const int _eId) {
	VI::iAudio::Play(Entity(_eId));
}
void InternalCalls::iAudio::Play(std::string const& _entityName, std::string const& _sceneName) {
	VI::iAudio::Play(VI::iEntity::GetEntity(_entityName, _sceneName));
}

/*!*****************************************************************************
\brief
	Plays a sound on loop
*******************************************************************************/
void InternalCalls::iAudio::PlayOnLoop(const Entity& _e) {
	if (_e.HasComponent<Audio>()) {
		_e.GetComponent<Audio>().sound.toPlay = true;
		_e.GetComponent<Audio>().sound.isLoop = true;
	}
}
void InternalCalls::iAudio::PlayOnLoop(const int _eId) {
	VI::iAudio::PlayOnLoop(Entity(_eId));
}
void InternalCalls::iAudio::PlayOnLoop(std::string const& _entityName, std::string const& _sceneName) {
	VI::iAudio::PlayOnLoop(VI::iEntity::GetEntity(_entityName, _sceneName));
}

/*!*****************************************************************************
\brief
   Loop functions
*******************************************************************************/
void InternalCalls::iAudio::SetLoop(const Entity& _e, bool _loop) {
	_e.GetComponent<Audio>().sound.isLoop = _loop;
}
void InternalCalls::iAudio::SetLoop(const int _eId, bool _loop) {
	VI::iAudio::SetLoop(Entity(_eId), _loop);
}
void InternalCalls::iAudio::SetLoop(std::string const& _entityName, std::string const& _sceneName, bool _loop) {
	VI::iAudio::SetLoop(VI::iEntity::GetEntity(_entityName, _sceneName), _loop);
}

/*!*****************************************************************************
\brief
	Stop a sound
*******************************************************************************/
void InternalCalls::iAudio::Stop(const Entity& _e) {
	if (_e.HasComponent<Audio>()) {
		audioManager->StopSound(_e);
		_e.GetComponent<Audio>().sound.toPlay = false;
	}
}
void InternalCalls::iAudio::Stop(const int _eId) {
	VI::iAudio::Stop(Entity(_eId));
}
void InternalCalls::iAudio::Stop(std::string const& _entityName, std::string const& _sceneName) {
	VI::iAudio::Stop(VI::iEntity::GetEntity(_entityName, _sceneName));
}

void InternalCalls::iAudio::StopAll() {
	audioManager->StopAllSound();
}
void InternalCalls::iAudio::StopBGM() {
	audioManager->StopBGMSound();
}
void InternalCalls::iAudio::StopSFX() {
	audioManager->StopSFXSound();
}

/*!*****************************************************************************
\brief
	BGM & force play
*******************************************************************************/
void InternalCalls::iAudio::PlayBGM(std::string const& _soundName) {
	audioManager->PlayBGSound(_soundName, (int)E_AUDIO_CHANNEL::MAINBACKGROUND);
}
bool InternalCalls::iAudio::IsBgmPlaying() {
	return audioManager->isPlaying((int)E_AUDIO_CHANNEL::MAINBACKGROUND);
}
void InternalCalls::iAudio::ForcePlay(std::string const& _soundName) {
	audioManager->PlayAnySound(_soundName, (int)E_AUDIO_CHANNEL::FORCEPLAY);
}

/*!*****************************************************************************
\brief
	Set volume
*******************************************************************************/
void InternalCalls::iAudio::SetAllVolume(float _vol) {
	audioManager->SetALLVolume(_vol);
}
void InternalCalls::iAudio::SetBGMVolume(float _vol) {
	audioManager->SetBGMVolume(_vol);
}
void InternalCalls::iAudio::SetSFXVolume(float _vol) {
	audioManager->SetSFXVolume(_vol);
}

/*!*****************************************************************************
\brief
Get transform of an entity.
*******************************************************************************/
Transform& InternalCalls::iTransform::GetTransform(const Entity& _e) {
	return _e.GetComponent<Transform>();
}
float InternalCalls::iTransform::GetRotation(const Entity& _e) {
	return _e.GetComponent<Transform>().rotation;
}
Math::Vec2 InternalCalls::iTransform::GetScale(const Entity& _e) {
	return _e.GetComponent<Transform>().scale;
}
Math::Vec2 InternalCalls::iTransform::GetTranslate(const Entity& _e) {
	return _e.GetComponent<Transform>().translation;
}

/*!*****************************************************************************
\brief
Get/Set pos of an entity.
*******************************************************************************/
float InternalCalls::iTransform::GetPosX(const Entity& _e) {
	return _e.GetComponent<Transform>().translation.x;
}
float InternalCalls::iTransform::GetPosY(const Entity& _e) {
	return _e.GetComponent<Transform>().translation.y;
}
void InternalCalls::iTransform::SetPosX(const Entity& _e, float _posX) {
	_e.GetComponent<Transform>().translation.x = _posX;
}
void InternalCalls::iTransform::SetPosY(const Entity& _e, float _posY) {
	_e.GetComponent<Transform>().translation.y = _posY;
}

float InternalCalls::iTransform::GetPosX(const int _eId) {
	return VI::iTransform::GetPosX(Entity(_eId));
}
float InternalCalls::iTransform::GetPosY(const int _eId) {
	return VI::iTransform::GetPosY(Entity(_eId));
}
void InternalCalls::iTransform::SetPosX(const int _eId, float _posX) {
	VI::iTransform::SetPosX(Entity(_eId), _posX);
}
void InternalCalls::iTransform::SetPosY(const int _eId, float _posY) {
	VI::iTransform::SetPosY(Entity(_eId), _posY);
}

float InternalCalls::iTransform::GetPosX(std::string const& _entityName, std::string const& _sceneName) {
	return VI::iTransform::GetPosX(VI::iEntity::GetEntity(_entityName, _sceneName));
}
float InternalCalls::iTransform::GetPosY(std::string const& _entityName, std::string const& _sceneName) {
	return VI::iTransform::GetPosY(VI::iEntity::GetEntity(_entityName, _sceneName));
}
void InternalCalls::iTransform::SetPosX(std::string const& _entityName, std::string const& _sceneName, float _posX) {
	VI::iTransform::SetPosX(VI::iEntity::GetEntity(_entityName, _sceneName), _posX);
}
void InternalCalls::iTransform::SetPosY(std::string const& _entityName, std::string const& _sceneName, float _posY) {
	VI::iTransform::SetPosY(VI::iEntity::GetEntity(_entityName, _sceneName), _posY);
}

/*!*****************************************************************************
\brief
Set/Get scale of an entity.
*******************************************************************************/
float InternalCalls::iTransform::GetScaleY(const Entity& _e) {
	return _e.GetComponent<Transform>().scale.y;
}
float InternalCalls::iTransform::GetScaleX(const Entity& _e) {
	return _e.GetComponent<Transform>().scale.x;
}
void InternalCalls::iTransform::SetScaleY(const Entity& _e, float _scaleY) {
	_e.GetComponent<Transform>().scale.y = _scaleY;
}
void InternalCalls::iTransform::SetScaleX(const Entity& _e, float _scaleX) {
	_e.GetComponent<Transform>().scale.x = _scaleX;
}

float InternalCalls::iTransform::GetScaleY(const int _eId) {
	return VI::iTransform::GetScaleY(Entity(_eId));
}
float InternalCalls::iTransform::GetScaleX(const int _eId) {
	return VI::iTransform::GetScaleX(Entity(_eId));
}
void InternalCalls::iTransform::SetScaleY(const int _eId, float _scaleY) {
	VI::iTransform::SetScaleY(Entity(_eId), _scaleY);
}
void InternalCalls::iTransform::SetScaleX(const int _eId, float _scaleX) {
	VI::iTransform::SetScaleX(Entity(_eId), _scaleX);
}

float InternalCalls::iTransform::GetScaleY(std::string const& _entityName, std::string const& _sceneName) {
	return VI::iTransform::GetScaleY(VI::iEntity::GetEntity(_entityName, _sceneName));
}
float InternalCalls::iTransform::GetScaleX(std::string const& _entityName, std::string const& _sceneName) {
	return VI::iTransform::GetScaleX(VI::iEntity::GetEntity(_entityName, _sceneName));
}
void InternalCalls::iTransform::SetScaleY(std::string const& _entityName, std::string const& _sceneName, float _scaleY) {
	VI::iTransform::SetScaleY(VI::iEntity::GetEntity(_entityName, _sceneName), _scaleY);
}
void InternalCalls::iTransform::SetScaleX(std::string const& _entityName, std::string const& _sceneName, float _scaleX) {
	VI::iTransform::SetScaleX(VI::iEntity::GetEntity(_entityName, _sceneName), _scaleX);
}

/*!*****************************************************************************
\brief
Set/Get rotation of an entity.
*******************************************************************************/
float InternalCalls::iTransform::GetRotate(const Entity& _e) {
	return _e.GetComponent<Transform>().rotation;
}
void InternalCalls::iTransform::SetRotate(const Entity& _e, float _rotate) {
	_e.GetComponent<Transform>().rotation = _rotate;
}

float InternalCalls::iTransform::GetRotate(const int _eId) {
	return VI::iTransform::GetRotate(Entity(_eId));
}
void InternalCalls::iTransform::SetRotate(const int _eId, float _rotate) {
	VI::iTransform::SetRotate(Entity(_eId), _rotate);
}

float InternalCalls::iTransform::GetRotate(std::string const& _entityName, std::string const& _sceneName) {
	return VI::iTransform::GetRotate(VI::iEntity::GetEntity(_entityName, _sceneName));
}
void InternalCalls::iTransform::SetRotate(std::string const& _entityName, std::string const& _sceneName, float _rotate) {
	VI::iTransform::SetRotate(VI::iEntity::GetEntity(_entityName, _sceneName), _rotate);
}

/*!*****************************************************************************
\brief
Changing text component text.
*******************************************************************************/
void InternalCalls::iText::UpdateText(const Entity& _e, std::string const& _text) {
	_e.GetComponent<Text>().text = _text;
}
void InternalCalls::iText::UpdateText(const int _eId, std::string const& _text) {
	VI::iText::UpdateText(Entity(_eId), _text);
}
void InternalCalls::iText::UpdateText(std::string const& _entityName, std::string const& _sceneName, std::string const& _text) {
	VI::iText::UpdateText(VI::iEntity::GetEntity(_entityName, _sceneName), _text);
}

void InternalCalls::iText::SetOffset(const Entity& _e, float _xoffset, float _yoffset) {
	_e.GetComponent<Text>().offset = Math::Vec2(_xoffset, _yoffset);
}
void InternalCalls::iText::SetOffset(const int _eId, float _xoffset, float _yoffset) {
	VI::iText::SetOffset(Entity(_eId), _xoffset, _yoffset);
}
void InternalCalls::iText::SetOffset(std::string const& _entityName, std::string const& _sceneName, float _xoffset, float _yoffset) {
	VI::iText::SetOffset(VI::iEntity::GetEntity(_entityName, _sceneName), _xoffset, _yoffset);
}

float InternalCalls::iText::GetOffsetX(const Entity& _e) {
	return _e.GetComponent<Text>().offset.x;
}
float InternalCalls::iText::GetOffsetX(const int _eId) {
	return VI::iText::GetOffsetX(Entity(_eId));
}
float InternalCalls::iText::GetOffsetX(std::string const& _entityName, std::string const& _sceneName) {
	return VI::iText::GetOffsetX(VI::iEntity::GetEntity(_entityName, _sceneName));
}

float InternalCalls::iText::GetOffsetY(const Entity& _e) {
	return _e.GetComponent<Text>().offset.y;
}
float InternalCalls::iText::GetOffsetY(const int _eId) {
	return VI::iText::GetOffsetX(Entity(_eId));
}
float InternalCalls::iText::GetOffsetY(std::string const& _entityName, std::string const& _sceneName) {
	return VI::iText::GetOffsetX(VI::iEntity::GetEntity(_entityName, _sceneName));
}

int InternalCalls::iText::GetLineCount(const Entity& _e) {
	return renderManager->GetTextLines(_e);
}
int InternalCalls::iText::GetLineCount(const int _eId) {
	return VI::iText::GetLineCount(Entity(_eId));
}
int InternalCalls::iText::GetLineCount(std::string const& _entityName, std::string const& _sceneName) {
	return VI::iText::GetLineCount(VI::iEntity::GetEntity(_entityName, _sceneName));
}

float InternalCalls::iText::GetScale(const Entity& _e) {
	if (!_e.HasComponent<Text>()) return -1.f;
	return _e.GetComponent<Text>().scale;
}
float InternalCalls::iText::GetScale(const int _eId) {
	return VI::iText::GetScale(Entity(_eId));
}
float InternalCalls::iText::GetScale(std::string const& _entityName, std::string const& _sceneName) {
	return VI::iText::GetScale(VI::iEntity::GetEntity(_entityName, _sceneName));
}

void InternalCalls::iText::SetScale(const Entity& _e, float _scale) {
	_e.GetComponent<Text>().scale = _scale;
}
void InternalCalls::iText::SetScale(const int _eId, float _scale) {
	VI::iText::SetScale(Entity(_eId), _scale);
}
void InternalCalls::iText::SetScale(std::string const& _entityName, std::string const& _sceneName, float _scale) {
	VI::iText::SetScale(VI::iEntity::GetEntity(_entityName, _sceneName), _scale);
}

/*!*****************************************************************************
\brief
Weather functions.
*******************************************************************************/
void InternalCalls::iWeather::WeatherInit(float _width, float _height) {
	aiManager->weatherAIinit(_width, _height);
}
int InternalCalls::iWeather::GetCurrentWeather(int _index, float _posX, float _posY) {
	return aiManager->GetCurrentWeather(_index, _posX, _posY);
}

/*!*****************************************************************************
\brief
Changing lightsource component.
*******************************************************************************/
float InternalCalls::iLightSource::GetRadius(const Entity& _e) {
	if (!_e.HasComponent<LightSource>())
		return -1.f;
	return _e.GetComponent<LightSource>().radius;
}
float InternalCalls::iLightSource::GetRadius(const int _eId) {
	return VI::iLightSource::GetRadius(Entity(_eId));
}
float InternalCalls::iLightSource::GetRadius(std::string const& _entityName, std::string const& _sceneName) {
	return VI::iLightSource::GetRadius(VI::iEntity::GetEntity(_entityName, _sceneName));
}

void InternalCalls::iLightSource::SetRadius(const Entity& _e, float _radius) {
	if (!_e.HasComponent<LightSource>())
		return;
	_e.GetComponent<LightSource>().radius = _radius;
}
void InternalCalls::iLightSource::SetRadius(const int _eId, float _radius) {
	VI::iLightSource::SetRadius(Entity(_eId), _radius);
}
void InternalCalls::iLightSource::SetRadius(std::string const& _entityName, std::string const& _sceneName, float _radius) {
	VI::iLightSource::SetRadius(VI::iEntity::GetEntity(_entityName, _sceneName), _radius);
}

/*!*****************************************************************************
\brief
Changing sprite component.
*******************************************************************************/
void InternalCalls::iLightSource::SetSpriteColor(const Entity& _e, int _r, int _g, int _b, int _a) {
	if (!_e.HasComponent<Sprite>())
		return;
	Color clr{ (GLubyte)_r, (GLubyte)_g, (GLubyte)_b, (GLubyte)_a};
	_e.GetComponent<Sprite>().color = clr;
}
void InternalCalls::iLightSource::SetSpriteColor(const int _eId, int _r, int _g, int _b, int _a) {
	VI::iLightSource::SetSpriteColor(Entity(_eId), _r, _g, _b, _a);
}
void InternalCalls::iLightSource::SetSpriteColor(std::string const& _entityName, std::string const& _sceneName, int _r, int _g, int _b, int _a) {
	VI::iLightSource::SetSpriteColor(VI::iEntity::GetEntity(_entityName, _sceneName), _r, _g, _b, _a);
}
