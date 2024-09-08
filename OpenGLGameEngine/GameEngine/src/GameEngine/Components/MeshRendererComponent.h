#pragma once
#include <memory.h>
#include "RendererComponent.h"
#include "../MeshRenderData.h"
#include "../Camera.h"
#include "Transform.h"
#include "../Entity.h"

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
		Camera* camera;
		Shader* dirShadowShader;
		Shader* omniShadowShader;
		DirectionalLight* directionalLight;
		void DrawMesh(GLuint uniformModel);
	private:
		void BindDirLightConfigToShader();
	};
}
