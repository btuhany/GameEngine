#include "TextRenderer.h"
namespace GameEngine
{
    //TODO Renderer comp events functions before initialization.
	void TextRenderer::Initialize()
	{
        if (m_Components.size() <= 0)
        {
            LOG_CORE_INFO("INFO::TEXTRENDERER: Could not init there aren't any");
            return;
        }

		FT_Library ft;
		if (FT_Init_FreeType(&ft))
		{
			LOG_CORE_ERROR("ERROR::FREETYPE: Could not init FreeType Library");
			return;
		}

		FT_Face face;
		if (FT_New_Face(ft, "src/BreakoutGame/Fonts/arial.ttf", 0, &face)) //TODO
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
        }
        glBindTexture(GL_TEXTURE_2D, 0);
        FT_Done_Face(face);
        FT_Done_FreeType(ft);
       
	}
    void TextRenderer::Render(glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0,1920, 1080);  //TODO viewport

        for (size_t i = 0; i < m_Components.size(); i++)
        {
            auto textComp = m_Components[i];
            auto ownerEntity = textComp->getEntity();

            if (ownerEntity.expired())
            {
                LOG_CORE_WARN("TextRenderer:: owner entity is exprired!");
                continue;
            }

            auto transform = ownerEntity.lock()->transform;
           
            auto shader = textComp->shader;
            shader->UseShader();
            shader->SetTextureUnit(2);

            glUniformMatrix4fv(shader->GetProjectionLocation(), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
            glActiveTexture(GL_TEXTURE2);

            auto uniformTextColorLocation = glGetUniformLocation(shader->shaderID, "textColor");
            glUniform3f(uniformTextColorLocation, textComp->color.x, textComp->color.y, textComp->color.z);

            std::vector<float> vertices;
            std::vector<unsigned int> indices;

            unsigned int indexOffset = 0;
            float textStartPosX = 500.0f;
            float textStartPosY = 500.0f;
            float textStartPosZ = 0.0f;

            float charWidth = 50.0f;
            float charHeight = 50.0f;


            auto VAO = textComp->vao;
            auto VBO = textComp->vbo;
            auto IBO = textComp->ibo;

            glBindVertexArray(VAO);
            // Iterate through all characters and generate vertex and index data
            std::string text = textComp->text;
            std::string::const_iterator c;
            for (c = text.begin(); c != text.end(); c++)
            {
                TextCharacter ch = charactersMap[*c];

                float xpos = textStartPosX;
                float ypos = textStartPosY;

                // Define the vertices for the current character
                float charVertices[4][5] = {
                    { xpos,     ypos + charHeight, textStartPosZ,  0.0f, 0.0f },
                    { xpos,     ypos,   textStartPosZ,    0.0f, 1.0f },
                    { xpos + charWidth, ypos,   textStartPosZ,    1.0f, 1.0f },
                    { xpos + charWidth, ypos + charHeight,  textStartPosZ, 1.0f, 0.0f }
                };

                // Append vertices for this character to the main vertex vector
                for (int i = 0; i < 4; ++i)
                {
                    vertices.insert(vertices.end(), { charVertices[i][0], charVertices[i][1], charVertices[i][2], charVertices[i][3], charVertices[i][4] });
                }

                // Define the indices for the current character quad (two triangles)
                indices.insert(indices.end(), {
                    indexOffset, indexOffset + 1, indexOffset + 2,
                    indexOffset, indexOffset + 2, indexOffset + 3
                    });

                // Update index offset for the next character
                indexOffset += 4;

                // Advance the cursor for the next glyph (advance is in 1/64 pixels)
                textStartPosX += 50.0f;


                // Update VBO with the complete vertex data for the string
                glBindTexture(GL_TEXTURE_2D, ch.textureID);

                glBindBuffer(GL_ARRAY_BUFFER, VBO);
                glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);


                // Update EBO with the index data
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_DYNAMIC_DRAW);

                // Render all characters in one draw call using indices
                glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);

                // Clean up
                glBindBuffer(GL_ARRAY_BUFFER, 0);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            }
            glBindVertexArray(0);
            glBindTexture(GL_TEXTURE_2D, 0);


            GLenum err = glGetError();
            if (err != GL_NO_ERROR)
            {
                // Hata mesajýný yazdýrma
                std::cerr << "OpenGL Error: " << err << std::endl;
            }
        }
    }
    void TextRenderer::HandleOnComponentAdded(std::shared_ptr<UITextRendererComponent> textRenderer)
    {
        auto it = std::find(m_Components.begin(), m_Components.end(), textRenderer);
        if (it == m_Components.end())
        {
            m_Components.push_back(textRenderer);
        }
    }
    void TextRenderer::HandleOnComponentRemoved(std::shared_ptr<UITextRendererComponent> textRenderer)
    {
        auto it = std::find(m_Components.begin(), m_Components.end(), textRenderer);
        if (it != m_Components.end())
        {
            m_Components.erase(it);
        }
    }
}
