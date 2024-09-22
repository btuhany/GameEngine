#pragma once
#include <string>
#include <typeindex>
#include <vector>
#include <unordered_map>
#include <memory>
#include <functional>
#include "../Core.h"
namespace GameEngine
{
	class ENGINE_API IEvent {
	public:
		virtual ~IEvent() = default;
		virtual std::type_index GetType() const = 0;
	};

	template<typename DerivedEvent>
	class EventBase : public IEvent {
	public:
		static std::type_index GetStaticType() {
			return std::type_index(typeid(DerivedEvent));
		}

		virtual std::type_index GetType() const override {
			return GetStaticType();
		}
	};

	struct Listener {
		std::function<void(std::shared_ptr<IEvent>)> Callback;
		int Priority;

		Listener(std::function<void(std::shared_ptr<IEvent>)> cb, int prio)
			: Callback(std::move(cb)), Priority(prio) {}
	};
}

