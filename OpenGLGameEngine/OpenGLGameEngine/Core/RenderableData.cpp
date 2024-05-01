#include "RenderableData.h"

RenderableData::RenderableData(IRenderable* renderable, Texture* texture)
{
	Renderable = renderable;
	TextureData = texture;
}
