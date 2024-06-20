#pragma once
#include "Core.h"
#include <vector>
#include <string>
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm/gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "ConstantValues.h"
#include "Mesh.h"
#include "Shader.h"
#include "Renderer.h"
namespace GameEngine {
	class ENGINE_API Skybox
	{
	public:
		Skybox();

		Skybox(std::vector<std::string> faceLocations, const char* vertexLocation, const char* fragmentLocation);
		void DrawSkybox(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);

		~Skybox();

	private:
		Mesh* m_SkyMesh;
		Shader* m_SkyShader;
		Renderer* m_Renderer;
		GLuint m_TextureId;
		GLuint m_UniformProjection, m_UniformView;
	};
}