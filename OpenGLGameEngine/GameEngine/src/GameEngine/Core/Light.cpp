#include "Light.h"
namespace GameEngine {
	Light::Light()
	{
		m_Colour = glm::vec3(1.0f, 1.0f, 1.0f);
		m_AmbientIntensity = 1.0f;
	}

	Light::Light(GLfloat ambientIntensityValue, GLfloat diffuseIntensityValue, GLfloat red, GLfloat green, GLfloat blue,
		GLuint shadowWidth, GLuint shadowHeight)
	{
		shadowMap = new ShadowMap();
		shadowMap->Init(shadowWidth, shadowHeight);
		m_Colour = glm::vec3(red, green, blue);
		m_AmbientIntensity = ambientIntensityValue;
		m_DiffuseIntensity = diffuseIntensityValue;
	}

	Light::~Light()
	{
		delete shadowMap;
	}

	void Light::useLight(GLuint ambientIntensityLocation, GLuint ambientColorLocation, GLuint diffuseIntensityLocaiton)
	{
		glUniform3f(ambientColorLocation, m_Colour.x, m_Colour.y, m_Colour.z);
		glUniform1f(ambientIntensityLocation, m_AmbientIntensity);
		glUniform1f(diffuseIntensityLocaiton, m_DiffuseIntensity);
	}
}