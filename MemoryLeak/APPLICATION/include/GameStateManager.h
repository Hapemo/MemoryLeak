#pragma once
#include "pch.h"
#include "Singleton.h"

class GameState;

enum class E_GS {
	INVALID,
	START,
	GameState1,
	GameState2,

	RESTART,
	EXIT
};

class GameStateManager : public Singleton<GameStateManager> {
public:
	GameStateManager();
	~GameStateManager() {};

	void Init();
	void Update();
	void Loop();
	void Exit();

	void SetNewGameState();
	void NextGS(E_GS);

	E_GS getNextGS() { return mNextGS; }
	E_GS getCurrGS() { return mCurrGS; }
	E_GS getPrevGS() { return mPrevGS; }

	static void GSControlPanel();

private:
	using FP = void (*)(void);
	using GS_pair = std::pair<E_GS, GameState*>;

	std::map<E_GS, GameState*> GS_List;
	E_GS mCurrGS, mPrevGS, mNextGS;
	GameState* mCurrGameState;
};


