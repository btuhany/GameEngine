#pragma once
#include "Light.h"
class PointLight :public Light
{
public:
    PointLight();
    PointLight(GLfloat ambientIntensityValue, GLfloat diffuseIntensityValue, 
               GLfloat red, GLfloat green, GLfloat blue,
               GLfloat xPos, GLfloat yPos, GLfloat zPos,
               GLfloat constantVal, GLfloat linearVal, GLfloat expoValue);
    void UseLight(GLuint ambientIntensityLocation, GLuint ambientColorLocation, GLuint diffuseIntensityLocation, GLuint positionLocation, GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation);
    ~PointLight();

private:
    glm::vec3 position;
    GLfloat constant, linear, exponent;
};
