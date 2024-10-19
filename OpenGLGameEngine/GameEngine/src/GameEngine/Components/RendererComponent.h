#pragma once
#include "../Resource/Shader.h"
#include <glm/gtc\matrix_transform.hpp>
#include "../Components/Component.h"
#include "../Scene/DirectionalLight.h"
#include "../Scene/Camera.h"

namespace GameEngine
{
	//TODO generic template class with render data
	class ENGINE_API RendererComponent : public Component
	{
	public:
		virtual void Render(GLuint modelLocation) = 0;
		virtual void HandleOnPreOwnerDestroyed() override;
		virtual std::shared_ptr<Shader> getRenderDataShader();
		ComponentType getType() override;
		virtual bool IsShadowRenderable() = 0;
	};
}
