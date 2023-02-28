#include "MoveMinimapScript.h"

REGISTER_SCRIPT(ScriptComponent, MoveMinimapScript);

void MoveMinimapScript::StartScript(const Entity& _e) {
	(void)_e;
	inited = false;
}

void MoveMinimapScript::UpdateScript(const Entity& _e) {
	if (!inited)
		currScene = &(FUNC->SelectScene("Level1"));
	_e.GetComponent<Transform>().translation += currScene->mCamera.translation;
	_e.GetComponent<Transform>().scale += currScene->mCamera.scale;
}

void MoveMinimapScript::EndScript(const Entity& _e) {
	(void)_e;
}