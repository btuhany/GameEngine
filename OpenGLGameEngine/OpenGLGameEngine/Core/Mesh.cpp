#include "Mesh.h"

Mesh::Mesh()
{
	VAO = 0;
	VBO = 0;
	IBO = 0;
	indexCount = 0;
}


//Creating the VAO, one array, where to store the id. 
//Graphics card memory one vertex array and id
//Bind the VAO and Any opengl functions there will be taking place in this vao
//Inside the VAO, we are creating the VBO and it gives the id and we take it with the VBO
//We want to bind the id of the vbo
//Buffering the data
//vertices to buffer data, pick the actual target to bind, 
//in this case you can use the sizeof, 
//location (layout = 0 in shader), size of each value going to past in (in vertices)
//each vertex position has three float value, so the size is 3. type is float.
//we could use "3*sizeof(float)" instead of 0 stride value and "(void*)0" instead of void pointer idk why.
//enable location
//unbinding
//we should unbind the ibo buffer after unbinding the vao

//indices ptr value holds an array.
void Mesh::CreateMesh(GLfloat* vertices, unsigned int* indices, unsigned int numOfVertices, unsigned int numOfIndices)
{
	indexCount = numOfIndices;

	
	glGenVertexArrays(1, &VAO);
	
	glBindVertexArray(VAO);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * numOfIndices, indices, GL_STATIC_DRAW);

	
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numOfVertices, vertices, GL_STATIC_DRAW);

	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, (void*)(sizeof(vertices[0]) * 3));  //texture coordinates 
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, (void*)(sizeof(vertices[0]) * 5));  //texture coordinates 
	glEnableVertexAttribArray(2);

	
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


void Mesh::RenderMesh()
{
	//if (indexcount == 0) do not render
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::ClearMesh()
{
	if (IBO != 0)
	{
		//removing from the graphics card memory
		glDeleteBuffers(1, &IBO);
		IBO = 0;
	}
	if (VBO != 0)
	{
		//removing from the graphics card memory
		glDeleteBuffers(1, &VBO);
		VBO = 0;
	}
	if (VAO != 0)
	{
		//removing from the graphics card memory
		glDeleteVertexArrays(1, &VAO);
		VAO = 0;
	}

	indexCount = 0;
}

Mesh::~Mesh()
{
	ClearMesh();
}