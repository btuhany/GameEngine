#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <functional>
#include "../Core.h"
namespace GameEngine
{
	class ENGINE_API Event {
	public:
		virtual ~Event() = default;
		virtual std::string GetName() const = 0;
	};

	struct Listener {
		std::function<void(std::shared_ptr<Event>)> Callback;
		int Priority;

		Listener(std::function<void(std::shared_ptr<Event>)> cb, int prio)
			: Callback(std::move(cb)), Priority(prio) {}
	};
}

