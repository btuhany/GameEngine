#include "Background.h"

namespace BreakoutGame
{
	void Background::Initialize()
	{
		static const char* vShaderLocation = "src/BreakoutGame/Shaders/bg_shader.vert";
		static const char* fShaderLocation = "src/BreakoutGame/Shaders/bg_shader.frag";
		m_Shader = std::make_shared<Shader>();
		m_Shader->CreateFromFiles(vShaderLocation, fShaderLocation);
		m_ShaderTimeLocation = glGetUniformLocation(m_Shader->shaderID, "iTime");

		std::shared_ptr<Texture> texture = std::make_shared<Texture>("src/BreakoutGame/Textures/background.PNG");
		texture->LoadTextureWithAlpha();
		std::shared_ptr<SpriteRenderData> renderData = std::make_shared<SpriteRenderData>(texture, nullptr, m_Shader);

		m_Entity = std::make_shared<SpriteEntity>(renderData);
		m_Entity->transform->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
		m_Entity->transform->SetScale(glm::vec3(60.0f, (60.0f * 9) / 16.0f, 1.0f));
	}

	void Background::Start()
	{
		m_Entity->setActive(true);
	}

	void Background::Tick(float deltaTime)
	{
		m_TimeCounter += deltaTime;
		m_Shader->UseShader();
		glUniform1f(m_ShaderTimeLocation, (GLfloat) m_TimeCounter);
	}
	std::shared_ptr<GameEntity> Background::getEntity()
	{
		return m_Entity;
	}
}
