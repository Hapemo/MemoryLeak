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

struct Paragraph
{
	std::string characters;
	Math::Vec2 pos;
	float scale;
	Math::Vec3 color;
};

class FontRenderer
{
public:
	FontRenderer() : FontRenderer("3Dumb.ttf") {}
	FontRenderer(const std::string& fontfile);
	void Init(const std::string& _fontfile);
	void AddParagraph(const std::string& text, const Math::Vec2& _pos, float scale, const Math::Vec3& color);
	void DrawParagraphs();
private:
	GLuint vao, vbo;
	glm::mat4 projection;
	std::unordered_map<char, Character> glyphs;
	std::vector<Paragraph> paragraphs;
	GLShader mFontProgram;
};