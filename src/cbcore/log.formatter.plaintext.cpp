//
// Created by noname on 31.03.2017.
//

module;

#include <chrono>
#include <format>

export module realn.codebox.core:log.formatter.plaintext;

import :log.formatter;

namespace realn::cb {
    std::string get_time_stamp() {
        auto time = std::chrono::system_clock::now();
        return std::format("{0:%Y.%m.%d|%H:%M:%S}", time);
    }

    constexpr std::string_view to_string(const log_level level) {
        switch (level) {
            case log_level::Debug: return "DBG";
            case log_level::Info: return "INF";
            case log_level::Warning: return "WRN";
            case log_level::Error: return "ERR";
            case log_level::Critical: return "CRI";
            default: return "MSN";
        }
    }

    export class plain_text_log_formatter final : public log_formatter {
    public:
        plain_text_log_formatter() = default;

        // Inherited via ILogFormat
        void begin_log(std::ostream &stream, std::string const &msg) override;

        void end_log(std::ostream &stream, std::string const &msg) override;

        void log_msg(std::ostream &stream, log_level level, const std::string &msg) override;
    };

    void plain_text_log_formatter::begin_log(std::ostream &stream, const std::string &msg) {
        stream << get_time_stamp() << " LOG START: " << msg << std::endl;
    }

    void plain_text_log_formatter::end_log(std::ostream &stream, const std::string &msg) {
        stream << get_time_stamp() << " LOG END" << msg << std::endl;
    }

    void plain_text_log_formatter::log_msg(std::ostream &stream, const log_level level, const std::string &msg) {
        stream << get_time_stamp() << " " << to_string(level) << " " << msg << std::endl;
    }
}
