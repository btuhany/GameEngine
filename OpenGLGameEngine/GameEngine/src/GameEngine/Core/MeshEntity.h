#pragma once
#include "RenderableEntity.h"
#include "MeshRenderer.h"
namespace GameEngine
{
	class ENGINE_API MeshEntity : public RenderableEntity
	{
	public:
		void Render(glm::mat4 projectionMatrix) override;
		//TODOby initialzie
		MeshRenderer* m_Renderer;
		RenderableData* m_RenderData;
	};
}
