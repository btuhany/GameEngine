#include "RendererComponent.h"

namespace GameEngine
{
    void RendererComponent::HandleOnPreOwnerDestroyed()
    {

    }
    std::shared_ptr<Shader> RendererComponent::getRenderDataShader()
    {
        return nullptr;
    }
    ComponentType RendererComponent::getType()
    {
        return ComponentType::Renderer;
    }
}
