/*!*****************************************************************************
\file FontManager.cpp
\author Kew Yu Jun
\par DP email: k.yujun\@digipen.edu
\par Group: Memory Leak Studios
\date 14-10-2022
\brief
This file contains a class FontRenderer, which is a tool for renderering fonts.
*******************************************************************************/
#include <FontManager.h>

/*!*****************************************************************************
\brief
Default constructor for FontRenderer class.
*******************************************************************************/
FontRenderer::FontRenderer(const std::string& fontfile) 
: mFontProgram("shaders/font.vert", "shaders/font.frag"), mVAO(), mVBO(), mProjection()
{
    mFontProgram.CompileLinkShaders();
    mFontProgram.Validate();
    mMatrixLocation = glGetUniformLocation(mFontProgram.GetID(), "projection");
    mTextColorLocation = glGetUniformLocation(mFontProgram.GetID(), "textColor");
    mZValueLocation = glGetUniformLocation(mFontProgram.GetID(), "zValue");
    Init(fontfile);
}
/*!*****************************************************************************
\brief
Initializes the FontRenderer

\param const std::string& fontfile
String containing name of the font file.
*******************************************************************************/
void FontRenderer::Init(const std::string& _fontfile)
{
    //free type
    FT_Library ft;
    ASSERT(FT_Init_FreeType(&ft), 
        "ERROR::FREETYPE: Could not init FreeType Library\n");

    std::string filepath = "../resources/Fonts/" + _fontfile;

    FT_Face face;
    if (FT_New_Face(ft, filepath.c_str(), 0, &face))
    {
        LOG_INFO("ERROR::FREETYPE: Failed to load font\n");
        return;
    }

    FT_Set_Pixel_Sizes(face, 0, 48);

    ASSERT(FT_Load_Char(face, 'X', FT_LOAD_RENDER), 
        "ERROR::FREETYTPE: Failed to load Glyph\n");
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

    for (unsigned char c = 0; c < 128; ++c)
    {
        // load character glyph into opengl
        ASSERT(FT_Load_Char(face, c, FT_LOAD_RENDER), 
            "ERROR::FREETYTPE: Failed to load Glyph\n");
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        // generate texture for the glyph
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        // set texture options 
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // store character for later use
        Character character = {
            texture,
            Math::Vec2((float)face->glyph->bitmap.width, (float)face->glyph->bitmap.rows),
            Math::Vec2((float)face->glyph->bitmap_left, (float)face->glyph->bitmap_top),
            (unsigned int)face->glyph->advance.x
        };
        mGlyphs.insert(std::pair<char, Character>(c, character));
    }
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    //projection matrix
    mProjection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);

    //create buffers for characters
    glGenVertexArrays(1, &mVAO);
    glGenBuffers(1, &mVBO);
    glBindVertexArray(mVAO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glm::mat4 _projection = glm::ortho(0.0f, 1600.f, 0.0f, 900.f);
    mFontProgram.Bind();
    //insert uniform
    glUniformMatrix4fv(mMatrixLocation, 1, GL_FALSE, glm::value_ptr(_projection));
    mFontProgram.Unbind();
 }
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
void FontRenderer::AddParagraph(const std::string& text, const Math::Vec2& _pos, float scale, const Math::Vec3& color, float layer)
{
    mParagraphs.push_back(Paragraph(text, _pos, scale, color, layer));
}
/*!*****************************************************************************
\brief
Renders all paragraphs stored in mParagraphs.
*******************************************************************************/
void FontRenderer::DrawParagraphs()
{
    for (const Paragraph& para : mParagraphs)
    {
        Math::Vec2 pos = para.pos;
        mFontProgram.Bind();
        glUniform3f(mTextColorLocation, para.color.r, para.color.g, para.color.b);
        glUniform1f(mZValueLocation, para.layer);
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(mVAO);

        // iterate through characters in paragraph
        for (std::string::const_iterator cIter = para.characters.begin(); cIter != para.characters.end(); ++cIter)
        {
            Character ch = mGlyphs[*cIter];
            float xpos = pos.x + ch.bearing.x * para.scale;
            float ypos = pos.y - (ch.size.y - ch.bearing.y) * para.scale;

            float w = ch.size.x * para.scale;
            float h = ch.size.y * para.scale;
            // update VBO for each character
            float vertices[6][4] = {
                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos,     ypos,       0.0f, 1.0f },
                { xpos + w, ypos,       1.0f, 1.0f },

                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos + w, ypos,       1.0f, 1.0f },
                { xpos + w, ypos + h,   1.0f, 0.0f }
            };
            // render glyph texture over quad
            glBindTexture(GL_TEXTURE_2D, ch.textureID);
            // update content of VBO memory
            glBindBuffer(GL_ARRAY_BUFFER, mVBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            // render quad
            glDrawArrays(GL_TRIANGLES, 0, 6);

            // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            pos.x += (ch.advance >> 6) * para.scale; // bitshift by 6 to get value in pixels (2^6 = 64)
        }
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
        mFontProgram.Unbind();
    }
    //clear paragraph for next frame
    mParagraphs.clear();
}