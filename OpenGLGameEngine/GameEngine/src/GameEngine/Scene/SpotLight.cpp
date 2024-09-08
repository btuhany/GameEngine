#include "SpotLight.h"
namespace GameEngine {
	SpotLight::SpotLight() : PointLight()
	{
		m_Direction = glm::vec3(0.0f, -1.0f, 0.0f);
		m_Edge = 0.0f;
		m_ProcEdge = cosf(glm::radians(m_Edge));
	}

	SpotLight::SpotLight(GLfloat ambientIntensityValue, GLfloat diffuseIntensityValue,
		GLfloat red, GLfloat green, GLfloat blue,
		GLfloat xPos, GLfloat yPos, GLfloat zPos,
		GLfloat xDir, GLfloat yDir, GLfloat zDir,
		GLfloat constantVal, GLfloat linearVal, GLfloat expoValue,
		GLfloat edgeValue, GLfloat shadowWidth, GLfloat shadowHeight, GLfloat nearPlaneVal, GLfloat farPlaneVal) : PointLight(ambientIntensityValue, diffuseIntensityValue, red, green, blue, xPos, yPos, zPos, constantVal, linearVal, expoValue, shadowWidth, shadowHeight, nearPlaneVal, farPlaneVal)
	{
		m_Direction = glm::normalize(glm::vec3(xDir, yDir, zDir));
		m_Edge = edgeValue;
		m_ProcEdge = cosf(glm::radians(m_Edge));
	}

	SpotLight::SpotLight(GLfloat ambientIntensityValue, GLfloat diffuseIntensityValue, GLfloat red, GLfloat green, GLfloat blue, GLfloat xPos, GLfloat yPos, GLfloat zPos, GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat constantVal, GLfloat linearVal, GLfloat expoValue, GLfloat edgeValue, GLfloat nearPlaneVal, GLfloat farPlaneVal) : PointLight(ambientIntensityValue, diffuseIntensityValue, red, green, blue, xPos, yPos, zPos, constantVal, linearVal, expoValue, nearPlaneVal, farPlaneVal)
	{
		m_Direction = glm::normalize(glm::vec3(xDir, yDir, zDir));
		m_Edge = edgeValue;
		m_ProcEdge = cosf(glm::radians(m_Edge));
	}

	void SpotLight::UseLight(GLuint ambientIntensityLocation, GLuint ambientColorLocation, GLuint diffuseIntensityLocation, GLuint positionLocation, GLuint directionLocation, GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation, GLuint useOmniShadowLoc, GLuint edgeLocation)
	{
		PointLight::UseLight(ambientIntensityLocation, ambientColorLocation, diffuseIntensityLocation, positionLocation, constantLocation, linearLocation, exponentLocation, useOmniShadowLoc);
		glUniform3f(directionLocation, m_Direction.x, m_Direction.y, m_Direction.z);
		glUniform1f(edgeLocation, m_ProcEdge);
	}

	SpotLight::~SpotLight()
	{
	}
}