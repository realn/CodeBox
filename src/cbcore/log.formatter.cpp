//
// Created by noname on 31.12.2025.
//

module;

#include <iostream>

export module realn.codebox.core:log.formatter;

import :file;

namespace realn::cb {
    export enum class log_level {
        Debug = -1,
        Info = 0,
        Warning = 1,
        Error = 2,
        Critical = 3,
    };

    export class log_formatter {
    protected:
        log_formatter() = default;

    public:
        virtual ~log_formatter() = default;

        virtual void begin_log(std::ostream &stream, const std::string &msg) = 0;

        virtual void end_log(std::ostream &stream, const std::string &msg) = 0;

        virtual void log_msg(std::ostream &stream, log_level level, const std::string &msg) = 0;
    };
}
