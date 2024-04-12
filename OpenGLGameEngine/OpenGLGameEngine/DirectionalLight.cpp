#include "DirectionalLight.h"

DirectionalLight::DirectionalLight() : Light()
{
	direction = glm::vec3(0.0f, -1.0f, 0.0f);
}

DirectionalLight::DirectionalLight(GLfloat ambientIntensityValue, GLfloat diffuseIntensityValue, 
	GLfloat red, GLfloat green, GLfloat blue, 
	GLfloat xDir, GLfloat yDir, GLfloat zDir) : 
	Light(ambientIntensityValue, diffuseIntensityValue, red, green, blue)
{
	direction = glm::vec3(xDir, yDir, zDir);
}

void DirectionalLight::UseLight(GLuint ambientIntensityLocation, GLuint ambientColorLocation, GLuint diffuseIntensityLocation, GLuint directionLocation)
{
	Light::useLight(ambientIntensityLocation, ambientColorLocation, diffuseIntensityLocation);
	glUniform3f(directionLocation, direction.x, direction.y, direction.z);
}


DirectionalLight::~DirectionalLight()
{
}
