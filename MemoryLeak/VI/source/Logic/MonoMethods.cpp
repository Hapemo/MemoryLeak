///*!*****************************************************************************
//\file MonoMethods.h
//\author Chen Jia Wen
//\par DP email: c.jiawen\@digipen.edu
//\par Course: GAM200
//\par Group: Memory Leak Studios
//\date 04-01-2023
//\brief
//This file contains the function declarations of the class MonoMethods.
//MonoMethods are where all the mono internal calls functions that scripts need
//to use from the engine is being linked.
//*******************************************************************************/
//
//#include "MonoMethods.h"
//
///*!*****************************************************************************
//\brief
//Checks for the state of certain key
//\param STATE
//- State of the key pressed
//\param KEY
//- Key to check the state of
//\return bool
//- Returns true if inputted state matches current state of specified key
//*******************************************************************************/
//void MonoMethods::RegisterCalls() {
//	//mono_add_internal_call("BonVoyage.TestClass::CheckKey", &FUNC->CheckKey);
//	//mono_add_internal_call("BonVoyage.TestClass::GetWorldMousePos", &FUNC->GetWorldMousePos);
//}
////
/////*!*****************************************************************************
////\brief
////ApplyImpulse function that adds a velocity impulse to the entity
////\param const Entity &
////A reference to a read-only Entity to
////\param const Math::Vec2 &
////A reference to a read-only variable containing the velocity impulse
////\param const Math::Vec2 &
////A reference to a read-only variable containing the rotation impulse
////calculation
////\return void
////NULL
////*******************************************************************************/
////void MonoMethods::ApplyImpulse(const Entity& _e, const Math::Vec2& _impulse, const Math::Vec2& _rotation) {
////	physics2DManager->ApplyImpulse(_e, _impulse, _rotation);
////}
////
/////*!*****************************************************************************
////\brief
////	Loads the dialogs from a json file to the dialog manager
////
////\return
////None.
////*******************************************************************************/
////void MonoMethods::LoadDialogs(std::string _filename) {
////	LOG_INFO("Loading Dialog: " + _filename);
////	serializationManager->LoadDialogs(_filename);
////}
////
/////*!*****************************************************************************
////\brief
////Retrieves the dialog text of the dialog with a specific id using function from
////DialogManager.
////
////\param int _id
////The id of the dialog to get.
////
////\return
////Returns the dialog text in string.
////*******************************************************************************/
////std::string MonoMethods::GetDialogue(int _id) {
////	return dialogManager->GetDialogue(_id);
////}
////
/////*!*****************************************************************************
////\brief
////Retrieves the next dialog id using function from DialogManager.
////
////\param int _id
////The id of the current dialog.
////
////\return
////Returns the next dialog id.
////*******************************************************************************/
////int MonoMethods::GetNextDialogueID(int _id) {
////	return dialogManager->GetNext(_id);
////}
////
/////*!*****************************************************************************
////\brief
////Checks if the dialog with a specific id has choices using function from
////DialogManager.
////
////\param int _id
////The id of the dialog to be checked.
////
////\return
////Returns true if the dialog has choices else returns false.
////*******************************************************************************/
////bool MonoMethods::HasChoice(int _id) {
////	return dialogManager->HasChoice(_id);
////}
////
/////*!*****************************************************************************
////\brief
////Retrieves the choices of the dialog with a specific id using function from
////DialogManager.
////
////\param int _id
////The id of the dialog to get the choices of.
////
////\return
////Returns a pair of integers with the choices of the dialog.
////*******************************************************************************/
////std::pair<int, int> MonoMethods::GetChoices(int _id) {
////	return dialogManager->GetChoices(_id);
////}
////
/////*!*****************************************************************************
////\brief
////Set the selected choice using function from DialogManager.
////
////\param int _id
////The id of the current dialog.
////
////\param int _selectedChoice
////The selected choice.
////*******************************************************************************/
////void MonoMethods::SetSelectedChoice(int _id, int _selectedChoice) {
////	dialogManager->SetSelectedChoice(_id, _selectedChoice);
////}
////
/////*!*****************************************************************************
////\brief
////Get current dialogue id using function from DialogManager.
////
////\param int _id
////The id of the current dialog.
////*******************************************************************************/
////bool MonoMethods::SetCurrentDialogueID(int _id) {
////	return dialogManager->SetCurrentDialogueID(_id);
////}
////
/////*!*****************************************************************************
////\brief
////Get current dialogue id using function from DialogManager.
////
////\return
////The id of the current dialog.
////*******************************************************************************/
////int MonoMethods::GetCurrentDialogueID() {
////	return dialogManager->GetCurrentDialogueID();
////}
////
/////*!*****************************************************************************
////\brief
////This function is called by user, to change the next game state
////*******************************************************************************/
////void MonoMethods::ChangeGameState(std::string const& _name) {
////	GameStateManager::GetInstance()->ChangeGameState(_name);
////}
////
/////*!*****************************************************************************
////\brief
////Gets an entity from scene.
////*******************************************************************************/
////Entity MonoMethods::GetEntity(std::string const& _entityName, std::string const& _sceneName) {
////	return GameStateManager::GetInstance()->GetEntity(_entityName, _sceneName);
////}
////
/////*!*****************************************************************************
////\brief
////Gets scene to pause or unpause the scene.
////*******************************************************************************/
////Scene& MonoMethods::SelectScene(std::string const& _name) {
////	return GameStateManager::GetInstance()->SelectScene(_name);
////}
////
/////*!*****************************************************************************
////\brief
////Sets the texture of an entity.
////*******************************************************************************/
////void MonoMethods::SetTexture(const Entity& _e, const std::string& _path) {
////	spriteManager->SetTexture(_e, _path);
////}
////
/////*!*****************************************************************************
////\brief
////Retrieves the texture of an entity.
////*******************************************************************************/
////std::string MonoMethods::GetTexture(const Entity& _e) {
////	return spriteManager->GetTexturePath(spriteManager->GetTexture(_e));
////}
////
/////*!*****************************************************************************
////\brief
////EntitiesCollided function that checks if two given entities have collided by
////checking whether if a contact with the two entities exists
////\param const Entity &
////A reference to a read-only entity to compare with
////\param const Entity &
////A reference to a read-only entity to compare against
////\return bool
////Evaluated result of whether a collision happened between the two given entities
////*******************************************************************************/
////bool MonoMethods::EntitiesCollided(const Entity& _e1, const Entity& _e2) {
////	return collision2DManager->EntitiesCollided(_e1, _e2);
////}
////
/////*!*****************************************************************************
////\brief
////Exits the game.
////*******************************************************************************/
////void MonoMethods::GameStateExit() {
////#ifdef _EDITOR
////	editorManager->SetScenePaused(true);
////	editorManager->SetFullScreen(false);
////#else
////	GameStateManager::GetInstance()->GameStateExit();
////#endif // _EDITOR
////}
////
/////*!*****************************************************************************
////\brief
////Gets the delta time in double.
////*******************************************************************************/
////double MonoMethods::GetDeltaTime() {
////	return FPSManager::dt;
////}
////
/////*!*****************************************************************************
////\brief
////Initialise the window width and height of the application using pointer.
////Should be called in application's init
////*******************************************************************************/
////void MonoMethods::InitScriptWindow(int* _windowWidth, int* _windowHeight) {
////	windowWidth = _windowWidth;
////	windowHeight = _windowHeight;
////}
////
/////*!*****************************************************************************
////\brief
////	Plays a single background sound
////*******************************************************************************/
////void MonoMethods::PlayAnySound(std::string _name, int _channel) {
////	audioManager->PlayAnySound(_name, _channel);
////}
////
/////*!*****************************************************************************
////\brief
////   Checks if a channel is playing
////*******************************************************************************/
////bool MonoMethods::IsPlaying(int _channel) {
////	return audioManager->isPlaying(_channel);
////}
////
/////*!*****************************************************************************
////\brief
////	Plays a single background sound
////*******************************************************************************/
////void MonoMethods::PlayBGSound(std::string _name, int _channel) {
////	audioManager->PlayBGSound(_name, _channel);
////}
