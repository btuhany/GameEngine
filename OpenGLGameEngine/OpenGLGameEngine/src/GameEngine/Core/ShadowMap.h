#pragma once

#include <stdio.h>
#include <GL\glew.h>

class ShadowMap
{
public:
	ShadowMap();

	virtual bool Init(GLuint width, GLuint height);
	virtual void Write();
	virtual void Read(GLenum textureUnit);

	GLuint GetShadowWidth() { return m_ShadowWidth; }
	GLuint GetShadowHeight() { return m_ShadowHeight; }

	~ShadowMap();

protected:
	GLuint m_FBO, m_ShadowMap;
	GLuint m_ShadowWidth, m_ShadowHeight;
};

