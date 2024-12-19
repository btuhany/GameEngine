#pragma once
#include "../Data/InputTypeEnum.h"
namespace BreakoutGame
{
	//TODO name refactor to state controller
	class InputController
	{
	public:
		virtual void HandleOnDeactivated() = 0;
		virtual void HandleOnActivated() = 0;
		virtual void HandleInputs(InputType inputType) = 0;
	};
}
