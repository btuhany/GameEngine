#pragma once
#include "../Data/InputTypeEnum.h"
namespace BreakoutGame
{
	class InputController
	{
	public:
		virtual void HandleInputs(InputType inputType) = 0;
	};
}
