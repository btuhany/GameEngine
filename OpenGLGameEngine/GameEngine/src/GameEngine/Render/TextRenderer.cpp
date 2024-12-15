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

            if (!isAbleToRender(textComp))
            {
                LOG_CORE_WARN("TextRenderer:: owner entity is exprired!");
                continue;
            }
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

            float textStartPosX = transform->getPosition().x;
            float textStartPosY = transform->getPosition().y;
            float textStartPosZ = transform->getPosition().z;


            auto scale = transform->getScale();
            auto VAO = textComp->vao;
            auto VBO = textComp->vbo;
            auto IBO = textComp->ibo;

            glBindVertexArray(VAO);
            std::string text = textComp->text;
            std::string::const_iterator c;
            for (c = text.begin(); c != text.end(); c++)
            {
                std::vector<float> charVertices;
                std::vector<unsigned int> charIndices;
                TextCharacter ch = charactersMap[*c];

                
                float xpos = textStartPosX + ch.bearing.x * scale.x;
                float ypos = textStartPosY - (ch.size.y - ch.bearing.y) * scale.y;

                float w = ch.size.x * scale.x;
                float h = ch.size.y * scale.y;

                float charVerticesTemp[4][5] = {
                    { xpos,     ypos + h, textStartPosZ,  0.0f, 0.0f },
                    { xpos,     ypos,   textStartPosZ,    0.0f, 1.0f },
                    { xpos + w, ypos,   textStartPosZ,    1.0f, 1.0f },
                    { xpos + w, ypos + h,  textStartPosZ, 1.0f, 0.0f }
                };

                for (int i = 0; i < 4; ++i)
                {
                    charVertices.insert(charVertices.end(), { charVerticesTemp[i][0], charVerticesTemp[i][1], charVerticesTemp[i][2], charVerticesTemp[i][3], charVerticesTemp[i][4] });
                }

                charIndices.insert(charIndices.end(), {
                    0, 1, 2,
                    0, 2, 3
                    });


                glBindTexture(GL_TEXTURE_2D, ch.textureID);

                glBindBuffer(GL_ARRAY_BUFFER, VBO);
                glBufferData(GL_ARRAY_BUFFER, charVertices.size() * sizeof(float), charVertices.data(), GL_DYNAMIC_DRAW);

                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, charIndices.size() * sizeof(unsigned int), charIndices.data(), GL_DYNAMIC_DRAW);

                glBindVertexArray(VAO);
                glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(charIndices.size()), GL_UNSIGNED_INT, 0);

                glBindBuffer(GL_ARRAY_BUFFER, 0);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


                textStartPosX += (ch.advance >> 6) * scale.x; // bitshift by 6 to get value in pixels (2^6 = 64)
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
    bool TextRenderer::isAbleToRender(std::shared_ptr<UITextRendererComponent> rendererComponent)
    {
        if (rendererComponent->getEntity().expired())
        {
            return false;
        }
        auto ownerEntity = rendererComponent->getEntity().lock();
        //std::cout << "renderer object name: " << ownerEntity->getName() << ", object active: " << ownerEntity->getActive() << " , compnentEnabled: " << rendererComponent->getEnabled() << std::endl;
        return rendererComponent->getEnabled() && ownerEntity->getActive();  //Scene control in the future
    }
}
