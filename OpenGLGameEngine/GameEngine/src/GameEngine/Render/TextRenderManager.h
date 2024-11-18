#pragma once
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <GLFW\glfw3.h>
#include <GL\glew.h>
#include <map>
#include "../Core.h"
#include "../Debugging/Log.h"
#include "../Resource/Shader.h"
#include "../Resource/MeshData.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include "../Resource/Texture.h"
#include "../Render/SpriteRenderData.h"
#include "../Scene/Scene.h"
namespace GameEngine
{
	struct TextCharacter {
		unsigned int	textureID;
		glm::ivec2		size;
		glm::ivec2		bearing;
		unsigned int	advance;
	};

	class ENGINE_API TextRenderManager
	{
	public:
		void Initialize(std::shared_ptr<Shader> mainShader, Scene* scenee);
		void Render();
		std::map<char, TextCharacter> charactersMap;
	};
}