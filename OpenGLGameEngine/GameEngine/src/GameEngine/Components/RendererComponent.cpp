#include "RendererComponent.h"

namespace GameEngine
{
    void RendererComponent::HandleOnPreOwnerDestroyed()
    {

    }
    Shader* RendererComponent::GetRenderDataShader()
    {
        return nullptr;
    }
    ComponentType RendererComponent::getType()
    {
        return ComponentType::Renderer;
    }
}
