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
		std::shared_ptr<Shader> GetRenderDataShader() override;
		std::shared_ptr<MeshRenderData> meshRenderData;
	private:
		void DrawMesh(GLuint uniformModel);
	};
}
