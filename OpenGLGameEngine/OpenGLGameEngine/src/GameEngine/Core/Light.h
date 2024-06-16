#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>
#include "ShadowMap.h"
#include <glm/gtc\matrix_transform.hpp>

class Light
{
public:
	Light();
	Light(GLfloat ambientIntensityValue, GLfloat diffuseIntensityValue, GLfloat red, GLfloat green, GLfloat blue,
		GLuint shadowWidth, GLuint shadowHeight);

	ShadowMap* GetShadowMap() { return shadowMap; }

	~Light();

protected:
	void useLight(GLuint ambientIntensityLocation, GLuint ambientColorLocation, GLuint diffuseIntensityLocation);
	glm::mat4 lightProjection;
	ShadowMap* shadowMap;

private:
	glm::vec3 m_Colour;
	GLfloat m_AmbientIntensity;
	GLfloat m_DiffuseIntensity;



};

