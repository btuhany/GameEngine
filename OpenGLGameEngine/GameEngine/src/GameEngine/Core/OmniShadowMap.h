#pragma once
#include "ShadowMap.h"
namespace GameEngine {
	class OmniShadowMap : public ShadowMap
	{
	public:
		OmniShadowMap();

		bool Init(GLuint width, GLuint height);
		void Write();
		void Read(GLenum textureUnit);

		~OmniShadowMap();
	};
}
