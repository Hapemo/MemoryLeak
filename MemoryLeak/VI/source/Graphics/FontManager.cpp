#include <FontManager.h>

FontRenderer::FontRenderer(const std::string& fontfile) 
: mFontProgram("shaders/font.vert", "shaders/font.frag"), vao(), vbo(), projection()
{
    mFontProgram.CompileLinkShaders();
    mFontProgram.Validate();
    Init(fontfile);
}

void FontRenderer::Init(const std::string& _fontfile)
{
    FT_Library ft;
    ASSERT(FT_Init_FreeType(&ft), "ERROR::FREETYPE: Could not init FreeType Library\n");

    std::string filepath = "../VI/fonts/" + _fontfile;

    FT_Face face;
    ASSERT(FT_New_Face(ft, filepath.c_str(), 0, &face), "ERROR::FREETYPE: Failed to load font\n");

    FT_Set_Pixel_Sizes(face, 0, 48);

    ASSERT(FT_Load_Char(face, 'X', FT_LOAD_RENDER), "ERROR::FREETYTPE: Failed to load Glyph\n");
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

    for (unsigned char c = 0; c < 128; ++c)
    {
        // load character glyph 
        ASSERT(FT_Load_Char(face, c, FT_LOAD_RENDER), "ERROR::FREETYTPE: Failed to load Glyph\n");
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        // generate texture
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
        // now store character for later use
        Character character = {
            texture,
            Math::Vec2((float)face->glyph->bitmap.width, (float)face->glyph->bitmap.rows),
            Math::Vec2((float)face->glyph->bitmap_left, (float)face->glyph->bitmap_top),
            (unsigned int)face->glyph->advance.x
        };
        glyphs.insert(std::pair<char, Character>(c, character));
    }
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    glm::mat4 _projection = glm::ortho(0.0f, 1600.f, 0.0f, 900.f);
    mFontProgram.Bind();
    glUniformMatrix4fv(glGetUniformLocation(mFontProgram.GetID(), "projection"), 1, GL_FALSE, glm::value_ptr(_projection));
    mFontProgram.Unbind();
 }

void FontRenderer::AddParagraph(const std::string& text, const Math::Vec2& _pos, float scale, const Math::Vec3& color)
{
    paragraphs.push_back(Paragraph(text, _pos, scale, color));
}


void FontRenderer::DrawParagraphs()
{
    for (const Paragraph& para : paragraphs)
    {
        Math::Vec2 pos = para.pos;
        mFontProgram.Bind();
        glUniform3f(glGetUniformLocation(mFontProgram.GetID(), "textColor"), para.color.r, para.color.g, para.color.b);
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(vao);

        for (std::string::const_iterator cIter = para.characters.begin(); cIter != para.characters.end(); ++cIter)
        {
            Character ch = glyphs[*cIter];
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
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
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
    paragraphs.clear();
}