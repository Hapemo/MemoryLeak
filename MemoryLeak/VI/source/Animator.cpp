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
#include "Animator.h"

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
void Animator::Animate(const Entity& e)
{
	if (!e.GetComponent<General>().isActive) return;
	if (!e.HasComponent<Animation>()) return;
	if (!e.GetComponent<Animation>().images.size())
	{
		if (!(e.HasComponent<Sprite>() && e.GetComponent<Sprite>().sprite == SPRITE::TEXTURE)) return;
		static GLuint addImage = e.GetComponent<Sprite>().texture;
		AddImages(e, addImage);
	}

	e.GetComponent<Animation>().timeToImageSwap -= Helper::dt;

	if (e.GetComponent<Animation>().timeToImageSwap >= 0) return;

	e.GetComponent<Animation>().timeToImageSwap = e.GetComponent<Animation>().timePerImage;
	e.GetComponent<Animation>().currentImageIndex = ++e.GetComponent<Animation>().currentImageIndex < e.GetComponent<Animation>().images.size() ?
		e.GetComponent<Animation>().currentImageIndex : 0;
	e.GetComponent<Sprite>().texture = e.GetComponent<Animation>().images[e.GetComponent<Animation>().currentImageIndex];
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
void Animator::AddImages(const Entity& e, GLuint frame)
{
	e.GetComponent<Animation>().images.push_back(frame);
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
void Animator::AddImages(const Entity& e, const std::vector<GLuint>& frames)
{
	e.GetComponent<Animation>().images.insert(e.GetComponent<Animation>().images.end(), frames.begin(), frames.end());
}