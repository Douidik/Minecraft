#ifndef MINECRAFT_LOGGER_H
#define MINECRAFT_LOGGER_H

#include <memory>
#include <spdlog/spdlog.h>

class Logger
{
public:
	static void Initialize();
	static std::shared_ptr<spdlog::logger> Get()
	{
		return s_Logger;
	}

private:
	static std::shared_ptr<spdlog::logger> s_Logger;
};

/* Logging macros */

#define MC_LOG_TRACE(...) Logger::Get()->trace(__VA_ARGS__)
#define MC_LOG_DEBUG(...) Logger::Get()->debug(__VA_ARGS__)
#define MC_LOG_INFO(...)  Logger::Get()->info (__VA_ARGS__)
#define MC_LOG_WARN(...)  Logger::Get()->warn (__VA_ARGS__)
#define MC_LOG_ERROR(...) Logger::Get()->error(__VA_ARGS__)

#endif //MINECRAFT_LOGGER_H