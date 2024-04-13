#define STB_IMAGE_IMPLEMENTATION
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm\glm.hpp>
#include <glm/gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "Mesh.h"
#include "Shader.h"
#include "Window.h"
#include "Camera.h"
#include "Texture.h"
#include "DirectionalLight.h"
#include "Material.h"
#include "ConstantValues.h"
#include "PointLight.h"

const float toRadians = 3.14159265f / 180.0f;

std::vector<Mesh*> meshList;
std::vector<Shader*> shaderList;
Camera mainCamera;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

Texture spidermanTexture;
Texture learnopenglTexture;

Material shinyMaterial;
Material roughMaterial;

DirectionalLight directionalLight;
PointLight pointLights[MAX_POINT_LIGHTS];

// Vertex shader
static const char* vShaderLocation = "Shaders/shader.vert";

// Fragment shader
static const char* fShaderLocation = "Shaders/shader.frag";


void CalculateAvarageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* verticesDataArr, unsigned int verticesDataArrCount, unsigned int vertexDataLength, unsigned int normalOffset)
{
	//Scan triangles
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		//x data of the vertex pos of the vertices array.
		unsigned int in0 = indices[i] * vertexDataLength; 
		unsigned int in1 = indices[i + 1] * vertexDataLength; 
		unsigned int in2 = indices[i + 2] * vertexDataLength;

		//vector1: v1 - v0
		glm::vec3 vector1(verticesDataArr[in1] - verticesDataArr[in0], verticesDataArr[in1 + 1] - verticesDataArr[in0 + 1], verticesDataArr[in1 + 2] - verticesDataArr[in0 + 2]);
		//vector1: v2 - v0
		glm::vec3 vector2(verticesDataArr[in2] - verticesDataArr[in0], verticesDataArr[in2 + 1] - verticesDataArr[in0 + 1], verticesDataArr[in2 + 2] - verticesDataArr[in0 + 2]);
		glm::vec3 normal = glm::cross(vector1, vector2);
		normal = glm::normalize(normal);

		//normal.x data indices at vertices array
		in0 += normalOffset;
		in1 += normalOffset;
		in2 += normalOffset;

		//ADDING normal values, we should normalize it after. Thus, we can calculate the AVARAGE.
		verticesDataArr[in0] += normal.x;
		verticesDataArr[in0 + 1] += normal.y;
		verticesDataArr[in0 + 2] += normal.z;

		verticesDataArr[in1] += normal.x;
		verticesDataArr[in1 + 1] += normal.y;
		verticesDataArr[in1 + 2] += normal.z;

		verticesDataArr[in2] += normal.x;
		verticesDataArr[in2 + 1] += normal.y;
		verticesDataArr[in2 + 2] += normal.z;
	}

	//Normalizing normal vectors
	for (size_t i = 0; i < verticesDataArrCount / vertexDataLength; i++)
	{
		unsigned int normalIndice = i * vertexDataLength + normalOffset;
		glm::vec3 normalVector(verticesDataArr[normalIndice], verticesDataArr[normalIndice + 1], verticesDataArr[normalIndice + 2]);

		//OpenGL normalize function does not work properly with zero vector
		if (normalVector.x != 0 || normalVector.y != 0 || normalVector.z != 0)
		{
			normalVector = glm::normalize(normalVector);
		}

		verticesDataArr[normalIndice] = normalVector.x;
		verticesDataArr[normalIndice + 1] = normalVector.y;
		verticesDataArr[normalIndice + 2] = normalVector.z;
	}
}

void CreateObject()
{
	unsigned int indices[] = {
		0, 2, 1,
		0, 3, 2,
		2, 4, 5,
		2, 3, 4,
		3, 7, 4,
		3, 0, 7,
		0, 1, 6,
		0, 6, 7,
		6, 1, 2,
		6, 2, 5,
		5, 4, 6,
		6, 4, 7
	};

	GLfloat vertices[] =
	{
 		//x      y     z		 u     y			normals
		-1.0f, -1.0f, 1.0f, 	1.0f, 0.0f,		-1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,		0.0f, 0.0f,		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,		0.0f, 1.0f,		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, 1.0f,	1.0f, 1.0f,		1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,		1.0f, 0.0f,		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, -1.0f,		0.0f, 0.0f,		1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,		1.0f, 0.0f,		-1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f,		0.0f, 0.0f,		-1.0f, 1.0f, 1.0f
	};


	CalculateAvarageNormals(indices, 36, vertices, 64, 8, 5);

	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 64, 36);
	meshList.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 64, 36);
	meshList.push_back(obj2);
}
void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShaderLocation, fShaderLocation);
	shaderList.push_back(shader1);
}

bool direction = true;
float triOffset = 0.0f;
float triMaxoffset = 3.0f;
float triIncrement = 1.0f;
float curAngle = 0.0f;
float sizeDirection = true;
float curSize = 0.5f;
float maxSize = 1.0f;
float minSize = 0.1f;

void HandleTransformActions()
{
	//printf("Mouse Pos X: %.6f\n", mainWindow.GetMouseDeltaX());

	if (direction)
	{
		triOffset += triIncrement * deltaTime;
	}
	else
	{
		triOffset -= triIncrement * deltaTime;
	}

	if (abs(triOffset) >= triMaxoffset)
	{
		direction = !direction;
	}

	curAngle += 15.0f * deltaTime;;
	//if (curAngle > 360)
	{
		//curAngle = 0.0f;
	}

	if (direction)
	{
		curSize += 0.001f * deltaTime;;
	}
	else
	{
		curSize -= 0.001f * deltaTime;;
	}

	if (curSize > maxSize || curSize < minSize)
	{
		sizeDirection = !sizeDirection;
	}

}

int main()
{
	Window mainWindow = Window(1366, 768);
	mainWindow.Initialize();

	CreateObject();
	CreateShaders();
	mainCamera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f, 0.0f, 5.0f, 0.1f);

	spidermanTexture = Texture("Textures/spiderman.png");
	spidermanTexture.LoadTexture();
	learnopenglTexture = Texture("Textures/learnopengl.png");
	learnopenglTexture.LoadTexture();

	shinyMaterial = Material(15.0f, 59.5f);
	roughMaterial = Material(0.5f, 4.0f);

	directionalLight = DirectionalLight(0.01f, 0.005f, 1.0f, 1.0f, 1.0f,
							0.0f, -10.0f, 5.0f);
	unsigned int pointLightCount = 0;
	pointLights[0] = PointLight(0.0f, 15.5f,
		1.0f, 0.0f, 1.0f,
		0.0f, 3.2f, 5.0f,
		0.0f, 0.0f, 0.5f);
	pointLightCount++;
	pointLights[1] = PointLight(0.0f, 15.5f,
		1.0f, 1.0f, 1.5f,
		0.0f, 2.2f, 0.0f,
		5.1f, 5.1f, 1.1f);
	pointLightCount++;


	GLuint uniformModel = 0;
	GLuint uniformProjection = 0;
	GLuint uniformView = 0;
	
	GLuint uniformMatSpecularInstensity = 0;
	GLuint uniformMatShininess = 0;
	GLuint uniformCameraPosition = 0;

	//unifrom value setted once
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.GetBufferWidth() / mainWindow.GetBufferHeight(), 0.1f, 100.0f);



	//Loop until window closed
	while (!mainWindow.GetShouldClose())
	{
		GLfloat timeNow = glfwGetTime(); //SDL_GetPerformanceCounter();
		deltaTime = timeNow - lastTime; // (timeNow - lastTime)*1000 / SDL_GetPerformanceFrequency();
		lastTime = timeNow;

		//Get and handle user inpu events
		glfwPollEvents();

		mainCamera.HandleKeys(mainWindow.GetKeys(), deltaTime);
		mainCamera.HandleMouse(mainWindow.GetMouseDeltaX(), mainWindow.GetMouseDeltaY());

		HandleTransformActions();

		//Clear window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		

		shaderList[0]->UseShader();
		uniformModel = shaderList[0]->GetModelLocation();
		uniformProjection = shaderList[0]->GetProjectionLocation();
		uniformView = shaderList[0]->GetViewLocation();

		uniformMatSpecularInstensity = shaderList[0]->GetMatSpecularIntensityLocation();
		uniformMatShininess = shaderList[0]->GetMatShininessLocation();
		uniformCameraPosition = shaderList[0]->GetCameraPositionLocation();
		
		shaderList[0]->SetDirectionalLight(&directionalLight);
		shaderList[0]->SetPointLights(pointLights, pointLightCount);

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(mainCamera.CalculateViewMatrix()));
		glUniform3f(uniformCameraPosition, mainCamera.GetCameraPosition().x, mainCamera.GetCameraPosition().y, mainCamera.GetCameraPosition().z);


		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 5.0f));
		//model = glm::scale(model, glm::vec3(0.4f, 0.7f, 0.7f));
		model = glm::rotate(model, 2 * curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));

		//setting model matrix inside the shader
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//setting projection matrix 

		learnopenglTexture.UseTexture();
		shinyMaterial.UseMaterial(uniformMatSpecularInstensity, uniformMatShininess);
		meshList[0]->RenderMesh();

		model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-triOffset, 0.0f, -10.0f));
		//model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		//model = glm::rotate(model, 0.6f * curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		spidermanTexture.UseTexture();
		meshList[1]->RenderMesh();

		glUseProgram(0);

		mainWindow.SwapBuffers();
	}

	printf("Window closed!");

	///* Clear */
	//glfwDestroyWindow(mainWindow);
	//glfwTerminate();

	return 0;
}
