#include "TextData.h"

namespace GameEngine
{
	TextData::TextData()
	{
		m_VAO = 0;
		m_VBO = 0;
	}
	TextData::~TextData()
	{
		ClearMesh();
	}
	void TextData::CreateMesh(GLfloat* vertices, unsigned int* indices, unsigned int numOfVertices, unsigned int numOfIndices)
	{
		unsigned int VAO, VBO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, 0, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	void TextData::ClearMesh()
	{
		if (m_VBO != 0)
		{
			//removing from the graphics card memory
			glDeleteBuffers(1, &m_VBO);
			m_VBO = 0;
		}
		if (m_VAO != 0)
		{
			//removing from the graphics card memory
			glDeleteVertexArrays(1, &m_VAO);
			m_VAO = 0;
		}
	}
	GLuint TextData::GetVAO()
	{
		return m_VAO;
	}
	GLuint TextData::GetVBO()
	{
		return m_VBO;
	}
}
