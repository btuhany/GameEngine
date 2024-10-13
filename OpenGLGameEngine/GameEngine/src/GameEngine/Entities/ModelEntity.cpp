#include "ModelEntity.h"

namespace GameEngine
{
	ModelEntity::ModelEntity(std::shared_ptr<ModelRenderData> modelRenderData)
	{
		renderer = std::make_shared<ModelRendererComponent>();
		renderer->setModelRenderData(modelRenderData);
		AddComponent<ModelRendererComponent>(renderer);
	}
}
