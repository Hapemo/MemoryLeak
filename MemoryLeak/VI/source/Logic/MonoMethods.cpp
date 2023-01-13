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
Checks for the state of certain key
\param STATE
- State of the key pressed
\param KEY
- Key to check the state of
\return bool
- Returns true if inputted state matches current state of specified key
*******************************************************************************/
void MonoMethods::RegisterCalls() {
	mono_add_internal_call("BonVoyage.InternalCalls::CheckKey", &FUNC->CheckKey);
	mono_add_internal_call("BonVoyage.InternalCalls::GetWorldMousePosX", &FUNC->GetWorldMousePosX);
	mono_add_internal_call("BonVoyage.InternalCalls::GetWorldMousePosY", &FUNC->GetWorldMousePosY);
	mono_add_internal_call("BonVoyage.InternalCalls::ApplyImpulse", &FUNC->ApplyImpulse);
	mono_add_internal_call("BonVoyage.InternalCalls::LoadDialogs", &FUNC->LoadDialogs);
	mono_add_internal_call("BonVoyage.InternalCalls::GetDialogue", &FUNC->GetDialogue);
	mono_add_internal_call("BonVoyage.InternalCalls::GetNextDialogueID", &FUNC->GetNextDialogueID);
	mono_add_internal_call("BonVoyage.InternalCalls::HasChoice", &FUNC->HasChoice);
	mono_add_internal_call("BonVoyage.InternalCalls::GetNext", &FUNC->GetNext);
	mono_add_internal_call("BonVoyage.InternalCalls::GetChoice1", &FUNC->GetChoice1);
	mono_add_internal_call("BonVoyage.InternalCalls::GetChoice2", &FUNC->GetChoice2);
	mono_add_internal_call("BonVoyage.InternalCalls::SetSelectedChoice", &FUNC->SetSelectedChoice);
	mono_add_internal_call("BonVoyage.InternalCalls::SetCurrentDialogueID", &FUNC->SetCurrentDialogueID);
	mono_add_internal_call("BonVoyage.InternalCalls::GetCurrentDialogueID", &FUNC->GetCurrentDialogueID);
	mono_add_internal_call("BonVoyage.InternalCalls::ChangeGameState", &FUNC->ChangeGameState);
	mono_add_internal_call("BonVoyage.InternalCalls::EntityIsActive", &FUNC->EntityIsActive);
	mono_add_internal_call("BonVoyage.InternalCalls::EntityActivate", &FUNC->EntityActivate);
	mono_add_internal_call("BonVoyage.InternalCalls::EntityDeactivate", &FUNC->EntityDeactivate);
	mono_add_internal_call("BonVoyage.InternalCalls::EntityGetParent", &FUNC->EntityGetParent);
	mono_add_internal_call("BonVoyage.InternalCalls::EntityGetParentId", &FUNC->EntityGetParentId);
	mono_add_internal_call("BonVoyage.InternalCalls::PauseScene", &FUNC->PauseScene);
	mono_add_internal_call("BonVoyage.InternalCalls::PlayScene", &FUNC->PlayScene);
	mono_add_internal_call("BonVoyage.InternalCalls::GetCurrentCameraScaleX", &FUNC->GetCurrentCameraScaleX);
	mono_add_internal_call("BonVoyage.InternalCalls::GetCurrentCameraScaleY", &FUNC->GetCurrentCameraScaleY);
	mono_add_internal_call("BonVoyage.InternalCalls::GetCurrentCameraPosX", &FUNC->GetCurrentCameraPosX);
	mono_add_internal_call("BonVoyage.InternalCalls::GetCurrentCameraPosY", &FUNC->GetCurrentCameraPosY);
	mono_add_internal_call("BonVoyage.InternalCalls::SetCurrentCameraScaleX", &FUNC->SetCurrentCameraScaleX);
	mono_add_internal_call("BonVoyage.InternalCalls::SetCurrentCameraScaleY", &FUNC->SetCurrentCameraScaleY);
	mono_add_internal_call("BonVoyage.InternalCalls::SetCurrentCameraPosX", &FUNC->SetCurrentCameraPosX);
	mono_add_internal_call("BonVoyage.InternalCalls::SetCurrentCameraPosY", &FUNC->SetCurrentCameraPosY);
	mono_add_internal_call("BonVoyage.InternalCalls::SetTexture", &FUNC->SetTexture);
	mono_add_internal_call("BonVoyage.InternalCalls::GetTexture", &FUNC->GetTexture);
	mono_add_internal_call("BonVoyage.InternalCalls::EntitiesCollided", &FUNC->EntitiesCollided);
	mono_add_internal_call("BonVoyage.InternalCalls::CheckCollision", &FUNC->CheckCollision);
	mono_add_internal_call("BonVoyage.InternalCalls::GameStateExit", &FUNC->GameStateExit);
	mono_add_internal_call("BonVoyage.InternalCalls::GetDeltaTime", &FUNC->GetDeltaTime);
	mono_add_internal_call("BonVoyage.InternalCalls::InitScriptWindow", &FUNC->InitScriptWindow);
	mono_add_internal_call("BonVoyage.InternalCalls::PlayAnySound", &FUNC->PlayAnySound);
	mono_add_internal_call("BonVoyage.InternalCalls::IsPlaying", &FUNC->IsPlaying);
	mono_add_internal_call("BonVoyage.InternalCalls::PlayBGSound", &FUNC->PlayBGSound);
	mono_add_internal_call("BonVoyage.InternalCalls::GetPosX", &FUNC->GetPosX);
	mono_add_internal_call("BonVoyage.InternalCalls::GetPosY", &FUNC->GetPosY);
	mono_add_internal_call("BonVoyage.InternalCalls::SetPosX", &FUNC->SetPosX);
	mono_add_internal_call("BonVoyage.InternalCalls::SetPosY", &FUNC->SetPosY);
	mono_add_internal_call("BonVoyage.InternalCalls::GetScaleX", &FUNC->GetScaleX);
	mono_add_internal_call("BonVoyage.InternalCalls::GetScaleY", &FUNC->GetScaleY);
	mono_add_internal_call("BonVoyage.InternalCalls::SetScaleX", &FUNC->SetScaleX);
	mono_add_internal_call("BonVoyage.InternalCalls::SetScaleY", &FUNC->SetScaleY);
	mono_add_internal_call("BonVoyage.InternalCalls::GetRotate", &FUNC->GetRotate);
	mono_add_internal_call("BonVoyage.InternalCalls::SetRotate", &FUNC->SetRotate);
}
