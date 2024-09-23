#pragma once
#include <memory.h>
#include "../Core.h"
#include "../Render/ModelRenderData.h"
#include "RendererComponent.h"
#include "../Scene/PointLight.h"
#include "../Scene/Camera.h"
#include "Transform.h"
#include "../Entities/Entity.h"
namespace GameEngine
{
	class ENGINE_API ModelRendererComponent : public RendererComponent
	{
	public:
		void Render(GLuint modelLocation) override;
		void RenderToDirLightShadowMap() override;
		void RenderToPointLightShadowMap(PointLight* pointLight) override;
		Shader* GetRenderDataShader() override;
		std::shared_ptr<ModelRenderData> modelRenderData;

		void DrawModel(GLuint uniformModel);
	private:
		void BindDirLightConfigToShader();

		// Inherited via RendererComponent
	};
}

