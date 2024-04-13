#include "SpotLight.h"

SpotLight::SpotLight() : PointLight()
{
	direction = glm::vec3(0.0f, -1.0f, 0.0f);
	edge = 0.0f;
	procEdge = cosf(glm::radians(edge));
}

SpotLight::SpotLight(GLfloat ambientIntensityValue, GLfloat diffuseIntensityValue, 
	GLfloat red, GLfloat green, GLfloat blue,
	GLfloat xPos, GLfloat yPos, GLfloat zPos, 
	GLfloat xDir, GLfloat yDir, GLfloat zDir,
	GLfloat constantVal, GLfloat linearVal, GLfloat expoValue, 
	GLfloat edgeValue) : PointLight(ambientIntensityValue, diffuseIntensityValue, red, green, blue, xPos, yPos, zPos, constantVal, linearVal, expoValue)
{
	direction = glm::normalize(glm::vec3(xDir, yDir, zDir));
	edge = edgeValue;
	procEdge = cosf(glm::radians(edge));
}

void SpotLight::UseLight(GLuint ambientIntensityLocation, GLuint ambientColorLocation, GLuint diffuseIntensityLocation, GLuint positionLocation, GLuint directionLocation, GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation, GLuint edgeLocation)
{
	PointLight::UseLight(ambientIntensityLocation, ambientColorLocation, diffuseIntensityLocation, positionLocation, constantLocation, linearLocation, exponentLocation);
	glUniform3f(directionLocation, direction.x, direction.y, direction.z);
	glUniform1f(edgeLocation, procEdge);
}

SpotLight::~SpotLight()
{
}
