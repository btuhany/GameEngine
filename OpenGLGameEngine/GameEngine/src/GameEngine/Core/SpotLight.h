#pragma once
#include "Core.h"
#include "PointLight.h"
namespace GameEngine {
    class ENGINE_API SpotLight :
        public PointLight
    {
    public:
        SpotLight();

        SpotLight(GLfloat ambientIntensityValue, GLfloat diffuseIntensityValue,
            GLfloat red, GLfloat green, GLfloat blue,
            GLfloat xPos, GLfloat yPos, GLfloat zPos,
            GLfloat xDir, GLfloat yDir, GLfloat zDir,
            GLfloat constantVal, GLfloat linearVal, GLfloat expoValue,
            GLfloat edgeValue, GLfloat shadowWidth, GLfloat shadowHeight, GLfloat nearPlaneVal, GLfloat farPlaneVal);

        SpotLight(GLfloat ambientIntensityValue, GLfloat diffuseIntensityValue,
            GLfloat red, GLfloat green, GLfloat blue,
            GLfloat xPos, GLfloat yPos, GLfloat zPos,
            GLfloat xDir, GLfloat yDir, GLfloat zDir,
            GLfloat constantVal, GLfloat linearVal, GLfloat expoValue,
            GLfloat edgeValue, GLfloat nearPlaneVal, GLfloat farPlaneVal);

        void UseLight(GLuint ambientIntensityLocation, GLuint ambientColorLocation, GLuint diffuseIntensityLocation, GLuint positionLocation, GLuint directionLocation, GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation, GLuint useOmniShadowLoc, GLuint edgeLocation);

        ~SpotLight();

    private:
        glm::vec3 m_Direction;
        GLfloat m_Edge, m_ProcEdge;
    };
}
