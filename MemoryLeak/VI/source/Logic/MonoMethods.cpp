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
	mono_add_internal_call("BonVoyage.InternalCalls::GetWorldMousePos", &FUNC->GetWorldMousePos);
	mono_add_internal_call("BonVoyage.InternalCalls::ApplyImpulse", &FUNC->ApplyImpulse);
	mono_add_internal_call("BonVoyage.InternalCalls::LoadDialogs", &FUNC->LoadDialogs);
	mono_add_internal_call("BonVoyage.InternalCalls::GetDialogue", &FUNC->GetDialogue);
	mono_add_internal_call("BonVoyage.InternalCalls::GetNextDialogueID", &FUNC->GetNextDialogueID);
	mono_add_internal_call("BonVoyage.InternalCalls::HasChoice", &FUNC->HasChoice);
	mono_add_internal_call("BonVoyage.InternalCalls::GetChoices", &FUNC->GetChoices);
	mono_add_internal_call("BonVoyage.InternalCalls::SetSelectedChoice", &FUNC->SetSelectedChoice);
	mono_add_internal_call("BonVoyage.InternalCalls::SetCurrentDialogueID", &FUNC->SetCurrentDialogueID);
	mono_add_internal_call("BonVoyage.InternalCalls::GetCurrentDialogueID", &FUNC->GetCurrentDialogueID);
	mono_add_internal_call("BonVoyage.InternalCalls::ChangeGameState", &FUNC->ChangeGameState);
	mono_add_internal_call("BonVoyage.InternalCalls::GetEntity", &FUNC->GetEntity);
	mono_add_internal_call("BonVoyage.InternalCalls::SelectScene", &FUNC->SelectScene);
	mono_add_internal_call("BonVoyage.InternalCalls::SetTexture", &FUNC->SetTexture);
	mono_add_internal_call("BonVoyage.InternalCalls::GetTexture", &FUNC->GetTexture);
	mono_add_internal_call("BonVoyage.InternalCalls::EntitiesCollided", &FUNC->EntitiesCollided);
	mono_add_internal_call("BonVoyage.InternalCalls::GameStateExit", &FUNC->GameStateExit);
	mono_add_internal_call("BonVoyage.InternalCalls::GetDeltaTime", &FUNC->GetDeltaTime);
	mono_add_internal_call("BonVoyage.InternalCalls::InitScriptWindow", &FUNC->InitScriptWindow);
	mono_add_internal_call("BonVoyage.InternalCalls::PlayAnySound", &FUNC->PlayAnySound);
	mono_add_internal_call("BonVoyage.InternalCalls::IsPlaying", &FUNC->IsPlaying);
	mono_add_internal_call("BonVoyage.InternalCalls::PlayBGSound", &FUNC->PlayBGSound);
}
