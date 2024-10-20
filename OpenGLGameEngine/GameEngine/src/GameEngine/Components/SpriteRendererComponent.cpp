#include "SpriteRendererComponent.h"

namespace GameEngine
{
	void SpriteRendererComponent::Render(GLuint modelLocation)
	{

	}

	std::shared_ptr<Shader> SpriteRendererComponent::getRenderDataShader()
	{
		return nullptr;
	}

	void SpriteRendererComponent::ChangeRenderShader(std::shared_ptr<Shader> newRenderShader)
	{
	}

	bool SpriteRendererComponent::IsShadowRenderable()
	{
		return false;
	}
	void SpriteRendererComponent::setSpriteRenderData(std::shared_ptr<SpriteRenderData> spriteRenderData)
	{
		m_SpriteRenderData = spriteRenderData;
	}
	void SpriteRendererComponent::drawSprite(GLuint uniformModel)
	{
	}
}
