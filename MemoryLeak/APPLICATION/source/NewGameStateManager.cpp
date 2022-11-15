/*!*****************************************************************************
\file NewGameStateManager.cpp
\author Jazz Teoh Yu Jue
\par DP email: j.teoh\@digipen.edu
\par Group: Memory Leak Studios
\date 24-09-2022
\brief
Manages the gamestate flow, control which game state is running or will be
running.
*******************************************************************************/
#include "NewGameStateManager.h"
#include "GameState.h"
#include "Application.h"
#include "Helper.h"
#include "PerformanceVisualiser.h"
#include "ResourceManager.h"
#include "Graphics/RenderManager.h"
#include "Graphics/SpriteManager.h"
#include "Input.h"

#include "NewGameState.h"


const std::string NewGameStateManager::EXIT{ "Exit" };
const std::string NewGameStateManager::RESTART{ "Restart" };
NewGameStateManager::E_GSMSTATE NewGameStateManager::mGSMState{ NewGameStateManager::E_GSMSTATE::STARTING };

//E_GS NewGameStateManager::mCurrentState = E_GS::EDITOR;
//NewGameStateManager::NewGameStateManager() :
//	mPrevGS(), mNextGS(), mCurrGS(), mStartingGS(), mCurrGameState(nullptr)
//{};
NewGameStateManager::NewGameStateManager() : mGameStates(), mCurrentGameState(nullptr), mNextGSPath("") {};

// Load the first game state.
void NewGameStateManager::Init() {
	mGameStates.emplace_back(NewGameState());
	mCurrentGameState = &mGameStates.front();

	mCurrentGameState->Load(mNextGSPath);
}

void NewGameStateManager::Update() {
	// Update gamestate and loop it. 
	// Stop when exit or restart game state.
	// Stop when change game state. 

	// Structure is this,
	// 
	// Application and controls first update
	// Editor update
	// Logic & Systems update
	// Graphics update
	// Application ending update

	while (mGSMState != E_GSMSTATE::EXIT) {
		TRACK_PERFORMANCE("MainLoop");
		Application::FirstUpdate();
		//GSControlPanel();

		TRACK_PERFORMANCE("Editor");
		editorManager->Update();
		END_TRACK("Editor");

		if (!editorManager->IsScenePaused()) {
			mCurrentGameState->Update(); // Game logic
			Application::SystemUpdate(); // Should be called after logic
		}

		TRACK_PERFORMANCE("Graphics");
		//--------------------- Drawing and rendering ---------------------
		renderManager->Render();

		//-----------------------------------------------------------------
		END_TRACK("Graphics");


		// If it changes, it should've came from when updaing game logic
		UpdateNextGSMState(); 

		Application::SecondUpdate(); // This should always be the last
		END_TRACK("MainLoop");
	}

	/*
	if (mCurrGS != E_GS::EDITOR)
	{
		if (mCurrGS == E_GS::RESTART) mNextGS = mCurrGS = mPrevGS;
		else {
			// Update();
			SetNewGameState();
			mCurrGameState->PrimaryLoad();
		}

		mCurrGameState->Init();
		////////logicSystem->Init(); // need inilitialze loaded script data else need do in serilization
		while (mCurrGS == mNextGS) {

			//-------------------------------------

			mCurrGameState->Update();
			Application::SystemUpdate(); // Should be called after logic


			TRACK_PERFORMANCE("Graphics");
			mCurrGameState->Draw();
			END_TRACK("Graphics");

			Application::SecondUpdate(); // This should always be the last
			END_TRACK("MainLoop");
		}

		mCurrGameState->Free();
		//editorManager->Free();

		if (mNextGS != E_GS::RESTART) {
			mCurrGameState->PrimaryUnload();
			glfwSwapBuffers(Application::getWindow());
		}
		mPrevGS = mCurrGS;
		mCurrGS = mNextGS;
	}
	else
	{
		TRACK_PERFORMANCE("MainLoop");
		Application::FirstUpdate();
		TRACK_PERFORMANCE("Editor");
		editorManager->Update();
		END_TRACK("Editor");

		TRACK_PERFORMANCE("Graphics");
		renderManager->Render();
		END_TRACK("Graphics");
		if (!editorManager->IsScenePaused())
			Application::SystemUpdate();
		GSControlPanel();
		Application::SecondUpdate();
		END_TRACK("MainLoop");
		mPrevGS = mCurrGS;
		mCurrGS = mNextGS;
	}
	*/
}

void NewGameStateManager::UpdateNextGSMState() {
	if (mGSMState == E_GSMSTATE::RUNNING) return; // No change in GS, ignore.

	mCurrentGameState->Exit();

	switch (mGSMState) {
	case E_GSMSTATE::EXIT:
		mCurrentGameState->Unload();
		return;
	case E_GSMSTATE::RESTART:
		mCurrentGameState->Init();
		break;
	case E_GSMSTATE::CHANGING:
		// Changing gamestate to some other gamestate.
		mCurrentGameState->Unload();
		mCurrentGameState->Load(mNextGSPath);
		mCurrentGameState->Init();
		break;
	}

	mGSMState = E_GSMSTATE::RUNNING;
}

void NewGameStateManager::ChangeGameState(std::string const& _path) {
	
	// Check if exit or restart;
	if (_path == EXIT)
		mGSMState = E_GSMSTATE::EXIT;
	else if (_path == RESTART)
		mGSMState = E_GSMSTATE::RESTART;
	else if (!ResourceManager::FileExist(_path)) {
		LOG_ERROR("Unable to change gamestate to: " + _path);
		return;
	} else {
		mNextGSPath = _path;
		mGSMState = E_GSMSTATE::CHANGING;
	}

}


void NewGameStateManager::Exit() {

}
//
//void NewGameStateManager::GSControlPanel() {
//	static bool renderToScreen{ true };
//	if (Input::CheckKey(PRESS, E) && Input::CheckKey(E_STATE::HOLD, E_KEY::LEFT_CONTROL)) {
//		renderToScreen = !renderToScreen;
//		if (renderToScreen)
//		{
//			renderManager->RenderToScreen();
//			editorManager->SetScenePaused(false);
//			NewGameStateManager::GetInstance()->NextGS(E_GS::MainMenu);
//
//		}
//		else
//		{
//			renderManager->RenderToFrameBuffer();
//			editorManager->SetScenePaused(true);
//			NewGameStateManager::GetInstance()->NextGS(E_GS::EDITOR);
//		}
//	}
//	if (Input::CheckKey(PRESS, ESCAPE)) NewGameStateManager::GetInstance()->NextGS(E_GS::EXIT);
//	if (Input::CheckKey(PRESS, I) && Input::CheckKey(E_STATE::HOLD, E_KEY::LEFT_CONTROL)) NewGameStateManager::GetInstance()->NextGS(E_GS::AIDemo);
//	else if (Input::CheckKey(PRESS, A) && Input::CheckKey(E_STATE::HOLD, E_KEY::LEFT_CONTROL)) NewGameStateManager::GetInstance()->NextGS(E_GS::ParallaxSprite);
//	else if (Input::CheckKey(PRESS, L) && Input::CheckKey(E_STATE::HOLD, E_KEY::LEFT_CONTROL)) NewGameStateManager::GetInstance()->NextGS(E_GS::Lighting);
//	else if (Input::CheckKey(PRESS, S) && Input::CheckKey(E_STATE::HOLD, E_KEY::LEFT_CONTROL)) NewGameStateManager::GetInstance()->NextGS(E_GS::ScriptingDemo);
//	else if (Input::CheckKey(PRESS, P) && Input::CheckKey(E_STATE::HOLD, E_KEY::LEFT_CONTROL)) NewGameStateManager::GetInstance()->NextGS(E_GS::PHYSICS);
//	else if (Input::CheckKey(PRESS, _0) && Input::CheckKey(E_STATE::HOLD, E_KEY::LEFT_CONTROL)) NewGameStateManager::GetInstance()->NextGS(E_GS::MainMenu);
//	else if (Input::CheckKey(PRESS, _1) && Input::CheckKey(E_STATE::HOLD, E_KEY::LEFT_CONTROL)) NewGameStateManager::GetInstance()->NextGS(E_GS::Level1);
//	else if (Input::CheckKey(PRESS, J) && Input::CheckKey(E_STATE::HOLD, E_KEY::LEFT_CONTROL)) NewGameStateManager::GetInstance()->NextGS(E_GS::JAZZ);
//	else if (Input::CheckKey(PRESS, RIGHT) && Input::CheckKey(E_STATE::HOLD, E_KEY::LEFT_CONTROL)) NewGameStateManager::GetInstance()->NextGS(++mCurrentState);
//	else if (Input::CheckKey(PRESS, LEFT) && Input::CheckKey(E_STATE::HOLD, E_KEY::LEFT_CONTROL)) NewGameStateManager::GetInstance()->NextGS(--mCurrentState);
//	//else if (Input::CheckKey(PRESS, ESCAPE)) NewGameStateManager::GetInstance()->NextGS(E_GS::EXIT);
//}
//
//E_GS& operator++(E_GS& _gs)                         // prefix increment operator
//{
//	_gs = (_gs == E_GS(static_cast<int>(E_GS::END_OF_LIST) - 1)) ? E_GS::MainMenu : E_GS(static_cast<int>(_gs) + 1);
//	return _gs;
//}
//
//E_GS& operator--(E_GS& _gs)                         // prefix decrement operator
//{
//	_gs = (_gs == E_GS::MainMenu) ? E_GS(static_cast<int>(E_GS::END_OF_LIST) - 1) : E_GS(static_cast<int>(_gs) - 1);
//	return _gs;
//}