#pragma once
#include "Core.h"
#include "GameEntity.h"
#include "MeshRenderer.h"
namespace GameEngine
{
	class ENGINE_API RenderableEntity : public GameEntity
	{
	public:
		RenderableEntity();
		virtual void Render(glm::mat4 projectionMatrix) = 0;
	};
}
