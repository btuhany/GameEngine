#pragma once
#include <GL\glew.h>
#include "Core.h"

namespace GameEngine {
	class ENGINE_API MeshData
	{
	public:
		MeshData();
		~MeshData();
		void CreateMesh(GLfloat* vertices, unsigned int* indices, unsigned int numOfVertices, unsigned int numOfIndices);
		void ClearMesh();
		GLuint GetVAO();
		GLuint GetVBO();
		GLuint GetIBO();
		GLuint GetIndexCount();
	private:
		GLuint m_VAO, m_VBO, m_IBO;
		GLsizei m_IndexCount;
	};
}