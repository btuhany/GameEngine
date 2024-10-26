#include "SpriteEntity.h"

namespace GameEngine
{
	SpriteEntity::SpriteEntity(std::shared_ptr<SpriteRenderData> spriteRenderData)
	{
		renderer = std::make_shared<SpriteRendererComponent>();
		renderer->setSpriteRenderData(spriteRenderData);
		AddComponent<SpriteRendererComponent>(renderer);
	}
}
