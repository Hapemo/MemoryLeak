/*!*****************************************************************************
\file	MoveMinimapScript.h
\author Kew Yu Jun
\par	DP email: k.yujun@digipen.edu
\par	Course: GAM200
\par	Group: Memory Leak Studios
\date	26-11-2022
\brief  This file contains the declaration of the MoveMinimapScript class
		that defines the game logic used to move the minimap
*******************************************************************************/
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
		currCamera = &FUNC->CurrentCamera();
		originalTranslate = _e.GetComponent<Transform>().translation;
		originalScale = _e.GetComponent<Transform>().scale;
		inited = true;
	}
	_e.GetComponent<Transform>().translation = currCamera->translation + originalTranslate / currCamera->rotation;
	_e.GetComponent<Transform>().scale = originalScale / currCamera->rotation;
}

void MoveMinimapScript::EndScript(const Entity& _e) {
	(void)_e;
}