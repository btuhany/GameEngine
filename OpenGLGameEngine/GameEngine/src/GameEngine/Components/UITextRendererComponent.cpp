#include "UITextRendererComponent.h"

namespace GameEngine
{
	UITextRendererComponent::UITextRendererComponent()
	{
		createQuad();
	}
	void UITextRendererComponent::Render(GLuint modelLocation)
	{
	}
	std::shared_ptr<Shader> UITextRendererComponent::getRenderDataShader()
	{
		return shader;
	}
	void UITextRendererComponent::ChangeRenderShader(std::shared_ptr<Shader> newRenderShader)
	{

	}
	bool UITextRendererComponent::IsShadowRenderable()
	{
		return false;
	}
	void UITextRendererComponent::drawText()
	{
		//GLuint VAO = m_RenderData->VAO;
		//GLuint VBO = m_RenderData->VBO;
		//GLuint IBO = m_RenderData->IBO;

		////TODO
		//std::vector<float> vertices;
		//std::vector<unsigned int> indices;
		//unsigned int indexOffset = 0;
		//float xpos = 10.0f;
		//float ypos = 500.0f;
		//float w = 500.0f;
		//float h = 300.0f;

		//float charVertices[4][4] = {
		//	{ xpos,     ypos + h,   0.0f, 0.0f },
		//	{ xpos,     ypos,       0.0f, 1.0f },
		//	{ xpos + w, ypos,       1.0f, 1.0f },
		//	{ xpos + w, ypos + h,   1.0f, 0.0f }
		//};
		//for (int i = 0; i < 4; ++i)
		//{
		//	vertices.insert(vertices.end(), { charVertices[i][0], charVertices[i][1], charVertices[i][2], charVertices[i][3] });
		//}

		//indices.insert(indices.end(), {
		//	indexOffset, indexOffset + 1, indexOffset + 2,
		//	indexOffset, indexOffset + 2, indexOffset + 3
		//	});

		//glActiveTexture(GL_TEXTURE2);
		//glBindVertexArray(VAO);

		//glBindBuffer(GL_ARRAY_BUFFER, VBO);
		//glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);

		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_DYNAMIC_DRAW);

		//glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);

		//// Clean up
		////glBindTexture(GL_TEXTURE_2D, 0); TODO shoudl bind textures to zero afterwards?
		//glBindBuffer(GL_ARRAY_BUFFER, 0);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		//glBindVertexArray(0);
	}
	void UITextRendererComponent::createQuad()
	{
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	ComponentType UITextRendererComponent::getType()
	{
		return ComponentType::UITextRenderer;
	}
}
