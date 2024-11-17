#pragma once
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW\glfw3.h>
#include <map>
#include "../Core.h"
#include "../Debugging/Log.h"
#include "../Resource/Shader.h"
#include "../Resource/TextData.h"
#include <ft2build.h>
#include FT_FREETYPE_H

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
		void Initialize();
		void Render();
		std::map<char, TextCharacter> charactersMap;
	};
}