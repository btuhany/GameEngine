#include "UIEntity.h"
namespace GameEngine
{
	UIEntity::UIEntity(std::shared_ptr<UIRenderData> uiRenderData)
	{
		renderer = std::make_shared<UIRendererComponent>();
		renderer->setUIRenderData(uiRenderData);
		AddComponent<UIRendererComponent>(renderer);
	}
}
