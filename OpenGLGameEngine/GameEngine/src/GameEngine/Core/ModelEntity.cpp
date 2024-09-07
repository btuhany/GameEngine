#include "ModelEntity.h"

namespace GameEngine
{
	ModelEntity::ModelEntity()
	{
		renderer = std::make_shared<ModelRendererComponent>();
		AddComponent<ModelRendererComponent>(renderer);
	}

	void ModelEntity::Render(glm::mat4 projectionMatrix)
	{
		renderer->Render(projectionMatrix);
	}
}
