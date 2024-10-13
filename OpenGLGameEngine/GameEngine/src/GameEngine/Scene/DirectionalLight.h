#pragma once
#include "../Core.h"
#include "../Scene/Light.h"
namespace GameEngine {
	class ENGINE_API DirectionalLight : public Light
	{
	public:
		DirectionalLight();
		DirectionalLight(GLfloat ambientIntensityValue, GLfloat diffuseIntensityValue, GLfloat red, GLfloat green, GLfloat blue, GLfloat xDir, GLfloat yDir, GLfloat zDir,
			GLfloat shadowWidth, GLfloat shadowHeight);
		DirectionalLight(GLfloat ambientIntensityValue, GLfloat diffuseIntensityValue, GLfloat red, GLfloat green, GLfloat blue, GLfloat xDir, GLfloat yDir, GLfloat zDir);
		void UseLight(GLuint ambientIntensityLocation, GLuint ambientColorLocation, GLuint diffuseIntensityLocation, GLuint directionLocation);

		glm::mat4 CalculateLightTransform();

		~DirectionalLight();
	private:
		glm::vec3 m_Direction;
	};
}
