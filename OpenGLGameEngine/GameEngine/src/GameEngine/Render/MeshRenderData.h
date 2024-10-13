#pragma once
#include <memory>
#include "../Core.h"
#include "RenderData.h"
#include "../Resource/MeshData.h"
namespace GameEngine
{
	class ENGINE_API MeshRenderData : public RenderData
	{
	public:
		MeshRenderData(std::shared_ptr<MeshData> meshData, std::shared_ptr<Texture> textureData, std::shared_ptr<Material> materialData, std::shared_ptr<Shader> shaderData);
		std::shared_ptr<MeshData> mesh;
	};
}

