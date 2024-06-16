#pragma once
#include "Light.h"

class DirectionalLight : public Light
{
public:
	DirectionalLight();
	DirectionalLight(GLfloat ambientIntensityValue, GLfloat diffuseIntensityValue, GLfloat red, GLfloat green, GLfloat blue, GLfloat xDir, GLfloat yDir, GLfloat zDir,
					GLfloat shadowWidth, GLfloat shadowHeight);
	void UseLight(GLuint ambientIntensityLocation, GLuint ambientColorLocation, GLuint diffuseIntensityLocation, GLuint directionLocation);

	glm::mat4 CalculateLightTransform();

	~DirectionalLight();
private:
	glm::vec3 m_Direction;
};

