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
	if (!_e.GetComponent<Animation>().images.size())
	{
		//if image vector is empty, initialize it with the texture in its sprite component
		if (!(_e.HasComponent<Sprite>() && _e.GetComponent<Sprite>().sprite == SPRITE::TEXTURE)) return;
		static GLuint addImage = _e.GetComponent<Sprite>().texture;
		AddImages(_e, addImage);
	}

	//update time to image swap
	_e.GetComponent<Animation>().timeToImageSwap -= static_cast<float>(FPSManager::dt);

	if (_e.GetComponent<Animation>().timeToImageSwap >= 0) return;

	//reset counter
	_e.GetComponent<Animation>().timeToImageSwap = _e.GetComponent<Animation>().timePerImage;
	//change the image
	_e.GetComponent<Animation>().currentImageIndex = ++_e.GetComponent<Animation>().currentImageIndex < _e.GetComponent<Animation>().images.size() ?
		_e.GetComponent<Animation>().currentImageIndex : 0;
	//change its texture
	_e.GetComponent<Sprite>().texture = _e.GetComponent<Animation>().images[_e.GetComponent<Animation>().currentImageIndex];
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
void Animator::AddImages(const Entity& _e, GLuint _frame)
{
	_e.GetComponent<Animation>().images.push_back(_frame);
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
void Animator::AddImages(const Entity& _e, const std::vector<GLuint>& _frames)
{
	_e.GetComponent<Animation>().images.insert(_e.GetComponent<Animation>().images.end(), _frames.begin(), _frames.end());
}