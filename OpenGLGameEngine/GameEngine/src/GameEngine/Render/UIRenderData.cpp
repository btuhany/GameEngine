#include "UIRenderData.h"

namespace GameEngine
{
    UIRenderData::UIRenderData(std::shared_ptr<Shader> shaderData)
    {
        shader = shaderData;
        createQuad();
    }
    UIRenderData::UIRenderData(std::shared_ptr<Shader> shaderData, std::shared_ptr<Texture> textureData)
    {
        shader = shaderData;
        texture = textureData;
        createQuad();
    }
    void UIRenderData::createQuad()
	{
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glGenBuffers(1, &IBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
