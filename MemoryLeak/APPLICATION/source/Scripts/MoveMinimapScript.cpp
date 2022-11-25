#include "MoveMinimapScript.h"

REGISTER_SCRIPT(ScriptComponent, MoveMinimapScript);

void MoveMinimapScript::StartScript(const Entity& _e) {
	(void)_e;
	inited = false;
}

void MoveMinimapScript::UpdateScript(const Entity& _e) {
	if (!inited)
	{
		currScene = &(FUNC->SelectScene("Level1"));
		originalTranslate = _e.GetComponent<Transform>().translation;
		originalScale = _e.GetComponent<Transform>().scale;
		inited = true;
	}
	_e.GetComponent<Transform>().translation = currScene->mCamera.translation + originalTranslate / currScene->mCamera.rotation;
	_e.GetComponent<Transform>().scale = originalScale / currScene->mCamera.rotation;
}

void MoveMinimapScript::EndScript(const Entity& _e) {
	(void)_e;
}