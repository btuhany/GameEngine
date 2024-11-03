#include "BreakoutScene.h"

namespace BreakoutGame
{
	BreakoutScene::BreakoutScene() : Scene()
	{
	}

	BreakoutScene::BreakoutScene(BreakoutSceneInputHandler* inputHandler) : Scene()
	{
		m_InputHandler = inputHandler;
		m_ObjectMoveSpeed = 5.0f;
	}

	BreakoutScene::~BreakoutScene()
	{
	}

	void BreakoutScene::Initialize()
	{
		initializeInputCallbacks();
		setCamera(std::make_shared<Camera>(
			glm::vec3(0.0f, 0.0f, 10.0f),
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

		for (size_t i = 0; i < 2; i++)
		{
			std::shared_ptr<SpriteEntity> spriteEntity = std::make_shared<SpriteEntity>(breakoutSpriteRenderData);
			std::string name = std::to_string(i) + ".Tile";
			spriteEntity->setName(name);
			spriteEntity->transform->SetPosition(glm::vec3(-3.0f + (i * 15.0f), 0.0f, 0.0f));
			auto boxCollider2DComp = std::make_shared<BoxCollider2DComponent>(6.0f, 2.0f, CollisionType::Static);
			spriteEntity->AddComponent<BoxCollider2DComponent>(boxCollider2DComp);
			instantiateGameEntity(spriteEntity);
		}

		m_SpriteEntity = std::make_shared<SpriteEntity>(breakoutSpriteRenderData2);
		m_SpriteEntity->setName("05-Breakout-Tiles obj");
		m_SpriteEntity->transform->SetPosition(glm::vec3(20.0f, -6.0f, 0.0f));
		auto collisionDetector = std::make_shared<CollisionDetector>();
		auto boxCollider2DComp2 = std::make_shared<BoxCollider2DComponent>(6.0f, 2.0f, CollisionType::Dynamic, collisionDetector);
		collisionDetector->AddCollisionCallback(CollisionState::Enter,
			[this](std::shared_ptr<ColliderComponent> collider) {
				if (!(collider->getEntity().expired()))
				{
					auto ownerEntity = collider->getEntity().lock();
					ownerEntity->setActive(false);
				}
			});
		m_SpriteEntity->AddComponent<BoxCollider2DComponent>(boxCollider2DComp2);
		instantiateGameEntity(m_SpriteEntity);

		m_Ball = std::make_shared<Ball>();
		m_Ball->Initialize(mainShader);
		auto ballEntity = m_Ball->getEntity();
		instantiateGameEntity(ballEntity);

		LOG_INFO("Breakout scene initialized!");
		Scene::Initialize();
	}

	void BreakoutScene::Start()
	{
		m_Ball->Start();
	}

	void BreakoutScene::Update(GLfloat deltaTime)
	{
		m_DeltaTime = deltaTime;
		m_Ball->Tick(deltaTime);
	}

	void BreakoutScene::initializeInputCallbacks()
	{
		m_InputHandler->OnPressedCameraTypeChangeKeyEvent.AddHandler(
			[this]() {
				//changeCameraType();
				for (size_t i = 0; i < m_GameEntities.size(); i++)
				{
					m_GameEntities[i]->setActive(true);
				}
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
		m_SpriteEntity->transform->Translate(glm::vec3(-(m_ObjectMoveSpeed * m_DeltaTime), 0.0f, 0.0f));
	}

	void BreakoutScene::handleOnRightKey()
	{
		m_SpriteEntity->transform->Translate(glm::vec3((m_ObjectMoveSpeed * m_DeltaTime), 0.0f, 0.0f));
	}

	void BreakoutScene::handleOnDownKey()
	{
		m_SpriteEntity->transform->Translate(glm::vec3(0.0f, -(m_ObjectMoveSpeed * m_DeltaTime), 0.0f));
	}

	void BreakoutScene::handleOnUpKey()
	{
		m_SpriteEntity->transform->Translate(glm::vec3(0.0f, (m_ObjectMoveSpeed * m_DeltaTime), 0.0f));
	}

}
