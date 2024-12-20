#include "UIButton.h"
namespace BreakoutGame
{
	void UIButton::Initialize(std::shared_ptr<Shader> uiShader, std::shared_ptr<Shader> textShader, std::shared_ptr<Texture> backgroundTex, std::shared_ptr<Texture> selectedTex, std::string text, Vector3 textColor, Vector2 posVal, Vector2 scaleVal, float viewPortWidth, float viewPortHeight)
	{
		pos = posVal;
		scale = scaleVal;
		m_ViewPortWidth = viewPortWidth;
		m_ViewPortHeight = viewPortHeight;
		m_BackgroundSpriteEntity = std::make_shared<GameEntity>();
		auto spriteComp = std::make_shared<UIRendererComponent>();
		spriteComp->setUIRenderData(std::make_shared<UIRenderData>(uiShader, backgroundTex));
		m_BackgroundSpriteEntity->AddComponent(spriteComp);

		m_SelectedStateEntity = std::make_shared<GameEntity>();
		auto selectedSpriteComp = std::make_shared<UIRendererComponent>();
		selectedSpriteComp->setUIRenderData(std::make_shared<UIRenderData>(uiShader, selectedTex));
		m_SelectedStateEntity->AddComponent(selectedSpriteComp);

		auto textEntity = std::make_shared<GameEntity>();
		m_TextComp = std::make_shared<UITextRendererComponent>();
		m_TextComp->shader = textShader;
		m_TextComp->text = text;
		m_TextComp->color = glm::vec3(textColor.x, textColor.y, textColor.z);

		textEntity->AddComponent(m_TextComp);

		m_GameEntites.push_back(m_SelectedStateEntity);
		m_GameEntites.push_back(m_BackgroundSpriteEntity);
		m_GameEntites.push_back(textEntity);
	}
	void UIButton::Start()
	{
		auto textEntity = m_TextComp->getEntity().lock();
		float textWidth = m_TextComp->calculatedTextWidth;
		float textHeight = m_TextComp->calculatedTextHeight;
		float scaleX = scale.x;
		float scaleY = scale.y;
		float posX = pos.x - scaleX / 2.0f;
		float posY = pos.y - scaleY / 2.0f;
		m_BackgroundSpriteEntity->transform->SetPosition(glm::vec3(posX, posY, -0.5f));
		m_BackgroundSpriteEntity->transform->Scale(scaleX, scaleY, 1.0f);
		m_SelectedStateEntity->transform->SetPosition(glm::vec3(posX, posY, -0.4f));
		m_SelectedStateEntity->transform->Scale(scaleX, scaleY, 1.0f);
		textEntity->transform->SetPosition(glm::vec3(posX + (scaleX - textWidth) / 2.0f, posY + (scaleY - textHeight) / 2.0f, 0.0f));
	}
	void UIButton::SetSelected(bool isSelected)
	{
		m_BackgroundSpriteEntity->setActive(!isSelected);
		m_SelectedStateEntity->setActive(isSelected);
		m_TextComp->getEntity().lock()->setActive(true);
	}
	void UIButton::UpdateText(std::string text)
	{
		m_TextComp->text = text;
		TextRenderer::CalculateTextWidthAndHeight(m_TextComp);
		auto textEntity = m_TextComp->getEntity().lock();
		float textWidth = m_TextComp->calculatedTextWidth;
		float textHeight = m_TextComp->calculatedTextHeight;
		float scaleX = scale.x;
		float scaleY = scale.y;
		float posX = pos.x - scaleX / 2.0f;
		float posY = pos.y - scaleY / 2.0f;
		textEntity->transform->SetPosition(glm::vec3(posX + (scaleX - textWidth) / 2.0f, posY + (scaleY - textHeight) / 2.0f, 0.0f));
	}
	void UIButton::Hide()
	{
		m_BackgroundSpriteEntity->setActive(false);
		m_SelectedStateEntity->setActive(false);
		m_TextComp->getEntity().lock()->setActive(false);
	}
	std::vector<std::shared_ptr<GameEntity>> UIButton::getEntities()
	{
		return m_GameEntites;
	}
}
