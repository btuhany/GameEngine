#pragma once
#include "Light.h"
#include "OmniShadowMap.h"
#include <vector>
class PointLight :public Light
{
public:
    PointLight();
    PointLight(GLfloat ambientIntensityValue, GLfloat diffuseIntensityValue, 
               GLfloat red, GLfloat green, GLfloat blue,
               GLfloat xPos, GLfloat yPos, GLfloat zPos,
               GLfloat constantVal, GLfloat linearVal, GLfloat expoValue, GLuint shadowWidth, GLuint shadowHeight, GLfloat nearPlaneVal, GLfloat farPlaneVal);
    void UseLight(GLuint ambientIntensityLocation, GLuint ambientColorLocation, GLuint diffuseIntensityLocation, GLuint positionLocation, GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation);
    std::vector<glm::mat4> CalculateLightTransform();
    GLfloat GetFarPlane();
    glm::vec3 GetPosition();
    ~PointLight();

private:
    glm::vec3 position;
    GLfloat constant, linear, exponent;

protected:
    GLfloat farPlane;
};

