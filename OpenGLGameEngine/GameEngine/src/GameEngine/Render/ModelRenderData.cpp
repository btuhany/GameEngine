#include "ModelRenderData.h"

GameEngine::ModelRenderData::ModelRenderData(std::shared_ptr<ModelData> modelData, std::shared_ptr<Texture> textureData, std::shared_ptr<Material> materialData, std::shared_ptr<Shader> shaderData) : RenderData(textureData, materialData, shaderData)
{
	model = modelData;
}
