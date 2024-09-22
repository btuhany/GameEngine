#pragma once
#include <memory.h>
#include "RendererComponent.h"
#include "../Render/MeshRenderData.h"
#include "../Scene/Camera.h"
#include "Transform.h"
#include "../Entities/Entity.h"

namespace GameEngine
{
	class ENGINE_API MeshRendererComponent : public RendererComponent 
	{
	public:
		void Render(glm::mat4 projectionMatrix) override;
		void RenderToDirLightShadowMap();
		void RenderToPointLightShadowMap(PointLight* pointLight);
		std::shared_ptr<MeshRenderData> meshRenderData;
		//TODOby fix
		std::shared_ptr<Camera> camera;
		Shader* dirShadowShader;
		Shader* omniShadowShader;
		DirectionalLight* directionalLight;
		void DrawMesh(GLuint uniformModel);
	private:
		void BindDirLightConfigToShader();
	};
}
