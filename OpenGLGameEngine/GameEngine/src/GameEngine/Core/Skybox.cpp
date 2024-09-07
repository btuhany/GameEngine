#include "Skybox.h"
namespace GameEngine {
	Skybox::Skybox()
	{
	}

	Skybox::Skybox(std::vector<std::string> faceLocations, const char* vertexLocation, const char* fragmentLocation)
	{
		//Shader setup
		m_SkyShader = new Shader();
		m_SkyShader->CreateFromFiles(vertexLocation, fragmentLocation);
		m_UniformProjection = m_SkyShader->GetProjectionLocation();
		m_UniformView = m_SkyShader->GetViewLocation();
		printf("Demo scene initialized3!");
		//Texture setup
		glGenTextures(1, &m_TextureId);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_TextureId);

		int width, height, bitDepth;

		for (size_t i = 0; i < 6; i++)
		{
			unsigned char* texData = stbi_load(faceLocations[i].c_str(), &width, &height, &bitDepth, 0);

			if (!texData)
			{
				printf("Failed to load image at: %d\n", faceLocations[i].c_str());
				return;
			}

			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
			stbi_image_free(texData);
		}
		printf("\n Demo scene initialized4!");
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//Mesh setup
		unsigned int skyboxIndices[] = {
			// front
			0, 1, 2,
			2, 1, 3,
			// right
			2, 3, 5,
			5, 3, 7,
			// back
			5, 7, 4,
			4, 7, 6,
			// left
			4, 6, 0,
			0, 6, 1,
			// top
			4, 0, 5,
			5, 0, 2,
			// bottom
			1, 6, 3,
			3, 6, 7
		};

		//we dont use the uv's, instead we use the directions from camera
		float skyboxVertices[] = {
			-1.0f, 1.0f, -1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			-1.0f, -1.0f, -1.0f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, 1.0f, -1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,

			-1.0f, 1.0f, 1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, 1.0f, 1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			-1.0f, -1.0f, 1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, 1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f
		};

		m_SkyMeshData = std::make_shared<MeshData>();
		m_SkyMeshData->CreateMesh(skyboxVertices, skyboxIndices, 64, 36);
		printf("\n Demo scene initialized5!");
		printf("\n Demo scene initialized6!");
	}

	void Skybox::DrawSkybox(glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
	{
		viewMatrix = glm::mat4(glm::mat3(viewMatrix)); //cut the translation values from 4x4 matrix.

		glDepthMask(GL_FALSE);

		m_SkyShader->UseShader();
		glUniformMatrix4fv(m_UniformProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
		glUniformMatrix4fv(m_UniformView, 1, GL_FALSE, glm::value_ptr(viewMatrix));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_TextureId);

		m_SkyShader->Validate();

		glBindVertexArray(m_SkyMeshData->GetVAO());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_SkyMeshData->GetIBO());
		glDrawElements(GL_TRIANGLES, m_SkyMeshData->GetIndexCount(), GL_UNSIGNED_INT, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		glDepthMask(GL_TRUE);
	}

	Skybox::~Skybox()
	{
	}
}