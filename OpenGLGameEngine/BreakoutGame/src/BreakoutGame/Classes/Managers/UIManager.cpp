#include "UIManager.h"

namespace BreakoutGame
{
	void UIManager::Initialize(float viewPortWidth, float viewPortHeight, int initalScore, int initialLevel, int maxPlayerLive)
	{
		m_ViewPortWidth = viewPortWidth;
		m_ViewPortHeight = viewPortHeight;

		m_TextShader = std::make_shared<Shader>();
		static const char* vTextShaderLocation = "src/BreakoutGame/Shaders/text_shader.vert";
		static const char* fTextShaderLocation = "src/BreakoutGame/Shaders/text_shader.frag";
		m_TextShader->CreateFromFiles(vTextShaderLocation, fTextShaderLocation);

		m_UIScreenSpaceShader = std::make_shared<Shader>();
		static const char* vUIShaderLocation = "src/BreakoutGame/Shaders/ui_screen_space_shader.vert";
		static const char* fUIShaderLocation = "src/BreakoutGame/Shaders/ui_screen_space_shader.frag";
		m_UIScreenSpaceShader->CreateFromFiles(vUIShaderLocation, fUIShaderLocation);

		initScoreText(std::to_string(initalScore));
		initLevelText(std::to_string(initialLevel));
		initHeartSpriteEntities(maxPlayerLive);

		initMainMenuPanelObjects();
	}
	void UIManager::Start()
	{
		startScoreText();
		startLevelText();
		startHeartSpriteEntities();
		startMainMenuPanelObjects();
		ShowMainMenuPanel();
		m_BreakoutText->getEntity().lock()->transform->Scale(glm::vec3(4.0f, 4.0f, 0.0f));
		m_BreakoutText->getEntity().lock()->setActive(true);
	}
	void UIManager::ShowPlayerHUD(int playerLiveCount)
	{
		m_ScoreCounterTextComponent->getEntity().lock()->setActive(true);
		m_LevelTextComponent->getEntity().lock()->setActive(true);
		for (size_t i = 0; i < playerLiveCount; i++)
		{
			m_HeartSpriteEntities[i]->setActive(true);
		}
	}
	void UIManager::HidePlayerHUD()
	{
		m_ScoreCounterTextComponent->getEntity().lock()->setActive(false);
		m_LevelTextComponent->getEntity().lock()->setActive(false);
		for (size_t i = 0; i < m_HeartSpriteEntities.size(); i++)
		{
			m_HeartSpriteEntities[i]->setActive(false);
		}
	}
	void UIManager::initMainMenuPanelObjects()
	{
		auto backgroundTexture = std::make_shared<Texture>("src/BreakoutGame/Textures/button_square_gradient.PNG");
		backgroundTexture->LoadTextureWithAlpha();

		auto selectedSpriteTexture = std::make_shared<Texture>("src/BreakoutGame/Textures/button_square_line.PNG");
		selectedSpriteTexture->LoadTextureWithAlpha();

		m_StartButton = std::make_shared<UIButton>();
		m_StartButton->Initialize(m_UIScreenSpaceShader, m_TextShader, backgroundTexture, selectedSpriteTexture, "Start", Vector3(1.0f, 0.0f, 0.0f), Vector2(m_ViewPortWidth, m_ViewPortHeight) / 2.0f, Vector2(300.0f, 100.0f), m_ViewPortWidth, m_ViewPortHeight);
		auto newEntityList = m_StartButton->getEntities();
		m_GameEntityList.insert(m_GameEntityList.end(), newEntityList.begin(), newEntityList.end());

		m_BreakoutText = std::make_shared<UITextRendererComponent>();
		m_BreakoutText->text = "Breakout!";
		m_BreakoutText->shader = m_TextShader;
		m_BreakoutText->color = glm::vec3(1.0f, 0.0f, 0.0f);
		auto breakoutTextEntity = std::make_shared<GameEntity>();
		breakoutTextEntity->AddComponent(m_BreakoutText);
		breakoutTextEntity->transform->SetPosition(Vector3(m_ViewPortWidth / 2.0f, m_ViewPortHeight / 2.0f + 300.0f, 0.0f));
		m_GameEntityList.push_back(breakoutTextEntity);
	}
	void UIManager::startMainMenuPanelObjects()
	{
		m_StartButton->Start();
	}
	void UIManager::ShowMainMenuPanel()
	{
		m_StartButton->SetSelected(false);
	}
	void UIManager::HideMainMenuPanel()
	{
	}
	void UIManager::SetScorePoint(int scorePoint)
	{
		m_ScoreCounterTextComponent->text = "Score: " + std::to_string(scorePoint);
	}
	std::vector<std::shared_ptr<GameEntity>> UIManager::getEntityList()
	{
		return m_GameEntityList;
	}
	void UIManager::initScoreText(std::string initialScoreStr)
	{
		auto textEntity = std::make_shared<GameEntity>();
		auto textComp = std::make_shared<UITextRendererComponent>();
		textComp->shader = m_TextShader;
		textComp->text = "Score: " + initialScoreStr;
		textComp->color = glm::vec3(1.0f, 1.0f, 0.1f);
		m_ScoreCounterTextComponent = textComp;
		textEntity->AddComponent(textComp);
		m_GameEntityList.push_back(textEntity);
	}
	void UIManager::startScoreText()
	{
		auto textEntity = m_ScoreCounterTextComponent->getEntity().lock();
		auto textWidth = m_ScoreCounterTextComponent->calculatedTextWidth;
		float textExtraXOffset = - (textWidth / 3.0f);
		textEntity->transform->Translate(glm::vec3(((m_ViewPortWidth - textWidth) / 2.0f) + textExtraXOffset, m_ViewPortHeight - MARGIN_TOP, 0.0f));
	}
	void UIManager::initLevelText(std::string initialLevelStr)
	{
		auto textEntity = std::make_shared<GameEntity>();
		auto textComp = std::make_shared<UITextRendererComponent>();
		textComp->shader = m_TextShader;
		textComp->text = "Level: " + initialLevelStr;
		textComp->color = glm::vec3(0.2f, 1.0f, 0.1f);
		m_LevelTextComponent = textComp;
		textEntity->AddComponent(textComp);
		m_GameEntityList.push_back(textEntity);
	}
	void UIManager::startLevelText()
	{
		auto textEntity = m_LevelTextComponent->getEntity().lock();
		auto textWidth = m_LevelTextComponent->calculatedTextWidth;
		float textXOffset = MARGIN_LEFT;
		textEntity->transform->Translate(glm::vec3(textXOffset, m_ViewPortHeight - MARGIN_TOP, 0.0f));
	}
	void UIManager::initHeartSpriteEntities(int liveCount)
	{
		std::shared_ptr<Texture> heartTexture = std::make_shared<Texture>("src/BreakoutGame/Textures/60-Breakout-Tiles.PNG");
		heartTexture->LoadTextureWithAlpha();

		float width = 50.0f;
		float spacingX = 5.0f;
		float spacingY = 0.0f;
		float localOffsetY = 10.0f;
		float totalWidth = (width + spacingX) * liveCount;
		float startPointX = m_ViewPortWidth - totalWidth - MARGIN_RIGHT;
		float startPointY = m_ViewPortHeight - MARGIN_TOP - localOffsetY;

		for (size_t i = 0; i < liveCount; i++)
		{
			auto uiEntity = std::make_shared<GameEntity>();
			auto uiRenderData = std::make_shared<UIRenderData>(m_UIScreenSpaceShader, heartTexture);
			auto uiRendererComp = std::make_shared<UIRendererComponent>();
			uiRendererComp->setUIRenderData(uiRenderData);
			uiEntity->AddComponent(uiRendererComp);
			uiEntity->transform->Translate(glm::vec3(startPointX + i * (width + spacingX), startPointY, 0.0f));
			uiEntity->transform->Scale(glm::vec3(width, width, 1.0f));
			m_HeartSpriteEntities.push_back(uiEntity);
			m_GameEntityList.push_back(uiEntity);
		}
	}
	void UIManager::startHeartSpriteEntities()
	{
	}

}