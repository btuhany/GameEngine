#include "Ball.h"

namespace BreakoutGame
{
	void Ball::Initialize()
	{
		static const char* vShaderLocation = "src/BreakoutGame/Shaders/shader.vert";
		static const char* fShaderLocation = "src/BreakoutGame/Shaders/shader.frag";
		std::shared_ptr<Shader> mainShader = std::make_shared<Shader>();
		mainShader->CreateFromFiles(vShaderLocation, fShaderLocation);

		std::shared_ptr<Texture> texture = std::make_shared<Texture>("src/BreakoutGame/Textures/58-Breakout-Tiles.PNG");
		texture->LoadTextureWithAlpha();

		std::shared_ptr<SpriteRenderData> renderData = std::make_shared<SpriteRenderData>(texture, nullptr, mainShader);

		m_Entity = std::make_shared<SpriteEntity>(renderData);

		std::string name = "Ball";
		m_Entity->setName(name);

		m_Entity->transform->SetPosition(glm::vec3(-10.0f, 0.0f, 0.0f));

		auto boxCollider = std::make_shared<BoxCollider2DComponent>(1.0f, 1.0f, CollisionType::Dynamic);
		m_Entity->AddComponent(boxCollider);
	}

	void Ball::Start()
	{
	}

	void Ball::Tick(float deltaTime)
	{
	}

	std::shared_ptr<SpriteEntity> Ball::getEntity()
	{
		return m_Entity;
	}
}
