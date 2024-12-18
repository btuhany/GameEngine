#pragma once
#include "../Data/InputTypeEnum.h"
namespace BreakoutGame
{
	class InputController
	{
	public:
		virtual void HandleOnActivated() = 0;
		virtual void HandleInputs(InputType inputType) = 0;
	};
}
