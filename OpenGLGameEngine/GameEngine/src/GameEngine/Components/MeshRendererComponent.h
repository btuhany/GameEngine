#pragma once
#include <memory.h>
#include "RendererComponent.h"
#include "../Render/MeshRenderData.h"
#include "../Scene/Camera.h"
#include "Transform.h"
#include "../Entities/GameEntity.h"

namespace GameEngine
{
	class ENGINE_API MeshRendererComponent : public RendererComponent 
	{
	public:
		void Render(GLuint modelLocation) override;
		void setMeshRenderData(std::shared_ptr<MeshRenderData> meshRenderData);
		std::shared_ptr<Shader> getRenderDataShader() override;
		void ChangeRenderShader(std::shared_ptr<Shader> newRenderShader) override;
		bool IsShadowRenderable() override;
	private:
		std::shared_ptr<MeshRenderData> m_MeshRenderData;
		void drawMesh(GLuint uniformModel);
	};
}
