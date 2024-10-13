#pragma once
#include "RenderableEntity.h"
#include "../Components/MeshRendererComponent.h"
#include "../Debug/Log.h"
#include "../Components/Component.h"
namespace GameEngine
{
	class ENGINE_API MeshEntity : public RenderableEntity
	{
	public:
		MeshEntity(std::shared_ptr<MeshRenderData> meshRenderData);
		std::shared_ptr<MeshRendererComponent> renderer;
	};
}
