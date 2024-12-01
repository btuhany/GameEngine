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


		static const char* vUIShaderLocation = "src/BreakoutGame/Shaders/ui_shader.vert";
		static const char* fUIShaderLocation = "src/BreakoutGame/Shaders/ui_shader.frag";
		std::shared_ptr<Shader> uiShader = std::make_shared<Shader>();
		uiShader->CreateFromFiles(vUIShaderLocation, fUIShaderLocation);
		//std::shared_ptr<Texture> uiButtonPanelTex = std::make_shared<Texture>("src/BreakoutGame/Textures/button_ui_panel.PNG");
		//uiButtonPanelTex->LoadTextureWithAlpha();
		//auto uiRenderData = std::make_shared<UIRenderData>(uiShader, uiButtonPanelTex);
		//auto uiEntity = std::make_shared<UIEntity>(uiRenderData);
		//uiEntity->transform->Translate(glm::vec3(1000.0f, 100.0f, 0.0f));
		//uiEntity->transform->Scale(glm::vec3(600.0f, 500.0f, 0.0f));
		//uiEntity->transform->Rotate(45.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		//instantiateGameEntity(uiEntity);


		/*static const char* vUIShaderLocation = "src/BreakoutGame/Shaders/text_shader.vert";
		static const char* fUIShaderLocation = "src/BreakoutGame/Shaders/text_shader.frag";*/
		std::shared_ptr<Shader> textShader = std::make_shared<Shader>();
		textShader->CreateFromFiles(vUIShaderLocation, fUIShaderLocation);
		auto textEntity = std::make_shared<UITextEntity>();
		auto textComp = std::make_shared<UITextRendererComponent>();
		textComp->shader = textShader;
		textComp->text = "HAHAHAHA";
		textEntity->AddComponent(textComp);
		instantiateGameEntity(textEntity);



		m_Ball = std::make_shared<Ball>();
		m_Ball->Initialize(mainShader);
		auto ballEntity = m_Ball->getEntity();
		instantiateGameEntity(ballEntity);

		LOG_INFO("Breakout scene initialized!");
		Scene::Initialize();
	}

	void BreakoutScene::Start()
	{
		m_ControlledObject = m_Paddle;
		m_Ball->Start();
		m_Paddle->Start();
	}

	void BreakoutScene::Update(GLfloat deltaTime)
	{
		m_DeltaTime = deltaTime;
		m_Ball->Tick(deltaTime);
		m_Paddle->Tick(deltaTime);
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
		m_ControlledObject->MoveLeft();
	}

	void BreakoutScene::handleOnRightKey()
	{
		m_ControlledObject->MoveRight();
	}

	void BreakoutScene::handleOnDownKey()
	{
		m_ControlledObject->MoveDown();
	}

	void BreakoutScene::handleOnUpKey()
	{
		m_ControlledObject->MoveUp();
	}

	bool isControllingBall = false;
	void BreakoutScene::handleOnBallDebugKey()
	{
		if (isControllingBall)
		{
			m_ControlledObject = m_Paddle;
			isControllingBall = false;
		}
		else
		{
			m_ControlledObject = m_Ball;
			isControllingBall = true;
		}
	}

}
