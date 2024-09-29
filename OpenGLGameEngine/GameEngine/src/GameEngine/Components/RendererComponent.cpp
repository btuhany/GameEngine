#include "RendererComponent.h"

namespace GameEngine
{
    Shader* RendererComponent::GetRenderDataShader()
    {
        return nullptr;
    }
    ComponentType RendererComponent::GetType()
    {
        return ComponentType::Renderer;
    }
}
