#pragma once
#include <GameEngine.h>
namespace BreakoutGame
{
	class UIButton
	{
	public:
		void Initialize(std::shared_ptr<Shader> uiShader, std::shared_ptr<Shader> textShader, std::shared_ptr<Texture> backgroundTex, std::shared_ptr<Texture> selectedTex, std::string text, Vector3 textColor, Vector2 posVal, Vector2 scaleVal, float viewPortWidth, float viewPortHeight);
		void Start();
		void SetSelected(bool isSelected);
		void Hide();
		std::vector<std::shared_ptr<GameEntity>> getEntities();
		Vector2 pos;
		Vector2 scale;
	private:
		float m_ViewPortWidth;
		float m_ViewPortHeight;
		std::shared_ptr<GameEntity> m_SelectedStateEntity;
		std::shared_ptr<GameEntity> m_BackgroundSpriteEntity;
		std::shared_ptr<UITextRendererComponent> m_TextComp;
		std::vector<std::shared_ptr<GameEntity>> m_GameEntites;
	};
}


