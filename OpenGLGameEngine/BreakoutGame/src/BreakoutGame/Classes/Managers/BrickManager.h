#pragma once
#include <GameEngine.h>
namespace BreakoutGame
{
	class BrickManager
	{
	public:
		void Initialize(std::shared_ptr<Shader> mainShader);
		std::vector<std::shared_ptr<GameEntity>> getEntityList();
	private:
		std::vector<std::shared_ptr<GameEntity>> m_CurrentBricks;
	};
}

