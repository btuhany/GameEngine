#pragma once
#include "Core.h"
#include "ShadowMap.h"
namespace GameEngine {
	class ENGINE_API OmniShadowMap : public ShadowMap
	{
	public:
		OmniShadowMap();

		bool Init(GLuint width, GLuint height);
		void Write();
		void Read(GLenum textureUnit);

		~OmniShadowMap();
	};
}
