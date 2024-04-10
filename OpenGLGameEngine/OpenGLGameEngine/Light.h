#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>


class Light
{
public:
	Light();
	Light(GLfloat ambientIntensityValue, GLfloat red, GLfloat green, GLfloat blue, GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat diffuseIntensityValue);

	void UseLight(GLuint ambientIntensityLocation, GLuint ambientColorLocation, GLuint diffuseIntensityLocaiton, GLuint directionLocation);

	~Light();

private:
	glm::vec3 colour;
	GLfloat ambientIntensity;

	glm::vec3 direction;
	GLfloat diffuseIntensity;
};

