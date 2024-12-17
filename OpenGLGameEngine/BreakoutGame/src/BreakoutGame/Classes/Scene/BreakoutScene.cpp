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

		m_GameManager = std::make_shared<GameManager>();
		m_GameManager->Initialize();
		m_Paddle = std::make_shared<Paddle>();
		m_Paddle->Initialize(m_MainShader);

		m_Ball = std::make_shared<Ball>();
		m_Ball->Initialize(m_MainShader);
		m_Ball->SetOnBallColliderEnterHandler(
			[this](std::shared_ptr<GameEntity> entity) {
				onBallColliderEnter(entity);
			});

		m_BrickManager = std::make_shared<BrickManager>();
		m_BrickManager->Initialize(m_MainShader);
		m_BrickManager->PoolBricks();
		m_UIManager = std::make_shared<UIManager>();
		m_UIManager->Initialize(viewPortWidth, viewPortHeight, 0, 1, 3);

		LevelBrickGridData::Initialize();

		instantiateGameEntity(m_Paddle->getEntity());
		instantiateGameEntity(m_Ball->getEntity());
		auto brickEntityList = m_BrickManager->getEntityList();
		for (size_t i = 0; i < brickEntityList.size(); i++)
		{
			instantiateGameEntity(brickEntityList[i]);
		}
		auto uiEntityList = m_UIManager->getEntityList();
		for (size_t i = 0; i < uiEntityList.size(); i++)
		{
			instantiateGameEntity(uiEntityList[i]);
		}

		m_GameManager->isGameStarted = false;
		LOG_INFO("Breakout scene initialized!");

		m_BrickManager->HandleOnAfterBricksInstantiated();
		Scene::Initialize(viewPortWidth, viewPortHeight);
	}

	void BreakoutScene::Start()
	{
		m_BrickManager->SpawnBricks(LevelBrickGridData::GetBrickGridData(0));
		m_ControlledMovableObject = std::static_pointer_cast<IMovable>(m_Paddle);
		m_Ball->Start();
		m_Paddle->Start();
		m_GameManager->Start();
		m_UIManager->Start();
	}

	void BreakoutScene::Update(GLfloat deltaTime)
	{
		m_DeltaTime = deltaTime;
		m_Ball->Tick(deltaTime);
		m_Paddle->Tick(deltaTime);


		if (m_GameManager->isGameStarted)
		{

		}
		else
		{
			m_Ball->SetPosition(m_Paddle->GetBallHolderPosition());
		}
	}

	void BreakoutScene::initializeInputCallbacks()
	{
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
				handleOnLeftKey();
			});
		m_InputHandler->OnRightArrowKeyEvent.AddHandler(
			[this]() {
				handleOnRightKey();
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
		if (isControllingBall)
		{
			m_ControlledMovableObject = std::static_pointer_cast<IMovable>(m_Paddle);
			isControllingBall = false;
		}
		else
		{
			m_ControlledMovableObject = std::static_pointer_cast<IMovable>(m_Ball);
			m_Ball->SetSpeed(0.0f);
			isControllingBall = true;
		}
	}

	void BreakoutScene::handleOnBallReleasedKey()
	{
		LOG_INFO("Ball Released!");
		m_GameManager->isGameStarted = true;
		m_Ball->StartMovement(Vector3(0.4f, 1.0f, 0.0f));
	}

}
