#include "Material.h"
namespace GameEngine {
	Material::Material()
	{
		m_SpecularIntensity = 0.0f;
		m_Shininess = 0.0f;
	}

	Material::Material(GLfloat specularIntensityValue, GLfloat shininessValue)
	{
		m_SpecularIntensity = specularIntensityValue;
		m_Shininess = shininessValue;
	}

	void Material::UseMaterial(GLuint specularIntensityLocation, GLuint shininessLocation)
	{
		glUniform1f(specularIntensityLocation, m_SpecularIntensity);
		glUniform1f(shininessLocation, m_Shininess);
	}

	Material::~Material()
	{
	}
}