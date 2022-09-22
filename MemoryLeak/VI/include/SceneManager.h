//#pragma once
//#include "Singleton.h"
//
//class GameState;
//
//enum class GS {
//	INVALID,
//	START,
//
//	RESTART,
//	EXIT
//};
//
//class GameStateManager : public Singleton<GameStateManager> {
//public:
//	GameStateManager();
//	~GameStateManager() {};
//
//	void Init();
//	void Update();
//	void Loop();
//	void Exit();
//
//	void setNewGameState();
//	void nextGS(GS);
//
//	GS getNextGS() { return next_GS; }
//	GS getCurrGS() { return curr_GS; }
//	GS getPrevGS() { return prev_GS; }
//
//private:
//	using FP = void (*)(void);
//	using GS_pair = std::pair<GS, GameState*>;
//
//	std::map<GS, GameState*> GS_list;
//	GS curr_GS, prev_GS, next_GS;
//	GameState* curr_gamestate;
//};
//
//
