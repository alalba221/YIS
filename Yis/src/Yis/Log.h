#pragma once
#include <memory>
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
namespace Yis {
	class YIS_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; };
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; };
	private:

		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

#define YS_CORE_TRACE(...) ::Yis::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define YS_CORE_INFO(...) ::Yis::Log::GetCoreLogger()->info(__VA_ARGS__)
#define YS_CORE_WARN(...) ::Yis::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define YS_CORE_ERROR(...) ::Yis::Log::GetCoreLogger()->error(__VA_ARGS__)
#define YS_CORE_FATAL(...) ::Yis::Log::GetCoreLogger()->fatal(__VA_ARGS__)


#define YS_APP_TRACE(...) ::Yis::Log::GetClientLogger()->trace(__VA_ARGS__)
#define YS_APP_INFO(...) ::Yis::Log::GetClientLogger()->info(__VA_ARGS__)
#define YS_APP_WARN(...) ::Yis::Log::GetClientLogger()->warn(__VA_ARGS__)
#define YS_APP_ERROR(...) ::Yis::Log::GetClientLogger()->error(__VA_ARGS__)
#define YS_APP_FATAL(...) ::Yis::Log::GetClientLogger()->fatal(__VA_ARGS__)