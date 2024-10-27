#pragma once
#include "RendererComponent.h"
#include "../Render/SpriteRenderData.h"
#include "../Entities/GameEntity.h"
namespace GameEngine
{
	class ENGINE_API SpriteRendererComponent : public RendererComponent
	{
	public:
		void Render(GLuint modelLocation) override;
		std::shared_ptr<Shader> getRenderDataShader() override;
		void ChangeRenderShader(std::shared_ptr<Shader> newRenderShader) override;
		bool IsShadowRenderable() override;
		void setSpriteRenderData(std::shared_ptr<SpriteRenderData> spriteRenderData);
	private:
		std::shared_ptr<SpriteRenderData> m_SpriteRenderData;
		void drawSprite(GLuint uniformModel);
	};
}

