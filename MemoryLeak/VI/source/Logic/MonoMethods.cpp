/*!*****************************************************************************
\file MonoMethods.h
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 04-01-2023
\brief
This file contains the function declarations of the class MonoMethods.
MonoMethods are where all the mono internal calls functions that scripts need
to use from the engine is being linked.
*******************************************************************************/

#include "MonoMethods.h"

/*!*****************************************************************************
\brief
MonoString conversion methods.
*******************************************************************************/
std::string MonoMethods::ConvertFromMonoString(MonoString* _string) {
	return mono_string_to_utf8(_string);
}
MonoString* MonoMethods::ConvertToMonoString(std::string _string) {
	return mono_string_new(mono_domain_get(), _string.c_str());
}

/*!*****************************************************************************
\brief
Internal Call functions that uses MonoString or needs overloading.
*******************************************************************************/
// Input
bool MonoMethods::iInput::iButton::s_Clicked(MonoString* _entityName, MonoString* _sceneName) {
	return VI::iInput::iButton::Clicked(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName));
}
bool MonoMethods::iInput::iButton::s_Released(MonoString* _entityName, MonoString* _sceneName) {
	return VI::iInput::iButton::Released(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName));
}
bool MonoMethods::iInput::iButton::s_Hover(MonoString* _entityName, MonoString* _sceneName) {
	return VI::iInput::iButton::Hover(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName));
}
bool MonoMethods::iInput::iButton::Clicked(const int _eId) {
	return VI::iInput::iButton::Clicked(_eId);
}
bool MonoMethods::iInput::iButton::Released(const int _eId) {
	return VI::iInput::iButton::Released(_eId);
}
bool MonoMethods::iInput::iButton::Hover(const int _eId) {
	return VI::iInput::iButton::Hover(_eId);
}

// Physics
void MonoMethods::iPhysics::s_ApplyImpulse(MonoString* _entityName, MonoString* _sceneName, const float _impulseX, const float _impulseY, const float _rotationX, const float _rotationY) {
	VI::iPhysics::ApplyImpulse(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName), _impulseX, _impulseY, _rotationX, _rotationY);
}
void MonoMethods::iPhysics::ApplyImpulse(const int _eId, const float _impulseX, const float _impulseY, const float _rotationX, const float _rotationY) {
	VI::iPhysics::ApplyImpulse(_eId, _impulseX, _impulseY, _rotationX, _rotationY);
}
bool MonoMethods::iPhysics::s_EntitiesCollided(MonoString* _entityName1, MonoString* _entityName2, MonoString* _sceneName) {
	return VI::iPhysics::EntitiesCollided(MONO->ConvertFromMonoString(_entityName1), MONO->ConvertFromMonoString(_entityName2), MONO->ConvertFromMonoString(_sceneName));
}
bool MonoMethods::iPhysics::EntitiesCollided(const int _eId1, const int _eId2) {
	return VI::iPhysics::EntitiesCollided(_eId1, _eId2);
}
bool MonoMethods::iPhysics::s_CheckCollision(MonoString* _entityName1, MonoString* _entityName2, MonoString* _sceneName, bool _dynamicCheck) {
	return VI::iPhysics::CheckCollision(MONO->ConvertFromMonoString(_entityName1), MONO->ConvertFromMonoString(_entityName2), MONO->ConvertFromMonoString(_sceneName), _dynamicCheck);
}
bool MonoMethods::iPhysics::CheckCollision(const int _eId1, const int _eId2, bool _dynamicCheck) {
	return VI::iPhysics::CheckCollision(_eId1, _eId2, _dynamicCheck);
}

// Dialogue
void MonoMethods::iDialogue::LoadScript(MonoString* _filename) {
	VI::iDialogue::LoadScript(MONO->ConvertFromMonoString(_filename));
}
MonoString* MonoMethods::iDialogue::GetLine(int _id) {
	return MONO->ConvertToMonoString(VI::iDialogue::GetLine(_id));
}
MonoString* MonoMethods::iDialogue::GetCurrentLine() {
	return MONO->ConvertToMonoString(VI::iDialogue::GetLine(VI::iDialogue::GetCurrentId()));
}

bool MonoMethods::iDialogue::HaveChoices() {
	return VI::iDialogue::HaveChoices(VI::iDialogue::GetCurrentId());
}
bool MonoMethods::iDialogue::GetCurrentChoice1() {
	return VI::iDialogue::GetChoice1(VI::iDialogue::GetCurrentId());
}
bool MonoMethods::iDialogue::GetCurrentChoice2() {
	return VI::iDialogue::GetChoice2(VI::iDialogue::GetCurrentId());
}
bool MonoMethods::iDialogue::IsPlayerCurrentSpeaker() {
	return VI::iDialogue::IsPlayerSpeaker(VI::iDialogue::GetCurrentId());
}

int MonoMethods::iDialogue::GetNextId() {
	return VI::iDialogue::GetNextId(VI::iDialogue::GetCurrentId());
}
MonoString* MonoMethods::iDialogue::GetNext() {
	return MONO->ConvertToMonoString(VI::iDialogue::GetNext(VI::iDialogue::GetCurrentId()));
}
bool MonoMethods::iDialogue::NextHaveChoices() {
	return VI::iDialogue::HaveChoices(VIM::iDialogue::GetNextId());
}
bool MonoMethods::iDialogue::GetNextChoice1() {
	return VI::iDialogue::GetChoice1(VIM::iDialogue::GetNextId());
}
bool MonoMethods::iDialogue::GetNextChoice2() {
	return VI::iDialogue::GetChoice2(VIM::iDialogue::GetNextId());
}
bool MonoMethods::iDialogue::IsPlayerNextSpeaker() {
	return VI::iDialogue::IsPlayerSpeaker(VIM::iDialogue::GetNextId());
}

// Gamestate
void MonoMethods::iGameState::Go(MonoString* _name) {
	VI::iGameState::ChangeGameState(MONO->ConvertFromMonoString(_name));
}
MonoString* MonoMethods::iGameState::GetCurrentName() {
	return MONO->ConvertToMonoString(VI::iGameState::GetCurrentGameStateName());
}

// Entity
int MonoMethods::iEntity::GetId(MonoString* _entityName, MonoString* _sceneName) {
	return VI::iEntity::GetId(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName));
}
bool MonoMethods::iEntity::s_IsActive(MonoString* _entityName, MonoString* _sceneName) {
	return VI::iEntity::IsActive(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName));
}
void MonoMethods::iEntity::s_SetIsActive(MonoString* _entityName, MonoString* _sceneName, bool _active) {
	VI::iEntity::SetIsActive(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName), _active);
}
void MonoMethods::iEntity::s_Activate(MonoString* _entityName, MonoString* _sceneName) {
	VI::iEntity::Activate(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName));
}
void MonoMethods::iEntity::s_Deactivate(MonoString* _entityName, MonoString* _sceneName) {
	VI::iEntity::Deactivate(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName));
}
MonoString* MonoMethods::iEntity::s_GetParent(MonoString* _entityName, MonoString* _sceneName) {
	return MONO->ConvertToMonoString(VI::iEntity::GetParent(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName)));
}
int MonoMethods::iEntity::s_GetParentId(MonoString* _entityName, MonoString* _sceneName) {
	return VI::iEntity::GetParentId(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName));
}

bool MonoMethods::iEntity::IsActive(const int _id) {
	return VI::iEntity::IsActive(_id);
}
void MonoMethods::iEntity::SetIsActive(const int _id, bool _active) {
	VI::iEntity::SetIsActive(_id, _active);
}
void MonoMethods::iEntity::Activate(const int _id) {
	VI::iEntity::Activate(_id);
}
void MonoMethods::iEntity::Deactivate(const int _id) {
	VI::iEntity::Deactivate(_id);
}
MonoString* MonoMethods::iEntity::GetParent(const int _id) {
	return MONO->ConvertToMonoString(VI::iEntity::GetParent(_id));
}
int MonoMethods::iEntity::GetParentId(const int _id) {
	return VI::iEntity::GetParentId(_id);
}

// Scene
void MonoMethods::iScene::Pause(MonoString* _name) {
	VI::iScene::Pause(MONO->ConvertFromMonoString(_name));
}
void MonoMethods::iScene::Play(MonoString* _name) {
	VI::iScene::Play(MONO->ConvertFromMonoString(_name));
}

// Animation
void MonoMethods::iAnimation::s_SetSpeed(MonoString* _entityName, MonoString* _sceneName, float _speed) {
	VI::iAnimation::SetSpeed(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName), _speed);
}
float MonoMethods::iAnimation::s_GetSpeed(MonoString* _entityName, MonoString* _sceneName) {
	return VI::iAnimation::GetSpeed(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName));
}
void MonoMethods::iAnimation::s_SetCurrentFrame(MonoString* _entityName, MonoString* _sceneName, int _index) {
	VI::iAnimation::SetCurrentFrame(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName), _index);
}
int MonoMethods::iAnimation::s_GetCurrentFrame(MonoString* _entityName, MonoString* _sceneName) {
	return VI::iAnimation::GetCurrentFrame(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName));
}
int MonoMethods::iAnimation::s_GetFrameCount(MonoString* _entityName, MonoString* _sceneName) {
	return VI::iAnimation::GetFrameCount(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName));
}
void MonoMethods::iAnimation::s_SetFrameCount(MonoString* _entityName, MonoString* _sceneName, int _count) {
	return VI::iAnimation::SetFrameCount(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName), _count);
}
void MonoMethods::iAnimation::s_SetSheetIndex(MonoString* _entityName, MonoString* _sceneName, int _index) {
	VI::iAnimation::SetSheetIndex(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName), _index);
}
int MonoMethods::iAnimation::s_GetSheetIndex(MonoString* _entityName, MonoString* _sceneName) {
	return VI::iAnimation::GetSheetIndex(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName));
}

void MonoMethods::iAnimation::SetSpeed(const int _eId, float _speed) {
	VI::iAnimation::SetSpeed(_eId, _speed);
}
float MonoMethods::iAnimation::GetSpeed(const int _eId) {
	return VI::iAnimation::GetSpeed(_eId);
}
void MonoMethods::iAnimation::SetCurrentFrame(const int _eId, int _index) {
	VI::iAnimation::SetCurrentFrame(_eId, _index);
}
int MonoMethods::iAnimation::GetCurrentFrame(const int _eId) {
	return VI::iAnimation::GetCurrentFrame(_eId);
}
int MonoMethods::iAnimation::GetFrameCount(const int _eId) {
	return VI::iAnimation::GetFrameCount(_eId);
}
void MonoMethods::iAnimation::SetFrameCount(const int _eId, int _count) {
	return VI::iAnimation::SetFrameCount(_eId, _count);
}
void MonoMethods::iAnimation::SetSheetIndex(const int _eId, int _index) {
	VI::iAnimation::SetSheetIndex(_eId, _index);
}
int MonoMethods::iAnimation::GetSheetIndex(const int _eId) {
	return VI::iAnimation::GetSheetIndex(_eId);
}

// Texture
void MonoMethods::iTexture::s_SetTexture(MonoString* _entityName, MonoString* _sceneName, MonoString* _path) {
	VI::iTexture::SetTexture(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName), MONO->ConvertFromMonoString(_path));
}
MonoString* MonoMethods::iTexture::s_GetTexture(MonoString* _entityName, MonoString* _sceneName) {
	return MONO->ConvertToMonoString(VI::iTexture::GetTexture(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName)));
}

void MonoMethods::iTexture::SetTexture(const int _eId, MonoString* _path) {
	VI::iTexture::SetTexture(_eId, MONO->ConvertFromMonoString(_path));
}
MonoString* MonoMethods::iTexture::GetTexture(const int _eId) {
	return MONO->ConvertToMonoString(VI::iTexture::GetTexture(_eId));
}

// Audio
void MonoMethods::iAudio::s_Play(MonoString* _entityName, MonoString* _sceneName) {
	VI::iAudio::Play(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName));
}
void MonoMethods::iAudio::s_PlayOnLoop(MonoString* _entityName, MonoString* _sceneName) {
	VI::iAudio::PlayOnLoop(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName));
}
void MonoMethods::iAudio::s_SetLoop(MonoString* _entityName, MonoString* _sceneName, bool _loop) {
	VI::iAudio::SetLoop(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName), _loop);
}
void MonoMethods::iAudio::s_Stop(MonoString* _entityName, MonoString* _sceneName) {
	VI::iAudio::Stop(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName));
}

void MonoMethods::iAudio::Play(const int _eId) {
	VI::iAudio::Play(_eId);
}
void MonoMethods::iAudio::PlayOnLoop(const int _eId) {
	VI::iAudio::PlayOnLoop(_eId);
}
void MonoMethods::iAudio::SetLoop(const int _eId, bool _loop) {
	VI::iAudio::SetLoop(_eId, _loop);
}
void MonoMethods::iAudio::Stop(const int _eId) {
	VI::iAudio::Stop(_eId);
}

void MonoMethods::iAudio::PlayBGM(MonoString* _soundName) {
	VI::iAudio::PlayBGM(MONO->ConvertFromMonoString(_soundName));
}
bool MonoMethods::iAudio::IsBgmPlaying() {
	return VI::iAudio::IsBgmPlaying();
}
void MonoMethods::iAudio::ForcePlay(MonoString* _soundName) {
	VI::iAudio::ForcePlay(MONO->ConvertFromMonoString(_soundName));
}

// Transform
float MonoMethods::iTransform::s_GetPosX(MonoString* _entityName, MonoString* _sceneName) {
	return VI::iTransform::GetPosX(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName));
}
float MonoMethods::iTransform::s_GetPosY(MonoString* _entityName, MonoString* _sceneName) {
	return VI::iTransform::GetPosY(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName));
}
void MonoMethods::iTransform::s_SetPosX(MonoString* _entityName, MonoString* _sceneName, float _posX) {
	VI::iTransform::SetPosX(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName), _posX);
}
void MonoMethods::iTransform::s_SetPosY(MonoString* _entityName, MonoString* _sceneName, float _posY) {
	VI::iTransform::SetPosY(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName), _posY);
}
float MonoMethods::iTransform::s_GetScaleX(MonoString* _entityName, MonoString* _sceneName) {
	return VI::iTransform::GetScaleX(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName));
}
float MonoMethods::iTransform::s_GetScaleY(MonoString* _entityName, MonoString* _sceneName) {
	return VI::iTransform::GetScaleY(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName));
}
void MonoMethods::iTransform::s_SetScaleX(MonoString* _entityName, MonoString* _sceneName, float _scaleX) {
	VI::iTransform::SetScaleX(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName), _scaleX);
}
void MonoMethods::iTransform::s_SetScaleY(MonoString* _entityName, MonoString* _sceneName, float _scaleY) {
	VI::iTransform::SetScaleY(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName), _scaleY);
}
float MonoMethods::iTransform::s_GetRotate(MonoString* _entityName, MonoString* _sceneName) {
	return VI::iTransform::GetRotate(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName));
}
void MonoMethods::iTransform::s_SetRotate(MonoString* _entityName, MonoString* _sceneName, float _rotate) {
	VI::iTransform::SetRotate(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName), _rotate);
}

float MonoMethods::iTransform::GetPosX(const int _eId) {
	return VI::iTransform::GetPosX(Entity(_eId));
}
float MonoMethods::iTransform::GetPosY(const int _eId) {
	return VI::iTransform::GetPosY(Entity(_eId));
}
void MonoMethods::iTransform::SetPosX(const int _eId, float _posX) {
	VI::iTransform::SetPosX(Entity(_eId), _posX);
}
void MonoMethods::iTransform::SetPosY(const int _eId, float _posY) {
	VI::iTransform::SetPosY(Entity(_eId), _posY);
}
float MonoMethods::iTransform::GetScaleX(const int _eId) {
	return VI::iTransform::GetScaleX(Entity(_eId));
}
float MonoMethods::iTransform::GetScaleY(const int _eId) {
	return VI::iTransform::GetScaleY(Entity(_eId));
}
void MonoMethods::iTransform::SetScaleX(const int _eId, float _scaleX) {
	VI::iTransform::SetScaleX(Entity(_eId), _scaleX);
}
void MonoMethods::iTransform::SetScaleY(const int _eId, float _scaleY) {
	VI::iTransform::SetScaleY(Entity(_eId), _scaleY);
}
float MonoMethods::iTransform::GetRotate(const int _eId) {
	return VI::iTransform::GetRotate(Entity(_eId));
}
void MonoMethods::iTransform::SetRotate(const int _eId, float _rotate) {
	VI::iTransform::SetRotate(Entity(_eId), _rotate);
}

// Text
void MonoMethods::iText::s_UpdateText(MonoString* _entityName, MonoString* _sceneName, MonoString* _text) {
	VI::iText::UpdateText(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName), MONO->ConvertFromMonoString(_text));
}
void MonoMethods::iText::s_SetOffset(MonoString* _entityName, MonoString* _sceneName, float _xoffset, float _yoffset) {
	VI::iText::SetOffset(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName), _xoffset, _yoffset);
}
float MonoMethods::iText::s_GetOffsetX(MonoString* _entityName, MonoString* _sceneName) {
	return VI::iText::GetOffsetX(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName));
}
float MonoMethods::iText::s_GetOffsetY(MonoString* _entityName, MonoString* _sceneName) {
	return VI::iText::GetOffsetY(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName));
}
int MonoMethods::iText::s_GetLineCount(MonoString* _entityName, MonoString* _sceneName) {
	return VI::iText::GetLineCount(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName));
}
float MonoMethods::iText::s_GetScale(MonoString* _entityName, MonoString* _sceneName) {
	return VI::iText::GetScale(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName));
}
void MonoMethods::iText::s_SetScale(MonoString* _entityName, MonoString* _sceneName, float _scale) {
	VI::iText::SetScale(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName), _scale);
}

void MonoMethods::iText::UpdateText(const int _eId, MonoString* _text) {
	VI::iText::UpdateText(_eId, MONO->ConvertFromMonoString(_text));
}
void MonoMethods::iText::SetOffset(const int _eId, float _xoffset, float _yoffset) {
	VI::iText::SetOffset(_eId, _xoffset, _yoffset);
}
float MonoMethods::iText::GetOffsetX(const int _eId) {
	return VI::iText::GetOffsetX(_eId);
}
float MonoMethods::iText::GetOffsetY(const int _eId) {
	return VI::iText::GetOffsetY(_eId);
}
int MonoMethods::iText::GetLineCount(const int _eId) {
	return VI::iText::GetLineCount(_eId);
}
float MonoMethods::iText::GetScale(const int _eId) {
	return VI::iText::GetScale(_eId);
}
void MonoMethods::iText::SetScale(const int _eId, float _scale) {
	VI::iText::SetScale(_eId, _scale);
}

// LightSource
float MonoMethods::iLightSource::s_GetRadius(MonoString* _entityName, MonoString* _sceneName) {
	return VI::iLightSource::GetRadius(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName));
}
void  MonoMethods::iLightSource::s_SetRadius(MonoString* _entityName, MonoString* _sceneName, float _radius) {
	VI::iLightSource::SetRadius(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName), _radius);
}
void MonoMethods::iLightSource::s_SetSpriteColor(MonoString* _entityName, MonoString* _sceneName, int _r, int _g, int _b, int _a) {
	VI::iLightSource::SetSpriteColor(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName), _r, _g, _b, _a);
}

float MonoMethods::iLightSource::GetRadius(const int _eId) {
	return VI::iLightSource::GetRadius(_eId);
}
void  MonoMethods::iLightSource::SetRadius(const int _eId, float _radius) {
	VI::iLightSource::SetRadius(_eId, _radius);
}
void MonoMethods::iLightSource::SetSpriteColor(const int _eId, int _r, int _g, int _b, int _a) {
	VI::iLightSource::SetSpriteColor(_eId, _r, _g, _b, _a);
}

/*!*****************************************************************************
\brief
	Registers the internal calls for mono use.
*******************************************************************************/
void MonoMethods::RegisterCalls() {
	// Test
	mono_add_internal_call("VI.Test::ArgString", &FUNC->TestArgString);
	mono_add_internal_call("VI.Test::ReturnString", &FUNC->TestReturnString);
	mono_add_internal_call("BonVoyage.THIS::IsActive", &VIM::iEntity::IsActive);

	// General
	mono_add_internal_call("VI.General::DeltaTime", &FUNC->GetDeltaTime);

	// Inputs
	mono_add_internal_call("VI.Input/Key::Press", &VI::iInput::iKey::Press);
	mono_add_internal_call("VI.Input/Key::Hold", &VI::iInput::iKey::Hold);
	mono_add_internal_call("VI.Input/Key::Release", &VI::iInput::iKey::Release);
	mono_add_internal_call("VI.Input/Key::Idle", &VI::iInput::iKey::Idle);

	mono_add_internal_call("VI.Input/Button::s_Clicked", &VIM::iInput::iButton::s_Clicked);
	mono_add_internal_call("VI.Input/Button::s_Released", &VIM::iInput::iButton::s_Released);
	mono_add_internal_call("VI.Input/Button::s_Hover", &VIM::iInput::iButton::s_Hover);

	mono_add_internal_call("VI.Input/Button::Clicked", &VIM::iInput::iButton::Clicked);
	mono_add_internal_call("VI.Input/Button::Released", &VIM::iInput::iButton::Released);
	mono_add_internal_call("VI.Input/Button::Hover", &VIM::iInput::iButton::Hover);

	mono_add_internal_call("VI.Input/Mouse::WorldPosX", &VI::iInput::iMouse::GetWorldPosX);
	mono_add_internal_call("VI.Input/Mouse::WorldPosY", &VI::iInput::iMouse::GetWorldPosY);

	mono_add_internal_call("VI.Input/Mouse::Press", &VI::iInput::iKey::Press);
	mono_add_internal_call("VI.Input/Mouse::Hold", &VI::iInput::iKey::Hold);
	mono_add_internal_call("VI.Input/Mouse::Release", &VI::iInput::iKey::Release);
	mono_add_internal_call("VI.Input/Mouse::Idle", &VI::iInput::iKey::Idle);

	// Physics
	mono_add_internal_call("VI.Physics::s_ApplyImpulse", &VIM::iPhysics::s_ApplyImpulse);
	mono_add_internal_call("VI.Physics::s_EntitiesCollided", &VIM::iPhysics::s_EntitiesCollided);
	mono_add_internal_call("VI.Physics::s_CheckCollision", &VIM::iPhysics::s_CheckCollision);

	mono_add_internal_call("VI.Physics::ApplyImpulse", &VIM::iPhysics::ApplyImpulse);
	mono_add_internal_call("VI.Physics::EntitiesCollided", &VIM::iPhysics::EntitiesCollided);
	mono_add_internal_call("VI.Physics::CheckCollision", &VIM::iPhysics::CheckCollision);

	// Dialogue
	mono_add_internal_call("VI.Dialogue::LoadScript", &VIM::iDialogue::LoadScript);
	mono_add_internal_call("VI.Dialogue::GetLine", &VIM::iDialogue::GetLine);
	mono_add_internal_call("VI.Dialogue::HaveChoices", &VI::iDialogue::HaveChoices);
	mono_add_internal_call("VI.Dialogue::GetSelectedChoice", &VI::iDialogue::GetSelectedChoice);
	mono_add_internal_call("VI.Dialogue::GetNext", &VI::iDialogue::GetNext);
	mono_add_internal_call("VI.Dialogue::GetNextId", &VI::iDialogue::GetNextId);

	mono_add_internal_call("VI.Dialogue/Current::GetLine", &VIM::iDialogue::GetCurrentLine);
	mono_add_internal_call("VI.Dialogue/Current::GetId", &VI::iDialogue::GetCurrentId);
	mono_add_internal_call("VI.Dialogue/Current::HaveChoices", &VIM::iDialogue::HaveChoices);
	mono_add_internal_call("VI.Dialogue/Current::SetTo", &VI::iDialogue::SetCurrentId);
	mono_add_internal_call("VI.Dialogue/Current::GetFirstChoice", &VIM::iDialogue::GetCurrentChoice1);
	mono_add_internal_call("VI.Dialogue/Current::GetSecondChoice", &VIM::iDialogue::GetCurrentChoice2);
	mono_add_internal_call("VI.Dialogue/Current::SetSelectedChoice", &VI::iDialogue::SetSelectedChoice);
	mono_add_internal_call("VI.Dialogue/Current::GetSelectedChoice", &VI::iDialogue::GetCurrentSelectedChoice);
	mono_add_internal_call("VI.Dialogue/current::PlayerSpeaking", &VIM::iDialogue::IsPlayerCurrentSpeaker);

	mono_add_internal_call("VI.Dialogue/Next::GetLine", &VIM::iDialogue::GetNext);
	mono_add_internal_call("VI.Dialogue/Next::GetId", &VI::iDialogue::GetNextId);
	mono_add_internal_call("VI.Dialogue/Next::HaveChoices", &VIM::iDialogue::NextHaveChoices);
	mono_add_internal_call("VI.Dialogue/Next::GetFirstChoice", &VIM::iDialogue::GetNextChoice1);
	mono_add_internal_call("VI.Dialogue/Next::GetSecondChoice", &VIM::iDialogue::GetNextChoice2);
	mono_add_internal_call("VI.Dialogue/Next::PlayerSpeaking", &VIM::iDialogue::IsPlayerNextSpeaker);

	mono_add_internal_call("VI.Dialogue/Choice::First", &VI::iDialogue::GetChoice1);
	mono_add_internal_call("VI.Dialogue/Choice::Second", &VI::iDialogue::GetChoice2);
	mono_add_internal_call("VI.Dialogue/Choice::Selected", &VI::iDialogue::SetSelectedChoice);
	mono_add_internal_call("VI.Dialogue/Speaker::IsPlayer", &VI::iDialogue::IsPlayerSpeaker);

	// Gamestate
	mono_add_internal_call("VI.GameState::Go", &VIM::iGameState::Go);
	mono_add_internal_call("VI.GameState::GetName", &VIM::iGameState::GetCurrentName);
	mono_add_internal_call("VI.GameState::Exit", &VI::iGameState::GameStateExit);

	// Entity
	mono_add_internal_call("VI.Entity::GetId", &VIM::iEntity::GetId);

	mono_add_internal_call("VI.Entity::s_IsActive", &VIM::iEntity::s_IsActive);
	mono_add_internal_call("VI.Entity::s_SetActive", &VIM::iEntity::s_SetIsActive);
	mono_add_internal_call("VI.Entity::s_Activate", &VIM::iEntity::s_Activate);
	mono_add_internal_call("VI.Entity::s_Deactivate", &VIM::iEntity::s_Deactivate);
	mono_add_internal_call("VI.Entity/Parent::s_Name", &VIM::iEntity::s_GetParent);
	mono_add_internal_call("VI.Entity/Parent::s_Id", &VIM::iEntity::s_GetParentId);

	mono_add_internal_call("VI.Entity::IsActive", &VIM::iEntity::IsActive);
	mono_add_internal_call("VI.Entity::SetActive", &VIM::iEntity::SetIsActive);
	mono_add_internal_call("VI.Entity::Activate", &VIM::iEntity::Activate);
	mono_add_internal_call("VI.Entity::Deactivate", &VIM::iEntity::Deactivate);
	mono_add_internal_call("VI.Entity/Parent::Name", &VIM::iEntity::GetParent);
	mono_add_internal_call("VI.Entity/Parent::Id", &VIM::iEntity::GetParentId);

	// Scene
	mono_add_internal_call("VI.Scene::Pause", &VIM::iScene::Pause);
	mono_add_internal_call("VI.Scene::Play", &VIM::iScene::Play);

	// Camera
	mono_add_internal_call("VI.Camera/GetScale::X", &VI::iCamera::GetScaleX);
	mono_add_internal_call("VI.Camera/GetScale::Y", &VI::iCamera::GetScaleY);
	mono_add_internal_call("VI.Camera/GetPos::X", &VI::iCamera::GetPosX);
	mono_add_internal_call("VI.Camera/GetPos::Y", &VI::iCamera::GetPosY);
	mono_add_internal_call("VI.Camera/SetScale::X", &VI::iCamera::SetScaleX);
	mono_add_internal_call("VI.Camera/SetScale::Y", &VI::iCamera::SetScaleY);
	mono_add_internal_call("VI.Camera/SetPos::X", &VI::iCamera::SetPosX);
	mono_add_internal_call("VI.Camera/SetPos::Y", &VI::iCamera::SetPosY);

	// Math
	mono_add_internal_call("VI.Math::SqMagnitude", &VI::iMath::SqMagnitude);
	mono_add_internal_call("VI.Math/Normalize::X", &VI::iMath::NormalizeX);
	mono_add_internal_call("VI.Math/Normalize::Y", &VI::iMath::NormalizeY);
	mono_add_internal_call("VI.Math::ArcTangent", &VI::iMath::ArcTangent);
	mono_add_internal_call("VI.Math::Negate", &VI::iMath::Negate);

	// Animation
	mono_add_internal_call("VI.Animation/SheetIndex::s_Set", &VIM::iAnimation::s_SetSheetIndex);
	mono_add_internal_call("VI.Animation/SheetIndex::s_Get", &VIM::iAnimation::s_GetSheetIndex);
	mono_add_internal_call("VI.Animation/Speed::s_Set", &VIM::iAnimation::s_SetSpeed);
	mono_add_internal_call("VI.Animation/Speed::s_Get", &VIM::iAnimation::s_GetSpeed);
	mono_add_internal_call("VI.Animation/CurrentFrame::s_Set", &VIM::iAnimation::s_SetCurrentFrame);
	mono_add_internal_call("VI.Animation/CurrentFrame::s_Get", &VIM::iAnimation::s_GetCurrentFrame);
	mono_add_internal_call("VI.Animation/FrameCount::s_Set", &VIM::iAnimation::s_SetFrameCount);
	mono_add_internal_call("VI.Animation/FrameCount::s_Get", &VIM::iAnimation::s_GetFrameCount);

	mono_add_internal_call("VI.Animation/SheetIndex::Set", &VIM::iAnimation::SetSheetIndex);
	mono_add_internal_call("VI.Animation/SheetIndex::Get", &VIM::iAnimation::GetSheetIndex);
	mono_add_internal_call("VI.Animation/Speed::Set", &VIM::iAnimation::SetSpeed);
	mono_add_internal_call("VI.Animation/Speed::Get", &VIM::iAnimation::GetSpeed);
	mono_add_internal_call("VI.Animation/CurrentFrame::Set", &VIM::iAnimation::SetCurrentFrame);
	mono_add_internal_call("VI.Animation/CurrentFrame::Get", &VIM::iAnimation::GetCurrentFrame);
	mono_add_internal_call("VI.Animation/FrameCount::Set", &VIM::iAnimation::SetFrameCount);
	mono_add_internal_call("VI.Animation/FrameCount::Get", &VIM::iAnimation::GetFrameCount);

	mono_add_internal_call("VI.Animation/Transform::Start", &VI::iAnimation::Start);
	mono_add_internal_call("VI.Animation/Transform::SetNext", &VI::iAnimation::SetNext);
	mono_add_internal_call("VI.Animation/Transform::Stop", &VI::iAnimation::Stop);
	mono_add_internal_call("VI.Animation/Transform::StopAfterEndLoop", &VI::iAnimation::StopAfterEndLoop);
	mono_add_internal_call("VI.Animation/Transform::ReverseOrder", &VI::iAnimation::ReverseOrder);
	mono_add_internal_call("VI.Animation/Transform::SetLoopCycle", &VI::iAnimation::SetLoopCycle);
	mono_add_internal_call("VI.Animation/Transform::AddTransform", &VI::iAnimation::AddTransform);
	mono_add_internal_call("VI.Animation/Transform::AddTransformDifference", &VI::iAnimation::AddTransformDifference);
	mono_add_internal_call("VI.Animation/Transform::SetCalculatedTimeFromPosition", &VI::iAnimation::SetCalculatedTimeFromPosition);
	mono_add_internal_call("VI.Animation/Transform::SetCalculatedTimeFromRotation", &VI::iAnimation::SetCalculatedTimeFromRotation);
	mono_add_internal_call("VI.Animation/Transform::SetCalculatedTimeFromScale", &VI::iAnimation::SetCalculatedTimeFromScale);

	// Textures
	mono_add_internal_call("VI.Texture::s_Set", &VIM::iTexture::s_SetTexture);
	mono_add_internal_call("VI.Texture::s_Get", &VIM::iTexture::s_GetTexture);
	mono_add_internal_call("VI.Texture::Set", &VIM::iTexture::SetTexture);
	mono_add_internal_call("VI.Texture::Get", &VIM::iTexture::GetTexture);

	// Audio
	mono_add_internal_call("VI.Audio::Play", &VIM::iAudio::Play);
	mono_add_internal_call("VI.Audio::PlayOnLoop", &VIM::iAudio::PlayOnLoop);
	mono_add_internal_call("VI.Audio::SetLoop", &VIM::iAudio::SetLoop);
	mono_add_internal_call("VI.Audio::Stop", &VIM::iAudio::Stop);

	mono_add_internal_call("VI.Audio::PlayBGM", &VIM::iAudio::PlayBGM);
	mono_add_internal_call("VI.Audio::IsBgmPlaying", &VIM::iAudio::IsBgmPlaying);
	mono_add_internal_call("VI.Audio::ForcePlay", &VIM::iAudio::ForcePlay);

	mono_add_internal_call("VI.Audio::StopAll", &VI::iAudio::StopAll);
	mono_add_internal_call("VI.Audio::StopBGM", &VI::iAudio::StopBGM);
	mono_add_internal_call("VI.Audio::StopSFX", &VI::iAudio::StopSFX);
	mono_add_internal_call("VI.Audio/Volume::SetVolume", &VI::iAudio::SetAllVolume);
	mono_add_internal_call("VI.Audio/Volume::SetBGMVolume", &VI::iAudio::SetBGMVolume);
	mono_add_internal_call("VI.Audio/Volume::SetSFXVolume", &VI::iAudio::SetSFXVolume);

	mono_add_internal_call("VI.Audio::s_Stop", &VIM::iAudio::s_Stop);
	mono_add_internal_call("VI.Audio::s_Play", &VIM::iAudio::s_Play);
	mono_add_internal_call("VI.Audio::s_PlayOnLoop", &MonoMethods::iAudio::s_PlayOnLoop);
	mono_add_internal_call("VI.Audio::s_SetLoop", &VIM::iAudio::s_SetLoop);

	// Transform
	mono_add_internal_call("VI.Transform/Position::s_GetX", &VIM::iTransform::s_GetPosX);
	mono_add_internal_call("VI.Transform/Position::s_GetY", &VIM::iTransform::s_GetPosY);
	mono_add_internal_call("VI.Transform/Position::s_SetX", &VIM::iTransform::s_SetPosX);
	mono_add_internal_call("VI.Transform/Position::s_SetY", &VIM::iTransform::s_SetPosY);

	mono_add_internal_call("VI.Transform/Position::GetX", &VIM::iTransform::GetPosX);
	mono_add_internal_call("VI.Transform/Position::GetY", &VIM::iTransform::GetPosY);
	mono_add_internal_call("VI.Transform/Position::SetX", &VIM::iTransform::SetPosX);
	mono_add_internal_call("VI.Transform/Position::SetY", &VIM::iTransform::SetPosY);

	mono_add_internal_call("VI.Transform/Scale::s_GetX", &VIM::iTransform::s_GetScaleX);
	mono_add_internal_call("VI.Transform/Scale::s_GetY", &VIM::iTransform::s_GetScaleY);
	mono_add_internal_call("VI.Transform/Scale::s_SetX", &VIM::iTransform::s_SetScaleX);
	mono_add_internal_call("VI.Transform/Scale::s_SetY", &VIM::iTransform::s_SetScaleY);

	mono_add_internal_call("VI.Transform/Scale::GetX", &VIM::iTransform::GetScaleX);
	mono_add_internal_call("VI.Transform/Scale::GetY", &VIM::iTransform::GetScaleY);
	mono_add_internal_call("VI.Transform/Scale::SetX", &VIM::iTransform::SetScaleX);
	mono_add_internal_call("VI.Transform/Scale::SetY", &VIM::iTransform::SetScaleY);

	mono_add_internal_call("VI.Transform/Rotate::s_Get", &VIM::iTransform::s_GetRotate);
	mono_add_internal_call("VI.Transform/Rotate::s_Set", &VIM::iTransform::s_SetRotate);

	mono_add_internal_call("VI.Transform/Rotate::Get", &VIM::iTransform::GetRotate);
	mono_add_internal_call("VI.Transform/Rotate::Set", &VIM::iTransform::SetRotate);

	// Text
	mono_add_internal_call("VI.Text::s_Update", &VIM::iText::s_UpdateText);
	mono_add_internal_call("VI.Text::s_GetLineCount", &VIM::iText::s_GetLineCount);
	mono_add_internal_call("VI.Text/Offset::s_Set", &VIM::iText::s_SetOffset);
	mono_add_internal_call("VI.Text/Offset::s_GetX", &VIM::iText::s_GetOffsetX);
	mono_add_internal_call("VI.Text/Offset::s_GetY", &VIM::iText::s_GetOffsetY);
	mono_add_internal_call("VI.Text/Scale::s_Get", &VIM::iText::s_GetScale);
	mono_add_internal_call("VI.Text/Scale::s_Set", &VIM::iText::s_SetScale);

	mono_add_internal_call("VI.Text::Update", &VIM::iText::UpdateText);
	mono_add_internal_call("VI.Text::GetLineCount", &VIM::iText::GetLineCount);
	mono_add_internal_call("VI.Text/Offset::Set", &VIM::iText::SetOffset);
	mono_add_internal_call("VI.Text/Offset::GetX", &VIM::iText::GetOffsetX);
	mono_add_internal_call("VI.Text/Offset::GetY", &VIM::iText::GetOffsetY);
	mono_add_internal_call("VI.Text/Scale::Get", &VIM::iText::GetScale);
	mono_add_internal_call("VI.Text/Scale::Set", &VIM::iText::SetScale);

	// Weather
	mono_add_internal_call("VI.Weather::Init", &VI::iWeather::WeatherInit);
	mono_add_internal_call("VI.Weather::GetCurrent", &VI::iWeather::GetCurrentWeather);

	// LightSource
	mono_add_internal_call("VI.LightSource/Radius::s_Get", &VIM::iLightSource::s_GetRadius);
	mono_add_internal_call("VI.LightSource/Radius::s_Set", &VIM::iLightSource::s_SetRadius);
	mono_add_internal_call("VI.LightSource/SpriteColor::s_Set", &VIM::iLightSource::s_SetSpriteColor);

	mono_add_internal_call("VI.LightSource/Radius::Get", &VIM::iLightSource::GetRadius);
	mono_add_internal_call("VI.LightSource/Radius::Set", &VIM::iLightSource::SetRadius);
	mono_add_internal_call("VI.LightSource/SpriteColor::Set", &VIM::iLightSource::SetSpriteColor);
}
