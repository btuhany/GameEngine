#include "CloneBallController.h"
namespace BreakoutGame
{
	void CloneBallController::Initialize(std::shared_ptr<Shader> shader, std::function<void(std::shared_ptr<GameEntity>)> handler)
	{
		std::shared_ptr<Texture> texture = std::make_shared<Texture>("src/BreakoutGame/Textures/clone_ball.PNG");
		texture->LoadTextureWithAlpha();
		std::shared_ptr<SpriteRenderData> renderData = std::make_shared<SpriteRenderData>(texture, nullptr, shader);
		float scale = 0.9f;
		for (size_t i = 0; i < CLONE_BALL_COUNT; i++)
		{
			auto ball = std::make_shared<Ball>();
			ball->Initialize(shader, handler);
			ball->IsClone = true;
			ball->IsOnPaddle = false;
			ball->Start();
			ball->getEntity()->renderer->setSpriteRenderData(renderData);
			ball->SetSpeed(ball->getSpeed() * 1.5f);
			ball->getEntity()->transform->Scale(scale, scale, scale);
			auto collider = ball->getEntity()->GetComponent<BoxCollider2DComponent>();
			auto colliderWidth = collider->getWidth();
			auto colliderHeight = collider->getHeight();
			collider->SetWidthAndHeight(colliderWidth * scale, colliderHeight * scale);
			ball->getEntity()->transform->SetPosition(glm::vec3(0.0f, 0.0f, -0.5f));
			m_CloneBallList.push_back(ball);
		}
	}
	void CloneBallController::Tick(float deltaTime)
	{
		for (size_t i = 0; i < m_CloneBallList.size(); i++)
		{
			if (m_CloneBallList[i]->getEntity()->getActive())
				m_CloneBallList[i]->Tick(deltaTime);
		}
	}
	void CloneBallController::ActivateClones(Vector3 pos)
	{
		pos.x -= 15.0f;
		float spacingX = 7.5f;
		for (size_t i = 0; i < m_CloneBallList.size(); i++)
		{
			pos.x += spacingX * i;
			m_CloneBallList[i]->getEntity()->setActive(true);
			m_CloneBallList[i]->getEntity()->transform->SetPosition(pos);
			float randomX = RandomGenerator::GetFloat(-0.5f, 0.5f);
			float randomY = RandomGenerator::GetFloat(0.7f, 1.0f);
			Vector3 randomNormalizedVec = Vector3(randomX, randomY, 0.0f).normalize();
			m_CloneBallList[i]->StartMovement(randomNormalizedVec);
		}
	}
	void CloneBallController::DeactivateClones()
	{
		for (size_t i = 0; i < m_CloneBallList.size(); i++)
		{
			m_CloneBallList[i]->getEntity()->setActive(false);
		}
	}
	std::vector<std::shared_ptr<GameEntity>> CloneBallController::getEntitiyList()
	{
		std::vector<std::shared_ptr<GameEntity>> entities;
		for (size_t i = 0; i < m_CloneBallList.size(); i++)
		{
			entities.push_back(m_CloneBallList[i]->getEntity());
		}
		return entities;
	}
}
