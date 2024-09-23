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
		void RenderToDirLightShadowMap() override;
		void RenderToPointLightShadowMap(PointLight* pointLight) override;
		Shader* GetRenderDataShader() override;
		std::shared_ptr<MeshRenderData> meshRenderData;

		void DrawMesh(GLuint uniformModel);
	private:
		void BindDirLightConfigToShader();

		// Inherited via RendererComponent
	};
}
