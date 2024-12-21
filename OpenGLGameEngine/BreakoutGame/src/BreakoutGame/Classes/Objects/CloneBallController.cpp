#include "CloneBallController.h"
namespace BreakoutGame
{
	void CloneBallController::Initialize(std::shared_ptr<Shader> shader, std::function<void(std::shared_ptr<GameEntity>)> handler)
	{
		for (size_t i = 0; i < CLONE_BALL_COUNT; i++)
		{
			auto ball = std::make_shared<Ball>();
			ball->Initialize(shader, handler);
			ball->IsClone = true;
			ball->IsOnPaddle = false;
			ball->Start();
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
		for (size_t i = 0; i < m_CloneBallList.size(); i++)
		{
			m_CloneBallList[i]->getEntity()->setActive(true);
			float randomX = RandomGenerator::GetFloat(-1.0f, 1.0f);
			float randomY = RandomGenerator::GetFloat(0.5f, 1.0f);
			Vector3 randomNormalizedVec = Vector3(randomX, randomY, 0.0f).normalize();
			m_CloneBallList[i]->StartMovement(randomNormalizedVec);
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
