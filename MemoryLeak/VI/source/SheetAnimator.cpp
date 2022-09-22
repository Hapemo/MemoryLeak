#include "SheetAnimator.h"

SheetAnimator::SheetAnimator(){}

void SheetAnimator::Animate()
{
	for (const Entity& e : mEntities)
		Animate(e);
}

void SheetAnimator::Animate(const Entity& e)
{
	if (!e.GetComponent<General>().isActive) return;
	if (!e.HasComponent<SheetAnimation>()) return;
	e.GetComponent<SheetAnimation>().timeToFrameSwap -= Helper::dt;

	if (e.GetComponent<SheetAnimation>().timeToFrameSwap >= 0) return;

	e.GetComponent<SheetAnimation>().timeToFrameSwap = e.GetComponent<SheetAnimation>().timePerFrame;
	e.GetComponent<SheetAnimation>().currFrameIndex = ++e.GetComponent<SheetAnimation>().currFrameIndex < e.GetComponent<SheetAnimation>().frameCount ?
		e.GetComponent<SheetAnimation>().currFrameIndex : 0;
}