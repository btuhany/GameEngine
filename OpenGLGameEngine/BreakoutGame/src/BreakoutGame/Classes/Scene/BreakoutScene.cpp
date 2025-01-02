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

		m_StateManager = std::make_shared<StateManager>();
		m_UIManager = std::make_shared<UIManager>();
		m_UIManager->Initialize(viewPortWidth, viewPortHeight, PlayerDataManager::INITIAL_SCORE_POINT, PlayerDataManager::INITAL_LEVEL, PlayerDataManager::INITAL_LIVES);
		m_Background = std::make_shared<Background>();
		m_Background->Initialize();

		auto mainMenuStateController = std::make_shared<MainMenuState>(m_UIManager);
		auto inGameStateController = std::make_shared<InGameState>();
		inGameStateController->Initialize(m_MainShader, m_UIManager);

		auto entityList = std::vector<std::shared_ptr<GameEntity>>();
		entityList.push_back(m_Background->getEntity());
		auto uiEntityList = m_UIManager->getEntityList();
		entityList.insert(entityList.end(), uiEntityList.begin(), uiEntityList.end());

		auto inGameStateEntities = inGameStateController->GetEntities();
		entityList.insert(entityList.end(), inGameStateEntities.begin(), inGameStateEntities.end());

		instantiateEntities(entityList);
		auto onGameQuitHandler = std::bind(&BreakoutScene::onGameQuitCallback, this);
		m_StateManager->Initialize(mainMenuStateController, inGameStateController, onGameQuitHandler);
		

		LOG_INFO("Breakout scene initialized!");
		Scene::Initialize(viewPortWidth, viewPortHeight);
	}

	void BreakoutScene::Start()
	{
		m_UIManager->Start();
		m_StateManager->Start();
		m_Background->Start();
	}

	void BreakoutScene::Update(GLfloat deltaTime)
	{
		m_DeltaTime = deltaTime;
		m_StateManager->Tick(deltaTime);
		m_Background->Tick(deltaTime);
	}

	void BreakoutScene::initializeInputCallbacks()
	{
		std::function<void(InputType)> inputTypeHandler = std::bind(&BreakoutScene::onInputCallback, this, std::placeholders::_1);
		m_InputHandler->onInputCallback = inputTypeHandler;
		m_InputHandler->OnPressedCameraTypeChangeKeyEvent.AddHandler(
			[this]() {
				changeCameraType();
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
		downBoundaryEntity->setTag((int)Tag::DeathBoundary);
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
			-90.0f, 0.0f, 5.0f, 0.1f, 46.0f, 0.1f, 100.0f, CAMERA_TYPE_ORTHOGONAL));
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
				yaw, pitch, 5.0f, 0.1f, 46.0, 0.1f, 100.0f, CAMERA_TYPE_ORTHOGONAL));
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

	void BreakoutScene::instantiateEntities(std::vector<std::shared_ptr<GameEntity>> entityList)
	{
		//TODO send/get instantiate data or instantiate outside scene class
		for (size_t i = 0; i < entityList.size(); i++)
		{
			instantiateGameEntity(entityList[i], false);
		}
	}





	//bool isControllingBall = false;
	//void BreakoutScene::handleOnBallDebugKey()
	//{
	//	//if (isControllingBall)
	//	//{
	//	//	m_ControlledMovableObject = std::static_pointer_cast<IMovable>(m_Paddle);
	//	//	isControllingBall = false;
	//	//}
	//	//else
	//	//{
	//	//	m_ControlledMovableObject = std::static_pointer_cast<IMovable>(m_Ball);
	//	//	m_Ball->SetSpeed(0.0f);
	//	//	isControllingBall = true;
	//	//}
	//	if (isControllingBall)
	//	{
	//		isControllingBall = false;
	//		onLevelEnded();
	//	}
	//	else
	//	{
	//		startGame();
	//		isControllingBall = true;
	//	}
	//}

	void BreakoutScene::onGameQuitCallback()
	{
		setIsSceneEnd(true);
	}

	void BreakoutScene::onInputCallback(InputType inputType)
	{
		m_StateManager->GetController()->HandleInputs(inputType);
	}
}
