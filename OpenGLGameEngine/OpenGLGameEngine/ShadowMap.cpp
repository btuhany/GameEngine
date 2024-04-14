#include "ShadowMap.h"

ShadowMap::ShadowMap()
{
    FBO = 0;
    shadowMap = 0;
}

bool ShadowMap::Init(GLuint width, GLuint height)
{
    shadowWidth = width;
    shadowHeight = height;

    glGenFramebuffers(1, &FBO);


    glGenTextures(1, &shadowMap);
    glBindTexture(GL_TEXTURE_2D, shadowMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowWidth, shadowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float bColour[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, bColour);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowMap, 0);

    /*  A framebuffer object however is not complete without a color buffer 
    so we need to explicitly tell OpenGL we're not going to render any color data.
    We do this by setting both the read and draw buffer to GL_NONE */
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

    if (status != GL_FRAMEBUFFER_COMPLETE)
    {
        printf("Framebuffer Error: %i\n", status);
        return false;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return false;
}

void ShadowMap::Write()
{
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
}

void ShadowMap::Read(GLenum textureUnit)
{
    glActiveTexture(textureUnit);
    glBindTexture(GL_TEXTURE_2D, shadowMap);
}

ShadowMap::~ShadowMap()
{
    if (FBO)
    {
        glDeleteFramebuffers(1, &FBO);
    }

    if (shadowMap)
    {
        glDeleteTextures(1, &shadowMap);
    }
}
