#include "PointLight.h"

PointLight::PointLight()
{
	m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
	m_Constant = 1.0f;
	m_Linear = 0.0f;
	m_Exponent = 0.0f;
}

PointLight::PointLight(GLfloat ambientIntensityValue, GLfloat diffuseIntensityValue, GLfloat red, GLfloat green, GLfloat blue, GLfloat xPos, GLfloat yPos, GLfloat zPos, GLfloat constantVal, GLfloat linearVal, GLfloat expoValue, GLuint shadowWidth, GLuint shadowHeight, GLfloat nearPlaneVal, GLfloat farPlaneVal) : Light(ambientIntensityValue, diffuseIntensityValue, red, green, blue, shadowWidth, shadowHeight)
{
	m_Position = glm::vec3(xPos, yPos, zPos);
	m_Constant = constantVal;
	m_Linear = linearVal;
	m_Exponent = expoValue;

	m_FarPlane = farPlaneVal;
	
	float aspect = (float)shadowWidth / (float)shadowHeight;
	lightProjection = glm::perspective(glm::radians(90.0f), aspect, nearPlaneVal, farPlaneVal);

	shadowMap = new OmniShadowMap();
	shadowMap->Init(shadowWidth, shadowHeight);
}

void PointLight::UseLight(GLuint ambientIntensityLocation, GLuint ambientColorLocation, GLuint diffuseIntensityLocation, GLuint positionLocation, GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation)
{
	Light::useLight(ambientIntensityLocation, ambientColorLocation, diffuseIntensityLocation);
	glUniform3f(positionLocation, m_Position.x, m_Position.y, m_Position.z);
	glUniform1f(constantLocation, m_Constant);
	glUniform1f(linearLocation, m_Linear);
	glUniform1f(exponentLocation, m_Exponent);
}

std::vector<glm::mat4> PointLight::CalculateLightTransform()
{
	std::vector<glm::mat4> lightMatrices;
	//+x, -x
	lightMatrices.push_back(lightProjection * glm::lookAt(m_Position, m_Position + glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
	lightMatrices.push_back(lightProjection * glm::lookAt(m_Position, m_Position + glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
	//+y, -y
	lightMatrices.push_back(lightProjection * glm::lookAt(m_Position, m_Position + glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0)));
	lightMatrices.push_back(lightProjection * glm::lookAt(m_Position, m_Position + glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.0, 0.0, -1.0)));
	//+z, -z
	lightMatrices.push_back(lightProjection * glm::lookAt(m_Position, m_Position + glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, -1.0, 0.0)));
	lightMatrices.push_back(lightProjection * glm::lookAt(m_Position, m_Position + glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, -1.0, 0.0)));

	return lightMatrices;
}

GLfloat PointLight::GetFarPlane()
{
	return m_FarPlane;
}

glm::vec3 PointLight::GetPosition()
{
	return m_Position;
}

PointLight::~PointLight()
{
}