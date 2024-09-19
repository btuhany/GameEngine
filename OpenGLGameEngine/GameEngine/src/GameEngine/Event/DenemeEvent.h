#pragma once
#include "Event.h"
namespace GameEngine
{
	class DenemeEvent : public Event
	{
	public:
		int denemeScore;
		int score;
		DenemeEvent() : denemeScore(0), score(0) {}
		DenemeEvent(int denemeScoref, int scoref) : denemeScore(denemeScoref), score(scoref) {}

		std::string GetName() const override;
	};
}

