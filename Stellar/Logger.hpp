#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__
#include "Base.hpp"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <filesystem>
#include "SDL2/SDL_assert.h"

#define STELLAR_CORE_LOGGER_NAME "Stellar"

class Logger {
public:
  static void OnCreate();
  static auto GetLogger() { return m_Logger; }
  static bool IsCreated() {return m_Created;}
  
private:
  Logger() = default;
  ~Logger() {spdlog::shutdown();}
  
private:
  static Base::Ref<spdlog::logger> m_Logger;
  static bool m_Created;
};

#define STELLAR_CORE_TRACE(...)    if(spdlog::get(STELLAR_CORE_LOGGER_NAME) != nullptr) spdlog::get(STELLAR_CORE_LOGGER_NAME)->trace(__VA_ARGS__) 
#define STELLAR_CORE_INFO(...)     if(spdlog::get(STELLAR_CORE_LOGGER_NAME) != nullptr) spdlog::get(STELLAR_CORE_LOGGER_NAME)->info(__VA_ARGS__)
#define STELLAR_CORE_WARN(...)     if(spdlog::get(STELLAR_CORE_LOGGER_NAME) != nullptr) spdlog::get(STELLAR_CORE_LOGGER_NAME)->warn(__VA_ARGS__)
#define STELLAR_CORE_ERROR(...)    if(spdlog::get(STELLAR_CORE_LOGGER_NAME) != nullptr) spdlog::get(STELLAR_CORE_LOGGER_NAME)->error(__VA_ARGS__)
#define STELLAR_CORE_CRITICAL(...) if(spdlog::get(STELLAR_CORE_LOGGER_NAME) != nullptr) spdlog::get(STELLAR_CORE_LOGGER_NAME)->critical(__VA_ARGS__)

#define STELLAR_FILENAME std::filesystem::path(__FILE__).filename().string()
#define STELLAR_LINE __LINE__

#define STELLAR_ASSERT(pred,msg,...) if(!(pred)){STELLAR_CORE_ERROR(msg,__VA_ARGS__); SDL_TriggerBreakpoint();}

#endif //!__LOGGER_HPP__