#include "GameStateManager.h"
#include "GameState.h"
#include "Start.h"
#include <sstream>
#include <iomanip>
#include "Application.h"
#include "Helper.h"
#include "Graphics.h"

GameStateManager::GameStateManager() :
	prev_GS(GS::START), next_GS(GS::START), curr_GS(GS::START), curr_gamestate(nullptr) 
{};

void GameStateManager::Loop() {
	if (curr_GS == GS::RESTART) next_GS = curr_GS = prev_GS;
	else {
		// Update();
		setNewGameState();
		curr_gamestate->Load();
	}

	curr_gamestate->Init();

	while (curr_GS == next_GS) {
		Application::FirstUpdate();

		// Update Input
		curr_gamestate->Update();
		curr_gamestate->Draw();

		Graphics::draw();

		Application::SecondUpdate();
	}

	curr_gamestate->Free();

	if (next_GS != GS::RESTART) curr_gamestate->Unload();;

	prev_GS = curr_GS;
	curr_GS = next_GS;
}

void GameStateManager::Init() {
	GS_list.insert(GS_pair(GS::START, new Start));
}


void GameStateManager::nextGS(GS gamestate) { next_GS = gamestate; }

void GameStateManager::setNewGameState() { curr_gamestate = GS_list[curr_GS]; }

void GameStateManager::Update() { }

void GameStateManager::Exit() {
	for (GS_pair pair : GS_list) {
		if (!pair.second) continue;
		delete pair.second;
		pair.second = nullptr;
	}
	curr_gamestate = nullptr;
}