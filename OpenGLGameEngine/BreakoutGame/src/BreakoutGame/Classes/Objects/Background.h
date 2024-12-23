#pragma once
#include <GameEngine.h>
namespace BreakoutGame
{
	class Background
	{
	public:
		void Initialize();
		void Start();
		void Tick(float deltaTime);
		std::shared_ptr<GameEntity> getEntity();
	private:
		float m_TimeCounter;
		GLuint m_ShaderTimeLocation;
		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<GameEntity> m_Entity;
	};
}

