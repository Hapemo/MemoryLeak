#pragma once
#include <pch.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <Logger.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Graphics/GLShader.h>

struct Character
{
	unsigned int textureID; //ID of the glyph
	Math::Vec2 size;		//size of the glyph
	Math::Vec2 bearing;		//offset from baseline to left/top of glyph
	unsigned int advance;	//offset to advance to next glyph
};

class FontManager
{
public:
	FontManager();
	void Init();
	void Draw(std::string text, float x, float y, float scale);
private:
	unsigned int vao, vbo;
	glm::mat4 projection;
	std::unordered_map<char, Character> glyphs;
	GLShader mFontProgram;
};