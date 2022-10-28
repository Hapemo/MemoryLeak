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
#include "Start.h"
#include "GameState1.h"
#include "GameState2.h"
#include "GameState3.h"
#include "ParallaxAndSpriteSwap.h"

GameStateManager::GameStateManager() :
	mPrevGS(), mNextGS(), mCurrGS(), mCurrGameState(nullptr) 
{};

void GameStateManager::Update() {
	if (mCurrGS == E_GS::RESTART) mNextGS = mCurrGS = mPrevGS;
	else {
		// Update();
		SetNewGameState();
		mCurrGameState->Load();
	}

	mCurrGameState->Init();

	while (mCurrGS == mNextGS) {
		TRACK_PERFORMANCE("MainLoop");
		Application::FirstUpdate();

		//-------------------------------------
		// ImGui update
		// ImGui is a tool that uses VI Engine to change the game data stored in VI Engine


		//-------------------------------------


		mCurrGameState->Update();
		GSControlPanel();

		Application::SystemUpdate();

		TRACK_PERFORMANCE("Graphics");
		mCurrGameState->Draw();
		END_TRACK("Graphics");

		Application::SecondUpdate(); // This should always be the last
		END_TRACK("MainLoop");
	}

	mCurrGameState->Free();

	if (mNextGS != E_GS::RESTART) {
		mCurrGameState->Unload();
		renderManager->Clear();
		glfwSwapBuffers(Application::getWindow());
		renderManager->Clear();
	}
	mPrevGS = mCurrGS;
	mCurrGS = mNextGS;
}

void GameStateManager::Init() {
	mPrevGS = mNextGS = mCurrGS = E_GS::GameState1;
	
	GS_List.insert(GS_pair(E_GS::START, new Start));
	GS_List.insert(GS_pair(E_GS::GameState1, new GameState1));
	GS_List.insert(GS_pair(E_GS::GameState2, new GameState2));
	GS_List.insert(GS_pair(E_GS::GameState3, new GameState3));
	GS_List.insert(GS_pair(E_GS::ParallaxSprite, new ParallaxAndSpriteSwap));
}


void GameStateManager::NextGS(E_GS gamestate) { mNextGS = gamestate; }

void GameStateManager::SetNewGameState() { mCurrGameState = GS_List[mCurrGS]; }

void GameStateManager::Exit() {
	for (GS_pair pair : GS_List) {
		if (!pair.second) continue;
		delete pair.second;
		pair.second = nullptr;
	}
	mCurrGameState = nullptr;
}

void GameStateManager::GSControlPanel() {
	if (Application::GetEditorMode()) return;
	if (Input::CheckKey(PRESS, _1) && Input::CheckKey(E_STATE::HOLD, E_KEY::LEFT_CONTROL)) GameStateManager::GetInstance()->NextGS(E_GS::GameState1);
	else if (Input::CheckKey(PRESS, _2) && Input::CheckKey(E_STATE::HOLD, E_KEY::LEFT_CONTROL)) GameStateManager::GetInstance()->NextGS(E_GS::GameState2);
	else if (Input::CheckKey(PRESS, _3) && Input::CheckKey(E_STATE::HOLD, E_KEY::LEFT_CONTROL)) GameStateManager::GetInstance()->NextGS(E_GS::GameState3);
	else if (Input::CheckKey(PRESS, _4) && Input::CheckKey(E_STATE::HOLD, E_KEY::LEFT_CONTROL)) GameStateManager::GetInstance()->NextGS(E_GS::ParallaxSprite);
	else if (Input::CheckKey(PRESS, _0) && Input::CheckKey(E_STATE::HOLD, E_KEY::LEFT_CONTROL)) GameStateManager::GetInstance()->NextGS(E_GS::START);
}