#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"
namespace GameEngine {

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	Log::Log()
	{
	}
	Log::~Log()
	{
	}
	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_CoreLogger = spdlog::stderr_color_mt("\nENGINE");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stderr_color_mt("\nSCENE");
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}