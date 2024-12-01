#pragma once
#include "../Core.h"
#include "../Components/RendererComponent.h"

namespace GameEngine
{
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
		GLuint vao, vbo, ibo;
		ComponentType getType() override;
	private:
		void drawText();
		void createQuad();
	};
}
