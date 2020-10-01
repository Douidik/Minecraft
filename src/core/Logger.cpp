#include "Logger.h"

#include <spdlog/sinks/stdout_color_sinks.h>

std::shared_ptr<spdlog::logger> Logger::s_Logger;

void Logger::Initialize()
{
	try
	{
		spdlog::sink_ptr consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
		consoleSink->set_pattern("[%n at %T] %v");

		s_Logger = std::make_shared<spdlog::logger>("Minecraft", consoleSink);
		s_Logger->set_level(spdlog::level::trace);
	}
	catch(const spdlog::spdlog_ex &error)
	{
		std::cerr << error.what() << std::endl;
	}
}
