//
// Created by noname on 31.03.2017.
//
module;

#include <iostream>
#include <memory>
#include <unordered_map>

export module realn.codebox.core:log.logger;

import :log.formatter;
import :log.formatter.plaintext;

namespace realn::cb {
    export class logger final {
        using stream_item = std::shared_ptr<std::ostream>;
        using stream_formatter = std::unique_ptr<log_formatter>;
        using stream_map = std::unordered_map<stream_item, stream_formatter>;

        stream_map m_stream_map;

        static std::weak_ptr<logger> m_instance;

    public:
        // explicit logger(std::ostream &base_out_stream);

        void add_stream(const std::shared_ptr<std::ostream> &stream);

        void add_stream(const std::shared_ptr<std::ostream> &stream, std::unique_ptr<log_formatter> formatter);

        void clear_streams();

        void begin_log(const std::string &msg = {}) const;

        void log_msg(log_level level, const std::string &msg) const;

        void end_log(std::string const &msg = {}) const;
        //
        static void set_instance(const std::shared_ptr<logger> &logger);

        static std::shared_ptr<logger> get_instance();
    };

    std::weak_ptr<logger> logger::m_instance;

    /*
     * on GCC 15.2 this ends with an internal compiler segmentation fault
     */
    // logger::logger(std::ostream &base_out_stream) {
    //     const auto stream_ptr = std::shared_ptr<std::ostream>({
    //         &base_out_stream, [](std::ostream *) {
    //         }
    //     });
    //     add_stream(stream_ptr);
    // }

    void logger::add_stream(const std::shared_ptr<std::ostream> &stream) {
        m_stream_map[stream] = std::make_unique<plain_text_log_formatter>();
    }

    void logger::add_stream(const std::shared_ptr<std::ostream> &stream,
                            std::unique_ptr<log_formatter> formatter) {
        m_stream_map[stream] = std::move(formatter);
    }

    void logger::clear_streams() {
        m_stream_map.clear();
    }

    void logger::begin_log(const std::string &msg) const {
        for (const auto &[stream, formatter]: m_stream_map) {
            formatter->begin_log(*stream, msg);
        }
    }

    void logger::log_msg(const log_level level, const std::string &msg) const {
        for (const auto &[stream, formatter]: m_stream_map) {
            formatter->log_msg(*stream, level, msg);
        }
    }

    void logger::end_log(const std::string &msg) const {
        for (const auto &[stream, formatter]: m_stream_map) {
            formatter->end_log(*stream, msg);
        }
    }

    void logger::set_instance(const std::shared_ptr<logger> &logger) {
        m_instance = logger;
    }

    std::shared_ptr<logger> logger::get_instance() {
        return m_instance.lock();
    }
}
