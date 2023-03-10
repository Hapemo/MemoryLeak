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
#include "Logger.h"

/*!*****************************************************************************
\brief
MonoString conversion methods.
*******************************************************************************/
std::string MonoMethods::ConvertFromMonoString(MonoString* _string) {
	return (_string == nullptr ? "" : mono_string_to_utf8(_string));
}
MonoString* MonoMethods::ConvertToMonoString(std::string _string) {
	return (_string == "" ? nullptr : mono_string_new(mono_domain_get(), _string.c_str()));
}

/*!*****************************************************************************
\brief
Logger function.
*******************************************************************************/
void MonoMethods::Logger(MonoString* _log) {
	FUNC->Logger(MONO->ConvertFromMonoString(_log));
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
bool MonoMethods::iPhysics::s_IsCollided(MonoString* _entityName1, MonoString* _entityName2, MonoString* _sceneName) {
	return VI::iPhysics::IsCollided(MONO->ConvertFromMonoString(_entityName1), MONO->ConvertFromMonoString(_entityName2), MONO->ConvertFromMonoString(_sceneName));
}
bool MonoMethods::iPhysics::IsCollided(const int _eId1, const int _eId2) {
	return VI::iPhysics::IsCollided(_eId1, _eId2);
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
	LOG_INFO("Ran monomethod getnextid");
	return VI::iDialogue::GetNextId(VI::iDialogue::GetCurrentId());
}
MonoString* MonoMethods::iDialogue::GetNext() {
	return MONO->ConvertToMonoString(VI::iDialogue::GetNext(VI::iDialogue::GetCurrentId()));
}
bool MonoMethods::iDialogue::NextHaveChoices() {
	return VI::iDialogue::HaveChoices(MM::iDialogue::GetNextId());
}
bool MonoMethods::iDialogue::GetNextChoice1() {
	return VI::iDialogue::GetChoice1(MM::iDialogue::GetNextId());
}
bool MonoMethods::iDialogue::GetNextChoice2() {
	return VI::iDialogue::GetChoice2(MM::iDialogue::GetNextId());
}
bool MonoMethods::iDialogue::IsPlayerNextSpeaker() {
	return VI::iDialogue::IsPlayerSpeaker(MM::iDialogue::GetNextId());
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
bool MonoMethods::iScene::IsPaused(MonoString* _name) {
	return VI::iScene::IsPaused(MONO->ConvertFromMonoString(_name));
}

// Animation
void MonoMethods::iAnimation::s_SetSpeed(MonoString* _entityName, MonoString* _sceneName, float _speed) {
	VI::iAnimation::iSpriteSheet::SetSpeed(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName), _speed);
}
float MonoMethods::iAnimation::s_GetSpeed(MonoString* _entityName, MonoString* _sceneName) {
	return VI::iAnimation::iSpriteSheet::GetSpeed(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName));
}
void MonoMethods::iAnimation::s_SetCurrentFrame(MonoString* _entityName, MonoString* _sceneName, int _index) {
	VI::iAnimation::iSpriteSheet::SetCurrentFrame(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName), _index);
}
int MonoMethods::iAnimation::s_GetCurrentFrame(MonoString* _entityName, MonoString* _sceneName) {
	return VI::iAnimation::iSpriteSheet::GetCurrentFrame(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName));
}
int MonoMethods::iAnimation::s_GetFrameCount(MonoString* _entityName, MonoString* _sceneName) {
	return VI::iAnimation::iSpriteSheet::GetFrameCount(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName));
}
void MonoMethods::iAnimation::s_SetFrameCount(MonoString* _entityName, MonoString* _sceneName, int _count) {
	return VI::iAnimation::iSpriteSheet::SetFrameCount(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName), _count);
}
void MonoMethods::iAnimation::s_SetSheetIndex(MonoString* _entityName, MonoString* _sceneName, int _index) {
	VI::iAnimation::iSpriteSheet::SetSheetIndex(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName), _index);
}
int MonoMethods::iAnimation::s_GetSheetIndex(MonoString* _entityName, MonoString* _sceneName) {
	return VI::iAnimation::iSpriteSheet::GetSheetIndex(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName));
}

void MonoMethods::iAnimation::SetSpeed(const int _eId, float _speed) {
	VI::iAnimation::iSpriteSheet::SetSpeed(_eId, _speed);
}
float MonoMethods::iAnimation::GetSpeed(const int _eId) {
	return VI::iAnimation::iSpriteSheet::GetSpeed(_eId);
}
void MonoMethods::iAnimation::SetCurrentFrame(const int _eId, int _index) {
	VI::iAnimation::iSpriteSheet::SetCurrentFrame(_eId, _index);
}
int MonoMethods::iAnimation::GetCurrentFrame(const int _eId) {
	return VI::iAnimation::iSpriteSheet::GetCurrentFrame(_eId);
}
int MonoMethods::iAnimation::GetFrameCount(const int _eId) {
	return VI::iAnimation::iSpriteSheet::GetFrameCount(_eId);
}
void MonoMethods::iAnimation::SetFrameCount(const int _eId, int _count) {
	return VI::iAnimation::iSpriteSheet::SetFrameCount(_eId, _count);
}
void MonoMethods::iAnimation::SetSheetIndex(const int _eId, int _index) {
	VI::iAnimation::iSpriteSheet::SetSheetIndex(_eId, _index);
}
int MonoMethods::iAnimation::GetSheetIndex(const int _eId) {
	return VI::iAnimation::iSpriteSheet::GetSheetIndex(_eId);
}

// Particle system
void MonoMethods::iParticleSystem::iParticleInfo::SetTexture(const int _eId, MonoString* _texture) {
	VI::iParticleSystem::iParticleInfo::SetTexture(_eId, MONO->ConvertFromMonoString(_texture));
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

int MonoMethods::iTexture::GetLayer(const int _eId) {
	return VI::iTexture::GetLayer(_eId);
}
int MonoMethods::iTexture::s_GetLayer(MonoString* _entityName, MonoString* _sceneName) {
	return VI::iTexture::GetLayer(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName));
}
void MonoMethods::iTexture::SetLayer(const int _eId, int layer) {
	VI::iTexture::SetLayer(_eId, layer);
}
void MonoMethods::iTexture::s_SetLayer(MonoString* _entityName, MonoString* _sceneName, int layer) {
	VI::iTexture::SetLayer(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName), layer);
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
void MonoMethods::iLightSource::SetRadius(const int _eId, float _radius) {
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
	//mono_add_internal_call("BonVoyage.THIS::IsActive", &MM::iEntity::IsActive);
	
	// Logger
	mono_add_internal_call("LOG::WRITE", &MONO->Logger);

	// General
	mono_add_internal_call("VI.General::DeltaTime", &FUNC->GetDeltaTime);

	// Inputs
	mono_add_internal_call("VI.Input/Key::Press", &VI::iInput::iKey::Press);
	mono_add_internal_call("VI.Input/Key::Hold", &VI::iInput::iKey::Hold);
	mono_add_internal_call("VI.Input/Key::Release", &VI::iInput::iKey::Release);
	mono_add_internal_call("VI.Input/Key::Idle", &VI::iInput::iKey::Idle);

	mono_add_internal_call("VI.Input/Button::s_Clicked", &MM::iInput::iButton::s_Clicked);
	mono_add_internal_call("VI.Input/Button::s_Released", &MM::iInput::iButton::s_Released);
	mono_add_internal_call("VI.Input/Button::s_Hover", &MM::iInput::iButton::s_Hover);

	mono_add_internal_call("VI.Input/Button::Clicked", &MM::iInput::iButton::Clicked);
	mono_add_internal_call("VI.Input/Button::Released", &MM::iInput::iButton::Released);
	mono_add_internal_call("VI.Input/Button::Hover", &MM::iInput::iButton::Hover);

	mono_add_internal_call("VI.Input/Mouse::WorldPosX", &VI::iInput::iMouse::GetWorldPosX);
	mono_add_internal_call("VI.Input/Mouse::WorldPosY", &VI::iInput::iMouse::GetWorldPosY);

	mono_add_internal_call("VI.Input/Mouse::Press", &VI::iInput::iKey::Press);
	mono_add_internal_call("VI.Input/Mouse::Hold", &VI::iInput::iKey::Hold);
	mono_add_internal_call("VI.Input/Mouse::Release", &VI::iInput::iKey::Release);
	mono_add_internal_call("VI.Input/Mouse::Idle", &VI::iInput::iKey::Idle);

	// Physics
	mono_add_internal_call("VI.Physics::s_ApplyImpulse", &MM::iPhysics::s_ApplyImpulse);
	mono_add_internal_call("VI.Physics::s_IsCollided", &MM::iPhysics::s_IsCollided);
	mono_add_internal_call("VI.Physics::s_CheckCollision", &MM::iPhysics::s_CheckCollision);

	mono_add_internal_call("VI.Physics::ApplyImpulse", &MM::iPhysics::ApplyImpulse);
	mono_add_internal_call("VI.Physics::IsCollided", &MM::iPhysics::IsCollided);
	mono_add_internal_call("VI.Physics::CheckCollision", &MM::iPhysics::CheckCollision);

	// Dialogue
	mono_add_internal_call("VI.Dialogue::LoadScript", &MM::iDialogue::LoadScript);
	mono_add_internal_call("VI.Dialogue::GetLine", &MM::iDialogue::GetLine);
	mono_add_internal_call("VI.Dialogue::HaveChoices", &VI::iDialogue::HaveChoices);
	mono_add_internal_call("VI.Dialogue::GetSelectedChoice", &VI::iDialogue::GetSelectedChoice);
	mono_add_internal_call("VI.Dialogue::GetNext", &VI::iDialogue::GetNext);
	mono_add_internal_call("VI.Dialogue::GetNextId", &VI::iDialogue::GetNextId);

	mono_add_internal_call("VI.Dialogue/Current::GetLine", &MM::iDialogue::GetCurrentLine);
	mono_add_internal_call("VI.Dialogue/Current::GetId", &VI::iDialogue::GetCurrentId);
	mono_add_internal_call("VI.Dialogue/Current::HaveChoices", &MM::iDialogue::HaveChoices);
	mono_add_internal_call("VI.Dialogue/Current::SetTo", &VI::iDialogue::SetCurrentId);
	mono_add_internal_call("VI.Dialogue/Current::GetFirstChoice", &MM::iDialogue::GetCurrentChoice1);
	mono_add_internal_call("VI.Dialogue/Current::GetSecondChoice", &MM::iDialogue::GetCurrentChoice2);
	mono_add_internal_call("VI.Dialogue/Current::SetSelectedChoice", &VI::iDialogue::SetSelectedChoice);
	mono_add_internal_call("VI.Dialogue/Current::GetSelectedChoice", &VI::iDialogue::GetCurrentSelectedChoice);
	mono_add_internal_call("VI.Dialogue/current::PlayerSpeaking", &MM::iDialogue::IsPlayerCurrentSpeaker);

	mono_add_internal_call("VI.Dialogue/Next::GetLine", &MM::iDialogue::GetNext);
	mono_add_internal_call("VI.Dialogue/Next::GetId", &VI::iDialogue::GetNextId);
	mono_add_internal_call("VI.Dialogue/Next::HaveChoices", &MM::iDialogue::NextHaveChoices);
	mono_add_internal_call("VI.Dialogue/Next::GetFirstChoice", &MM::iDialogue::GetNextChoice1);
	mono_add_internal_call("VI.Dialogue/Next::GetSecondChoice", &MM::iDialogue::GetNextChoice2);
	mono_add_internal_call("VI.Dialogue/Next::PlayerSpeaking", &MM::iDialogue::IsPlayerNextSpeaker);

	mono_add_internal_call("VI.Dialogue/Choice::First", &VI::iDialogue::GetChoice1);
	mono_add_internal_call("VI.Dialogue/Choice::Second", &VI::iDialogue::GetChoice2);
	mono_add_internal_call("VI.Dialogue/Choice::Selected", &VI::iDialogue::SetSelectedChoice);
	mono_add_internal_call("VI.Dialogue/Speaker::IsPlayer", &VI::iDialogue::IsPlayerSpeaker);

	// Gamestate
	mono_add_internal_call("VI.GameState::Go", &MM::iGameState::Go);
	mono_add_internal_call("VI.GameState::GetName", &MM::iGameState::GetCurrentName);
	mono_add_internal_call("VI.GameState::Exit", &VI::iGameState::GameStateExit);

	// Entity
	mono_add_internal_call("VI.Entity::GetId", &MM::iEntity::GetId);

	mono_add_internal_call("VI.Entity::s_IsActive", &MM::iEntity::s_IsActive);
	mono_add_internal_call("VI.Entity::s_SetActive", &MM::iEntity::s_SetIsActive);
	mono_add_internal_call("VI.Entity::s_Activate", &MM::iEntity::s_Activate);
	mono_add_internal_call("VI.Entity::s_Deactivate", &MM::iEntity::s_Deactivate);
	mono_add_internal_call("VI.Entity/Parent::s_Name", &MM::iEntity::s_GetParent);
	mono_add_internal_call("VI.Entity/Parent::s_Id", &MM::iEntity::s_GetParentId);

	mono_add_internal_call("VI.Entity::IsActive", &MM::iEntity::IsActive);
	mono_add_internal_call("VI.Entity::SetActive", &MM::iEntity::SetIsActive);
	mono_add_internal_call("VI.Entity::Activate", &MM::iEntity::Activate);
	mono_add_internal_call("VI.Entity::Deactivate", &MM::iEntity::Deactivate);
	mono_add_internal_call("VI.Entity/Parent::Name", &MM::iEntity::GetParent);
	mono_add_internal_call("VI.Entity/Parent::Id", &MM::iEntity::GetParentId);

	mono_add_internal_call("VI.Entity/Sprite::GetType", &VI::iEntity::GetSpriteType);
	mono_add_internal_call("VI.Entity/Sprite::SetType", &VI::iEntity::SetSpriteType);

	// Scene
	mono_add_internal_call("VI.Scene::Pause", &MM::iScene::Pause);
	mono_add_internal_call("VI.Scene::Play", &MM::iScene::Play);

	// Camera
	mono_add_internal_call("VI.Camera/GetScale::X", &VI::iCamera::GetScaleX);
	mono_add_internal_call("VI.Camera/GetScale::Y", &VI::iCamera::GetScaleY);
	mono_add_internal_call("VI.Camera/GetPos::X", &VI::iCamera::GetPosX);
	mono_add_internal_call("VI.Camera/GetPos::Y", &VI::iCamera::GetPosY);
	mono_add_internal_call("VI.Camera/SetScale::X", &VI::iCamera::SetScaleX);
	mono_add_internal_call("VI.Camera/SetScale::Y", &VI::iCamera::SetScaleY);
	mono_add_internal_call("VI.Camera/SetPos::X", &VI::iCamera::SetPosX);
	mono_add_internal_call("VI.Camera/SetPos::Y", &VI::iCamera::SetPosY);

	// Window
	mono_add_internal_call("VI.Window::GetScreenWidth", &VI::iWindow::GetScreenWidth);
	mono_add_internal_call("VI.Window::GetScreenHeight", &VI::iWindow::GetScreenHeight);
	mono_add_internal_call("VI.Window::SetFullScreen", &VI::iWindow::SetFullScreen);

	// Viewport
	mono_add_internal_call("VI.Viewport::GetWidth", &VI::iViewport::GetWidth);
	mono_add_internal_call("VI.Viewport::SetWidth", &VI::iViewport::SetWidth);
	mono_add_internal_call("VI.Viewport::IsUI", &VI::iViewport::IsUI);
	mono_add_internal_call("VI.Viewport::SetIsUI", &VI::iViewport::SetIsUI);

	// Math
	mono_add_internal_call("VI.Math::SqMagnitude", &VI::iMath::SqMagnitude);
	mono_add_internal_call("VI.Math::Magnitude", &VI::iMath::Magnitude);
	mono_add_internal_call("VI.Math/Normalize::X", &VI::iMath::NormalizeX);
	mono_add_internal_call("VI.Math/Normalize::Y", &VI::iMath::NormalizeY);
	mono_add_internal_call("VI.Math::ArcTangent", &VI::iMath::ArcTangent);
	mono_add_internal_call("VI.Math::Negate", &VI::iMath::Negate);
	mono_add_internal_call("VI.Math::Epsilon", &VI::iMath::Epsilon);
	mono_add_internal_call("VI.Math::Pi", &VI::iMath::Pi);
	mono_add_internal_call("VI.Math::ConvertRadToDeg", &VI::iMath::ConvertRadToDeg);
	mono_add_internal_call("VI.Math::ConvertDegToRad", &VI::iMath::ConvertDegToRad);

	// Animation
	mono_add_internal_call("VI.Animation/SheetIndex::s_Set", &MM::iAnimation::s_SetSheetIndex);
	mono_add_internal_call("VI.Animation/SheetIndex::s_Get", &MM::iAnimation::s_GetSheetIndex);
	mono_add_internal_call("VI.Animation/Speed::s_Set", &MM::iAnimation::s_SetSpeed);
	mono_add_internal_call("VI.Animation/Speed::s_Get", &MM::iAnimation::s_GetSpeed);
	mono_add_internal_call("VI.Animation/CurrentFrame::s_Set", &MM::iAnimation::s_SetCurrentFrame);
	mono_add_internal_call("VI.Animation/CurrentFrame::s_Get", &MM::iAnimation::s_GetCurrentFrame);
	mono_add_internal_call("VI.Animation/FrameCount::s_Set", &MM::iAnimation::s_SetFrameCount);
	mono_add_internal_call("VI.Animation/FrameCount::s_Get", &MM::iAnimation::s_GetFrameCount);

	mono_add_internal_call("VI.Animation/SheetIndex::Set", &MM::iAnimation::SetSheetIndex);
	mono_add_internal_call("VI.Animation/SheetIndex::Get", &MM::iAnimation::GetSheetIndex);
	mono_add_internal_call("VI.Animation/Speed::Set", &MM::iAnimation::SetSpeed);
	mono_add_internal_call("VI.Animation/Speed::Get", &MM::iAnimation::GetSpeed);
	mono_add_internal_call("VI.Animation/CurrentFrame::Set", &MM::iAnimation::SetCurrentFrame);
	mono_add_internal_call("VI.Animation/CurrentFrame::Get", &MM::iAnimation::GetCurrentFrame);
	mono_add_internal_call("VI.Animation/FrameCount::Set", &MM::iAnimation::SetFrameCount);
	mono_add_internal_call("VI.Animation/FrameCount::Get", &MM::iAnimation::GetFrameCount);

	mono_add_internal_call("VI.Animation/Transform::Run", &VI::iAnimation::iTransform::Start);
	mono_add_internal_call("VI.Animation/Transform::SetNext", &VI::iAnimation::iTransform::SetNext);
	mono_add_internal_call("VI.Animation/Transform::GoToNext", &VI::iAnimation::iTransform::GoToNext);
	mono_add_internal_call("VI.Animation/Transform::Stop", &VI::iAnimation::iTransform::Stop);
	mono_add_internal_call("VI.Animation/Transform::StopAfterEndLoop", &VI::iAnimation::iTransform::StopAfterEndLoop);
	mono_add_internal_call("VI.Animation/Transform::ReverseOrder", &VI::iAnimation::iTransform::ReverseOrder);
	mono_add_internal_call("VI.Animation/Transform::SetLoopCycle", &VI::iAnimation::iTransform::SetLoopCycle);
	mono_add_internal_call("VI.Animation/Transform::GetCurrentIndex", &VI::iAnimation::iTransform::GetCurrentIndex);
	mono_add_internal_call("VI.Animation/Transform::Remove", &VI::iAnimation::iTransform::Remove);
	mono_add_internal_call("VI.Animation/Edit::Timing", &VI::iAnimation::iTransform::EditTiming);
	mono_add_internal_call("VI.Animation/Edit::CurrentTiming", &VI::iAnimation::iTransform::EditCurrentTiming);
	mono_add_internal_call("VI.Animation/Edit::Current", &VI::iAnimation::iTransform::EditCurrent);
	mono_add_internal_call("VI.Animation/Edit::CurrentScaleX", &VI::iAnimation::iTransform::CurrentScaleX);
	mono_add_internal_call("VI.Animation/Edit::CurrentScaleY", &VI::iAnimation::iTransform::CurrentScaleY);
	mono_add_internal_call("VI.Animation/Edit::CurrentRotate", &VI::iAnimation::iTransform::CurrentRotate);
	mono_add_internal_call("VI.Animation/Edit::CurrentPosX", &VI::iAnimation::iTransform::CurrentPosX);
	mono_add_internal_call("VI.Animation/Edit::CurrentPosY", &VI::iAnimation::iTransform::CurrentPosY);
	mono_add_internal_call("VI.Animation/Get::Timing", &VI::iAnimation::iTransform::GetTiming);
	mono_add_internal_call("VI.Animation/Get::CurrentTiming", &VI::iAnimation::iTransform::GetCurrentTiming);
	mono_add_internal_call("VI.Animation/Get::CurrentScaleX", &VI::iAnimation::iTransform::GetCurrentScaleX);
	mono_add_internal_call("VI.Animation/Get::CurrentScaleY", &VI::iAnimation::iTransform::GetCurrentScaleY);
	mono_add_internal_call("VI.Animation/Get::CurrentRotate", &VI::iAnimation::iTransform::GetCurrentRotate);
	mono_add_internal_call("VI.Animation/Get::CurrentPosX", &VI::iAnimation::iTransform::GetCurrentPosX);
	mono_add_internal_call("VI.Animation/Get::CurrentPosY", &VI::iAnimation::iTransform::GetCurrentPosY);
	mono_add_internal_call("VI.Animation/Add::Transform", &VI::iAnimation::iTransform::AddTransform);
	mono_add_internal_call("VI.Animation/Add::TransformAt", &VI::iAnimation::iTransform::AddTransformAt);
	mono_add_internal_call("VI.Animation/Add::TransformScaleAt", &VI::iAnimation::iTransform::TransformScaleAt);
	mono_add_internal_call("VI.Animation/Add::TransformRotateAt", &VI::iAnimation::iTransform::TransformRotateAt);
	mono_add_internal_call("VI.Animation/Add::TransformPosAt", &VI::iAnimation::iTransform::TransformPosAt);
	mono_add_internal_call("VI.Animation/Add::TransformDifference", &VI::iAnimation::iTransform::AddTransformDifference);
	mono_add_internal_call("VI.Animation/SetCalculatedTime::FromPosition", &VI::iAnimation::iTransform::SetCalculatedTimeFromPosition);
	mono_add_internal_call("VI.Animation/SetCalculatedTime::FromRotation", &VI::iAnimation::iTransform::SetCalculatedTimeFromRotation);
	mono_add_internal_call("VI.Animation/SetCalculatedTime::FromScale", &VI::iAnimation::iTransform::SetCalculatedTimeFromScale);
	mono_add_internal_call("VI.Animation/AddAtCurrent::Transform", &VI::iAnimation::iTransform::AddTransformAtCurrent);
	mono_add_internal_call("VI.Animation/AddAtCurrent::TransformScale", &VI::iAnimation::iTransform::TransformScaleAtCurrent);
	mono_add_internal_call("VI.Animation/AddAtCurrent::TransformRotate", &VI::iAnimation::iTransform::TransformRotateAtCurrent);
	mono_add_internal_call("VI.Animation/AddAtCurrent::TransformPos", &VI::iAnimation::iTransform::TransformPosAtCurrent);

	// Particle System
	mono_add_internal_call("VI.ParticleSystem::GetDensity", &VI::iParticleSystem::GetDensity);
	mono_add_internal_call("VI.ParticleSystem::SetDensity", &VI::iParticleSystem::SetDensity);
	mono_add_internal_call("VI.ParticleSystem::GetPosX", &VI::iParticleSystem::GetPosX);
	mono_add_internal_call("VI.ParticleSystem::SetPosX", &VI::iParticleSystem::SetPosX);
	mono_add_internal_call("VI.ParticleSystem::GetPosY", &VI::iParticleSystem::GetPosY);
	mono_add_internal_call("VI.ParticleSystem::SetPosY", &VI::iParticleSystem::SetPosY);
	mono_add_internal_call("VI.ParticleSystem::GetWidth", &VI::iParticleSystem::GetWidth);
	mono_add_internal_call("VI.ParticleSystem::SetWidth", &VI::iParticleSystem::SetWidth);
	mono_add_internal_call("VI.ParticleSystem::GetDir", &VI::iParticleSystem::GetDir);
	mono_add_internal_call("VI.ParticleSystem::SetDir", &VI::iParticleSystem::SetDir);
	mono_add_internal_call("VI.ParticleSystem::GetSpread", &VI::iParticleSystem::GetSpread);
	mono_add_internal_call("VI.ParticleSystem::SetSpread", &VI::iParticleSystem::SetSpread);
	mono_add_internal_call("VI.ParticleSystem::GetDuration", &VI::iParticleSystem::GetDuration);
	mono_add_internal_call("VI.ParticleSystem::SetDuration", &VI::iParticleSystem::SetDuration);
	mono_add_internal_call("VI.ParticleSystem::IsActive", &VI::iParticleSystem::IsActive);
	mono_add_internal_call("VI.ParticleSystem::SetIsActive", &VI::iParticleSystem::SetIsActive);
	mono_add_internal_call("VI.ParticleSystem::GetSlow", &VI::iParticleSystem::GetSlow);
	mono_add_internal_call("VI.ParticleSystem::SetSlow", &VI::iParticleSystem::SetSlow);
	mono_add_internal_call("VI.ParticleSystem::GenerateOnce", &VI::iParticleSystem::GenerateOnce);
	mono_add_internal_call("VI.ParticleSystem::GenerateLoop", &VI::iParticleSystem::GenerateLoop);
	
	mono_add_internal_call("VI.ParticleSystem/ParticleInfo::GetScale", &VI::iParticleSystem::iParticleInfo::GetScale);
	mono_add_internal_call("VI.ParticleSystem/ParticleInfo::GetDirection", &VI::iParticleSystem::iParticleInfo::GetDirection);
	mono_add_internal_call("VI.ParticleSystem/ParticleInfo::GetLifeSpan", &VI::iParticleSystem::iParticleInfo::GetLifeSpan);
	mono_add_internal_call("VI.ParticleSystem/ParticleInfo::GetRotation", &VI::iParticleSystem::iParticleInfo::GetRotation);
	mono_add_internal_call("VI.ParticleSystem/ParticleInfo::GetSpeed", &VI::iParticleSystem::iParticleInfo::GetSpeed);
	mono_add_internal_call("VI.ParticleSystem/ParticleInfo::GetFading", &VI::iParticleSystem::iParticleInfo::GetFading);
	mono_add_internal_call("VI.ParticleSystem/ParticleInfo::GetSpriteType", &VI::iParticleSystem::iParticleInfo::GetSpriteType);
	mono_add_internal_call("VI.ParticleSystem/ParticleInfo::GetLayer", &VI::iParticleSystem::iParticleInfo::GetLayer);

	mono_add_internal_call("VI.ParticleSystem/ParticleInfo::SetScale", &VI::iParticleSystem::iParticleInfo::SetScale);
	mono_add_internal_call("VI.ParticleSystem/ParticleInfo::SetDirection", &VI::iParticleSystem::iParticleInfo::SetDirection);
	mono_add_internal_call("VI.ParticleSystem/ParticleInfo::SetLifeSpan", &VI::iParticleSystem::iParticleInfo::SetLifeSpan);
	mono_add_internal_call("VI.ParticleSystem/ParticleInfo::SetRotation", &VI::iParticleSystem::iParticleInfo::SetRotation);
	mono_add_internal_call("VI.ParticleSystem/ParticleInfo::SetSpeed", &VI::iParticleSystem::iParticleInfo::SetSpeed);
	mono_add_internal_call("VI.ParticleSystem/ParticleInfo::SetFading", &VI::iParticleSystem::iParticleInfo::SetFading);
	mono_add_internal_call("VI.ParticleSystem/ParticleInfo::SetColour", &VI::iParticleSystem::iParticleInfo::SetColour);
	mono_add_internal_call("VI.ParticleSystem/ParticleInfo::SetSpriteType", &VI::iParticleSystem::iParticleInfo::SetSpriteType);
	mono_add_internal_call("VI.ParticleSystem/ParticleInfo::SetTexture", &MM::iParticleSystem::iParticleInfo::SetTexture);
	mono_add_internal_call("VI.ParticleSystem/ParticleInfo::SetLayer", &VI::iParticleSystem::iParticleInfo::SetLayer);

	// Textures
	mono_add_internal_call("VI.Texture::s_Set", &MM::iTexture::s_SetTexture);
	mono_add_internal_call("VI.Texture::s_Get", &MM::iTexture::s_GetTexture);
	mono_add_internal_call("VI.Texture::Set", &MM::iTexture::SetTexture);
	mono_add_internal_call("VI.Texture::Get", &MM::iTexture::GetTexture);

	mono_add_internal_call("VI.Texture::GetLayer", &MM::iTexture::GetLayer);
	mono_add_internal_call("VI.Texture::SetLayer", &MM::iTexture::SetLayer);
	mono_add_internal_call("VI.Texture::s_GetLayer", &MM::iTexture::s_GetLayer);
	mono_add_internal_call("VI.Texture::s_SetLayer", &MM::iTexture::s_SetLayer);
	// Audio
	mono_add_internal_call("VI.Audio::Play", &MM::iAudio::Play);
	mono_add_internal_call("VI.Audio::PlayOnLoop", &MM::iAudio::PlayOnLoop);
	mono_add_internal_call("VI.Audio::SetLoop", &MM::iAudio::SetLoop);
	mono_add_internal_call("VI.Audio::Stop", &MM::iAudio::Stop);

	mono_add_internal_call("VI.Audio::PlayBGM", &MM::iAudio::PlayBGM);
	mono_add_internal_call("VI.Audio::IsBgmPlaying", &MM::iAudio::IsBgmPlaying);
	mono_add_internal_call("VI.Audio::ForcePlay", &MM::iAudio::ForcePlay);

	mono_add_internal_call("VI.Audio::StopAll", &VI::iAudio::StopAll);
	mono_add_internal_call("VI.Audio::StopBGM", &VI::iAudio::StopBGM);
	mono_add_internal_call("VI.Audio::StopSFX", &VI::iAudio::StopSFX);
	mono_add_internal_call("VI.Audio/Volume::SetVolume", &VI::iAudio::SetAllVolume);
	mono_add_internal_call("VI.Audio/Volume::SetBGMVolume", &VI::iAudio::SetBGMVolume);
	mono_add_internal_call("VI.Audio/Volume::SetSFXVolume", &VI::iAudio::SetSFXVolume);

	mono_add_internal_call("VI.Audio::s_Stop", &MM::iAudio::s_Stop);
	mono_add_internal_call("VI.Audio::s_Play", &MM::iAudio::s_Play);
	mono_add_internal_call("VI.Audio::s_PlayOnLoop", &MonoMethods::iAudio::s_PlayOnLoop);
	mono_add_internal_call("VI.Audio::s_SetLoop", &MM::iAudio::s_SetLoop);

	// Transform
	mono_add_internal_call("VI.Transform/Position::s_GetX", &MM::iTransform::s_GetPosX);
	mono_add_internal_call("VI.Transform/Position::s_GetY", &MM::iTransform::s_GetPosY);
	mono_add_internal_call("VI.Transform/Position::s_SetX", &MM::iTransform::s_SetPosX);
	mono_add_internal_call("VI.Transform/Position::s_SetY", &MM::iTransform::s_SetPosY);

	mono_add_internal_call("VI.Transform/Position::GetX", &MM::iTransform::GetPosX);
	mono_add_internal_call("VI.Transform/Position::GetY", &MM::iTransform::GetPosY);
	mono_add_internal_call("VI.Transform/Position::SetX", &MM::iTransform::SetPosX);
	mono_add_internal_call("VI.Transform/Position::SetY", &MM::iTransform::SetPosY);

	mono_add_internal_call("VI.Transform/Scale::s_GetX", &MM::iTransform::s_GetScaleX);
	mono_add_internal_call("VI.Transform/Scale::s_GetY", &MM::iTransform::s_GetScaleY);
	mono_add_internal_call("VI.Transform/Scale::s_SetX", &MM::iTransform::s_SetScaleX);
	mono_add_internal_call("VI.Transform/Scale::s_SetY", &MM::iTransform::s_SetScaleY);

	mono_add_internal_call("VI.Transform/Scale::GetX", &MM::iTransform::GetScaleX);
	mono_add_internal_call("VI.Transform/Scale::GetY", &MM::iTransform::GetScaleY);
	mono_add_internal_call("VI.Transform/Scale::SetX", &MM::iTransform::SetScaleX);
	mono_add_internal_call("VI.Transform/Scale::SetY", &MM::iTransform::SetScaleY);

	mono_add_internal_call("VI.Transform/Rotate::s_Get", &MM::iTransform::s_GetRotate);
	mono_add_internal_call("VI.Transform/Rotate::s_Set", &MM::iTransform::s_SetRotate);

	mono_add_internal_call("VI.Transform/Rotate::Get", &MM::iTransform::GetRotate);
	mono_add_internal_call("VI.Transform/Rotate::Set", &MM::iTransform::SetRotate);

	// Text
	mono_add_internal_call("VI.Text::s_Update", &MM::iText::s_UpdateText);
	mono_add_internal_call("VI.Text::s_GetLineCount", &MM::iText::s_GetLineCount);
	mono_add_internal_call("VI.Text/Offset::s_Set", &MM::iText::s_SetOffset);
	mono_add_internal_call("VI.Text/Offset::s_GetX", &MM::iText::s_GetOffsetX);
	mono_add_internal_call("VI.Text/Offset::s_GetY", &MM::iText::s_GetOffsetY);
	mono_add_internal_call("VI.Text/Scale::s_Get", &MM::iText::s_GetScale);
	mono_add_internal_call("VI.Text/Scale::s_Set", &MM::iText::s_SetScale);

	mono_add_internal_call("VI.Text::Update", &MM::iText::UpdateText);
	mono_add_internal_call("VI.Text::GetLineCount", &MM::iText::GetLineCount);
	mono_add_internal_call("VI.Text/Offset::Set", &MM::iText::SetOffset);
	mono_add_internal_call("VI.Text/Offset::GetX", &MM::iText::GetOffsetX);
	mono_add_internal_call("VI.Text/Offset::GetY", &MM::iText::GetOffsetY);
	mono_add_internal_call("VI.Text/Scale::Get", &MM::iText::GetScale);
	mono_add_internal_call("VI.Text/Scale::Set", &MM::iText::SetScale);

	mono_add_internal_call("VI.Text::SetColour", &VI::iText::SetColour);

	// Weather
	mono_add_internal_call("VI.Weather::Init", &VI::iWeather::WeatherInit);
	mono_add_internal_call("VI.Weather::GetCurrent", &VI::iWeather::GetCurrentWeather);

	// LightSource
	mono_add_internal_call("VI.LightSource/Radius::s_Get", &MM::iLightSource::s_GetRadius);
	mono_add_internal_call("VI.LightSource/Radius::s_Set", &MM::iLightSource::s_SetRadius);
	mono_add_internal_call("VI.LightSource/SpriteColor::s_Set", &MM::iLightSource::s_SetSpriteColor);

	mono_add_internal_call("VI.LightSource/Radius::Get", &MM::iLightSource::GetRadius);
	mono_add_internal_call("VI.LightSource/Radius::Set", &MM::iLightSource::SetRadius);
	mono_add_internal_call("VI.LightSource/SpriteColor::Set", &MM::iLightSource::SetSpriteColor);
}
