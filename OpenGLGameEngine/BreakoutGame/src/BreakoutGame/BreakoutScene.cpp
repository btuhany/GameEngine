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

	void BreakoutScene::Initialize()
	{
		m_IsGameStarted = false;
		initializeInputCallbacks();
		initializeBoundaryObjects();
		setCamera(std::make_shared<Camera>(
			glm::vec3(0.0f, 0.0f, 30.0f),
			glm::vec3(0.0f, 1.0f, 0.0f),
			-90.0f, 0.0f, 5.0f, 0.1f, 60, 0.1f, 100.0f, CAMERA_TYPE_PERSPECTIVE));

		static const char* vShaderLocation = "src/BreakoutGame/Shaders/shader.vert";
		static const char* fShaderLocation = "src/BreakoutGame/Shaders/shader.frag";
		std::shared_ptr<Shader> mainShader = std::make_shared<Shader>();
		mainShader->CreateFromFiles(vShaderLocation, fShaderLocation);

		std::shared_ptr<Texture> blueTex = std::make_shared<Texture>("src/BreakoutGame/Textures/01-Breakout-Tiles.PNG");
		blueTex->LoadTextureWithAlpha();
		std::shared_ptr<Texture> purpleTex = std::make_shared<Texture>("src/BreakoutGame/Textures/05-Breakout-Tiles.PNG");
		purpleTex->LoadTextureWithAlpha();

		std::shared_ptr<SpriteRenderData> breakoutSpriteRenderData = std::make_shared<SpriteRenderData>(blueTex, nullptr, mainShader);
		std::shared_ptr<SpriteRenderData> breakoutSpriteRenderData2 = std::make_shared<SpriteRenderData>(purpleTex, nullptr, mainShader);

		float radius = 12.0f;
		float angleIncrement = 2 * glm::pi<float>() / 10;

		for (size_t i = 0; i < 10; i++)
		{
			std::shared_ptr<SpriteEntity> spriteEntity = std::make_shared<SpriteEntity>(breakoutSpriteRenderData);
			std::string name = std::to_string(i) + ".Tile";
			spriteEntity->setName(name);

			float angle = i * angleIncrement;
			float x = radius * glm::cos(angle);
			float y = radius * glm::sin(angle);

			spriteEntity->transform->SetPosition(glm::vec3(x, y, 0.0f));
			auto boxCollider2DComp = std::make_shared<BoxCollider2DComponent>(6.0f, 2.0f, CollisionType::Static);
			spriteEntity->AddComponent<BoxCollider2DComponent>(boxCollider2DComp);
			instantiateGameEntity(spriteEntity);
		}

		for (size_t i = 0; i < 8; i++)
		{
			std::shared_ptr<SpriteEntity> spriteEntity = std::make_shared<SpriteEntity>(breakoutSpriteRenderData);
			std::string name = std::to_string(i) + ".Tile";
			spriteEntity->setName(name);

			float angle = i * angleIncrement;
			float x = 2.0f * radius * glm::cos(angle);
			float y = 2.0f * radius * glm::sin(angle);

			spriteEntity->transform->SetPosition(glm::vec3(x, y, 0.0f));
			auto boxCollider2DComp = std::make_shared<BoxCollider2DComponent>(6.0f, 2.0f, CollisionType::Static);
			spriteEntity->AddComponent<BoxCollider2DComponent>(boxCollider2DComp);
			instantiateGameEntity(spriteEntity);
		}

		m_Paddle = std::make_shared<Paddle>();
		m_Paddle->Initialize(mainShader);
		auto paddleEntity = m_Paddle->getEntity();
		instantiateGameEntity(paddleEntity);

		m_Ball = std::make_shared<Ball>();
		m_Ball->Initialize(mainShader);
		auto ballEntity = m_Ball->getEntity();
		instantiateGameEntity(ballEntity);

		
		m_UIManager = std::make_shared<UIManager>();
		m_UIManager->Initialize();
		auto uiEntityList = m_UIManager->getEntityList();
		for (size_t i = 0; i < uiEntityList.size(); i++)
		{
			instantiateGameEntity(uiEntityList[i]);
		}

		LOG_INFO("Breakout scene initialized!");
		Scene::Initialize();
	}

	void BreakoutScene::Start()
	{
		m_ControlledMovableObject = std::static_pointer_cast<IMovable>(m_Paddle);
		m_Ball->Start();
		m_Paddle->Start();
	}

	void BreakoutScene::Update(GLfloat deltaTime)
	{
		m_DeltaTime = deltaTime;
		m_Ball->Tick(deltaTime);
		m_Paddle->Tick(deltaTime);


		if (m_IsGameStarted)
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
		rightBoundaryEntity->transform->SetPosition(glm::vec3(33.0f, 0.0f, 0.0f));
		instantiateGameEntity(rightBoundaryEntity, true);

		auto leftBoundaryEntity = std::make_shared<GameEntity>();
		leftBoundaryEntity->setName("left_boundary_collider_object");
		auto leftBoundaryColliderComp = std::make_shared<BoxCollider2DComponent>(5.0f, 50.0f, CollisionType::Static);
		leftBoundaryColliderComp->SetEnableStaticSingleNormalVector(true, Vector2::right);
		leftBoundaryEntity->AddComponent(leftBoundaryColliderComp);
		leftBoundaryEntity->transform->SetPosition(glm::vec3(-33.0f, 0.0f, 0.0f));
		instantiateGameEntity(leftBoundaryEntity, true);

		auto upBoundaryEntity = std::make_shared<GameEntity>();
		upBoundaryEntity->setName("down_boundary_collider_object");
		auto upBoundaryColliderComp = std::make_shared<BoxCollider2DComponent>(75.0f, 5.0f, CollisionType::Static);
		upBoundaryColliderComp->SetEnableStaticSingleNormalVector(true, Vector2::down);
		upBoundaryEntity->AddComponent(upBoundaryColliderComp);
		upBoundaryEntity->transform->SetPosition(glm::vec3(0.0f, 27.5f, 0.0f));
		instantiateGameEntity(upBoundaryEntity, true);

		auto downBoundaryEntity = std::make_shared<GameEntity>();
		downBoundaryEntity->setName("left_boundary_collider_object");
		auto downBoundaryColliderComp = std::make_shared<BoxCollider2DComponent>(75.0f, 5.0f, CollisionType::Static);
		downBoundaryColliderComp->SetEnableStaticSingleNormalVector(true, Vector2::up);
		downBoundaryEntity->AddComponent(downBoundaryColliderComp);
		downBoundaryEntity->transform->SetPosition(glm::vec3(0.0f, -27.5f, 0.0f));
		instantiateGameEntity(downBoundaryEntity, true);

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
			isControllingBall = true;
		}
	}

	void BreakoutScene::handleOnBallReleasedKey()
	{
		LOG_INFO("Ball Released!");
		m_IsGameStarted = true;
		m_Ball->StartMovement(Vector3(0.4f, 1.0f, 0.0f));
	}

}
