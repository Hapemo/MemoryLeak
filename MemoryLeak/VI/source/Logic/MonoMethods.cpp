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
	// Test
	mono_add_internal_call("VI.Test::ArgString", &FUNC->TestArgString);
	mono_add_internal_call("VI.Test::ReturnString", &FUNC->TestReturnString);
	mono_add_internal_call("BonVoyage.THIS::IsActive", &FUNC->EntityIsActive2);

	// General
	mono_add_internal_call("VI.General::DeltaTime", &FUNC->GetDeltaTime);

	// Inputs
	mono_add_internal_call("VI.Input/Key::Press", &FUNC->CheckKeyPress);
	mono_add_internal_call("VI.Input/Key::Hold", &FUNC->CheckKeyHold);
	mono_add_internal_call("VI.Input/Key::Release", &FUNC->CheckKeyRelease);
	mono_add_internal_call("VI.Input/Key::Idle", &FUNC->CheckKeyIdle);
	mono_add_internal_call("VI.Input/Button::Clicked", &MonoMethods::ButtonClicked);
	mono_add_internal_call("VI.Input/Button::Released", &MonoMethods::ButtonReleased);
	mono_add_internal_call("VI.Input/Button::Hover", &MonoMethods::ButtonHover);
	mono_add_internal_call("VI.Input/Mouse::WorldPosX", &FUNC->GetWorldMousePosX);
	mono_add_internal_call("VI.Input/Mouse::WorldPosY", &FUNC->GetWorldMousePosY);
	mono_add_internal_call("VI.Input/Mouse::Press", &FUNC->CheckKeyPress); //
	mono_add_internal_call("VI.Input/Mouse::Hold", &FUNC->CheckKeyHold); //
	mono_add_internal_call("VI.Input/Mouse::Release", &FUNC->CheckKeyRelease); //
	mono_add_internal_call("VI.Input/Mouse::Idle", &FUNC->CheckKeyIdle); //

	// Physics
	mono_add_internal_call("VI.Physics::ApplyImpulse", &MonoMethods::ApplyImpulse);
	mono_add_internal_call("VI.Physics::EntitiesCollided", &MonoMethods::EntitiesCollided);
	mono_add_internal_call("VI.Physics::CheckCollision", &MonoMethods::CheckCollision);

	// Dialogue
	mono_add_internal_call("VI.Dialogue::LoadScript", &MonoMethods::LoadDialogs);
	mono_add_internal_call("VI.Dialogue::GetLine", &MonoMethods::GetDialogue);
	mono_add_internal_call("VI.Dialogue::HaveChoices", &FUNC->HasChoice);
	mono_add_internal_call("VI.Dialogue/Current::GetLine", &MonoMethods::GetDialogue); //
	mono_add_internal_call("VI.Dialogue/Current::GetId", &FUNC->GetCurrentDialogueID);
	mono_add_internal_call("VI.Dialogue/Current::HaveChoices", &FUNC->HasChoice); //
	mono_add_internal_call("VI.Dialogue/Current::SetTo", &FUNC->SetCurrentDialogueID);
	mono_add_internal_call("VI.Dialogue/Current::GetChoice1", &FUNC->GetChoice1); //
	mono_add_internal_call("VI.Dialogue/Current::GetChoice2", &FUNC->GetChoice2); //
	mono_add_internal_call("VI.Dialogue/Current::SetSelectedChoice", &FUNC->SetSelectedChoice); //
	mono_add_internal_call("VI.Dialogue/current::PlayerSpeaking", &FUNC->IsPlayerSpeaker); //
	mono_add_internal_call("VI.Dialogue/Next::GetLine", &FUNC->GetNext); //
	mono_add_internal_call("VI.Dialogue/Next::GetLine2", &FUNC->GetNext); // !!
	mono_add_internal_call("VI.Dialogue/Next::GetId", &FUNC->GetNextDialogueID);
	mono_add_internal_call("VI.Dialogue/Next::GetId2", &FUNC->GetNextDialogueID); // !!
	mono_add_internal_call("VI.Dialogue/Next::HaveChoices", &FUNC->HasChoice); //
	mono_add_internal_call("VI.Dialogue/Next::GetChoice1", &FUNC->GetChoice1); //
	mono_add_internal_call("VI.Dialogue/Next::GetChoice2", &FUNC->GetChoice2); //
	mono_add_internal_call("VI.Dialogue/Next::PlayerSpeaking", &FUNC->IsPlayerSpeaker); //
	mono_add_internal_call("VI.Dialogue/Choice::First", &FUNC->GetChoice1);
	mono_add_internal_call("VI.Dialogue/Choice::Second", &FUNC->GetChoice2);
	mono_add_internal_call("VI.Dialogue/Choice::Selected", &FUNC->SetSelectedChoice);
	mono_add_internal_call("VI.Dialogue/Speaker::IsPlayer", &FUNC->IsPlayerSpeaker);

	// Gamestate
	mono_add_internal_call("VI.GameState::Go", &MonoMethods::ChangeGameState);
	mono_add_internal_call("VI.GameState::GetName", &MonoMethods::GetCurrentGameStateName);
	mono_add_internal_call("VI.GameState::Exit", &FUNC->GameStateExit);

	// Entity
	mono_add_internal_call("VI.Entity::GetId", &MonoMethods::GetEntityId);
	mono_add_internal_call("VI.Entity::IsActive", &MonoMethods::EntityIsActive);
	mono_add_internal_call("VI.Entity::SetActive", &MonoMethods::SetEntityIsActive);
	mono_add_internal_call("VI.Entity::Activate", &MonoMethods::EntityActivate);
	mono_add_internal_call("VI.Entity::Deactivate", &MonoMethods::EntityDeactivate);
	mono_add_internal_call("VI.Entity/Parent::Name", &MonoMethods::EntityGetParent);
	mono_add_internal_call("VI.Entity/Parent::Id", &MonoMethods::EntityGetParentId);

	// Scene
	mono_add_internal_call("VI.Scene::Pause", &MonoMethods::PauseScene);
	mono_add_internal_call("VI.Scene::Play", &MonoMethods::PlayScene);

	// Camera
	mono_add_internal_call("VI.Camera/GetScale::X", &FUNC->GetCurrentCameraScaleX);
	mono_add_internal_call("VI.Camera/GetScale::Y", &FUNC->GetCurrentCameraScaleY);
	mono_add_internal_call("VI.Camera/GetPos::X", &FUNC->GetCurrentCameraPosX);
	mono_add_internal_call("VI.Camera/GetPos::Y", &FUNC->GetCurrentCameraPosY);
	mono_add_internal_call("VI.Camera/SetScale::X", &FUNC->SetCurrentCameraScaleX);
	mono_add_internal_call("VI.Camera/SetScale::Y", &FUNC->SetCurrentCameraScaleY);
	mono_add_internal_call("VI.Camera/SetPos::X", &FUNC->SetCurrentCameraPosX);
	mono_add_internal_call("VI.Camera/SetPos::Y", &FUNC->SetCurrentCameraPosY);

	// Math
	mono_add_internal_call("VI.Math::SqMagnitude", &FUNC->SqMagnitude);
	mono_add_internal_call("VI.Math/Normalize::X", &FUNC->NormalizeX);
	mono_add_internal_call("VI.Math/Normalize::Y", &FUNC->NormalizeY);
	mono_add_internal_call("VI.Math::ArcTangent", &FUNC->ArcTangent);
	mono_add_internal_call("VI.Math::Negate", &FUNC->Negate);

	// Animation
	mono_add_internal_call("VI.Animation/SheetIndex::Set", &MonoMethods::SetSpriteSheetIndex);
	mono_add_internal_call("VI.Animation/SheetIndex::Get", &MonoMethods::GetSpriteSheetIndex);
	mono_add_internal_call("VI.Animation/Speed::Set", &MonoMethods::SetAnimationSpeed);
	mono_add_internal_call("VI.Animation/Speed::Get", &MonoMethods::GetAnimationSpeed);
	mono_add_internal_call("VI.Animation/CurrentFrame::Set", &MonoMethods::SetAnimationCurrentIndex);
	mono_add_internal_call("VI.Animation/CurrentFrame::Get", &MonoMethods::GetAnimationCurrentIndex);
	mono_add_internal_call("VI.Animation/FrameCount::Get", &MonoMethods::GetAnimationFrameCount);
	mono_add_internal_call("VI.Animation/FrameCount::Set", &MonoMethods::SetAnimationFrameCount);

	// Textures
	mono_add_internal_call("VI.Texture::Set", &MonoMethods::SetTexture);
	mono_add_internal_call("VI.Texture::Get", &MonoMethods::GetTexture);

	// Audio
	mono_add_internal_call("VI.Audio::Stop", &MonoMethods::StopSound);
	mono_add_internal_call("VI.Audio::StopAll", &MonoMethods::StopSound); //
	mono_add_internal_call("VI.Audio::StopBGM", &MonoMethods::StopSound); //
	mono_add_internal_call("VI.Audio::StopSFX", &MonoMethods::StopSound); //
	mono_add_internal_call("VI.Audio::Play", &MonoMethods::PlayEntitySound);
	mono_add_internal_call("VI.Audio::PlayOnLoop", &MonoMethods::PlaySoundOnLoop);
	mono_add_internal_call("VI.Audio/Channel::Play", &MonoMethods::PlaySoundInChannel);
	mono_add_internal_call("VI.Audio/Channel::PlayBGM", &MonoMethods::PlayBGSound);
	mono_add_internal_call("VI.Audio/Channel::Stop", &MonoMethods::StopSound); //
	mono_add_internal_call("VI.Audio/Channel::IsPlaying", &FUNC->IsPlaying);
	mono_add_internal_call("VI.Audio/Volume::SetVolume", &MonoMethods::StopSound); //
	mono_add_internal_call("VI.Audio/Volume::SetBGMVolume", &MonoMethods::StopSound); //
	mono_add_internal_call("VI.Audio/Volume::SetSFXVolume", &MonoMethods::StopSound); //

	// Transform
	mono_add_internal_call("VI.Transform/Position::GetX", &MonoMethods::GetPosX);
	mono_add_internal_call("VI.Transform/Position::GetY", &MonoMethods::GetPosY);
	mono_add_internal_call("VI.Transform/Position::SetX", &MonoMethods::SetPosX);
	mono_add_internal_call("VI.Transform/Position::SetY", &MonoMethods::SetPosY);
	mono_add_internal_call("VI.Transform/Scale::GetX", &MonoMethods::GetScaleX);
	mono_add_internal_call("VI.Transform/Scale::GetY", &MonoMethods::GetScaleY);
	mono_add_internal_call("VI.Transform/Scale::SetX", &MonoMethods::SetScaleX);
	mono_add_internal_call("VI.Transform/Scale::SetY", &MonoMethods::SetScaleY);
	mono_add_internal_call("VI.Transform/Rotate::Get", &MonoMethods::GetRotate);
	mono_add_internal_call("VI.Transform/Rotate::Set", &MonoMethods::SetRotate);

	// Text
	mono_add_internal_call("VI.Text::Update", &MonoMethods::UpdateText);
	mono_add_internal_call("VI.Text::GetLineCount", &MonoMethods::GetLineCount);
	mono_add_internal_call("VI.Text/Offset::Set", &MonoMethods::SetTextOffset);
	mono_add_internal_call("VI.Text/Offset::GetX", &MonoMethods::SetTextOffset); //
	mono_add_internal_call("VI.Text/Offset::GetY", &MonoMethods::SetTextOffset); //
	mono_add_internal_call("VI.Text/Scale::Get", &MonoMethods::GetFontScale);
	mono_add_internal_call("VI.Text/Scale::Set", &MonoMethods::GetFontScale); //

	// Weather
	mono_add_internal_call("VI.Weather::Init", &FUNC->WeatherAIinit);
	mono_add_internal_call("VI.Weather::GetCurrent", &FUNC->GetCurrentWeather);

	// LightSource
	mono_add_internal_call("VI.LightSource/Radius::Get", &MonoMethods::GetLightSourceRadius);
	mono_add_internal_call("VI.LightSource/Radius::Set", &MonoMethods::SetLightSourceRadius);
	mono_add_internal_call("VI.LightSource/SpriteColor::Set", &MonoMethods::SetSpriteColor);
}
