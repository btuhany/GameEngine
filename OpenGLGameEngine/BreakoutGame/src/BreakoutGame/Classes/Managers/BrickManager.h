#pragma once
#include <GameEngine.h>
#include "IEntityProvider.h"
#include "../Data/BrickData.h"
#include "../Objects/Brick.h"
namespace BreakoutGame
{
	class BrickManager : public IEntityProvider
	{
	public:
		void Initialize(std::shared_ptr<Shader> mainShader);
		std::vector<std::shared_ptr<GameEntity>> getEntityList();
	private:
		void initializeEasyBrickData(std::shared_ptr<Shader> shader);
		void initializeMediumBrickData(std::shared_ptr<Shader> shader);
		void initializeHardBrickData(std::shared_ptr<Shader> shader);

		std::vector<std::shared_ptr<Brick>> m_BrickList;

		static const int ROW_SIZE = 5;
		static const int COLUMN_SIZE = 11;
		const Vector2 SPACING = Vector2(7.0f, 3.0f);
		const Vector2 START_POS = Vector2(-35.0f, 8.0f);
		std::shared_ptr<BrickData> m_EasyBrickData;
		std::shared_ptr<BrickData> m_MediumBrickData;
		std::shared_ptr<BrickData> m_HardBrickData;

	};
}

