#include "BreakoutScene.h"

namespace BreakoutGame
{
	BreakoutScene::BreakoutScene() : Scene()
	{
	}

	BreakoutScene::BreakoutScene(BreakoutSceneInputHandler* inputHandler) : Scene()
	{
		m_InputHandler = inputHandler;
		m_ObjectMoveSpeed = 15.0f;
	}

	BreakoutScene::~BreakoutScene()
	{
	}

	void BreakoutScene::Initialize(float viewPortWidth, float viewPortHeight)
	{
		initializeMainShader();
		initializeInputCallbacks();
		initializeBoundaryObjects();
		initializeMainCamera();
		initializeBreakoutObjects(viewPortWidth, viewPortHeight);
		LevelBrickGridData::Initialize();
		getAndInstantiateEntities();
		LOG_INFO("Breakout scene initialized!");
		Scene::Initialize(viewPortWidth, viewPortHeight);
	}

	void BreakoutScene::Start()
	{
		m_ControlledMovableObject = std::static_pointer_cast<IMovable>(m_Paddle);
		m_Ball->Start();
		m_Paddle->Start();
		m_GameManager->Start();
		m_UIManager->Start();
	}

	float lerpTime;
	void BreakoutScene::Update(GLfloat deltaTime)
	{
		m_DeltaTime = deltaTime;
		m_Paddle->Tick(deltaTime);

		m_Ball->Tick(deltaTime);
		if (m_Ball->IsOnPaddle)
		{
			m_Ball->SetPosition(m_Paddle->GetBallHolderPosition());
		}

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

	void BreakoutScene::initializeInputCallbacks()
	{
		std::function<void(InputType)> inputTypeHandler = std::bind(&BreakoutScene::onInputCallback, this, std::placeholders::_1);
		m_InputHandler->onInputCallback = inputTypeHandler;
		m_InputHandler->OnPressedCameraTypeChangeKeyEvent.AddHandler(
			[this]() {
				changeCameraType();
				//for (size_t i = 0; i < m_GameEntities.size(); i++)
				//{
				//	m_GameEntities[i]->setActive(true);
				//} 
			});
		m_InputHandler->OnLeftArrowKeyEvent.AddHandler(
			[this]() {

			});
		m_InputHandler->OnRightArrowKeyEvent.AddHandler(
			[this]() {

			});
		m_InputHandler->OnDownArrowKeyEvent.AddHandler(
			[this]() {
				handleOnDownKey();
			});
		m_InputHandler->OnUpArrowKeyEvent.AddHandler(
			[this]() {
				handleOnUpKey();
			});
		m_InputHandler->OnBallDebugKeyEvent.AddHandler(
			[this]() {
				handleOnBallDebugKey();
			});
		m_InputHandler->OnBallReleaseKeyEvent.AddHandler(
			[this]() {
				handleOnBallReleasedKey();
			});
	}

	void BreakoutScene::initializeBoundaryObjects()
	{
		auto rightBoundaryEntity = std::make_shared<GameEntity>();
		rightBoundaryEntity->setName("right_boundary_collider_object");
		auto rightBoundaryColliderComp = std::make_shared<BoxCollider2DComponent>(5.0f, 50.0f, CollisionType::Static);
		rightBoundaryColliderComp->SetEnableStaticSingleNormalVector(true, Vector2::left);
		rightBoundaryEntity->AddComponent(rightBoundaryColliderComp);
		rightBoundaryEntity->transform->SetPosition(glm::vec3(44.0f, 0.0f, 0.0f));
		instantiateGameEntity(rightBoundaryEntity, true);

		auto leftBoundaryEntity = std::make_shared<GameEntity>();
		leftBoundaryEntity->setName("left_boundary_collider_object");
		auto leftBoundaryColliderComp = std::make_shared<BoxCollider2DComponent>(5.0f, 50.0f, CollisionType::Static);
		leftBoundaryColliderComp->SetEnableStaticSingleNormalVector(true, Vector2::right);
		leftBoundaryEntity->AddComponent(leftBoundaryColliderComp);
		leftBoundaryEntity->transform->SetPosition(glm::vec3(-44.0f, 0.0f, 0.0f));
		instantiateGameEntity(leftBoundaryEntity, true);

		auto upBoundaryEntity = std::make_shared<GameEntity>();
		upBoundaryEntity->setName("down_boundary_collider_object");
		auto upBoundaryColliderComp = std::make_shared<BoxCollider2DComponent>(87.0f, 5.0f, CollisionType::Static);
		upBoundaryColliderComp->SetEnableStaticSingleNormalVector(true, Vector2::down);
		upBoundaryEntity->AddComponent(upBoundaryColliderComp);
		upBoundaryEntity->transform->SetPosition(glm::vec3(0.0f, 25.7f, 0.0f));
		instantiateGameEntity(upBoundaryEntity, true);

		auto downBoundaryEntity = std::make_shared<GameEntity>();
		downBoundaryEntity->setName("left_boundary_collider_object");
		auto downBoundaryColliderComp = std::make_shared<BoxCollider2DComponent>(87.0f, 5.0f, CollisionType::Static);
		downBoundaryColliderComp->SetEnableStaticSingleNormalVector(true, Vector2::up);
		downBoundaryEntity->AddComponent(downBoundaryColliderComp);
		downBoundaryEntity->transform->SetPosition(glm::vec3(0.0f, -25.7f, 0.0f));
		instantiateGameEntity(downBoundaryEntity, true);

	}

	void BreakoutScene::initializeMainShader()
	{
		static const char* vShaderLocation = "src/BreakoutGame/Shaders/shader.vert";
		static const char* fShaderLocation = "src/BreakoutGame/Shaders/shader.frag";
		m_MainShader = std::make_shared<Shader>();
		m_MainShader->CreateFromFiles(vShaderLocation, fShaderLocation);
	}

	void BreakoutScene::initializeMainCamera()
	{
		setCamera(std::make_shared<Camera>(
			glm::vec3(0.0f, 0.0f, 40.0f),
			glm::vec3(0.0f, 1.0f, 0.0f),
			-90.0f, 0.0f, 5.0f, 0.1f, 60, 0.1f, 100.0f, CAMERA_TYPE_PERSPECTIVE));
	}

	void BreakoutScene::initializeBreakoutObjects(float viewPortWidth, float viewPortHeight)
	{
		m_GameManager = std::make_shared<GameManager>();
		m_Ball = std::make_shared<Ball>();
		m_Paddle = std::make_shared<Paddle>();
		m_UIManager = std::make_shared<UIManager>();
		m_BrickManager = std::make_shared<BrickManager>();

		std::function<void(std::shared_ptr<GameEntity> entity)> ballHandler = std::bind(&BreakoutScene::onBallColliderEnter, this, std::placeholders::_1);
		std::function<void()> brickManagerHandler = std::bind(&BreakoutScene::onThereIsNoBrickLeft, this);
		m_GameManager->Initialize();
		m_Paddle->Initialize(m_MainShader);
		m_Ball->Initialize(m_MainShader, ballHandler);
		m_BrickManager->Initialize(m_MainShader, brickManagerHandler);
		m_UIManager->Initialize(viewPortWidth, viewPortHeight, 0, 1, 3);
	}

	void BreakoutScene::changeCameraType()
	{
		if (getCamera()->getCameraType() == CAMERA_TYPE_PERSPECTIVE)
		{
			auto pos = getCamera()->getPosition();
			auto yaw = getCamera()->getYawValue();
			auto pitch = getCamera()->getPitchValue();
			setCamera(std::make_shared<Camera>(
				pos,
				glm::vec3(0.0f, 1.0f, 0.0f),
				yaw, pitch, 5.0f, 0.1f, 30.0f, 0.1f, 100.0f, CAMERA_TYPE_ORTHOGONAL));
		}
		else if (getCamera()->getCameraType() == CAMERA_TYPE_ORTHOGONAL)
		{
			auto pos = getCamera()->getPosition();
			auto yaw = getCamera()->getYawValue();
			auto pitch = getCamera()->getPitchValue();
			setCamera(std::make_shared<Camera>(
				pos,
				glm::vec3(0.0f, 1.0f, 0.0f),
				yaw, pitch, 5.0f, 0.1f, 60.0f, 0.1f, 100.0f, CAMERA_TYPE_PERSPECTIVE));
		}
	}

	void BreakoutScene::onBallColliderEnter(std::shared_ptr<GameEntity> gameEntity)
	{
		if (gameEntity->getTag() == (int)Tag::Brick)
		{
			auto hitData = m_BrickManager->HandleOnGotHitByBall(gameEntity);
			m_GameManager->ProcessBallHitBrickData(hitData);
			m_UIManager->SetScorePoint(m_GameManager->GetScorePoint());
		}
	}

	void BreakoutScene::onThereIsNoBrickLeft()
	{
		LOG_INFO("THERE IS NO BRICK LEFT!");
	}

	void BreakoutScene::handleOnLeftKey()
	{
		m_ControlledMovableObject->MoveLeft();
	}

	void BreakoutScene::handleOnRightKey()
	{
		m_ControlledMovableObject->MoveRight();
	}

	void BreakoutScene::handleOnDownKey()
	{
		m_ControlledMovableObject->MoveDown();
	}

	void BreakoutScene::handleOnUpKey()
	{
		m_ControlledMovableObject->MoveUp();
	}

	bool isControllingBall = false;
	void BreakoutScene::handleOnBallDebugKey()
	{
		//if (isControllingBall)
		//{
		//	m_ControlledMovableObject = std::static_pointer_cast<IMovable>(m_Paddle);
		//	isControllingBall = false;
		//}
		//else
		//{
		//	m_ControlledMovableObject = std::static_pointer_cast<IMovable>(m_Ball);
		//	m_Ball->SetSpeed(0.0f);
		//	isControllingBall = true;
		//}
		if (isControllingBall)
		{
			isControllingBall = false;
			onLevelEnded();
		}
		else
		{
			onLevelStarted();
			isControllingBall = true;
		}
	}

	void BreakoutScene::handleOnBallReleasedKey()
	{
		LOG_INFO("Ball Released!");
		m_Ball->IsOnPaddle = false;
		m_Ball->StartMovement(Vector3(0.4f, 1.0f, 0.0f));
	}

	void BreakoutScene::getAndInstantiateEntities()
	{
		//TODO send/get instantiate data or instantiate outside scene class
		auto entityList = std::vector<std::shared_ptr<GameEntity>>();
		entityList.push_back(m_Paddle->getEntity());
		entityList.push_back(m_Ball->getEntity());
		auto brickManagerEntityList = m_BrickManager->getEntityList();
		entityList.insert(entityList.end(), brickManagerEntityList.begin(), brickManagerEntityList.end());
		auto uiEntityList = m_UIManager->getEntityList();
		entityList.insert(entityList.end(), uiEntityList.begin(), uiEntityList.end());
		for (size_t i = 0; i < entityList.size(); i++)
		{
			instantiateGameEntity(entityList[i], false);
		}
	}

	void BreakoutScene::onLevelStarted()
	{
		m_InputHandler->IsPlayerControlsActive = true;
		m_Paddle->getEntity()->setActive(true);
		m_Paddle->Reset();
		m_Ball->getEntity()->setActive(true);
		m_Ball->Reset();
		m_BrickManager->Reset();
		m_BrickManager->UpdateBrickGrid(LevelBrickGridData::GetBrickGridData(1));
		m_UIManager->ShowPlayerHUD(m_GameManager->GetPlayerLive());
	}

	void BreakoutScene::onLevelEnded()
	{
		m_UIManager->HidePlayerHUD();
		m_InputHandler->IsPlayerControlsActive = false;
		m_Ball->Reset();
		m_Paddle->Reset();
		m_BrickManager->Reset();
	}
	void BreakoutScene::onInputCallback(InputType inputType)
	{
		if (inputType == InputType::LeftArrow)
		{
			handleOnLeftKey();
		}
		else if (inputType == InputType::RightArrow)
		{
			handleOnRightKey();
		}
	}
}
