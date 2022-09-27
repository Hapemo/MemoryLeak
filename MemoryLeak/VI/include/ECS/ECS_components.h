/*!*****************************************************************************
\file ECS_components.h
\author Jazz Teoh Yu Jue
\par DP email: j.teoh\@digipen.edu
\par Group: Memory Leak Studios
\date 24-09-2022
\brief
This file contains all the structs of components used in ECS
*******************************************************************************/
#pragma once
#include <glm/glm.hpp>
#include "vec2.h"
#include "Graphics/SpriteVariable.h"
#include "AudioVariable.h"
#include "TagVariable.h"

struct General {
	std::string name;
	TAG tag;
	SUBTAG	subtag = SUBTAG::NOSUBTAG;
	bool isActive;
};

struct Lifespan {
	float lifetime; // Duration of entity's existance
	float limit; // Maximum duration of entity's existance

	//Lifespan(float _lifetime, float _limit) : lifetime(_lifetime), limit(_limit) {}
};

struct Transform
{
	Math::Vec2		scale;
	float			rotation;
	Math::Vec2		translation;
};

struct Sprite
{
	Color color;
	SPRITE sprite;
	GLuint texture = 0;
	int layer = 0;
};

struct Animation
{
	std::vector<GLuint> images;
	float timePerImage;
	float timeToImageSwap;
	int currentImageIndex;
};

struct SheetAnimation
{
	short frameCount = 1;
	short currFrameIndex = 0;
	float timePerFrame = 1.f;
	float timeToFrameSwap = 0.f;
};

struct Physics2D {
	bool gravityEnabled = false;
	float mass,
		  speed,
		  moveDirection;
	Math::Vec2 forces,
			   velocity;
	bool renderFlag = false;
};

struct RectCollider {
	Math::Vec2 centerOffset,
		scaleOffset = {1.f,1.f};
	// float rotationOffset;
	bool renderFlag = false;
};

struct CircleCollider {
	Math::Vec2 centerOffset;
	float scaleOffset =1.f;
	bool renderFlag = false;
};

struct Edge2DCollider {
	Math::Vec2 p0Offset;
	float rotationOffset,
		  scaleOffset;
	bool renderFlag;
};

struct Point2DCollider {
	Math::Vec2 centerOffset;
	bool renderFlag;
};

struct PlayerTmp {
	int HP;
};


struct Stuff {
	int	colorChange =0;
	int	movement = 0;
	float	speed = 1.f;
	float range = 10.f;
};

struct Audio {
	//std::vector<Sound> sound;
	Sound sound;
	bool isSpacial = false;
};

struct Text {
	std::string text;
	int textID;
	int nextTextID;
	GLuint texture = 0; //for dialog box
};

