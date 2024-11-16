#include "TextRendererComponent.h"

namespace GameEngine
{
	void TextRendererComponent::Render(GLuint modelLocation)
	{
	}
	std::shared_ptr<Shader> TextRendererComponent::getRenderDataShader()
	{
		return std::shared_ptr<Shader>();
	}
	void TextRendererComponent::ChangeRenderShader(std::shared_ptr<Shader> newRenderShader)
	{

	}
	bool TextRendererComponent::IsShadowRenderable()
	{
		return false;
	}
	void TextRendererComponent::drawText()
	{

	}
}
