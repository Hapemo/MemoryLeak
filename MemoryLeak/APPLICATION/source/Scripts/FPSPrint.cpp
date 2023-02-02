/*!*****************************************************************************
\file FPSPrint.cpp
\author Jazz Teoh Yu Jue
\par DP email: j.teoh\@digipen.edu
\par Course: GAM250
\par Group: Memory Leak Studios
\date 25-01-2023
\brief
Updates the fps count, for the fps printer in entity
*******************************************************************************/


#include "FPSPrint.h"

REGISTER_SCRIPT(ScriptComponent, FPSPrintScript);

/*!*****************************************************************************
\brief
Function will run on initialisation of the entity.
*******************************************************************************/
void FPSPrintScript::StartScript(Entity const& gob) {
	(void)gob;
	//LOG_INFO("How to Play button script starts works!!!");
}

/*!*****************************************************************************
\brief
Function will run on every update while the entity is active.
*******************************************************************************/
void FPSPrintScript::UpdateScript(Entity const& gob) {
	(void)gob;
	// Update every 2 seconds
	static float timeCounter{1};
	timeCounter += static_cast<float>(FPSManager::dt);
	if (timeCounter <= 2) return;
	timeCounter = 0;

	std::stringstream str;
	str << std::fixed << std::setprecision(1) << FPSManager::fps;
	FUNC->UpdateText("fpsDisplay", "FPS", str.str());
}

/*!*****************************************************************************
\brief
Function will run on exit or when the entity is destroyed.
*******************************************************************************/
void FPSPrintScript::EndScript(Entity const& gob) {
	(void)gob;
	//LOG_INFO("How to Play button script end works!!!");
}
