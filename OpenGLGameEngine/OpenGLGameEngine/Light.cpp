#include "Light.h"

Light::Light()
{
	colour = glm::vec3(1.0f, 1.0f, 1.0f);
	ambientIntensity = 1.0f;

	direction = glm::vec3(0.0f, -1.0f, 0.0f);

}

Light::Light(GLfloat ambientIntensityValue, GLfloat red, GLfloat green, GLfloat blue, GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat diffuseIntensityValue)
{
	colour = glm::vec3(red, green, blue);
	ambientIntensity = ambientIntensityValue;

	direction = glm::vec3(xDir, yDir, zDir);
	diffuseIntensity = diffuseIntensityValue;
}

void Light::UseLight(GLuint ambientIntensityLocation, GLuint ambientColorLocation, GLuint diffuseIntensityLocaiton, GLuint directionLocation)
{
	glUniform3f(ambientColorLocation, colour.x, colour.y, colour.z);
	glUniform1f(ambientIntensityLocation, ambientIntensity);

	glUniform3f(directionLocation, direction.x, direction.y, direction.z);
	glUniform1f(diffuseIntensityLocaiton, diffuseIntensity);
}

Light::~Light()
{
}
