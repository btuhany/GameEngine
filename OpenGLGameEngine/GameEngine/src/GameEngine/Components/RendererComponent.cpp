#include "RendererComponent.h"

namespace GameEngine
{
    Shader* RendererComponent::GetRenderDataShader()
    {
        return nullptr;
    }
    ComponentType RendererComponent::getType()
    {
        return ComponentType::Renderer;
    }
}
