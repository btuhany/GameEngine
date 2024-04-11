#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include <GL\glew.h>

class Shader
{
public:
	Shader();

	void CreateFromString(const char* vertexCode, const char* fragmentCode);
	void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);

	GLuint GetProjectionLocation();
	GLuint GetModelLocation();
	GLuint GetViewLocation();
	GLuint GetAmbientIntensityLocation();
	GLuint GetAmbientColourLocation();
	GLuint GetDiffuseIntensityLocation();
	GLuint GetDiffuseDirectionLocation();
	GLuint GetMatSpecularIntensityLocation();
	GLuint GetMatShininessLocation();
	GLuint GetCameraPositionLocation();

	void UseShader();
	void ClearShader();

	~Shader();

private:
	GLuint shaderID, uniformProjection, uniformModel, uniformView, uniformCameraPosition;
	GLuint uniformAmbientIntensity, uniformAmbientColour, uniformDiffuseIntensity, uniformDiffuseDirection;
	GLuint uniformMatSpecularIntensity, uniformMatShininess;

	std::string ReadFile(const char* fileLocation);
	void CompileShader(const char* vertexCode, const char* fragmentCode);
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};

