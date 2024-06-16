#pragma once
#include <GL\glew.h>
#include "IRenderable.h"
namespace GameEngine {
	class Mesh : public IRenderable
	{
	public:
		Mesh();
		void CreateMesh(GLfloat* vertices, unsigned int* indices, unsigned int numOfVertices, unsigned int numOfIndices);
		void ClearMesh();
		~Mesh();
		GLuint GetVAO();
		GLuint GetVBO();
		GLuint GetIBO();
		GLuint GetIndexCount();
		void Render() override;
	private:
		GLuint m_VAO, m_VBO, m_IBO;
		GLsizei m_IndexCount;
	};
}