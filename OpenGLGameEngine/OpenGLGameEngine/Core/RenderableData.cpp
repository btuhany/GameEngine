#include "RenderableData.h"

RenderableData::RenderableData()
{
}

RenderableData::RenderableData(IRenderable* renderable, Texture* texture, Material* material)
{
	Renderable = renderable;
	TextureData = texture;
	MaterialData = material;
}

RenderableData::RenderableData(IRenderable* renderable, Material* material)
{
	Renderable = renderable;
	MaterialData = material;
}