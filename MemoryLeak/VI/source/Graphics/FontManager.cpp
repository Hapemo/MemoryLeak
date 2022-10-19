#include <FontManager.h>

FontManager::FontManager() : mFontProgram("shaders/font.vert", "shaders/font.frag")
{
    mFontProgram.CompileLinkShaders();
    mFontProgram.Validate();
}

void FontManager::Init()
{
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return -1;
    }

    FT_Face face;
    if (FT_New_Face(ft, "fonts/arial.ttf", 0, &face))
    {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        return -1;
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


    glm::mat4 projection = glm::ortho(0.0f, 1600.f, 0.0f, 900.f);
    mFontProgram.Bind();
    glUniformMatrix4fv(glGetUniformLocation(mFontProgram.GetID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    mFontProgram.Unbind();
 }

void FontManager::Draw(std::string text, float x, float y, float scale)
{
    mFontProgram.Bind();
    glUniform3f(glGetUniformLocation(mFontProgram.GetID(), "textColor"), 0, 0, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(vao);

    for (std::string::const_iterator cIter = text.begin(); cIter != text.end(); ++cIter)
    {
        Character ch = glyphs[*cIter];
        float xpos = x + ch.bearing.x * scale;
        float ypos = y - (ch.size.y - ch.bearing.y) * scale;

        float w = ch.size.x * scale;
        float h = ch.size.y * scale;
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
        x += (ch.advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    mFontProgram.Unbind();
}