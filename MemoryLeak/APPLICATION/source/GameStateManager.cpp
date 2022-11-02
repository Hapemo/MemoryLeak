/*!*****************************************************************************
\file GameStateManager.cpp
\author Jazz Teoh Yu Jue
\par DP email: j.teoh\@digipen.edu
\par Group: Memory Leak Studios
\date 24-09-2022
\brief
Manages the gamestate flow, control which game state is running or will be
running.
*******************************************************************************/
#include "GameStateManager.h"
#include "GameState.h"
#include "Application.h"
#include "Helper.h"
#include "PerformanceVisualiser.h"
#include "ResourceManager.h"
#include "Graphics/RenderManager.h"
#include "Graphics/SpriteManager.h"
#include "Input.h"
#include "AIDemo.h"
#include "ScriptingDemo.h"
#include "GameStatePhysics.h"
#include "ParallaxAndSpriteSwap.h"
#include "Lighting.h"
#include "MainMenu.h"
#include "Level1.h"
E_GS GameStateManager::mCurrentState = E_GS::MainMenu;
GameStateManager::GameStateManager() :
	mPrevGS(), mNextGS(), mCurrGS(), mCurrGameState(nullptr) 
{};

void GameStateManager::Update() {
	if (mCurrGS == E_GS::RESTART) mNextGS = mCurrGS = mPrevGS;
	else {
		// Update();
		SetNewGameState();
		mCurrGameState->PrimaryLoad();
	}

	mCurrGameState->Init();
	////////logicSystem->Init(); // need inilitialze loaded script data else need do in serilization
	while (mCurrGS == mNextGS) {
		TRACK_PERFORMANCE("MainLoop");
		Application::FirstUpdate();

		//-------------------------------------
		// ImGui update
		// ImGui is a tool that uses VI Engine to change the game data stored in VI Engine

		TRACK_PERFORMANCE("Editor");
		editorManager->Update();
		END_TRACK("Editor");
		//-------------------------------------

		mCurrGameState->Update();
		GSControlPanel();

		if(!editorManager->IsScenePaused())
			Application::SystemUpdate();

		TRACK_PERFORMANCE("Graphics");
		mCurrGameState->Draw();
		END_TRACK("Graphics");

		Application::SecondUpdate(); // This should always be the last
		END_TRACK("MainLoop");
	}

	mCurrGameState->Free();
	editorManager->Free();

	if (mNextGS != E_GS::RESTART) {
		mCurrGameState->PrimaryUnload();
		glfwSwapBuffers(Application::getWindow());
	}
	mPrevGS = mCurrGS;
	mCurrGS = mNextGS;
}

void GameStateManager::Init() {
	LOG_CUSTOM_CREATE("GAMESTATE");
	LOG_CUSTOM_CREATE("SCENE");
	mPrevGS = mNextGS = mCurrGS = E_GS::MainMenu; // Starting game state
	
	GS_List.insert(GS_pair(E_GS::MainMenu, new MainMenu));
	GS_List.insert(GS_pair(E_GS::Level1, new Level1));
	GS_List.insert(GS_pair(E_GS::PHYSICS, new GameStatePhysics));
	GS_List.insert(GS_pair(E_GS::ScriptingDemo, new ScriptingDemo));
	GS_List.insert(GS_pair(E_GS::Lighting, new Lighting));
	GS_List.insert(GS_pair(E_GS::ParallaxSprite, new ParallaxAndSpriteSwap));
	GS_List.insert(GS_pair(E_GS::AIDemo, new AIDemo));
}


void GameStateManager::NextGS(E_GS gamestate) { mNextGS = gamestate; }

void GameStateManager::SetNewGameState() { 
	mCurrGameState = GS_List[mCurrGS];
	switch (mCurrGS) {
	case E_GS::PHYSICS:
		Application::GetCurrGameStateName() = "PHYSICS";
		break;
	case E_GS::ScriptingDemo:
		Application::GetCurrGameStateName() = "ScriptingDemo";
		break;
	case E_GS::Lighting:
		Application::GetCurrGameStateName() = "Lighting";
		break;
	case E_GS::EXIT:
		Application::GetCurrGameStateName() = "EXIT";
		break;
	case E_GS::INVALID:
		Application::GetCurrGameStateName() = "INVALID";
		break;
	case E_GS::RESTART:
		Application::GetCurrGameStateName() = "RESTART";
		break;
	case E_GS::ParallaxSprite:
		Application::GetCurrGameStateName() = "ParallaxSprite";
		break;
	case E_GS::AIDemo:
		Application::GetCurrGameStateName() = "AI Demo";
		break;
	case E_GS::MainMenu:
		Application::GetCurrGameStateName() = "Main Menu";
		break;
	case E_GS::Level1:
		Application::GetCurrGameStateName() = "Level1";
		break;
	default:
		Application::GetCurrGameStateName() = "Unknown";
	}
}

void GameStateManager::Exit() {
	for (GS_pair pair : GS_List) {
		if (!pair.second) continue;
		delete pair.second;
		pair.second = nullptr;
	}
	mCurrGameState = nullptr;
}

void GameStateManager::GSControlPanel() {
	static bool renderToScreen{ false };
	if (Input::CheckKey(PRESS, E) && Input::CheckKey(E_STATE::HOLD, E_KEY::LEFT_CONTROL)) {
		renderToScreen = !renderToScreen;
		if (renderToScreen)
		{
			renderManager->RenderToScreen();
			editorManager->SetScenePaused(false);
		}
		else
		{
			renderManager->RenderToFrameBuffer();
			editorManager->SetScenePaused(true);
		}
	}
	if (Input::CheckKey(PRESS, ESCAPE)) GameStateManager::GetInstance()->NextGS(E_GS::EXIT);
	if (Input::CheckKey(PRESS, I) && Input::CheckKey(E_STATE::HOLD, E_KEY::LEFT_CONTROL)) GameStateManager::GetInstance()->NextGS(E_GS::AIDemo);
	else if (Input::CheckKey(PRESS, A) && Input::CheckKey(E_STATE::HOLD, E_KEY::LEFT_CONTROL)) GameStateManager::GetInstance()->NextGS(E_GS::ParallaxSprite);
	else if (Input::CheckKey(PRESS, L) && Input::CheckKey(E_STATE::HOLD, E_KEY::LEFT_CONTROL)) GameStateManager::GetInstance()->NextGS(E_GS::Lighting);
	else if (Input::CheckKey(PRESS, S) && Input::CheckKey(E_STATE::HOLD, E_KEY::LEFT_CONTROL)) GameStateManager::GetInstance()->NextGS(E_GS::ScriptingDemo);
	else if (Input::CheckKey(PRESS, P) && Input::CheckKey(E_STATE::HOLD, E_KEY::LEFT_CONTROL)) GameStateManager::GetInstance()->NextGS(E_GS::PHYSICS);
	else if (Input::CheckKey(PRESS, _0) && Input::CheckKey(E_STATE::HOLD, E_KEY::LEFT_CONTROL)) GameStateManager::GetInstance()->NextGS(E_GS::MainMenu);
	else if (Input::CheckKey(PRESS, _1) && Input::CheckKey(E_STATE::HOLD, E_KEY::LEFT_CONTROL)) GameStateManager::GetInstance()->NextGS(E_GS::Level1);
	else if (Input::CheckKey(PRESS, RIGHT) && Input::CheckKey(E_STATE::HOLD, E_KEY::LEFT_CONTROL)) GameStateManager::GetInstance()->NextGS(++mCurrentState);
	else if (Input::CheckKey(PRESS, LEFT) && Input::CheckKey(E_STATE::HOLD, E_KEY::LEFT_CONTROL)) GameStateManager::GetInstance()->NextGS(--mCurrentState);
	//else if (Input::CheckKey(PRESS, ESCAPE)) GameStateManager::GetInstance()->NextGS(E_GS::EXIT);
}

E_GS& operator++(E_GS& _gs)                         // prefix increment operator
{
	_gs = (_gs == E_GS(static_cast<int>(E_GS::END_OF_LIST) - 1)) ? E_GS::MainMenu : E_GS(static_cast<int>(_gs) + 1);
	return _gs;
}

E_GS& operator--(E_GS& _gs)                         // prefix decrement operator
{
	_gs = (_gs == E_GS::MainMenu) ? E_GS(static_cast<int>(E_GS::END_OF_LIST) - 1) : E_GS(static_cast<int>(_gs) - 1);
	return _gs;
}