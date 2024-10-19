#pragma once
#include <memory.h>
#include "../Core.h"
#include "../Render/ModelRenderData.h"
#include "RendererComponent.h"
#include "../Scene/PointLight.h"
#include "../Scene/Camera.h"
#include "Transform.h"
#include "../Entities/GameEntity.h"
namespace GameEngine
{
	class ENGINE_API ModelRendererComponent : public RendererComponent
	{
	public:
		void Render(GLuint modelLocation) override;
		void setModelRenderData(std::shared_ptr<ModelRenderData> modelRenderData);
		std::shared_ptr<Shader> getRenderDataShader() override;
		void ChangeRenderShader(std::shared_ptr<Shader> newRenderShader) override;
		bool IsShadowRenderable() override;
	private:
		void DrawModel(GLuint uniformModel);
		std::shared_ptr<ModelRenderData> m_ModelRenderData;
	};
}

