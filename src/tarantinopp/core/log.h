#pragma once

#include <vector>

#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

namespace tarantinopp {
enum LogLevel : int {
  trace = spdlog::level::trace,
  debug = spdlog::level::debug,
  info = spdlog::level::info,
  warn = spdlog::level::warn,
  err = spdlog::level::err,
  critical = spdlog::level::critical,
  off = spdlog::level::off
};

class Logger {
 public:
  Logger(std::string name, LogLevel level) {
    m_name = name;
    m_level = level;

    std::vector<spdlog::sink_ptr> sinks;
    sinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
    sinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>(
        "tarantino.log", true));

    sinks[0]->set_pattern("%^[%c][%l] %n - %v%$");
    sinks[1]->set_pattern("[%c][%l] %n - %v");

    m_logger =
        std::make_shared<spdlog::logger>(m_name, sinks.begin(), sinks.end());
    spdlog::register_logger(m_logger);
    m_logger->set_level(spdlog::level::level_enum(m_level));
    m_logger->flush_on(spdlog::level::level_enum(m_level));
  }

  template <typename... Args>
  void trace(spdlog::format_string_t<Args...> fmt, Args &&...args) {
    m_logger->trace(fmt, args...);
  }

  template <typename... Args>
  void debug(spdlog::format_string_t<Args...> fmt, Args &&...args) {
    m_logger->debug(fmt, args...);
  }

  template <typename... Args>
  void info(spdlog::format_string_t<Args...> fmt, Args &&...args) {
    m_logger->info(fmt, args...);
  }

  template <typename... Args>
  void warn(spdlog::format_string_t<Args...> fmt, Args &&...args) {
    m_logger->warn(fmt, args...);
  }

  template <typename... Args>
  void error(spdlog::format_string_t<Args...> fmt, Args &&...args) {
    m_logger->error(fmt, args...);
  }

  template <typename... Args>
  void critical(spdlog::format_string_t<Args...> fmt, Args &&...args) {
    m_logger->critical(fmt, args...);
  }

 private:
  std::shared_ptr<spdlog::logger> m_logger;
  std::string m_name;
  LogLevel m_level;
};
}  // namespace tarantinopp