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
		void Render(glm::mat4 projectionMatrix) override;
		void RenderToDirLightShadowMap();
		void RenderToPointLightShadowMap(PointLight* pointLight);
		std::shared_ptr<ModelRenderData> modelRenderData;
		//TODOby fix
		std::shared_ptr<Camera> camera;
		Shader* dirShadowShader;
		Shader* omniShadowShader;
		DirectionalLight* directionalLight;
		void DrawModel(GLuint uniformModel);
	private:
		void BindDirLightConfigToShader();
	};
}

