#include "MeshRenderData.h"

namespace GameEngine
{
	MeshRenderData::MeshRenderData(std::shared_ptr<MeshData> meshData, std::shared_ptr<Texture> textureData, std::shared_ptr<Material> materialData, std::shared_ptr<Shader> shaderData) : RenderData(textureData, materialData, shaderData)
	{
		mesh = meshData;
	}
}
