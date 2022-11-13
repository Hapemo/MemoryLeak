/*!*****************************************************************************
\file SheetAnimator.cpp
\author Kew Yu Jun
\par DP email: k.yujun\@digipen.edu
\par Group: Memory Leak Studios
\date 20-09-2022
\brief
This file contains function declarations for an Animator system that operates on
Entities with the Sprite and SheetAnimation Component. It uses !SPRITESHEETS! to
animate.
*******************************************************************************/
#include "Graphics/SheetAnimator.h"

/*!*****************************************************************************
\brief
Animates a all Entities with Components Sprite and SheetAnimation.

\return
None.
*******************************************************************************/
void SheetAnimator::Animate()
{
	for (const Entity& e : mEntities)
		Animate(e);
}

/*!*****************************************************************************
\brief
Animates a single Entity with Components Sprite and SheetAnimation.

\param const Entity& e
The Entity to be animated.

\return
None.
*******************************************************************************/
void SheetAnimator::Animate(const Entity& _e)
{
	if (!_e.GetComponent<General>().isActive) return;
	if (!_e.ShouldRun()) return;
	if (!_e.HasComponent<SheetAnimation>()) return;

	//decrement time to swap
	_e.GetComponent<SheetAnimation>().timeToFrameSwap -= static_cast<float>(FPSManager::dt);

	if (_e.GetComponent<SheetAnimation>().timeToFrameSwap >= 0) return;

	//reset counter
	_e.GetComponent<SheetAnimation>().timeToFrameSwap = _e.GetComponent<SheetAnimation>().timePerFrame;
	//change tex coordinates
	_e.GetComponent<SheetAnimation>().currFrameIndex = ++_e.GetComponent<SheetAnimation>().currFrameIndex 
		< _e.GetComponent<SheetAnimation>().frameCount ?
		_e.GetComponent<SheetAnimation>().currFrameIndex : 0;
}