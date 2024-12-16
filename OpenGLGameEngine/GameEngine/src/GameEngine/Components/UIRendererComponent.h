#pragma once
#include "../Core.h"
#include "../Components/RendererComponent.h"
#include "../Render/UIRenderData.h"

#include "../Components/Transform.h"
#include "../Entities/GameEntity.h"
namespace GameEngine
{
	//TODO UISpriteRendererComponent name refactor
	class ENGINE_API UIRendererComponent : public RendererComponent
	{
	public:
		void Render(GLuint modelLocation) override;
		bool IsShadowRenderable() override;
		ComponentType getType() override;
		void setUIRenderData(std::shared_ptr<UIRenderData> uiRenderData);
		void ChangeRenderShader(std::shared_ptr<Shader> newRenderShader) override;
		std::shared_ptr<Shader> getRenderDataShader() override;
	private:
		void drawQuad();
		std::shared_ptr<UIRenderData> m_RenderData;
	};
}

