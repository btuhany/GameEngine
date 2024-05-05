#pragma once
#include "Mesh.h"
#include "Texture.h"

class RenderableData
{
public:
	RenderableData();
	RenderableData(IRenderable* renderable, Texture* texture);
	RenderableData(IRenderable* renderable);
	IRenderable* Renderable;
	Texture* TextureData;
};

