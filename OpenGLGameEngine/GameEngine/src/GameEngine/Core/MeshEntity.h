#pragma once
#include "RenderableEntity.h"
#include "MeshRenderer.h"
namespace GameEngine
{
	class ENGINE_API MeshEntity : public RenderableEntity
	{
	public:
		MeshEntity();
		void Render(glm::mat4 projectionMatrix) override;
		//TODOby initialzie
		std::shared_ptr<MeshRenderer> renderer;
		MeshRenderer* m_Renderer;
		RenderableData* m_RenderData;
	};
}
