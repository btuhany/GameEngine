#include "DirectionalLight.h"

DirectionalLight::DirectionalLight() : Light()
{
	m_Direction = glm::vec3(0.0f, -1.0f, 0.0f);
}

DirectionalLight::DirectionalLight(GLfloat ambientIntensityValue, GLfloat diffuseIntensityValue, 
	GLfloat red, GLfloat green, GLfloat blue, 
	GLfloat xDir, GLfloat yDir, GLfloat zDir,
	 GLfloat shadowWidth, GLfloat shadowHeight) :
	Light(ambientIntensityValue, diffuseIntensityValue, red, green, blue, shadowWidth, shadowHeight)
{
	m_Direction = glm::vec3(xDir, yDir, zDir);
	lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, -200.0f, 155.0f);
}

void DirectionalLight::UseLight(GLuint ambientIntensityLocation, GLuint ambientColorLocation, GLuint diffuseIntensityLocation, GLuint directionLocation)
{
	Light::useLight(ambientIntensityLocation, ambientColorLocation, diffuseIntensityLocation);
	glUniform3f(directionLocation, m_Direction.x, m_Direction.y, m_Direction.z);
}

glm::mat4 DirectionalLight::CalculateLightTransform()
{
	return lightProjection * glm::lookAt(-m_Direction, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));  // projection * view
}


DirectionalLight::~DirectionalLight()
{
}
