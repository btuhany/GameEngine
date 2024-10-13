#include "RendererComponent.h"

namespace GameEngine
{
    void RendererComponent::HandleOnPreOwnerDestroyed()
    {

    }
    std::shared_ptr<Shader> RendererComponent::GetRenderDataShader()
    {
        return nullptr;
    }
    ComponentType RendererComponent::getType()
    {
        return ComponentType::Renderer;
    }
}
