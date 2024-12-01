#pragma once
#include <vector>
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
#include "../Components/UITextRendererComponent.h"
namespace GameEngine
{
	struct TextCharacter {
		unsigned int	textureID;
		glm::ivec2		size;
		glm::ivec2		bearing;
		unsigned int	advance;
	};

	class ENGINE_API TextRenderer
	{
	public:
		void Initialize();
		void Render(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
		void HandleOnComponentAdded(std::shared_ptr<UITextRendererComponent> textRenderer);
		void HandleOnComponentRemoved(std::shared_ptr<UITextRendererComponent> textRenderer);
		std::vector<std::shared_ptr<UITextRendererComponent>> m_Components;
		std::map<char, TextCharacter> charactersMap;
	};
}