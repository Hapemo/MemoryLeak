#pragma once
#include "pch.h"

enum class SPRITE
{
	SQUARE,
	CIRCLE,
	TEXTURE,
	DEBUG_POINT,
	DEBUG_LINE,
	DEBUG_SQUARE,
	DEBUG_CIRCLE,
	DEBUG_ARROW
};

struct Color
{
	GLubyte r, g, b, a;
};
