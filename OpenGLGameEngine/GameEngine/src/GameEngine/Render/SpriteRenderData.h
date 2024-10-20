#pragma once
#include "RenderData.h"

namespace GameEngine
{
	class ENGINE_API SpriteRenderData : public RenderData
	{
	public:
		SpriteRenderData(std::shared_ptr<Texture> textureData, std::shared_ptr<Material> materialData, std::shared_ptr<Shader> shaderData);
	private:
		void createQuadMesh();
	};
}

