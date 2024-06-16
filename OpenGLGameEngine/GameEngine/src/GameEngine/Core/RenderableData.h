#pragma once
#include "Mesh.h"
#include "Texture.h"
#include "Material.h"
namespace GameEngine {
	class RenderableData
	{
	public:
		RenderableData();
		~RenderableData();
		RenderableData(IRenderable* renderable, Texture* texture, Material* material);
		RenderableData(IRenderable* renderable, Material* material);
		IRenderable* Renderable;
		Texture* TextureData;
		Material* MaterialData;
	};
}
