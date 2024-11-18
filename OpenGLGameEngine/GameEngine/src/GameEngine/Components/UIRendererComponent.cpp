#include "UIRendererComponent.h"
namespace GameEngine
{
	void UIRendererComponent::Render(GLuint modelLocation)
	{
		drawQuad();
	}
	bool UIRendererComponent::IsShadowRenderable()
	{
		return false;
	}
	ComponentType UIRendererComponent::getType()
	{
		return ComponentType::UIRenderer;
	}
	void UIRendererComponent::setUIRenderData(std::shared_ptr<UIRenderData> uiRenderData)
	{
		m_RenderData = uiRenderData;
	}
	void UIRendererComponent::ChangeRenderShader(std::shared_ptr<Shader> newRenderShader)
	{
	}
	std::shared_ptr<Shader> UIRendererComponent::getRenderDataShader()
	{
		return m_RenderData->shader;
	}
	void UIRendererComponent::drawQuad()
	{
		GLuint VAO = m_RenderData->VAO;
		GLuint VBO = m_RenderData->VBO;
		GLuint IBO = m_RenderData->IBO;

		//TODO
		std::vector<float> vertices;
		std::vector<unsigned int> indices;
		unsigned int indexOffset = 0;
		float xpos = 10.0f;
		float ypos = 0.0f;
		float w = 30.0f;
		float h = 30.0f;

		float charVertices[4][4] = {
			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos,     ypos,       0.0f, 1.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },
			{ xpos + w, ypos + h,   1.0f, 0.0f }
		};
		for (int i = 0; i < 4; ++i)
		{
			vertices.insert(vertices.end(), { charVertices[i][0], charVertices[i][1], charVertices[i][2], charVertices[i][3] });
		}

		indices.insert(indices.end(), {
			indexOffset, indexOffset + 1, indexOffset + 2,
			indexOffset, indexOffset + 2, indexOffset + 3
			});

			glBindVertexArray(VAO);
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
		glBindVertexArray(0);
	}
}