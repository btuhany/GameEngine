#pragma once
#include "RenderableEntity.h"
#include "../Components/SpriteRendererComponent.h"
namespace GameEngine
{
	class ENGINE_API SpriteEntity : public RenderableEntity
	{
	public:
		SpriteEntity(std::shared_ptr<SpriteRenderData> spriteRenderData);
		std::shared_ptr<SpriteRendererComponent> renderer;
	};
}

