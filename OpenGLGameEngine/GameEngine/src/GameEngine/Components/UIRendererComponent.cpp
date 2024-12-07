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
		if (m_OwnerEntity.expired())
		{
			LOG_CORE_WARN("UIRendererComponent::DrawMesh owner entity is exprired!");
			return;
		}

		auto transform = m_OwnerEntity.lock()->transform;
		float xpos = transform->getPosition().x;
		float ypos = transform->getPosition().y;
		float zpos = transform->getPosition().z;
		float w = transform->getScale().x;
		float h = transform->getScale().y;


		if (m_RenderData->texture != nullptr)
		{
			m_RenderData->texture->UseTexture();
		}

		GLuint VAO = m_RenderData->VAO;
		GLuint VBO = m_RenderData->VBO;
		GLuint IBO = m_RenderData->IBO;

		//EMPTY QUAD PANEL
		//std::vector<float> vertices;
		//std::vector<unsigned int> indices;
		unsigned int indexOffset = 0;


		float vertices[] = {
			xpos,     ypos + h, zpos, 0.0f, 0.0f, // Top-left
			xpos,     ypos,     zpos, 0.0f, 1.0f, // Bottom-left
			xpos + w, ypos,     zpos, 1.0f, 1.0f, // Bottom-right
			xpos + w, ypos + h, zpos, 1.0f, 0.0f  // Top-right
		};

		//float vertices[] = {
		//	0.0f, 1.0f, 0.0f, 0.0f, // Top-left
		//	0.0f, 0.0f, 0.0f, 1.0f, // Bottom-left
		//	1.0f, 0.0f, 1.0f, 1.0f, // Bottom-right
		//	1.0f, 1.0f, 1.0f, 0.0f  // Top-right
		//};

		//glm::mat4 rotation = transform->getRotation();
		//// Apply rotation
		//for (int i = 0; i < 4; ++i) {
		//	glm::vec4 vertexPos(vertices[i * 4], vertices[i * 4 + 1], 0.0f, 1.0f); // x, y, z, w
		//	vertexPos = rotation * vertexPos; // Apply rotation matrix

		//	// Update vertex positions
		//	vertices[i * 4] = vertexPos.x * w + xpos; // Scale and translate X
		//	vertices[i * 4 + 1] = vertexPos.y * h + ypos; // Scale and translate Y
		//}


		unsigned int indices[] = {
			indexOffset, indexOffset + 1, indexOffset + 2, // First triangle
			indexOffset, indexOffset + 2, indexOffset + 3  // Second triangle
		};


		glActiveTexture(GL_TEXTURE2);
		glBindVertexArray(VAO);

		// Upload vertex data
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

		// Upload index data
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);



		// Draw elements
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// Clean up
		//glBindTexture(GL_TEXTURE_2D, 0); TODO shoudl bind textures to zero afterwards?
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

	}
}