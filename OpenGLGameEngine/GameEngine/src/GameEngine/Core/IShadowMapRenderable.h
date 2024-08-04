#pragma once
#include "DirectionalLight.h"
#include "PointLight.h"

namespace GameEngine
{
	class IShadowMapRenderable
	{
	public:
		virtual void RenderDirectionalShadowMap(DirectionalLight* dirLight) = 0;
		virtual void RenderOmniShadowMap(PointLight* pointLight) = 0;
	};
}
