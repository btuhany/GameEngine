#include "Light.h"

Light::Light()
{
	colour = glm::vec3(1.0f, 1.0f, 1.0f);
	ambientIntensity = 1.0f;
}

Light::Light(GLfloat ambientIntensityValue, GLfloat diffuseIntensityValue, GLfloat red, GLfloat green, GLfloat blue,
	GLuint shadowWidth, GLuint shadowHeight)
{
	shadowMap = new ShadowMap();
	shadowMap->Init(shadowWidth, shadowHeight);
	colour = glm::vec3(red, green, blue);
	ambientIntensity = ambientIntensityValue;
	diffuseIntensity = diffuseIntensityValue;
}

Light::~Light()
{
}

void Light::useLight(GLuint ambientIntensityLocation, GLuint ambientColorLocation, GLuint diffuseIntensityLocaiton)
{
	glUniform3f(ambientColorLocation, colour.x, colour.y, colour.z);
	glUniform1f(ambientIntensityLocation, ambientIntensity);
	glUniform1f(diffuseIntensityLocaiton, diffuseIntensity);
}