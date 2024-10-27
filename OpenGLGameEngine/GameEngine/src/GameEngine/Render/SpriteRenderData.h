#pragma once
#include "RenderData.h"

namespace GameEngine
{
	class ENGINE_API SpriteRenderData : public RenderData
	{
	public:
		SpriteRenderData(std::shared_ptr<Texture> textureData, std::shared_ptr<Material> materialData, std::shared_ptr<Shader> shaderData);
		std::shared_ptr<MeshData> quadMesh;
	private:
		std::shared_ptr<MeshData> createQuadMesh();
	};
}

