#pragma once
#include "../Core.h"
#include <GL/glew.h>
#include "../ConstantValues.h"
namespace GameEngine {
	class ENGINE_API Texture
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
		GLuint m_TextureID;
		int m_Width, m_Height, m_BitDepth;
		const char* m_FileLocation;


	};
}
