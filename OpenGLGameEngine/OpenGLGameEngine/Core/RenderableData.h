#pragma once
#include "Mesh.h"
#include "Texture.h"

class RenderableData
{
public:
	RenderableData();
	RenderableData(IRenderable* renderable, Texture* texture);
	IRenderable* Renderable;
	Texture* TextureData;
};

