#include "DebugRenderData.h"

namespace GameEngine
{
	DebugRenderData::DebugRenderData(std::shared_ptr<MeshData> meshData, std::shared_ptr<Shader> shaderData)
	{
		mesh = meshData;
		shader = shaderData;
	}
}


