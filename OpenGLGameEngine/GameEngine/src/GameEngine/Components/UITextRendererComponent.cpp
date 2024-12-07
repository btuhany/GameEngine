#include "UITextRendererComponent.h"

namespace GameEngine
{
	UITextRendererComponent::UITextRendererComponent()
	{
		text = "EMPTY TEXT";
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
	void UITextRendererComponent::createQuad()
	{
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
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
