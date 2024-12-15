#include "UIManager.h"

namespace BreakoutGame
{
	void UIManager::Initialize(float viewPortWidth, float viewPortHeight)
	{
		m_ViewPortWidth = viewPortWidth;
		m_ViewPortHeight = viewPortHeight;

		m_TextShader = std::make_shared<Shader>();
		static const char* vTextShaderLocation = "src/BreakoutGame/Shaders/text_shader.vert";
		static const char* fTextShaderLocation = "src/BreakoutGame/Shaders/text_shader.frag";
		m_TextShader->CreateFromFiles(vTextShaderLocation, fTextShaderLocation);

		initScoreText();
		initLevelText();


		//static const char* vUIShaderLocation = "src/BreakoutGame/Shaders/ui_screen_space_shader.vert";
		//static const char* fUIShaderLocation = "src/BreakoutGame/Shaders/ui_screen_space_shader.frag";
		//std::shared_ptr<Shader> uiShader = std::make_shared<Shader>();
		//uiShader->CreateFromFiles(vUIShaderLocation, fUIShaderLocation);
		//std::shared_ptr<Texture> uiButtonPanelTex = std::make_shared<Texture>("src/BreakoutGame/Textures/button_ui_panel.PNG");
		//uiButtonPanelTex->LoadTextureWithAlpha();
		//auto uiEntity = std::make_shared<GameEntity>();
		//auto uiRenderData = std::make_shared<UIRenderData>(uiShader, uiButtonPanelTex);
		//auto uiRendererComp = std::make_shared<UIRendererComponent>();
		//uiRendererComp->setUIRenderData(uiRenderData);
		//uiEntity->AddComponent(uiRendererComp);
		//uiEntity->transform->Translate(glm::vec3(630.0f, 100.0f, -0.1f));
		//uiEntity->transform->Scale(glm::vec3(500.0f, 500.0f, 0.0f));
		//uiEntity->transform->Rotate(45.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		//m_GameEntityList.push_back(uiEntity);

	}
	void UIManager::SetScorePoint(int scorePoint)
	{
		m_ScoreCounterTextComponent->text = "Score: " + std::to_string(scorePoint);
	}
	std::vector<std::shared_ptr<GameEntity>> UIManager::getEntityList()
	{
		return m_GameEntityList;
	}
	void UIManager::Start()
	{
		startScoreText();
		startLevelText();
	}
	void UIManager::initScoreText()
	{
		auto textEntity = std::make_shared<GameEntity>();
		auto textComp = std::make_shared<UITextRendererComponent>();
		textComp->shader = m_TextShader;
		textComp->text = "Score: ";
		textComp->color = glm::vec3(1.0f, 1.0f, 0.1f);
		m_ScoreCounterTextComponent = textComp;
		textEntity->AddComponent(textComp);
		m_GameEntityList.push_back(textEntity);
	}
	void UIManager::startScoreText()
	{
		auto textEntity = m_ScoreCounterTextComponent->getEntity().lock();
		auto textWidth = m_ScoreCounterTextComponent->textWidth;
		float textExtraXOffset = - (textWidth / 3.0f);
		textEntity->transform->Translate(glm::vec3(((m_ViewPortWidth - textWidth) / 2.0f) + textExtraXOffset, m_ViewPortHeight - TEXT_MARGIN_TOP, 0.0f));
	}
	void UIManager::initLevelText()
	{
		auto textEntity = std::make_shared<GameEntity>();
		auto textComp = std::make_shared<UITextRendererComponent>();
		textComp->shader = m_TextShader;
		textComp->text = "Level: ";
		textComp->color = glm::vec3(0.2f, 1.0f, 0.1f);
		m_LevelTextComponent = textComp;
		textEntity->AddComponent(textComp);
		m_GameEntityList.push_back(textEntity);
	}
	void UIManager::startLevelText()
	{
		auto textEntity = m_LevelTextComponent->getEntity().lock();
		auto textWidth = m_LevelTextComponent->textWidth;
		float textXOffset = 50.0f;
		textEntity->transform->Translate(glm::vec3(textXOffset, m_ViewPortHeight - TEXT_MARGIN_TOP, 0.0f));
	}
}