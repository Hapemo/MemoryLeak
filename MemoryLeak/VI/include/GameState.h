#pragma once

//--------------------------------------------------
// How to make a gamestate?
// 
// 1. Make a class for your gamestate, inherited from class GameState
// 2. Declare and define all the virtual functions
// 3. In GameStateManager.h > class enum GS, make a new enum for your game state
// 4. In GameStateManager's Init(), make a new line "GS_list.insert(GS_pair(<GS>, new <GameState>));"
//		where <GS> is your game state's enum and <GameState> is your game state class
//--------------------------------------------------


class GameState {
public:
	GameState() {};
	virtual ~GameState() {};

	virtual void Load() = 0;
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Free() = 0;
	virtual void Unload() = 0;

};
