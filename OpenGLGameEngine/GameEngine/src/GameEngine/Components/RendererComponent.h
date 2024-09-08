#pragma once
#include <glm/gtc\matrix_transform.hpp>
#include "../Component.h"

namespace GameEngine
{
	class ENGINE_API RendererComponent : public Component
	{
		virtual void Render(glm::mat4 projectionMatrix) = 0;
		
	};
}
