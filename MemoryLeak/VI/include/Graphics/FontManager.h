#pragma once
#include <pch.h>
#include <ft2build.h>
#include FT_FREETYPE_H

class FontManager
{
public:
	FontManager() = default;
	int Init();
};