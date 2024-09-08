#pragma once
#include "../Core.h"
#include <GL/glew.h>
namespace GameEngine {
	class ENGINE_API Material
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
}