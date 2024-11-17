#include "TextRenderManager.h"
namespace GameEngine
{
    Shader* textShader;
    MeshData* textData;
    GLuint VAO, VBO, EBO;
    std::shared_ptr<SpriteRenderData> breakoutSpriteRenderData;
    Scene* scenee;
	void TextRenderManager::Initialize(std::shared_ptr<Shader> mainShader, Scene* scen2e)
	{
        scenee = scen2e;
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
        static const char* vShaderLocation = "src/BreakoutGame/Shaders/text_shader.vert";
        static const char* fShaderLocation = "src/BreakoutGame/Shaders/text_shader.frag";
        textShader = new Shader();
        textShader->CreateFromFiles(vShaderLocation, fShaderLocation);

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        // Generate and bind Vertex Buffer Object (VBO)
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        // Define vertex attributes (position and texture coordinates)
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // Generate and bind Element Buffer Object (EBO)
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        // Unbind VAO (to avoid accidental modification)
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


        std::shared_ptr<Texture> blueTex = std::make_shared<Texture>("src/BreakoutGame/Textures/01-Breakout-Tiles.PNG");
        blueTex->LoadTextureWithAlpha();
        breakoutSpriteRenderData = std::make_shared<SpriteRenderData>(blueTex, nullptr, mainShader);
	}
    void TextRenderManager::Render()
    {
        std::string text = "TOOK ME A DAY";
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, 1920, 1080);
        //Clear window
        //glClearColor(0.0f, 0.5f, 0.0f, 1.0f);
        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        auto mainShader = breakoutSpriteRenderData->shader;
        mainShader->UseShader();
        glUniformMatrix4fv(mainShader->GetViewLocation(), 1, GL_FALSE, glm::value_ptr(scenee->getCamera()->CalculateViewMatrix()));
        glUniformMatrix4fv(mainShader->GetModelLocation(), 1,
            GL_FALSE, glm::value_ptr(
                glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f)) * 
                glm::mat4(1.0f) *
                glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
            ));
        glUniformMatrix4fv(mainShader->GetProjectionLocation(), 1, GL_FALSE, glm::value_ptr(scenee->getCamera()->CalcGetProjectionMatrix(1080.0f / 1920.0f)));
        if (breakoutSpriteRenderData->material != nullptr)
        {
            breakoutSpriteRenderData->material->UseMaterial(breakoutSpriteRenderData->shader->GetMatSpecularIntensityLocation(), breakoutSpriteRenderData->shader->GetMatShininessLocation());
        }

        if (breakoutSpriteRenderData->texture != nullptr)
        {
            breakoutSpriteRenderData->texture->UseTexture();
        }

        auto spriteMeshData = breakoutSpriteRenderData->quadMesh;
        glBindVertexArray(spriteMeshData->GetVAO());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, spriteMeshData->GetIBO());
        glDrawElements(GL_TRIANGLES, spriteMeshData->GetIndexCount(), GL_UNSIGNED_INT, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        glm::mat4 projectionMatrix = glm::ortho(-500.0f, 500.0f, -500.0f, 500.0f, -500.0f, 500.0f);
        glUniformMatrix4fv(textShader->GetProjectionLocation(), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
        auto hh = glGetUniformLocation(textShader->shaderID, "textColor");
        glActiveTexture(GL_TEXTURE2);
        glUniform3f(hh, 0.5f, 1.0f, 0.5f);
        glBindVertexArray(VAO);

        std::vector<float> vertices;
        std::vector<unsigned int> indices;

        unsigned int indexOffset = 0;
        float x = -500.0f;
        float y = 0.0f;
        // Iterate through all characters and generate vertex and index data
        std::string::const_iterator c;
        for (c = text.begin(); c != text.end(); c++)
        {
            TextCharacter ch = charactersMap[*c];
            float w = 30.0f;
            float h = 30.0f;
            float xpos = x;
            float ypos = y;
            // Define the vertices for the current character
            float charVertices[4][4] = {
                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos,     ypos,       0.0f, 1.0f },
                { xpos + w, ypos,       1.0f, 1.0f },
                { xpos + w, ypos + h,   1.0f, 0.0f }
            };

            // Append vertices for this character to the main vertex vector
            for (int i = 0; i < 4; ++i)
            {
                vertices.insert(vertices.end(), { charVertices[i][0], charVertices[i][1], charVertices[i][2], charVertices[i][3] });
            }

            // Define the indices for the current character quad (two triangles)
            indices.insert(indices.end(), {
                indexOffset, indexOffset + 1, indexOffset + 2,
                indexOffset, indexOffset + 2, indexOffset + 3
                });

            // Update index offset for the next character
            indexOffset += 4;

            // Advance the cursor for the next glyph (advance is in 1/64 pixels)
            x += 40.0f;
        

        // Update VBO with the complete vertex data for the string
        glBindTexture(GL_TEXTURE_2D, ch.textureID);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);


        // Update EBO with the index data
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
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
