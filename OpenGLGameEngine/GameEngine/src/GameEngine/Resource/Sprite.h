#pragma once
#include "Core.h"
#include "IRenderable.h"

namespace GameEngine
{
	class ENGINE_API Sprite : public IRenderable
	{
	public:
		void Render() override;
	};
}