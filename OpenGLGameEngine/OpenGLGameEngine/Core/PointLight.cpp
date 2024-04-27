#include "PointLight.h"

PointLight::PointLight()
{
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	constant = 1.0f;
	linear = 0.0f;
	exponent = 0.0f;
}

PointLight::PointLight(GLfloat ambientIntensityValue, GLfloat diffuseIntensityValue, GLfloat red, GLfloat green, GLfloat blue, GLfloat xPos, GLfloat yPos, GLfloat zPos, GLfloat constantVal, GLfloat linearVal, GLfloat expoValue, GLuint shadowWidth, GLuint shadowHeight, GLfloat nearPlaneVal, GLfloat farPlaneVal) : Light(ambientIntensityValue, diffuseIntensityValue, red, green, blue, shadowWidth, shadowHeight)
{
	position = glm::vec3(xPos, yPos, zPos);
	constant = constantVal;
	linear = linearVal;
	exponent = expoValue;

	farPlane = farPlaneVal;
	
	float aspect = (float)shadowWidth / (float)shadowHeight;
	lightProjection = glm::perspective(glm::radians(90.0f), aspect, nearPlaneVal, farPlaneVal);

	shadowMap = new OmniShadowMap();
	shadowMap->Init(shadowWidth, shadowHeight);
}

void PointLight::UseLight(GLuint ambientIntensityLocation, GLuint ambientColorLocation, GLuint diffuseIntensityLocation, GLuint positionLocation, GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation)
{
	Light::useLight(ambientIntensityLocation, ambientColorLocation, diffuseIntensityLocation);
	glUniform3f(positionLocation, position.x, position.y, position.z);
	glUniform1f(constantLocation, constant);
	glUniform1f(linearLocation, linear);
	glUniform1f(exponentLocation, exponent);
}

std::vector<glm::mat4> PointLight::CalculateLightTransform()
{
	std::vector<glm::mat4> lightMatrices;
	//+x, -x
	lightMatrices.push_back(lightProjection * glm::lookAt(position, position + glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
	lightMatrices.push_back(lightProjection * glm::lookAt(position, position + glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
	//+y, -y
	lightMatrices.push_back(lightProjection * glm::lookAt(position, position + glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0)));
	lightMatrices.push_back(lightProjection * glm::lookAt(position, position + glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.0, 0.0, -1.0)));
	//+z, -z
	lightMatrices.push_back(lightProjection * glm::lookAt(position, position + glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, -1.0, 0.0)));
	lightMatrices.push_back(lightProjection * glm::lookAt(position, position + glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, -1.0, 0.0)));

	return lightMatrices;
}

GLfloat PointLight::GetFarPlane()
{
	return farPlane;
}

glm::vec3 PointLight::GetPosition()
{
	return position;
}

PointLight::~PointLight()
{
}
