#include "UIManager.h"

namespace BreakoutGame
{
	void UIManager::Initialize()
	{
		auto scoreTextEntity = std::make_shared<GameEntity>();
		static const char* vTextShaderLocation = "src/BreakoutGame/Shaders/text_shader.vert";
		static const char* fTextShaderLocation = "src/BreakoutGame/Shaders/text_shader.frag";
		std::shared_ptr<Shader> textShader = std::make_shared<Shader>();
		textShader->CreateFromFiles(vTextShaderLocation, fTextShaderLocation);
		auto textComp = std::make_shared<UITextRendererComponent>();
		textComp->shader = textShader;
		textComp->text = "ABBA";
		textComp->color = glm::vec3(0.6f, 0.1f, 0.5f);
		m_ScoreCounterTextComponent = textComp;
		scoreTextEntity->AddComponent(textComp);
		scoreTextEntity->transform->Translate(glm::vec3(100.0f, 150.0f, -0.2f));
		m_GameEntityList.push_back(scoreTextEntity);



		static const char* vUIShaderLocation = "src/BreakoutGame/Shaders/ui_shader.vert";
		static const char* fUIShaderLocation = "src/BreakoutGame/Shaders/ui_shader.frag";
		std::shared_ptr<Shader> uiShader = std::make_shared<Shader>();
		uiShader->CreateFromFiles(vUIShaderLocation, fUIShaderLocation);
		std::shared_ptr<Texture> uiButtonPanelTex = std::make_shared<Texture>("src/BreakoutGame/Textures/button_ui_panel.PNG");
		uiButtonPanelTex->LoadTextureWithAlpha();
		auto uiEntity = std::make_shared<GameEntity>();
		auto uiRenderData = std::make_shared<UIRenderData>(uiShader, uiButtonPanelTex);
		auto uiRendererComp = std::make_shared<UIRendererComponent>();
		uiRendererComp->setUIRenderData(uiRenderData);
		uiEntity->AddComponent(uiRendererComp);
		uiEntity->transform->Translate(glm::vec3(630.0f, 100.0f, -0.1f));
		uiEntity->transform->Scale(glm::vec3(500.0f, 500.0f, 0.0f));
		uiEntity->transform->Rotate(45.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		m_GameEntityList.push_back(uiEntity);
	}
	std::vector<std::shared_ptr<GameEntity>> UIManager::getEntityList()
	{
		return m_GameEntityList;
	}
}