#pragma once
#include <GL\glew.h>
#include <glm/glm.hpp>
#include "../Core.h"
namespace GameEngine
{
	class ENGINE_API TextData
	{
	public:
		TextData();
		~TextData();
		void CreateMesh();
		void ClearMesh();
		GLuint GetVAO();
		GLuint GetVBO();
	private:
		GLuint m_VAO, m_VBO, m_IBO;
		GLsizei m_IndexCount;
	};
}

