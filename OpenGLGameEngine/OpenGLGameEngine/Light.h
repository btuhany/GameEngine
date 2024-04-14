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
		  bool useShadowMap, GLfloat shadowWidth, GLfloat shadowHeight);

	ShadowMap* GetShadowMap() { return shadowMap; }

	~Light();

protected:
	void useLight(GLuint ambientIntensityLocation, GLuint ambientColorLocation, GLuint diffuseIntensityLocation);
	glm::mat4 lightProjection;

private:
	glm::vec3 colour;
	GLfloat ambientIntensity;
	GLfloat diffuseIntensity;


	ShadowMap* shadowMap;
};

