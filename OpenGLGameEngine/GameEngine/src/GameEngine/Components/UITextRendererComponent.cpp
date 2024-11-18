#include "UITextRendererComponent.h"

namespace GameEngine
{
	UITextRendererComponent::UITextRendererComponent()
	{
	}
	void UITextRendererComponent::Render(GLuint modelLocation)
	{
	}
	std::shared_ptr<Shader> UITextRendererComponent::getRenderDataShader()
	{
		return std::shared_ptr<Shader>();
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

	}
}
