/*!*****************************************************************************
\file GameState.cpp
\author Jazz Teoh Yu Jue
\par DP email: j.teoh\@digipen.edu
\par Group: Memory Leak Studios
\date 24-09-2022
\brief
Game state base class, contains Load, Init, Update, Draw, Free and Unload
functions.

How to make a gamestate?

1. Make a class for your gamestate, inherited from class GameState
2. Declare and define all the virtual functions
3. In GameStateManager.h > class enum GS, make a new enum for your game state
4. In GameStateManager's Init(), make a new line "GS_list.insert(GS_pair(<GS>,
	 new <GameState>));" where <GS> is your game state's enum and <GameState> is
	 your game state class
*******************************************************************************/
#include "GameState.h"

// Nothing for now