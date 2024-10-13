#pragma once
#include "../Core.h"
#include <GL\glew.h>
#include <glm\glm.hpp>
#include "ShadowMap.h"
#include <glm/gtc\matrix_transform.hpp>
namespace GameEngine {
	class ENGINE_API Light
	{
	public:
		Light();
		Light(GLfloat ambientIntensityValue, GLfloat diffuseIntensityValue, GLfloat red, GLfloat green, GLfloat blue,
			GLuint shadowWidth, GLuint shadowHeight);
		//shadow map constructor shouldn't be used if shadow is not desired and shadow shaders won't be used
		Light(GLfloat ambientIntensityValue, GLfloat diffuseIntensityValue, GLfloat red, GLfloat green, GLfloat blue);

		ShadowMap* getShadowMap();

		~Light();

	protected:
		void useLight(GLuint ambientIntensityLocation, GLuint ambientColorLocation, GLuint diffuseIntensityLocation);
		glm::mat4 m_LightProjection;
		ShadowMap* m_ShadowMap;

	private:
		glm::vec3 m_Colour;
		GLfloat m_AmbientIntensity;
		GLfloat m_DiffuseIntensity;



	};
}
