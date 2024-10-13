#pragma once
#include "../Core.h"
#include <stdio.h>
#include <GL\glew.h>
namespace GameEngine {
	class ENGINE_API ShadowMap
	{
	public:
		ShadowMap();

		virtual bool Init(GLuint width, GLuint height);
		virtual void Write();
		virtual void Read(GLenum textureUnit);

		GLuint getShadowWidth();
		GLuint getShadowHeight();

		~ShadowMap();

	protected:
		GLuint m_FBO, m_ShadowMap;
		GLuint m_ShadowWidth, m_ShadowHeight;
	};
}
