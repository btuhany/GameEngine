#include "OmniShadowMap.h"
namespace GameEngine {
	OmniShadowMap::OmniShadowMap() : ShadowMap()
	{
	}

	bool OmniShadowMap::Init(GLuint width, GLuint height)
	{
		m_ShadowWidth = width;
		m_ShadowHeight = height;

		glGenFramebuffers(1, &m_FBO);

		glGenTextures(1, &m_ShadowMap);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_ShadowMap);

		for (size_t i = 0; i < 6; i++)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, m_ShadowWidth, m_ShadowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
		}

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_ShadowMap, 0);

		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);

		GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

		if (status != GL_FRAMEBUFFER_COMPLETE)
		{
			printf("Framebuffer Error: %i\n", status);
			return false;
		}

		//glBindFramebuffer(GL_FRAMEBUFFER, 0);

		return true;
	}

	void OmniShadowMap::Write()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
	}

	void OmniShadowMap::Read(GLenum textureUnit)
	{
		glActiveTexture(textureUnit);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_ShadowMap);
	}

	OmniShadowMap::~OmniShadowMap()
	{
	}
}