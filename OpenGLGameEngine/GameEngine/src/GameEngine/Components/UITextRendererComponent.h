#pragma once
#include "../Core.h"
#include "../Components/RendererComponent.h"

namespace GameEngine
{
	enum class TextSize
	{
		Medium, //48
		Large //128
	};
	class ENGINE_API UITextRendererComponent : public RendererComponent
	{
	public:
		UITextRendererComponent();
		void Render(GLuint modelLocation) override;
		std::shared_ptr<Shader> getRenderDataShader() override;
		void ChangeRenderShader(std::shared_ptr<Shader> newRenderShader) override;
		bool IsShadowRenderable() override;
		std::shared_ptr<Shader> shader;
		std::string text;
		glm::vec3 color;
		float charWidth;
		float charHeight;
		GLuint vao, vbo, ibo;
		ComponentType getType() override;
		float calculatedTextWidth = -1.0f;
		float calculatedTextHeight = -1.0f;
		TextSize textSize;
	private:
		void createQuad();
	};
}
