#pragma once
namespace BreakoutGame
{
	class IMovable
	{
	public:
		virtual void MoveLeft() = 0;
		virtual void MoveRight() = 0;
		virtual void MoveUp() = 0;
		virtual void MoveDown() = 0;
	protected:
		float m_Speed = 0.01f;
	};
}

