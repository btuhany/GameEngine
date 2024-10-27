#include "Texture.h"
namespace GameEngine {
	Texture::Texture()
	{
		m_TextureID = 0;
		m_Width = 0;
		m_Height = 0;
		m_BitDepth = 0;
		m_FileLocation = "";
	}

	Texture::Texture(const char* fileLoc)
	{
		m_TextureID = 0;
		m_Width = 0;
		m_Height = 0;
		m_BitDepth = 0;
		m_FileLocation = fileLoc;
	}

	Texture::~Texture()
	{
		ClearTexture();
	}

	bool Texture::LoadTexture()
	{
		//unsigned char* equal to byte array, commonly used for containing imgdata 
		unsigned char* texData = stbi_load(m_FileLocation, &m_Width, &m_Height, &m_BitDepth, 0);

		if (!texData)
		{
			printf("Failed to load image at: %d\n", m_FileLocation);
			return false;
		}

		glGenTextures(1, &m_TextureID);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(texData);

		return true;
	}

	//Initializing the texture starting with binding
	bool Texture::LoadTextureWithAlpha()
	{
		//unsigned char* equal to byte array, commonly used for containing imgdata 
		unsigned char* texData = stbi_load(m_FileLocation, &m_Width, &m_Height, &m_BitDepth, 0);

		if (!texData)
		{
			printf("Failed to load image at: %d\n", m_FileLocation);
			return false;
		}

		glGenTextures(1, &m_TextureID);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(texData);

		return true;
	}

	void Texture::UseTexture()
	{
		//you can pass this code because 0 is the default for most graphic cards
		//GL_TEXTURE 0 is going to be used as empty texture unit
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
	}

	void Texture::ClearTexture()
	{
		glDeleteTextures(1, &m_TextureID);
		m_TextureID = 0;
		m_Width = 0;
		m_Height = 0;
		m_BitDepth = 0;
		m_FileLocation = "";
	}
	float Texture::GetAspectRatio()
	{
		return m_Width / m_Height;
	}
}