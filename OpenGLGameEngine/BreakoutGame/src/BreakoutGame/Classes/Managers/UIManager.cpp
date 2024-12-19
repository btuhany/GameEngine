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
		initPausePanelObjects();
		initLevelCompletedObjects();
	}
	void UIManager::Start()
	{
		startScoreText();
		startLevelText();
		startHeartSpriteEntities();
		startMainMenuPanelObjects();
		startPausePanelObjects();
		startLevelCompletedObjects();
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
	void UIManager::ShowPausePanel()
	{
		m_PauseText->getEntity().lock()->setActive(true);
	}
	void UIManager::HidePausePanel()
	{
		m_PauseText->getEntity().lock()->setActive(false);
	}
	void UIManager::ShowHelpPanel()
	{
	}
	void UIManager::initMainMenuPanelObjects()
	{
		auto backgroundTexture = std::make_shared<Texture>("src/BreakoutGame/Textures/button_square_gradient.PNG");
		backgroundTexture->LoadTextureWithAlpha();

		auto selectedSpriteTexture = std::make_shared<Texture>("src/BreakoutGame/Textures/button_square_line.PNG");
		selectedSpriteTexture->LoadTextureWithAlpha();

		m_StartButton = std::make_shared<UIButton>();
		m_StartButton->Initialize(m_UIScreenSpaceShader, m_TextShader, backgroundTexture, selectedSpriteTexture, "Start", Vector3(1.0f, 0.0f, 0.0f), Vector2(m_ViewPortWidth, m_ViewPortHeight) / 2.0f, Vector2(300.0f, 100.0f), m_ViewPortWidth, m_ViewPortHeight);
		auto startButtonEntities = m_StartButton->getEntities();
		m_GameEntityList.insert(m_GameEntityList.end(), startButtonEntities.begin(), startButtonEntities.end());

		float helpButtonOffset = 150.0f;
		m_HelpButton = std::make_shared<UIButton>();
		m_HelpButton->Initialize(m_UIScreenSpaceShader, m_TextShader, backgroundTexture, selectedSpriteTexture, "Help", Vector3(1.0f, 0.0f, 0.0f), Vector2(m_ViewPortWidth / 2.0f, m_ViewPortHeight / 2.0f - helpButtonOffset), Vector2(300.0f, 100.0f), m_ViewPortWidth, m_ViewPortHeight);
		auto helpButtonEntities = m_HelpButton->getEntities();
		m_GameEntityList.insert(m_GameEntityList.end(), helpButtonEntities.begin(), helpButtonEntities.end());

		float quitButtonOffset = 300.0f;
		m_QuitButton = std::make_shared<UIButton>();
		m_QuitButton->Initialize(m_UIScreenSpaceShader, m_TextShader, backgroundTexture, selectedSpriteTexture, "Quit", Vector3(1.0f, 0.0f, 0.0f), Vector2(m_ViewPortWidth / 2.0f, m_ViewPortHeight / 2.0f - quitButtonOffset), Vector2(300.0f, 100.0f), m_ViewPortWidth, m_ViewPortHeight);
		auto quitButtonEntities = m_QuitButton->getEntities();
		m_GameEntityList.insert(m_GameEntityList.end(), quitButtonEntities.begin(), quitButtonEntities.end());

		m_BreakoutText = std::make_shared<UITextRendererComponent>();
		m_BreakoutText->text = "Breakout!";
		m_BreakoutText->shader = m_TextShader;
		m_BreakoutText->textSize = TextSize::Large;
		m_BreakoutText->color = glm::vec3(1.0f, 0.0f, 0.0f);
		auto breakoutTextEntity = std::make_shared<GameEntity>();
		breakoutTextEntity->AddComponent(m_BreakoutText);
		m_GameEntityList.push_back(breakoutTextEntity);
	}
	void UIManager::startMainMenuPanelObjects()
	{
		m_StartButton->Start();
		m_HelpButton->Start();
		m_QuitButton->Start();

		float textOffsetY = 150.0f;
		m_BreakoutText->getEntity().lock()->transform->
			SetPosition(
				Vector3(
					(m_ViewPortWidth - m_BreakoutText->calculatedTextWidth) / 2.0f, 
					m_ViewPortHeight / 2.0f + textOffsetY, 
					0.0f));
	}
	void UIManager::initPausePanelObjects()
	{
		m_PauseText = std::make_shared<UITextRendererComponent>();
		m_PauseText->text = "Paused";
		m_PauseText->shader = m_TextShader;
		m_PauseText->textSize = TextSize::Large;
		m_PauseText->color = glm::vec3(1.0f, 0.0f, 0.0f);
		auto breakoutTextEntity = std::make_shared<GameEntity>();
		breakoutTextEntity->AddComponent(m_PauseText);
		m_GameEntityList.push_back(breakoutTextEntity);
	}
	void UIManager::startPausePanelObjects()
	{
		m_PauseText->getEntity().lock()->transform->
			SetPosition(
				Vector3(
					(m_ViewPortWidth - m_PauseText->calculatedTextWidth) / 2.0f,
					m_ViewPortHeight / 2.0f,
					0.0f));
	}
	void UIManager::initLevelCompletedObjects()
	{
		m_BreakoutCongratsText = std::make_shared<UITextRendererComponent>();
		m_BreakoutCongratsText->text = "Breakout!";
		m_BreakoutCongratsText->shader = m_TextShader;
		m_BreakoutCongratsText->textSize = TextSize::Large;
		m_BreakoutCongratsText->color = glm::vec3(0.0f, 0.0f, 1.0f);
		auto breakoutTextEntity = std::make_shared<GameEntity>();
		breakoutTextEntity->AddComponent(m_BreakoutCongratsText);
		m_GameEntityList.push_back(breakoutTextEntity);
	}
	void UIManager::startLevelCompletedObjects()
	{
		m_BreakoutCongratsText->getEntity().lock()->transform->
			SetPosition(
				Vector3(
					(m_ViewPortWidth - m_BreakoutCongratsText->calculatedTextWidth) / 2.0f,
					m_ViewPortHeight / 2.0f,
					0.0f));
	}
	void UIManager::HideHelpPanel()
	{
	}
	void UIManager::ShowMainMenuPanel()
	{
		m_BreakoutText->getEntity().lock()->setActive(true);
		m_StartButton->SetSelected(false);
		m_HelpButton->SetSelected(false);
		m_QuitButton->SetSelected(false);
	}
	void UIManager::HideMainMenuPanel()
	{
		m_BreakoutText->getEntity().lock()->setActive(false);
		m_StartButton->Hide();
		m_HelpButton->Hide();
		m_QuitButton->Hide();
	}
	void UIManager::ShowLevelCompletedPanel()
	{
		m_BreakoutCongratsText->getEntity().lock()->setActive(true);
	}
	void UIManager::HideLevelCompletedPanel()
	{
		m_BreakoutCongratsText->getEntity().lock()->setActive(false);
	}
	void UIManager::SelectMainMenuButton(MainMenuButtonType buttonType)
	{
		switch (buttonType)
		{
		case MainMenuButtonType::None:
			break;
		case MainMenuButtonType::Start:
			m_StartButton->SetSelected(true);
			m_HelpButton->SetSelected(false);
			m_QuitButton->SetSelected(false);
			break;
		case MainMenuButtonType::Help:
			m_StartButton->SetSelected(false);
			m_QuitButton->SetSelected(false);
			m_HelpButton->SetSelected(true);
			break;
		case MainMenuButtonType::Quit:
			m_StartButton->SetSelected(false);
			m_HelpButton->SetSelected(false);
			m_QuitButton->SetSelected(true);
			break;
		default:
			break;
		}
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