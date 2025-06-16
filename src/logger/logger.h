#pragma once

#include <glm/ext/vector_float3.hpp>
#include <memory>
#include <fstream>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/ostream_sink.h>

class Logger {
public:
    static void init(const std::string& logfile = "logs/log.txt") {
        if (s_Logger) return;

        // Open /dev/tty to write directly to terminal
        static auto tty_stream = std::make_shared<std::ofstream>("/dev/tty");
        auto tty_sink = std::make_shared<spdlog::sinks::ostream_sink_mt>(*tty_stream, true);

        auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(logfile, true);

        s_Logger = std::make_shared<spdlog::logger>("gentracer", spdlog::sinks_init_list{ tty_sink, file_sink });
        s_Logger->set_level(spdlog::level::trace);
        spdlog::set_default_logger(s_Logger);
    }

    static std::shared_ptr<spdlog::logger>& get() { return s_Logger; }

private:
    static std::shared_ptr<spdlog::logger> s_Logger;
};


template <>
struct fmt::formatter<glm::vec3> {
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

    template <typename FormatContext>
    auto format(const glm::vec3& v, FormatContext& ctx) {
        return format_to(ctx.out(), "({}, {}, {})", v.x, v.y, v.z);
    }
};

// Logging macros
#define LOG_TRACE(...)    ::Logger::get()->trace(__VA_ARGS__)
#define LOG_DEBUG(...)    ::Logger::get()->debug(__VA_ARGS__)
#define LOG_INFO(...)     ::Logger::get()->info(__VA_ARGS__)
#define LOG_WARN(...)     ::Logger::get()->warn(__VA_ARGS__)
#define LOG_ERROR(...)    ::Logger::get()->error(__VA_ARGS__)
#define LOG_CRITICAL(...) ::Logger::get()->critical(__VA_ARGS__)

