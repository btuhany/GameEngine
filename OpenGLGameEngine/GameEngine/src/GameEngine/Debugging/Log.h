#pragma once
#include "../Core.h"
#include <memory>
#include "spdlog/spdlog.h"
namespace GameEngine {
	class ENGINE_API Log
	{
	public:
		Log();
		~Log();
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core Logging
#define LOG_CORE_TRACE(...)		GameEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define LOG_CORE_INFO(...)		GameEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define LOG_CORE_WARN(...)		GameEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LOG_CORE_ERROR(...)		GameEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
//#define LOG_CORE_FATAL(...)		::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client logging
#define LOG_TRACE(...)		::Log::GetClientLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...)		::Log::GetClientLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)		::Log::GetClientLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)		::Log::GetClientLogger()->error(__VA_ARGS__)
//#define LOG_FATAL(...)		::Log::GetClientLogger()->fatal(__VA_ARGS__)


#define LOG_INFO_STREAM(content)                          \
    {                                                     \
        std::ostringstream oss;                           \
        oss << content;                                   \
        LOG_INFO(oss.str());                              \
    }
#define LOG_CORE_INFO_STREAM(content)                          \
    {                                                     \
        std::ostringstream oss;                           \
        oss << content;                                   \
        LOG_CORE_INFO(oss.str());                              \
    }