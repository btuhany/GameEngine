//#include "RenderableData.h"
//namespace GameEngine {
//	RenderableData::RenderableData()
//	{
//	}
//
//	RenderableData::RenderableData(IRenderable* renderable, Texture* texture, Material* material)
//	{
//		Renderable = renderable;
//		TextureData = texture;
//		MaterialData = material;
//	}
//
//	RenderableData::RenderableData(IRenderable* renderable, Material* material)
//	{
//		Renderable = renderable;
//		MaterialData = material;
//	}
//
//	RenderableData::~RenderableData()
//	{
//		printf("deleted renderable data \n");
//		//we will not delete the asset data in this class due to multiple usages
//		/*delete Renderable;
//		delete TextureData;
//		delete MaterialData;*/
//	}
//}