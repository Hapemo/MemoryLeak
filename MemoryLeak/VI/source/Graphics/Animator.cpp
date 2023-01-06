/*!*****************************************************************************
\file Animator.cpp
\author Kew Yu Jun
\par DP email: k.yujun\@digipen.edu
\par Group: Memory Leak Studios
\date 20-09-2022
\brief
This file contains function definitions for an Animator system that operates on
Entities with the Sprite and Animation Component.
*******************************************************************************/
#include "Graphics/Animator.h"

/*!*****************************************************************************
\brief
Animates a single Entity with Components Sprite and Animation.

\return
None.
*******************************************************************************/
void Animator::Animate()
{
	for (const Entity& e : mEntities)
		Animate(e);
}

/*!*****************************************************************************
\brief
Animates all Entities with Components Sprite and Animation.

\param const Entity& e
The Entity to be animated.

\return
None.
*******************************************************************************/
void Animator::Animate(const Entity& _e)
{
	if (!_e.GetComponent<General>().isActive) return;
	if (!_e.HasComponent<Animation>()) return;

	Animation animation = _e.GetComponent<Animation>();
	_e.GetComponent<Sprite>().texture = animation.images[animation.currentImageIndex];

	if (!_e.HasComponent<SheetAnimation>()) return;
	_e.GetComponent<SheetAnimation>().frameCount = animation.frameCount[animation.currentImageIndex];
	_e.GetComponent<SheetAnimation>().timePerFrame = animation.timePerImage[animation.currentImageIndex];
}

/*!*****************************************************************************
\brief
Adds an image to the Entity with an Animation Component. This increases the
Animation by one frame (the image added).

\param const Entity& e
The Entity whose Animation Component will have another image.

\param GLuint frame
The texture ID of the image stored in OpenGL to be added to the Animation
Component.

\return
None.
*******************************************************************************/
void AddImages(const Entity& _e, GLuint _frame, int _frameCount, float _timePerImage)
{
	_e.GetComponent<Animation>().images.push_back(_frame);
	_e.GetComponent<Animation>().frameCount.push_back(_frameCount);
	_e.GetComponent<Animation>().timePerImage.push_back(_timePerImage);
}

/*!*****************************************************************************
\brief
Adds a series of images to the Animation Component. This increases the Animation
by

\param const Entity& e
The Entity whose Animation Component will have a series of images added.

\param const std::vector<GLuint>& frames
A vector of texture ID of images stored in OpenGL to be added to the Animation
component

\return
None.
*******************************************************************************/
void AddImages(const Entity& _e, const std::vector<GLuint>& _frames,
	const std::vector<int>& _frameCounts, const std::vector<float>& _timePerImage)
{
	if (_frames.size() != _frameCounts.size() || _frameCounts.size() != _timePerImage.size() || _timePerImage.size() != _frames.size())
	{
		LOG_ERROR("Different sized vectors!!");
		return;
	}

	_e.GetComponent<Animation>().images.insert(_e.GetComponent<Animation>().images.end(), _frames.begin(), _frames.end());
	_e.GetComponent<Animation>().frameCount.insert(_e.GetComponent<Animation>().frameCount.end(), _frameCounts.begin(), _frameCounts.end());
	_e.GetComponent<Animation>().timePerImage.insert(_e.GetComponent<Animation>().timePerImage.end(), _timePerImage.begin(), _timePerImage.end());
}
