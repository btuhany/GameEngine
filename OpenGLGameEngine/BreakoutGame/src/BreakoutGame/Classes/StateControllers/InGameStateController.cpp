#include "InGameStateController.h"

namespace BreakoutGame
{
	void InGameStateController::Initialize(std::shared_ptr<Shader> mainShader, std::shared_ptr<UIManager> uiManager)
	{
		m_IsGamePaused = false;
		m_UIManager = uiManager;

		LevelBrickGridData::Initialize();

		m_Ball = std::make_shared<Ball>();
		m_Paddle = std::make_shared<Paddle>();
		m_BrickManager = std::make_shared<BrickManager>();

		m_Paddle->Initialize(mainShader);

		std::function<void(std::shared_ptr<GameEntity> entity)> ballHandler = std::bind(&InGameStateController::onBallColliderEnter, this, std::placeholders::_1);
		m_Ball->Initialize(mainShader, ballHandler);


		std::function<void()> brickManagerHandler = std::bind(&InGameStateController::onThereIsNoBrickLeft, this);
		m_BrickManager->Initialize(mainShader, brickManagerHandler);
	}
	void InGameStateController::Start()
	{
		m_Ball->Start();
		m_Paddle->Start();
	}
	void InGameStateController::Tick(float deltaTime)
	{
		if (m_IsGamePaused)
			return;

		m_Paddle->Tick(deltaTime);
		m_Ball->Tick(deltaTime);
		if (m_Ball->IsOnPaddle)
		{
			m_Ball->SetPosition(m_Paddle->GetBallHolderPosition());
		}
		m_BrickManager->Tick(deltaTime);
		//PADDLE ANIMATION FOR JUST TESTING
		//if (m_Paddle->getEntity()->getActive())
		//{
		//	lerpTime += m_DeltaTime;
		//	lerpTime = std::min(lerpTime, 1.0f);
		//	auto curPos = m_Paddle->getEntity()->transform->getPosition();
		//	Vector3 curPosVec3 = Vector3(curPos.x, curPos.y, curPos.z);
		//	Vector3 newPosVec3 = Vector3(10.0f, 20.0f, 0.0f);
		//	float easeValue = TweenEase::EaseInOutElastic(lerpTime);
		//	auto newPos = Vector3::UnclampedLerp(Vector3(0.0f, -20.0f, 0.0f), newPosVec3, easeValue);
		//	m_Paddle->getEntity()->transform->SetPosition(newPos);
		//}
	}
	std::vector<std::shared_ptr<GameEntity>> InGameStateController::GetEntities()
	{
		auto entityList = std::vector<std::shared_ptr<GameEntity>>();
		entityList.push_back(m_Paddle->getEntity());
		entityList.push_back(m_Ball->getEntity());
		auto brickManagerEntityList = m_BrickManager->getEntityList();
		entityList.insert(entityList.end(), brickManagerEntityList.begin(), brickManagerEntityList.end());
		return entityList;
	}
	void InGameStateController::HandleOnDeactivated()
	{
	}

	void InGameStateController::HandleOnActivated()
	{
		m_PlayerDataManager = std::make_shared<PlayerDataManager>();
		startGame();
	}

	void InGameStateController::HandleInputs(InputType inputType)
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
	void InGameStateController::onBallColliderEnter(std::shared_ptr<GameEntity> gameEntity)
	{
		if (gameEntity->getTag() == (int)Tag::Brick)
		{
			auto hitData = m_BrickManager->HandleOnGotHitByBall(gameEntity);
			m_PlayerDataManager->ProcessBallHitBrickData(hitData);
			m_UIManager->SetScorePoint(m_PlayerDataManager->GetScorePoint());
		}
	}
	void InGameStateController::onPause()
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
	void InGameStateController::startGame()
	{
		m_Paddle->getEntity()->setActive(true);
		m_Ball->getEntity()->setActive(true);
		m_UIManager->ShowPlayerHUD(m_PlayerDataManager->GetPlayerLive());
		std::function<void()> levelInitHandler = std::bind(&InGameStateController::onLevelInitializationCompleted, this);
		initLevel(m_PlayerDataManager->GetPlayerLevel(), levelInitHandler);
	}
	void InGameStateController::onLevelInitializationCompleted()
	{
		m_Paddle->EnableMovement();
		m_Ball->EnableMovement();
	}
	void InGameStateController::initLevel(int level, std::function<void()> onLevelInitializedCallback)
	{
		m_Paddle->Reset();
		m_Paddle->DisableMovement();
		m_Ball->Reset();
		m_Ball->DisableMovement();
		m_BrickManager->Reset();
		m_BrickManager->UpdateBrickGrid(LevelBrickGridData::GetBrickGridData(level));
		m_BrickManager->PlayBrickGridEnterAnimation(onLevelInitializedCallback);
	}
	void InGameStateController::onLevelEnded()
	{
		m_UIManager->HidePlayerHUD();
		m_Ball->Reset();
		m_Paddle->Reset();
		m_BrickManager->Reset();
	}
	void InGameStateController::onThereIsNoBrickLeft()
	{
		
	}
}
