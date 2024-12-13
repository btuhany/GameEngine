#pragma once
#include <GameEngine.h>
#include "IEntityProvider.h"
#include "../Data/BrickData.h"
namespace BreakoutGame
{
	class BrickManager : public IEntityProvider
	{
	public:
		void Initialize(std::shared_ptr<Shader> mainShader);
		std::vector<std::shared_ptr<GameEntity>> getEntityList();
	private:
		void initializeEasyBrickData();
		void initializeMediumBrickData();
		void initializeHardBrickData();

		std::vector<std::shared_ptr<GameEntity>> m_CurrentBricks;

		std::shared_ptr<BrickData> m_EasyBrickData;
		std::shared_ptr<BrickData> m_MediumBrickData;
		std::shared_ptr<BrickData> m_HardBrickData;

	};
}

