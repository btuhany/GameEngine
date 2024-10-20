#pragma once
#pragma once
#include "../Core.h"
#include "../Components/Component.h"
#include "Event.h"
#include "../Scene/Camera.h"
namespace GameEngine
{
	class ENGINE_API SceneCameraChangedEvent : public EventBase<SceneCameraChangedEvent>
	{
	public:
		std::shared_ptr<Camera> camera;
	};
}