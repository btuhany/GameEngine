#pragma once
#include "../Core.h"

namespace GameEngine
{
	class ENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();
		virtual void Run();
	};

	Application* CreateApplication();
}
