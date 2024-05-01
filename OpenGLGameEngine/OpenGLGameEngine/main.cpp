//#define STB_IMAGE_IMPLEMENTATION
//#include <stdio.h>
//#include <string.h>
//#include <cmath>
//#include <vector>
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//#include <glm\glm.hpp>
//#include <glm/gtc\matrix_transform.hpp>
//#include <glm\gtc\type_ptr.hpp>
//#include "Core/Mesh.h"
//#include "Core/Shader.h"
//#include "Core/Window.h"
//#include "Core/Camera.h"
//#include "Core/Texture.h"
//#include "Core/DirectionalLight.h"
//#include "Core/Material.h"
//#include "Core/ConstantValues.h"
//#include "Core/PointLight.h"
//#include "Core/SpotLight.h"
//#include "Core/Model.h"
//#include "Core/Skybox.h"
//
//const float toRadians = 3.14159265f / 180.0f;
//
//std::vector<Mesh*> meshList;
//std::vector<Shader*> shaderList;
//Shader directionalShadowShader;
//Shader omniShadowShader;
//
//GLuint uniformModel = 0;
//GLuint uniformProjection = 0;
//GLuint uniformView = 0;
//
//GLuint uniformMatSpecularInstensity = 0;
//GLuint uniformMatShininess = 0;
//GLuint uniformCameraPosition = 0;
//
//GLuint uniformOmniLightPos = 0, uniformFarPlane = 0;
//
//Camera mainCamera;
//
//GLfloat deltaTime = 0.0f;
//GLfloat lastTime = 0.0f;
//
//Texture spidermanTexture;
//Texture learnopenglTexture;
//Texture plainTexture;
//
//Material shinyMaterial;
//Material roughMaterial;
//
//Model ironMan;
//Model helicopter;
//
//DirectionalLight directionalLight;
//PointLight pointLights[MAX_POINT_LIGHTS];
//SpotLight spotLights[MAX_SPOT_LIGHTS];
//
//Skybox skybox;
//
//// Vertex shader
//static const char* vShaderLocation = "Shaders/shader.vert";
//
//// Fragment shader
//static const char* fShaderLocation = "Shaders/shader.frag";
//
//bool direction = true;
//float triOffset = -15.0f;
//float triMaxoffset = 15.0f;
//float triIncrement = 8.0f;
//float curAngle = 0.0f;
//float sizeDirection = true;
//float curSize = 0.5f;
//float maxSize = 1.0f;
//float minSize = 0.1f;
//
//unsigned int pointLightCount = 0;
//unsigned int spotLightCount = 0;
//glm::mat4 lightTransform;
//
//void CalculateAvarageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* verticesDataArr, unsigned int verticesDataArrCount, unsigned int vertexDataLength, unsigned int normalOffset)
//{
//	//Scan triangles
//	for (size_t i = 0; i < indiceCount; i += 3)
//	{
//		//x data of the vertex pos of the vertices array.
//		unsigned int in0 = indices[i] * vertexDataLength; 
//		unsigned int in1 = indices[i + 1] * vertexDataLength; 
//		unsigned int in2 = indices[i + 2] * vertexDataLength;
//
//		//vector1: v1 - v0
//		glm::vec3 vector1(verticesDataArr[in1] - verticesDataArr[in0], verticesDataArr[in1 + 1] - verticesDataArr[in0 + 1], verticesDataArr[in1 + 2] - verticesDataArr[in0 + 2]);
//		//vector1: v2 - v0
//		glm::vec3 vector2(verticesDataArr[in2] - verticesDataArr[in0], verticesDataArr[in2 + 1] - verticesDataArr[in0 + 1], verticesDataArr[in2 + 2] - verticesDataArr[in0 + 2]);
//		glm::vec3 normal = glm::cross(vector1, vector2);
//
//		normal = glm::normalize(normal);
//
//		//normal.x data indices at vertices array
//		in0 += normalOffset;
//		in1 += normalOffset;
//		in2 += normalOffset;
//
//		//ADDING normal values, we should normalize it after. Thus, we can calculate the AVARAGE.
//		verticesDataArr[in0] += normal.x;
//		verticesDataArr[in0 + 1] += normal.y;
//		verticesDataArr[in0 + 2] += normal.z;
//
//		verticesDataArr[in1] += normal.x;
//		verticesDataArr[in1 + 1] += normal.y;
//		verticesDataArr[in1 + 2] += normal.z;
//
//		verticesDataArr[in2] += normal.x;
//		verticesDataArr[in2 + 1] += normal.y;
//		verticesDataArr[in2 + 2] += normal.z;
//	}
//
//	//Normalizing normal vectors
//	for (size_t i = 0; i < verticesDataArrCount / vertexDataLength; i++)
//	{
//		unsigned int normalIndice = i * vertexDataLength + normalOffset;
//		glm::vec3 normalVector(verticesDataArr[normalIndice], verticesDataArr[normalIndice + 1], verticesDataArr[normalIndice + 2]);
//
//		//OpenGL normalize function does not work properly with zero vector
//		if (normalVector.x != 0 || normalVector.y != 0 || normalVector.z != 0)
//		{
//			normalVector = glm::normalize(normalVector);
//		}
//
//
//
//		verticesDataArr[normalIndice] = normalVector.x;
//		verticesDataArr[normalIndice + 1] = normalVector.y;
//		verticesDataArr[normalIndice + 2] = normalVector.z;
//	}
//}
//
//void CreateObject()
//{
//	unsigned int indices[] = {
//		2, 0, 1,
//		3, 0, 2,
//		4, 2, 5,
//		3, 2, 4,
//		7, 3, 4,
//		0, 3, 7,
//		1, 0, 6,
//		6, 0, 7,
//		1, 6, 2,
//		2, 6, 5,
//		4, 5, 6,
//		4, 6, 7
//	};
//
//	GLfloat vertices[] =
//	{
// 		//x      y     z		 u     y			normals
//		-1.0f, -1.0f, 1.0f, 	1.0f, 0.0f,		-1.0f, -1.0f, 1.0f,
//		-1.0f, -1.0f, -1.0f,		0.0f, 0.0f,		-1.0f, -1.0f, -1.0f,
//		1.0f, -1.0f, -1.0f,		0.0f, 1.0f,		1.0f, -1.0f, -1.0f,
//		1.0f, -1.0f, 1.0f,	1.0f, 1.0f,		1.0f, -1.0f, 1.0f,
//		1.0f, 1.0f, 1.0f,		1.0f, 0.0f,		1.0f, 1.0f, 1.0f,
//		1.0f, 1.0f, -1.0f,		0.0f, 0.0f,		1.0f, 1.0f, -1.0f,
//		-1.0f, 1.0f, -1.0f,		1.0f, 0.0f,		-1.0f, 1.0f, -1.0f,
//		-1.0f, 1.0f, 1.0f,		0.0f, 0.0f,		-1.0f, 1.0f, 1.0f
//	};
//
//	unsigned int floorIndices[] = {
//		0, 2, 1,
//		1, 2, 3
//	};
//
//	GLfloat floorVertices[] = {
//		-50.0f, -10.0f, -50.0f,	0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
//		50.0f, -10.0f, -50.0f,	20.0f, 0.0f,  0.0f, 1.0f, 0.0f,
//		-50.0f, -10.0f, 50.0f,	0.0f, 20.0f,  0.0f, 1.0f, 0.0f,
//		50.0f, -10.0f, 50.0f,	20.0f, 20.0f,  0.0f, 1.0f, 0.0f
//	};
//
//	CalculateAvarageNormals(indices, 36, vertices, 64, 8, 5);
//
//	Mesh* obj1 = new Mesh();
//	obj1->CreateMesh(vertices, indices, 64, 36);
//	meshList.push_back(obj1);
//
//	Mesh* obj2 = new Mesh();
//	obj2->CreateMesh(vertices, indices, 64, 36);
//	meshList.push_back(obj2);
//
//	Mesh* obj3 = new Mesh();
//	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
//	meshList.push_back(obj3);
//
//	Mesh* obj4 = new Mesh();
//	obj4->CreateMesh(floorVertices, floorIndices, 32, 6);
//	meshList.push_back(obj4);
//}
//
//void CreateShaders()
//{
//	Shader* shader1 = new Shader();
//	shader1->CreateFromFiles(vShaderLocation, fShaderLocation);
//	shaderList.push_back(shader1);
//
//	//directionalShadowShader = Shader();
//	directionalShadowShader.CreateFromFiles("Shaders/directional_shadow_map.vert", "Shaders/directional_shadow_map.frag");
//	omniShadowShader.CreateFromFiles("Shaders/omni_shadow_map.vert", "Shaders/omni_shadow_map.geom", "Shaders/omni_shadow_map.frag");
//}
//
//void HandleTransformActions()
//{
//	//printf("Mouse Pos X: %.6f\n", mainWindow.GetMouseDeltaX());
//
//	if (direction)
//	{
//		triOffset += triIncrement * deltaTime;
//	}
//	else
//	{
//		triOffset -= triIncrement * deltaTime;
//	}
//
//	if (abs(triOffset) >= triMaxoffset)
//	{
//		direction = !direction;
//	}
//
//	curAngle += 35.0f * deltaTime;;
//	//if (curAngle > 360)
//	{
//		//curAngle = 0.0f;
//	}
//
//	if (direction)
//	{
//		curSize += 0.001f * deltaTime;;
//	}
//	else
//	{
//		curSize -= 0.001f * deltaTime;;
//	}
//
//	if (curSize > maxSize || curSize < minSize)
//	{
//		sizeDirection = !sizeDirection;
//	}
//
//}
//
//void RenderScene()
//{
//	glm::mat4 model(1.0f);
//	model = glm::translate(model, glm::vec3(5.0f, 0.0f, 0.0f));
//	//model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
//	model = glm::rotate(model, 2 * curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
//
//	//setting model matrix inside the shader
//	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
//	//setting projection matrix 
//
//	learnopenglTexture.UseTexture();
//	shinyMaterial.UseMaterial(uniformMatSpecularInstensity, uniformMatShininess);
//	meshList[0]->RenderMesh();
//
//	model = glm::mat4(1.0f);
//	//model = glm::translate(model, glm::vec3(-triOffset, 0.0f, -10.0f));
//	//model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
//	//model = glm::rotate(model, 0.6f * curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
//	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
//	spidermanTexture.UseTexture();
//	meshList[1]->RenderMesh();
//
//
//	model = glm::mat4(1.0f);
//	//model = glm::translate(model, glm::vec3(-triOffset, 0.0f, -10.0f));
//	//model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
//	//model = glm::rotate(model, 0.6f * curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
//	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
//	plainTexture.UseTexture();
//	roughMaterial.UseMaterial(uniformMatSpecularInstensity, uniformMatShininess);
//	meshList[2]->RenderMesh();
//
//	model = glm::mat4(1.0f);
//	model = glm::translate(model, glm::vec3(-0.0, 0.3f, 0.0f));
//	model = glm::scale(model, glm::vec3(1.0f, 0.5f, 1.0f));
//	//model = glm::rotate(model, 0.6f * curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
//	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
//	spidermanTexture.UseTexture();
//	roughMaterial.UseMaterial(uniformMatSpecularInstensity, uniformMatShininess);
//	meshList[3]->RenderMesh();
//
//
//	model = glm::mat4(1.0f);
//	model = glm::translate(model, glm::vec3(20.0f, 0.0f, 0.0f));
//	model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
//	model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
//	model = glm::rotate(model, -curAngle * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
//	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
//	shinyMaterial.UseMaterial(uniformMatSpecularInstensity, uniformMatShininess);
//	helicopter.RenderModel();
//
//	model = glm::mat4(1.0f);
//	model = glm::translate(model, glm::vec3(20.0f, triOffset, -20.0f));
//	model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
//	//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
//	model = glm::rotate(model, 290 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
//	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
//	shinyMaterial.UseMaterial(uniformMatSpecularInstensity, uniformMatShininess);
//	ironMan.RenderModel();
//}
//
//void DirectionalShadowMapPass(DirectionalLight* dLight)
//{
//	directionalShadowShader.UseShader();
//
//	glViewport(0, 0, dLight->GetShadowMap()->GetShadowWidth(), dLight->GetShadowMap()->GetShadowHeight());
//
//	dLight->GetShadowMap()->Write();
//	glClear(GL_DEPTH_BUFFER_BIT);
//
//	uniformModel = directionalShadowShader.GetModelLocation();
//	lightTransform = dLight->CalculateLightTransform();
//	directionalShadowShader.SetDirectionalLightTransform(&lightTransform);
//
//	directionalShadowShader.Validate();
//
//	RenderScene();
//
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//}
//void OmniShadowMapPass(PointLight* plight)
//{
//	omniShadowShader.UseShader();
//
//	glViewport(0, 0, plight->GetShadowMap()->GetShadowWidth(), plight->GetShadowMap()->GetShadowHeight());
//
//	plight->GetShadowMap()->Write();
//	glClear(GL_DEPTH_BUFFER_BIT);
//
//	uniformModel = omniShadowShader.GetModelLocation();
//	uniformOmniLightPos = omniShadowShader.GetOmniLightPosLocation();
//	uniformFarPlane = omniShadowShader.GetFarPlaneLocation();
//
//	glUniform3f(uniformOmniLightPos, plight->GetPosition().x, plight->GetPosition().y, plight->GetPosition().z);
//	glUniform1f(uniformFarPlane, plight->GetFarPlane());
//	omniShadowShader.SetLightMatrices(plight->CalculateLightTransform());
//
//	omniShadowShader.Validate();
//
//	RenderScene();
//
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//}
//
//void RenderPass(glm::mat4 projectionMatrix, glm::mat4 viewMatrix)
//{
//	glViewport(0, 0, 1366, 768);
//
//	//Clear window
//	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	skybox.DrawSkybox(viewMatrix, projectionMatrix);
//
//	shaderList[0]->UseShader();
//	uniformModel = shaderList[0]->GetModelLocation();
//	uniformProjection = shaderList[0]->GetProjectionLocation();
//	uniformView = shaderList[0]->GetViewLocation();
//
//	uniformMatSpecularInstensity = shaderList[0]->GetMatSpecularIntensityLocation();
//	uniformMatShininess = shaderList[0]->GetMatShininessLocation();
//	uniformCameraPosition = shaderList[0]->GetCameraPositionLocation();
//
//
//
//
//	glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
//	glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(viewMatrix));
//	glUniform3f(uniformCameraPosition, mainCamera.GetCameraPosition().x, mainCamera.GetCameraPosition().y, mainCamera.GetCameraPosition().z);
//
//	shaderList[0]->SetDirectionalLight(&directionalLight);
//	//order important for omnidirectional shadow mapping
//	shaderList[0]->SetPointLights(pointLights, pointLightCount, 3, 0);
//	shaderList[0]->SetSpotLights(spotLights, spotLightCount, 3 + pointLightCount, pointLightCount);
//	shaderList[0]->SetDirectionalLightTransform(&lightTransform);
//
//	directionalLight.GetShadowMap()->Read(GL_TEXTURE2);
//	shaderList[0]->SetTextureUnit(1);
//	shaderList[0]->SetDirectionalShadowMap(2);
//	shaderList[0]->Validate();
//
//	RenderScene();
//
//}
//
//int main2()
//{
//	Window mainWindow = Window(1366, 768);
//	mainWindow.Initialize();
//
//	CreateObject();
//	CreateShaders();
//	mainCamera = Camera(glm::vec3(-10.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f, 5.0f, 0.1f);
//
//	spidermanTexture = Texture("Textures/spiderman.png");
//	spidermanTexture.LoadTextureWithAlpha();
//	learnopenglTexture = Texture("Textures/learnopengl.png");
//	learnopenglTexture.LoadTextureWithAlpha();
//	plainTexture = Texture("Textures/plain.png");
//	plainTexture.LoadTextureWithAlpha();
//
//	shinyMaterial = Material(5.0f, 45.5f);
//	roughMaterial = Material(0.5f, 4.0f);
//
//	ironMan = Model();
//	ironMan.LoadModel("Models/IronMan.obj");
//	helicopter = Model();
//	helicopter.LoadModel("Models/uh60.obj");
//
//	directionalLight = DirectionalLight(0.0f, 0.1f, 1.0f, 1.0f, 1.0f,
//							0.0f, -1.0f, 0.0f, 2048, 2048);
//
//
//	pointLights[0] = PointLight(0.0f, 55.5f,
//		1.0f, 0.0f, 0.0f,
//		0.0f, 4.2f, 5.0f,
//		1.0f, 1.0f, 1.5f, 
//		1024, 1024,
//		0.01f, 100.0f);
//	pointLightCount++;
//	pointLights[1] = PointLight(0.0f, 25.5f,
//		0.0f, 1.0f, 0.5f,
//		3.0f, 5.0f, 0.0f,
//		1.1f, 0.5f, 0.1f,
//		1024, 1024,
//		0.01f, 100.0f);
//	pointLightCount++;
//	
//	//pointLights[2] = PointLight(0.0f, 30.1f,
//	//	0.3f, 0.6f, 0.2f,
//	//	30.0f, 20.0f, 5.0f,
//	//	1.0f, 1.7f, 0.01f);
//	//pointLightCount++;
//
//
//	spotLights[0] = SpotLight(0.0f,17.5f,
//		1.0f, 0.5f, 0.0f,
//		0.0f, 20.0f, -5.0f,
//		0.9f, -0.4f, -0.8f,
//		2.0f, 0.7f, 0.01f,
//		70.0f, 
//		1024, 1024,
//		0.01f, 100.0f);
//	spotLightCount++;
//
//	spotLights[1] = SpotLight(0.0f, 15.5f,
//		1.0f, 1.0f, 1.0f,
//		-5.0f, 15.0f, -5.0f,
//		0.0f, -1.0f, 0.0f,
//		0.0f, 0.0f, 0.5f,
//		60.0f, 
//		1024, 1024,
//		0.01f, 100.0f);
//	spotLightCount++;
//
//
//	//spotLights[2] = SpotLight(0.0f, 3.5f,
//	//	0.5f, 1.0f, 0.5f,
//	//	-1.0f, 3.0f, 0.0f,
//	//	0.3f, -1.0f, 0.0f,
//	//	2.0f, 0.7f, 0.01f,
//	//	25.0f);
//	//spotLightCount++;
//
//
//	//spotLights[3] = SpotLight(0.0f, 330.5f,
//	//	1.0f, 0.0f, 0.0f,
//	//	24.0f, 40.0f,-23.0f,
//	//	0.0f, -1.0f, 0.0f,
//	//	2.0f, 0.7f, 0.01f,
//	//	20.0f);
//	//spotLightCount++;
//
//	std::vector<std::string> skyboxFaces;
//	skyboxFaces.push_back("Textures/skybox/cupertin-lake_rt.tga");
//	skyboxFaces.push_back("Textures/skybox/cupertin-lake_lf.tga");
//	skyboxFaces.push_back("Textures/skybox/cupertin-lake_up.tga");
//	skyboxFaces.push_back("Textures/skybox/cupertin-lake_dn.tga");
//	skyboxFaces.push_back("Textures/skybox/cupertin-lake_bk.tga");
//	skyboxFaces.push_back("Textures/skybox/cupertin-lake_ft.tga");
//
//	skybox = Skybox(skyboxFaces);
//
//	//unifrom value setted once
//	glm::mat4 projection = glm::perspective(glm::radians(60.0f), (GLfloat)mainWindow.GetBufferWidth() / mainWindow.GetBufferHeight(), 0.1f, 100.0f);
//
//	//Loop until window closed
//	while (!mainWindow.GetShouldClose())
//	{
//		GLfloat timeNow = glfwGetTime(); //SDL_GetPerformanceCounter();
//		deltaTime = timeNow - lastTime; // (timeNow - lastTime)*1000 / SDL_GetPerformanceFrequency();
//		lastTime = timeNow;
//
//		//Get and handle user inpu events
//		glfwPollEvents();
//
//		mainCamera.HandleKeys(mainWindow.GetKeys(), deltaTime);
//		mainCamera.HandleMouse(mainWindow.GetMouseDeltaX(), mainWindow.GetMouseDeltaY());
//
//		HandleTransformActions();
//
//		DirectionalShadowMapPass(&directionalLight);
//		for (size_t i = 0; i < pointLightCount; i++)
//		{
//			OmniShadowMapPass(&pointLights[i]);
//		}
//		for (size_t i = 0; i < spotLightCount; i++)
//		{
//			OmniShadowMapPass(&spotLights[i]);
//		}
//		RenderPass(projection, mainCamera.CalculateViewMatrix());
//
//		glUseProgram(0);
//
//		mainWindow.SwapBuffers();
//	}
//
//	printf("Window closed!");
//
//	///* Clear */
//	//glfwDestroyWindow(mainWindow);
//	//glfwTerminate();
//
//	return 0;
//}
