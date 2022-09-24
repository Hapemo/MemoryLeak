/*!*****************************************************************************
\file Scene.cpp
\author Jazz Teoh Yu Jue
\par DP email: j.teoh\@digipen.edu
\par Group: Memory Leak Studios
\date 24-09-2022
\brief
Scene base class. Each game state can have multiple scenes which encapsulates
a group of entities and operates on them.
*******************************************************************************/
#include "Scene.h"

void Scene::PrimaryUpdate() {
	if (pause) return;
	Update();
}

void Scene::Pause(bool _pause) { pause = _pause; }







