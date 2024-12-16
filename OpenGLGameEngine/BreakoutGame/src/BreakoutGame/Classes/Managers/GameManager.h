#pragma once
namespace BreakoutGame
{
	class GameManager
	{
	public:
		void Initialize();
		void Start();
		void IncreaseScorePoint(int value);
		int GetScorePoint();
		bool isGameStarted;
	private:
		int m_ScorePoint;
	};
}


