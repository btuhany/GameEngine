#include "InGameState.h"

namespace BreakoutGame
{
	void InGameState::Initialize(std::shared_ptr<Shader> mainShader, std::shared_ptr<UIManager> uiManager)
	{
		m_InLevelCompletedDelay = false;
		m_LevelCompletedDelayTimeCounter = 0.0f;
		m_IsGamePaused = false;
		m_UIManager = uiManager;

		LevelBrickGridData::Initialize();

		m_Ball = std::make_shared<Ball>();
		m_Paddle = std::make_shared<Paddle>();
		m_BrickManager = std::make_shared<BrickManager>();
		m_PerkManager = std::make_shared<PerkManager>();
		m_PerkManager->Initialize(mainShader);
		m_Paddle->Initialize(mainShader);

		std::function<void(std::shared_ptr<GameEntity> entity)> ballHandler = std::bind(&InGameState::onBallColliderEnter, this, std::placeholders::_1);
		m_Ball->Initialize(mainShader, ballHandler);


		std::function<void()> brickManagerHandler = std::bind(&InGameState::onThereIsNoBrickLeft, this);
		m_BrickManager->Initialize(mainShader, brickManagerHandler);
	}
	void InGameState::Start()
	{
		m_Ball->Start();
		m_Paddle->Start();
		m_PerkManager->Start();
	}
	void InGameState::Tick(float deltaTime)
	{
		if (m_IsGamePaused)
			return;

		//TICK OBJECTS
		m_Paddle->Tick(deltaTime);
		m_Ball->Tick(deltaTime);
		if (m_Ball->IsOnPaddle)
		{
			m_Ball->SetPosition(m_Paddle->GetBallHolderPosition());
		}
		m_BrickManager->Tick(deltaTime);
		m_PerkManager->Tick(deltaTime);

		//ON LEVEL COMPLETED DELAY
		if (m_InLevelCompletedDelay)
		{
			m_LevelCompletedDelayTimeCounter += deltaTime;
			if (m_LevelCompletedDelayTimeCounter > DELAY_BETWEEN_LEVELS)
			{
				m_LevelCompletedDelayTimeCounter = 0.0f;
				m_InLevelCompletedDelay = false;
				if (isAllLevelsCompleted())
				{
					m_UIManager->HideCenteredText();
					m_UIManager->UpdateMainMenuStartButtonText("Restart");
					m_OnAllLevelsCompleted();
					return;
				}
				else
				{
					//STARTING A LEVEL OTHER THAN FIRST
					m_PlayerDataManager->IncreasePlayerLevel(1);
					initLevel(m_PlayerDataManager->GetPlayerLevel());
				}
			}
		}
	}
	std::vector<std::shared_ptr<GameEntity>> InGameState::GetEntities()
	{
		auto entityList = std::vector<std::shared_ptr<GameEntity>>();
		entityList.push_back(m_Paddle->getEntity());
		entityList.push_back(m_Ball->getEntity());
		auto brickManagerEntityList = m_BrickManager->getEntityList();
		entityList.insert(entityList.end(), brickManagerEntityList.begin(), brickManagerEntityList.end());
		auto perkEntityList = m_PerkManager->getEntityList();
		entityList.insert(entityList.end(), perkEntityList.begin(), perkEntityList.end());
		return entityList;
	}
	void InGameState::HandleOnDeactivated()
	{
		m_Ball->getEntity()->setActive(false);
		m_Paddle->getEntity()->setActive(false);
		m_UIManager->HidePlayerHUD();
	}

	void InGameState::HandleOnActivated()
	{
		m_PlayerDataManager = std::make_shared<PlayerDataManager>();
		m_UIManager->ShowPlayerHUD();
		startGame();
	}

	void InGameState::HandleInputs(InputType inputType)
	{
		if (inputType == InputType::LeftArrow)
		{
			m_Paddle->MoveLeft();
		}
		else if (inputType == InputType::RightArrow)
		{
			m_Paddle->MoveRight();
		}
		else if (inputType == InputType::UpArrow)
		{
			m_Paddle->MoveUp();
		}
		else if (inputType == InputType::DownArrow)
		{
			m_Paddle->MoveDown();
		}
		else if (inputType == InputType::SpaceKey)
		{
			LOG_INFO("Ball Released!");
			m_Ball->IsOnPaddle = false;
			m_Ball->StartMovement(Vector3(0.4f, 1.0f, 0.0f));
		}
		else if (inputType == InputType::PauseKey)
		{
			onPause();
		}
	}
	void InGameState::SetCallbacks(std::function<void()> onAllLevelsCompletedHandler)
	{
		m_OnAllLevelsCompleted = onAllLevelsCompletedHandler;
	}
	void InGameState::onBallColliderEnter(std::shared_ptr<GameEntity> gameEntity)
	{
		if (gameEntity->getTag() == (int)Tag::Brick)
		{
			auto hitData = m_BrickManager->HandleOnGotHitByBall(gameEntity);
			m_PlayerDataManager->ProcessBallHitBrickData(hitData);
			m_UIManager->UpdatePlayerHUDScorePoint(m_PlayerDataManager->GetScorePoint());
		}
		else if (gameEntity->getTag() == (int)Tag::Perk)
		{

		}
	}
	bool InGameState::isAllLevelsCompleted()
	{
		if (m_PlayerDataManager->GetPlayerLevel() + 1 >= LevelBrickGridData::GetLevelCount())
		{
			return true;
		}
		return false;
	}
	void InGameState::onPause()
	{
		if (m_IsGamePaused)
		{
			m_IsGamePaused = false;
			m_UIManager->HidePausePanel();
			m_Ball->EnableMovement();
			m_Paddle->EnableMovement();
		}
		else
		{
			m_IsGamePaused = true;
			m_UIManager->ShowPausePanel();
			//bad
			m_Ball->DisableMovement();
			m_Paddle->DisableMovement();
		}
	}
	void InGameState::startGame()
	{
		m_Paddle->getEntity()->setActive(true);
		m_Ball->getEntity()->setActive(true);
		m_UIManager->UpdatePlayerHUDLevel(m_PlayerDataManager->GetPlayerLevel());
		m_UIManager->UpdatePlayerHUDLive(m_PlayerDataManager->GetPlayerLive());
		m_UIManager->UpdatePlayerHUDScorePoint(m_PlayerDataManager->GetScorePoint());

		initLevel(m_PlayerDataManager->GetPlayerLevel());
	}
	void InGameState::onLevelInitializationCompleted()
	{
		m_Paddle->EnableMovement();
		m_Ball->EnableMovement();
	}
	void InGameState::initLevel(int level)
	{
		m_UIManager->UpdatePlayerHUDLevel(m_PlayerDataManager->GetPlayerLevel());
		m_UIManager->HideCenteredText();
		m_Paddle->Reset();
		m_Paddle->DisableMovement();
		m_Ball->Reset();
		m_Ball->DisableMovement();
		m_BrickManager->Reset();
		m_BrickManager->UpdateBrickGrid(LevelBrickGridData::GetBrickGridData(level));
		std::function<void()> levelInitHandler = std::bind(&InGameState::onLevelInitializationCompleted, this);
		m_BrickManager->PlayBrickGridEnterAnimation(levelInitHandler);
	}
	void InGameState::onThereIsNoBrickLeft() //ON LEVEL COMPLETED
	{
		if (!isAllLevelsCompleted())
		{
			m_UIManager->ShowCenteredText("Level Completed!", glm::vec3(0.0f, 0.0f, 1.0f));
		}
		else
		{
			m_UIManager->ShowCenteredText("Game Completed!", glm::vec3(0.0f, 1.0f, 0.0f));
		}
		m_Ball->SetSpeed(100.0f);
		m_LevelCompletedDelayTimeCounter = 0.0f;
		m_InLevelCompletedDelay = true;
	}
}
