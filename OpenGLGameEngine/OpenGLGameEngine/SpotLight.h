#pragma once
#include "PointLight.h"
class SpotLight :
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

    void UseLight(GLuint ambientIntensityLocation, GLuint ambientColorLocation, GLuint diffuseIntensityLocation, GLuint positionLocation, GLuint directionLocation, GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation, GLuint edgeLocation);

    ~SpotLight();

private:
    glm::vec3 direction;
    GLfloat edge, procEdge;
};

