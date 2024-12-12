#pragma once
#include <GameEngine.h>
#include "IEntityProvider.h"
namespace BreakoutGame
{
	class BrickManager : public IEntityProvider
	{
	public:
		void Initialize(std::shared_ptr<Shader> mainShader);
		std::vector<std::shared_ptr<GameEntity>> getEntityList();
	private:
		std::vector<std::shared_ptr<GameEntity>> m_CurrentBricks;
	};
}

