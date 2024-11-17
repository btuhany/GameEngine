#include "TextRenderManager.h"
namespace GameEngine
{
    Shader* textShader;
    TextData* textData;
	void TextRenderManager::Initialize()
	{
		FT_Library ft;
		if (FT_Init_FreeType(&ft))
		{
			LOG_CORE_ERROR("ERROR::FREETYPE: Could not init FreeType Library");
			return;
		}

		FT_Face face;
		if (FT_New_Face(ft, "fonts/arial.ttf", 0, &face)) //TODO
		{
			LOG_CORE_ERROR("ERROR::FREETYPE: Failed to load font");
			return;
		}

		FT_Set_Pixel_Sizes(face, 0, 48);  //0 means dynamically calculate the width based on height


		if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
		{
			LOG_CORE_ERROR("ERROR::FREETYTPE: Failed to load Glyph");
			return;
		}

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

        for (unsigned char c = 0; c < 128; c++)
        {
            // load character glyph 
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                LOG_CORE_ERROR("ERROR::FREETYTPE: Failed to load Glyph");
                continue;
            }
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
            TextCharacter character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                face->glyph->advance.x
            };
            charactersMap.insert(std::pair<char, TextCharacter>(c, character));

            FT_Done_Face(face);
            FT_Done_FreeType(ft);
        }

        static const char* vShaderLocation = "src/BreakoutGame/Shaders/text_shader.vert";
        static const char* fShaderLocation = "src/BreakoutGame/Shaders/text_shader.frag";
        textShader = new Shader();
        textShader->CreateFromFiles(vShaderLocation, fShaderLocation);
	}
    void TextRenderManager::Render()
    {
        std::string text = "HELLO HELLO HELLO";
        auto VAO = textData->GetVAO();
        auto VBO = textData->GetVBO();
        auto color = glm::vec3(1.0f, 1.0f, 0.0f);
        float scale = 3.0f;
        float x = 10.0f;
        float y = 5.0f;


        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);

        textShader->UseShader();
        glUniform3f(glGetUniformLocation(textShader->shaderID, "textColor"), color.x, color.y, color.z);
        glActiveTexture(GL_TEXTURE2);
        glBindVertexArray(VAO);

        std::string::const_iterator c;
        for (c = text.begin(); c != text.end(); c++)
        {
            TextCharacter ch = charactersMap[*c];

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
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            // render quad
            glDrawArrays(GL_TRIANGLES, 0, 6);
            // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            x += (ch.advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
        }
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}
