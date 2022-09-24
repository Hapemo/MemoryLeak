#include "GameStateManager.h"
#include "GameState.h"
#include "Application.h"
#include "Helper.h"
#include "PerformanceVisualiser.h"
#include "ResourceManager.h"
#include "Graphics/SpriteManager.h"
#include "Input.h"
#include "Start.h"
#include "GameState1.h"
#include "GameState2.h"

GameStateManager::GameStateManager() :
	mPrevGS(E_GS::START), mNextGS(E_GS::START), mCurrGS(E_GS::START), mCurrGameState(nullptr) 
{};

void GameStateManager::Loop() {
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

		mCurrGameState->Update();
		int update = CHECK_TEXTURES_UPDATE();
		if (update > -1) {
			//spriteManager->InitializeTexture(GET_TEXTURE((size_t)update));
		}

		TRACK_PERFORMANCE("Graphics");
		mCurrGameState->Draw();
		END_TRACK("Graphics");

		GSControlPanel();

		Application::SecondUpdate(); // This should always be the last
		END_TRACK("MainLoop");
	}

	mCurrGameState->Free();

	if (mNextGS != E_GS::RESTART) mCurrGameState->Unload();;

	mPrevGS = mCurrGS;
	mCurrGS = mNextGS;
}

void GameStateManager::Init() {
	GS_List.insert(GS_pair(E_GS::START, new Start));
	GS_List.insert(GS_pair(E_GS::GameState1, new GameState1));
	GS_List.insert(GS_pair(E_GS::GameState2, new GameState2));
}


void GameStateManager::NextGS(E_GS gamestate) { mNextGS = gamestate; }

void GameStateManager::SetNewGameState() { mCurrGameState = GS_List[mCurrGS]; }

void GameStateManager::Update() { }

void GameStateManager::Exit() {
	for (GS_pair pair : GS_List) {
		if (!pair.second) continue;
		delete pair.second;
		pair.second = nullptr;
	}
	mCurrGameState = nullptr;
}

void GameStateManager::GSControlPanel() {
	if (Input::CheckKey(PRESS, _1)) GameStateManager::GetInstance()->NextGS(E_GS::GameState1);
	else if (Input::CheckKey(PRESS, _2)) GameStateManager::GetInstance()->NextGS(E_GS::GameState2);
	else if (Input::CheckKey(PRESS, _0)) GameStateManager::GetInstance()->NextGS(E_GS::START);
}