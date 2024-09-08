#pragma once
#include <memory.h>
#include "../Core.h"
#include "../ModelRenderData.h"
#include "RendererComponent.h"
#include "../PointLight.h"
#include "../Camera.h"
#include "Transform.h"
#include "../Entity.h"
namespace GameEngine
{
	class ENGINE_API ModelRendererComponent : public RendererComponent
	{
	public:
		void Render(glm::mat4 projectionMatrix) override;
		void RenderToDirLightShadowMap();
		void RenderToPointLightShadowMap(PointLight* pointLight);
		std::shared_ptr<ModelRenderData> modelRenderData;
		//TODOby fix
		Camera* camera;
		Shader* dirShadowShader;
		Shader* omniShadowShader;
		DirectionalLight* directionalLight;
		void DrawModel(GLuint uniformModel);
	private:
		void BindDirLightConfigToShader();
	};
}

