#pragma once

#include <GL/glew.h>
#include "stb_image.h"

class Texture
{
public:
	Texture();
	Texture(const char* fileLocation);
	~Texture();

	bool LoadTexture();
	bool LoadTextureWithAlpha();
	void UseTexture();
	void ClearTexture();

private:
	GLuint textureID;
	int width, height, bitDepth;

	const char* fileLocation;


};

