#pragma once
#include "../Core.h"
#include "../Components/RendererComponent.h"

namespace GameEngine
{
	class ENGINE_API TextRendererComponent : public RendererComponent
	{
	public:
		TextRendererComponent();
		void Render(GLuint modelLocation) override;
		std::shared_ptr<Shader> getRenderDataShader() override;
		void ChangeRenderShader(std::shared_ptr<Shader> newRenderShader) override;
		bool IsShadowRenderable() override;
	private:
		void drawText();
	};
}
