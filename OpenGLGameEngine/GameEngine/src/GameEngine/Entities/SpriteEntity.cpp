#include "SpriteEntity.h"

namespace GameEngine
{
	SpriteEntity::SpriteEntity(std::shared_ptr<SpriteRenderData> spriteRenderData)
	{
		renderer = std::make_shared<SpriteRendererComponent>();
		renderer->setSpriteRenderData(spriteRenderData);
		auto aspectRatio = spriteRenderData->texture->GetAspectRatio();
		AddComponent<SpriteRendererComponent>(renderer);
		auto scale = transform->getScale();
		transform->Scale(scale.x * aspectRatio, scale.y, scale.z);
	}
}
