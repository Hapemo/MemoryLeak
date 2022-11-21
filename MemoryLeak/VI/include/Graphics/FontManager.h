/*!*****************************************************************************
\file FontManager.h
\author Kew Yu Jun
\par DP email: k.yujun\@digipen.edu
\par Group: Memory Leak Studios
\date 14-10-2022
\brief
This file contains a class FontRenderer, which is a tool for renderering fonts.
*******************************************************************************/
#pragma once
#include <pch.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <Logger.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Graphics/GLShader.h>

/*!*****************************************************************************
\brief
Struct that encapsulates what is needed for rendering a single character.
*******************************************************************************/
struct Character
{
	unsigned int textureID; //ID of the glyph
	Math::Vec2 size;		//size of the glyph
	Math::Vec2 bearing;		//offset from baseline to left/top of glyph
	unsigned int advance;	//offset to advance to next glyph
};

/*!*****************************************************************************
\brief
Struct that encapsulates a string.
*******************************************************************************/
struct Paragraph
{
	std::string characters;
	Math::Vec2 pos;
	float scale;
	Math::Vec3 color;
	float layer;
};

/*!*****************************************************************************
\brief
Class that encapsulates a FontRenderer tool.
*******************************************************************************/
class FontRenderer
{
public:
	/*!*****************************************************************************
	\brief
	Default constructor for FontRenderer class.
	*******************************************************************************/
	FontRenderer() : FontRenderer("3Dumb.ttf") {}
	/*!*****************************************************************************
	\brief
	Non-default constructor for FontRenderer class.

	\param const std::string& fontfile
	String containing name of the font file.
	*******************************************************************************/
	FontRenderer(const std::string& _fontfile);
	/*!*****************************************************************************
	\brief
	Adds a paragraph to the font renderer to be rendered.

	\param const std::string& _text
	String containing text to be rendered.

	\param const Math::Vec2& _pos
	Position to render the string.

	\param float _scale
	Scale of the font.

	\param const Math::Vec3& _color
	Color of the font.
	*******************************************************************************/
	void AddParagraph(const std::string& _text, const Math::Vec2& _pos, float _scale, const Math::Vec3& _color, float layer);
	/*!*****************************************************************************
	\brief
	Renders all paragraphs stored in mParagraphs.
	*******************************************************************************/
	void DrawParagraphs();

	bool IsInitialized() { return mInitialized; }
private:
	/*!*****************************************************************************
	\brief
	Initializes the FontRenderer

	\param const std::string& fontfile
	String containing name of the font file.
	*******************************************************************************/
	bool Init(const std::string& _fontfile);
	GLuint mVAO, mVBO;
	glm::mat4 mProjection;
	std::unordered_map<char, Character> mGlyphs;
	std::vector<Paragraph> mParagraphs;
	GLShader mFontProgram;
	GLint mTextColorLocation, mMatrixLocation, mZValueLocation;
	bool mInitialized;
};