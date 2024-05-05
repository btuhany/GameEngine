#pragma once
#include <GL/glew.h>
class Material
{
public:
	Material();
	Material(GLfloat specularIntensityValue, GLfloat shininessValue);
	~Material();

	void UseMaterial(GLuint specularIntensityLocation, GLuint shininessLocation);
private:
	GLfloat m_SpecularIntensity;
	GLfloat m_Shininess;
};
