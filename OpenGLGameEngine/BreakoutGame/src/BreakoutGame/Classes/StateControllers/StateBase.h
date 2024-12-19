#pragma once
#include "../Data/InputTypeEnum.h"
namespace BreakoutGame
{
	//TODO name refactor to state controller
	class StateBase
	{
	public:
		virtual void HandleOnDeactivated() = 0;
		virtual void HandleOnActivated() = 0;
		virtual void HandleInputs(InputType inputType) = 0;
		virtual void Tick(float deltaTime) = 0;
		virtual void Start() = 0;
	};
}
