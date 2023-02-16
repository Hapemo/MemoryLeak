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
Internal Call functions that uses MonoString.
*******************************************************************************/
void MonoMethods::ApplyImpulse(MonoString* _entityName, MonoString* _sceneName, const float _impulseX, const float _impulseY, const float _rotationX, const float _rotationY) {
	FUNC->ApplyImpulse(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName), _impulseX, _impulseY, _rotationX, _rotationY);
}

void MonoMethods::LoadDialogs(MonoString* _filename) {
	FUNC->LoadDialogs(MONO->ConvertFromMonoString(_filename));
}

MonoString* MonoMethods::GetDialogue(int _id) {
	return MONO->ConvertToMonoString(FUNC->GetDialogue(_id));
}

void MonoMethods::ChangeGameState(MonoString* _name) {
	FUNC->ChangeGameState(MONO->ConvertFromMonoString(_name));
}

int MonoMethods::GetEntityId(MonoString* _entityName, MonoString* _sceneName) {
	return FUNC->GetEntityId(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName));
}

bool MonoMethods::EntityIsActive(MonoString* _entityName, MonoString* _sceneName) {
	return FUNC->EntityIsActive(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName));
}

void MonoMethods::SetEntityIsActive(MonoString* _entityName, MonoString* _sceneName, bool _active) {
	FUNC->SetEntityIsActive(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName), _active);
}

void MonoMethods::EntityActivate(MonoString* _entityName, MonoString* _sceneName) {
	FUNC->EntityActivate(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName));
}

void MonoMethods::EntityDeactivate(MonoString* _entityName, MonoString* _sceneName) {
	FUNC->EntityDeactivate(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName));
}

MonoString* MonoMethods::EntityGetParent(MonoString* _entityName, MonoString* _sceneName) {
	return MONO->ConvertToMonoString(FUNC->EntityGetParent(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName)));
}

int MonoMethods::EntityGetParentId(MonoString* _entityName, MonoString* _sceneName) {
	return FUNC->EntityGetParentId(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName));
}

MonoString* MonoMethods::GetCurrentGameStateName() {
	return MONO->ConvertToMonoString(FUNC->GetCurrentGameStateName());
}

void MonoMethods::PauseScene(MonoString* _name) {
	FUNC->PauseScene(MONO->ConvertFromMonoString(_name));
}

void MonoMethods::PlayScene(MonoString* _name) {
	FUNC->PlayScene(MONO->ConvertFromMonoString(_name));
}

void MonoMethods::SetAnimationSpeed(MonoString* _entityName, MonoString* _sceneName, float _speed) {
	FUNC->SetAnimationSpeed(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName), _speed);
}

float MonoMethods::GetAnimationSpeed(MonoString* _entityName, MonoString* _sceneName) {
	return FUNC->GetAnimationSpeed(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName));
}

void MonoMethods::SetAnimationCurrentIndex(MonoString* _entityName, MonoString* _sceneName, int _index) {
	FUNC->SetAnimationCurrentIndex(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName), _index);
}

int MonoMethods::GetAnimationCurrentIndex(MonoString* _entityName, MonoString* _sceneName) {
	return FUNC->GetAnimationCurrentIndex(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName));
}

int MonoMethods::GetAnimationFrameCount(MonoString* _entityName, MonoString* _sceneName) {
	return FUNC->GetAnimationFrameCount(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName));
}

void MonoMethods::SetAnimationFrameCount(MonoString* _entityName, MonoString* _sceneName, int _count) {
	return FUNC->SetAnimationFrameCount(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName), _count);
}

void MonoMethods::SetSpriteSheetIndex(MonoString* _entityName, MonoString* _sceneName, int _index) {
	FUNC->SetSpriteSheetIndex(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName), _index);
}

int MonoMethods::GetSpriteSheetIndex(MonoString* _entityName, MonoString* _sceneName) {
	return FUNC->GetSpriteSheetIndex(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName));
}

void MonoMethods::SetTexture(MonoString* _entityName, MonoString* _sceneName, MonoString* _path) {
	FUNC->SetTexture(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName), MONO->ConvertFromMonoString(_path));
}

MonoString* MonoMethods::GetTexture(MonoString* _entityName, MonoString* _sceneName) {
	return MONO->ConvertToMonoString(FUNC->GetTexture(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName)));
}

bool MonoMethods::EntitiesCollided(MonoString* _entityName1, MonoString* _entityName2, MonoString* _sceneName) {
	return FUNC->EntitiesCollided(MONO->ConvertFromMonoString(_entityName1), MONO->ConvertFromMonoString(_entityName2), MONO->ConvertFromMonoString(_sceneName));
}

bool MonoMethods::CheckCollision(MonoString* _entityName1, MonoString* _entityName2, MonoString* _sceneName, bool _dynamicCheck) {
	return FUNC->CheckCollision(MONO->ConvertFromMonoString(_entityName1), MONO->ConvertFromMonoString(_entityName2), MONO->ConvertFromMonoString(_sceneName), _dynamicCheck);
}

void MonoMethods::StopSound(MonoString* _entityName, MonoString* _sceneName) {
	FUNC->StopSound(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName));
}

void MonoMethods::PlaySoundOnLoop(MonoString* _entityName, MonoString* _sceneName) {
	FUNC->PlaySoundOnLoop(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName));
}

void MonoMethods::PlayEntitySound(MonoString* _entityName, MonoString* _sceneName) {
	FUNC->PlayEntitySound(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName));
}

void MonoMethods::PlayBGSound(MonoString* _name, int _channel) {
	FUNC->PlayBGSound(MONO->ConvertFromMonoString(_name), _channel);
}

void MonoMethods::PlaySoundInChannel(MonoString* _name, int _channel) {
	FUNC->PlaySoundInChannel(MONO->ConvertFromMonoString(_name), _channel);
}

float MonoMethods::GetPosX(MonoString* _entityName, MonoString* _sceneName) {
	return FUNC->GetPosX(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName));
}

float MonoMethods::GetPosY(MonoString* _entityName, MonoString* _sceneName) {
	return FUNC->GetPosY(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName));
}

void MonoMethods::SetPosX(MonoString* _entityName, MonoString* _sceneName, float _posX) {
	FUNC->SetPosX(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName), _posX);
}

void MonoMethods::SetPosY(MonoString* _entityName, MonoString* _sceneName, float _posY) {
	FUNC->SetPosY(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName), _posY);
}

float MonoMethods::GetScaleX(MonoString* _entityName, MonoString* _sceneName) {
	return FUNC->GetScaleX(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName));
}

float MonoMethods::GetScaleY(MonoString* _entityName, MonoString* _sceneName) {
	return FUNC->GetScaleY(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName));
}

void MonoMethods::SetScaleX(MonoString* _entityName, MonoString* _sceneName, float _scaleX) {
	FUNC->SetScaleX(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName), _scaleX);
}

void MonoMethods::SetScaleY(MonoString* _entityName, MonoString* _sceneName, float _scaleY) {
	FUNC->SetScaleY(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName), _scaleY);
}

float MonoMethods::GetRotate(MonoString* _entityName, MonoString* _sceneName) {
	return FUNC->GetRotate(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName));
}

void MonoMethods::SetRotate(MonoString* _entityName, MonoString* _sceneName, float _rotate) {
	FUNC->SetRotate(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName), _rotate);
}

bool MonoMethods::ButtonClicked(MonoString* _entityName, MonoString* _sceneName) {
	return FUNC->ButtonClicked(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName));
}

bool MonoMethods::ButtonReleased(MonoString* _entityName, MonoString* _sceneName) {
	return FUNC->ButtonReleased(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName));
}

bool MonoMethods::ButtonHover(MonoString* _entityName, MonoString* _sceneName) {
	return FUNC->ButtonHover(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName));
}

void MonoMethods::UpdateText(MonoString* _entityName, MonoString* _sceneName, MonoString* _text) {
	FUNC->UpdateText(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName), MONO->ConvertFromMonoString(_text));
}

void MonoMethods::SetTextOffset(MonoString* _entityName, MonoString* _sceneName, float _xoffset, float _yoffset) {
	FUNC->SetTextOffset(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName), _xoffset, _yoffset);
}

int MonoMethods::GetLineCount(MonoString* _entityName, MonoString* _sceneName) {
	return FUNC->GetLineCount(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName));
}

float MonoMethods::GetLightSourceRadius(MonoString* _entityName, MonoString* _sceneName)
{
	return FUNC->GetLightSourceRadius(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName));
}

void  MonoMethods::SetLightSourceRadius(MonoString* _entityName, MonoString* _sceneName, float _radius)
{
	FUNC->SetLightSourceRadius(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName), _radius);
}

void MonoMethods::SetSpriteColor(MonoString* _entityName, MonoString* _sceneName, int _r, int _g, int _b, int _a)
{
	FUNC->SetSpriteColor(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName), _r, _g, _b, _a);
}

float MonoMethods::GetFontScale(MonoString* _entityName, MonoString* _sceneName)
{
	return FUNC->GetFontScale(MONO->ConvertFromMonoString(_entityName), MONO->ConvertFromMonoString(_sceneName));
}

/*!*****************************************************************************
\brief
	Registers the internal calls for mono use.
*******************************************************************************/
void MonoMethods::RegisterCalls() {
	mono_add_internal_call("BonVoyage.InternalCalls::TestArgString", &FUNC->TestArgString);
	mono_add_internal_call("BonVoyage.InternalCalls::TestReturnString", &FUNC->TestReturnString);
	mono_add_internal_call("BonVoyage.InternalCalls::CheckKeyPress", &FUNC->CheckKeyPress);
	mono_add_internal_call("BonVoyage.InternalCalls::CheckKeyHold", &FUNC->CheckKeyHold);
	mono_add_internal_call("BonVoyage.InternalCalls::CheckKeyRelease", &FUNC->CheckKeyRelease);
	mono_add_internal_call("BonVoyage.InternalCalls::CheckKeyIdle", &FUNC->CheckKeyIdle);
	mono_add_internal_call("BonVoyage.InternalCalls::GetWorldMousePosX", &FUNC->GetWorldMousePosX);
	mono_add_internal_call("BonVoyage.InternalCalls::GetWorldMousePosY", &FUNC->GetWorldMousePosY);
	mono_add_internal_call("BonVoyage.InternalCalls::ApplyImpulse", &MonoMethods::ApplyImpulse);
	mono_add_internal_call("BonVoyage.InternalCalls::LoadDialogs", &MonoMethods::LoadDialogs);
	mono_add_internal_call("BonVoyage.InternalCalls::GetDialogue", &MonoMethods::GetDialogue);
	mono_add_internal_call("BonVoyage.InternalCalls::GetNextDialogueID", &FUNC->GetNextDialogueID);
	mono_add_internal_call("BonVoyage.InternalCalls::HasChoice", &FUNC->HasChoice);
	mono_add_internal_call("BonVoyage.InternalCalls::GetNext", &FUNC->GetNext);
	mono_add_internal_call("BonVoyage.InternalCalls::GetChoice1", &FUNC->GetChoice1);
	mono_add_internal_call("BonVoyage.InternalCalls::GetChoice2", &FUNC->GetChoice2);
	mono_add_internal_call("BonVoyage.InternalCalls::SetSelectedChoice", &FUNC->SetSelectedChoice);
	mono_add_internal_call("BonVoyage.InternalCalls::SetCurrentDialogueID", &FUNC->SetCurrentDialogueID);
	mono_add_internal_call("BonVoyage.InternalCalls::GetCurrentDialogueID", &FUNC->GetCurrentDialogueID);
	mono_add_internal_call("BonVoyage.InternalCalls::IsPlayerSpeaker", &FUNC->IsPlayerSpeaker);
	mono_add_internal_call("BonVoyage.InternalCalls::ChangeGameState", &MonoMethods::ChangeGameState);
	mono_add_internal_call("BonVoyage.InternalCalls::GetEntityId", &MonoMethods::GetEntityId);
	mono_add_internal_call("BonVoyage.InternalCalls::EntityIsActive", &MonoMethods::EntityIsActive);
	mono_add_internal_call("BonVoyage.InternalCalls::SetEntityIsActive", &MonoMethods::SetEntityIsActive);
	mono_add_internal_call("BonVoyage.InternalCalls::EntityActivate", &MonoMethods::EntityActivate);
	mono_add_internal_call("BonVoyage.InternalCalls::EntityDeactivate", &MonoMethods::EntityDeactivate);
	mono_add_internal_call("BonVoyage.InternalCalls::EntityGetParent", &MonoMethods::EntityGetParent);
	mono_add_internal_call("BonVoyage.InternalCalls::EntityGetParentId", &MonoMethods::EntityGetParentId);
	mono_add_internal_call("BonVoyage.InternalCalls::GetCurrentGameStateName", &MonoMethods::GetCurrentGameStateName);
	mono_add_internal_call("BonVoyage.InternalCalls::PauseScene", &MonoMethods::PauseScene);
	mono_add_internal_call("BonVoyage.InternalCalls::PlayScene", &MonoMethods::PlayScene);
	mono_add_internal_call("BonVoyage.InternalCalls::GetCurrentCameraScaleX", &FUNC->GetCurrentCameraScaleX);
	mono_add_internal_call("BonVoyage.InternalCalls::GetCurrentCameraScaleY", &FUNC->GetCurrentCameraScaleY);
	mono_add_internal_call("BonVoyage.InternalCalls::GetCurrentCameraPosX", &FUNC->GetCurrentCameraPosX);
	mono_add_internal_call("BonVoyage.InternalCalls::GetCurrentCameraPosY", &FUNC->GetCurrentCameraPosY);
	mono_add_internal_call("BonVoyage.InternalCalls::SetCurrentCameraScaleX", &FUNC->SetCurrentCameraScaleX);
	mono_add_internal_call("BonVoyage.InternalCalls::SetCurrentCameraScaleY", &FUNC->SetCurrentCameraScaleY);
	mono_add_internal_call("BonVoyage.InternalCalls::SetCurrentCameraPosX", &FUNC->SetCurrentCameraPosX);
	mono_add_internal_call("BonVoyage.InternalCalls::SetCurrentCameraPosY", &FUNC->SetCurrentCameraPosY);
	mono_add_internal_call("BonVoyage.InternalCalls::SqMagnitude", &FUNC->SqMagnitude);
	mono_add_internal_call("BonVoyage.InternalCalls::NormalizeX", &FUNC->NormalizeX);
	mono_add_internal_call("BonVoyage.InternalCalls::NormalizeY", &FUNC->NormalizeY);
	mono_add_internal_call("BonVoyage.InternalCalls::ArcTangent", &FUNC->ArcTangent);
	mono_add_internal_call("BonVoyage.InternalCalls::Negate", &FUNC->Negate);
	mono_add_internal_call("BonVoyage.InternalCalls::SetAnimationSpeed", &MonoMethods::SetAnimationSpeed);
	mono_add_internal_call("BonVoyage.InternalCalls::GetAnimationSpeed", &MonoMethods::GetAnimationSpeed);
	mono_add_internal_call("BonVoyage.InternalCalls::SetAnimationCurrentIndex", &MonoMethods::SetAnimationCurrentIndex);
	mono_add_internal_call("BonVoyage.InternalCalls::GetAnimationCurrentIndex", &MonoMethods::GetAnimationCurrentIndex);
	mono_add_internal_call("BonVoyage.InternalCalls::GetAnimationFrameCount", &MonoMethods::GetAnimationFrameCount);
	mono_add_internal_call("BonVoyage.InternalCalls::SetAnimationFrameCount", &MonoMethods::SetAnimationFrameCount);
	mono_add_internal_call("BonVoyage.InternalCalls::SetSpriteSheetIndex", &MonoMethods::SetSpriteSheetIndex);
	mono_add_internal_call("BonVoyage.InternalCalls::GetSpriteSheetIndex", &MonoMethods::GetSpriteSheetIndex);
	mono_add_internal_call("BonVoyage.InternalCalls::SetTexture", &MonoMethods::SetTexture);
	mono_add_internal_call("BonVoyage.InternalCalls::GetTexture", &MonoMethods::GetTexture);
	mono_add_internal_call("BonVoyage.InternalCalls::EntitiesCollided", &MonoMethods::EntitiesCollided);
	mono_add_internal_call("BonVoyage.InternalCalls::CheckCollision", &MonoMethods::CheckCollision);
	mono_add_internal_call("BonVoyage.InternalCalls::GameStateExit", &FUNC->GameStateExit);
	mono_add_internal_call("BonVoyage.InternalCalls::GetDeltaTime", &FUNC->GetDeltaTime);
	mono_add_internal_call("BonVoyage.InternalCalls::StopSound", &MonoMethods::StopSound);
	mono_add_internal_call("BonVoyage.InternalCalls::PlaySoundOnLoop", &MonoMethods::PlaySoundOnLoop);
	mono_add_internal_call("BonVoyage.InternalCalls::PlayEntitySound", &MonoMethods::PlayEntitySound);
	mono_add_internal_call("BonVoyage.InternalCalls::PlaySoundInChannel", &MonoMethods::PlaySoundInChannel);
	mono_add_internal_call("BonVoyage.InternalCalls::IsPlaying", &FUNC->IsPlaying);
	mono_add_internal_call("BonVoyage.InternalCalls::PlayBGSound", &MonoMethods::PlayBGSound);
	mono_add_internal_call("BonVoyage.InternalCalls::GetPosX", &MonoMethods::GetPosX);
	mono_add_internal_call("BonVoyage.InternalCalls::GetPosY", &MonoMethods::GetPosY);
	mono_add_internal_call("BonVoyage.InternalCalls::SetPosX", &MonoMethods::SetPosX);
	mono_add_internal_call("BonVoyage.InternalCalls::SetPosY", &MonoMethods::SetPosY);
	mono_add_internal_call("BonVoyage.InternalCalls::GetScaleX", &MonoMethods::GetScaleX);
	mono_add_internal_call("BonVoyage.InternalCalls::GetScaleY", &MonoMethods::GetScaleY);
	mono_add_internal_call("BonVoyage.InternalCalls::SetScaleX", &MonoMethods::SetScaleX);
	mono_add_internal_call("BonVoyage.InternalCalls::SetScaleY", &MonoMethods::SetScaleY);
	mono_add_internal_call("BonVoyage.InternalCalls::GetRotate", &MonoMethods::GetRotate);
	mono_add_internal_call("BonVoyage.InternalCalls::SetRotate", &MonoMethods::SetRotate);
	mono_add_internal_call("BonVoyage.InternalCalls::ButtonClicked", &MonoMethods::ButtonClicked);
	mono_add_internal_call("BonVoyage.InternalCalls::ButtonReleased", &MonoMethods::ButtonReleased);
	mono_add_internal_call("BonVoyage.InternalCalls::ButtonHover", &MonoMethods::ButtonHover);
	mono_add_internal_call("BonVoyage.InternalCalls::UpdateText", &MonoMethods::UpdateText);
	mono_add_internal_call("BonVoyage.InternalCalls::SetTextOffset", &MonoMethods::SetTextOffset);
	mono_add_internal_call("BonVoyage.InternalCalls::GetLineCount", &MonoMethods::GetLineCount);
	mono_add_internal_call("BonVoyage.InternalCalls::WeatherAIinit", &FUNC->WeatherAIinit);
	mono_add_internal_call("BonVoyage.InternalCalls::GetCurrentWeather", &FUNC->GetCurrentWeather);
	mono_add_internal_call("BonVoyage.InternalCalls::GetLightSourceRadius", &MonoMethods::GetLightSourceRadius);
	mono_add_internal_call("BonVoyage.InternalCalls::SetLightSourceRadius", &MonoMethods::SetLightSourceRadius);
	mono_add_internal_call("BonVoyage.InternalCalls::SetSpriteColor", &MonoMethods::SetSpriteColor);
	mono_add_internal_call("BonVoyage.InternalCalls::GetFontScale", &MonoMethods::GetFontScale);
}
