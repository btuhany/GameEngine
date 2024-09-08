#pragma once
#include "Core.h"
#include <vector>
#include <string>
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm/gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "ConstantValues.h"
#include "MeshData.h"
#include "Shader.h"
#include "Components/MeshRendererComponent.h"
namespace GameEngine {
	class ENGINE_API Skybox
	{
	public:
		Skybox();

		Skybox(std::vector<std::string> faceLocations, const char* vertexLocation, const char* fragmentLocation);
		void DrawSkybox(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);

		~Skybox();

	private:
		std::shared_ptr<MeshData> m_SkyMeshData;
		Shader* m_SkyShader;
		GLuint m_TextureId;
		GLuint m_UniformProjection, m_UniformView;
	};
}
