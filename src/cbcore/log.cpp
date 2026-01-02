//
// Created by noname on 31.03.2017.
//
module;

#include <format>

export module realn.codebox.core:log;

import :log.logger;
import :log.formatter;
import :log.formatter.plaintext;

namespace realn::cb {
    export void log(const log_level level, const std::string &msg) {
        if (const auto logger = logger::get_instance()) {
            logger->log_msg(level, msg);
        }
    }

    export template<class... Args>
    void log(const log_level level, const std::string &fmt, Args &&... args) {
        log(level, std::format(fmt, std::make_format_args(args...)));
    }

    export void debug(std::string const &msg) {
        log(log_level::Debug, msg);
    }

    export template<class... Args>
    void debug(const std::string &fmt, Args &&... args) {
        debug(std::format(fmt, std::make_format_args(args...)));
    }

    export void info(std::string const &msg) {
        log(log_level::Info, msg);
    }

    export template<class... Args>
    void info(const std::string &fmt, Args &&... args) {
        info(std::format(fmt, std::make_format_args(args...)));
    }

    export void warn(std::string const &msg) {
        log(log_level::Warning, msg);
    }

    export template<class... Args>
    void warn(const std::string &fmt, Args &&... args) {
        warn(std::format(fmt, std::make_format_args(args...)));
    }

    export void error(std::string const &msg) {
        log(log_level::Error, msg);
    }

    export template<class... Args>
    void error(const std::string &fmt, Args &&... args) {
        error(std::format(fmt, std::make_format_args(args...)));
    }

    export void crit(std::string const &msg) {
        log(log_level::Critical, msg);
    }

    export template<class... Args>
    void crit(const std::string &fmt, Args &&... args) {
        crit(std::format(fmt, std::make_format_args(args...)));
    }
}
