#include "Scene.h"

void Scene::PrimaryUpdate() {
	if (pause) return;
	Update();
}

void Scene::Pause(bool _pause) { pause = _pause; }







