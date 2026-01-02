//
// Created by noname on 31.03.2017.
//

module;

#include <fstream>
#include <filesystem>

export module realn.codebox.core:file;

import :util.functions;

namespace realn::cb {
    export using byte = uint8_t;
    export using byte_vector = std::vector<byte>;

    export using istream = std::basic_istream<byte>;
    export using ostream = std::basic_ostream<byte>;

    export using fstream = std::basic_fstream<byte>;
    export using ifstream = std::basic_ifstream<byte>;
    export using ofstream = std::basic_ofstream<byte>;

    export template<class value_type = byte>
    std::streamsize file_size(std::basic_ifstream<value_type> &stream) {
        const auto pos = stream.tellg();
        auto pos_guard = on_scope_exit([&]() { stream.seekg(pos, std::ios::beg); });
        stream.seekg(0, std::ios::end);
        return stream.tellg();
    }

    export template<typename value_type = byte>
    std::streamsize file_size(std::basic_ofstream<value_type> &stream) {
        auto pos = stream.tellp();
        auto pos_guard = on_scope_exit([&]() { stream.seekp(pos, std::ios::beg); });
        stream.seekp(0, std::ios::end);
        return stream.tellp();
    }

    export template<class char_type, class string_type = std::basic_string<char_type> >
    std::streamsize file_size(const string_type &filepath) {
        auto file = ifstream(filepath, std::ios::in);
        return file_size(file);
    }

    export template<class char_type, class string_type = std::basic_string<char_type> >
    bool file_exists(const string_type &filepath) {
        auto file = ifstream(filepath, std::ios::in);
        return file.is_open();
    }

    export bool read_file(ifstream &stream, byte_vector &out_data) {
        const auto size = file_size(stream);
        out_data.resize(static_cast<byte_vector::size_type>(size));
        stream.read(out_data.data(), size);
        return !stream.fail();
    }

    export byte_vector read_file(ifstream &stream) {
        byte_vector result;
        if (!read_file(stream, result)) {
            return {};
        }
        return result;
    }

    export bool read_file(const std::filesystem::path &filepath, byte_vector &out_data) {
        auto file = ifstream(filepath, std::ios::binary | std::ios::in);
        if (!file.is_open())
            return false;
        return read_file(file, out_data);
    }

    export byte_vector read_file(const std::filesystem::path &filepath) {
        auto file = ifstream(filepath, std::ios::binary | std::ios::in);
        if (!file.is_open())
            return {};
        return read_file(file);
    }

    export bool writefile(ofstream &stream, const byte_vector &data) {
        if (data.empty())
            return false;
        stream.write(data.data(), static_cast<std::streamsize>(data.size()));
        return !stream.fail();
    }

    export bool writefile(const std::filesystem::path &filepath, const byte_vector &data) {
        auto file = ofstream(filepath, std::ios::binary | std::ios::trunc | std::ios::out);
        if (!file.is_open()) {
            return false;
        }
        return writefile(file, data);
    }

    export std::u8string read_textfile_utf8(std::ifstream &file) {
        const auto size = file_size(file);
        if (size == 0)
            return {};

        auto data = std::u8string(static_cast<size_t>(size), 0);
        const auto data_ptr = reinterpret_cast<std::istream::char_type *>(&data[0]);
        file.read(data_ptr, size);

        return data;
    }

    export std::u8string read_textfile_utf8(const std::filesystem::path &filepath) {
        auto file = std::ifstream(filepath, std::ios::in | std::ios::binary);
        if (!file.is_open())
            return {};
        return read_textfile_utf8(file);
    }

    export std::u16string read_textfile_utf16(std::ifstream &file) {
        auto size = file_size(file);
        if (size == 0)
            return {};

        const auto string_length = size / static_cast<std::streamsize>(sizeof(std::u16string::value_type));
        size = string_length * static_cast<std::streamsize>(sizeof(std::u16string::value_type));

        auto data = std::u16string(static_cast<std::u16string::size_type>(size), 0);
        const auto data_ptr = reinterpret_cast<std::ifstream::char_type *>(&data[0]);
        file.read(data_ptr, size);

        return data;
    }

    export std::u16string read_textfile_utf16(const std::filesystem::path &filepath) {
        auto file = std::ifstream(filepath, std::ios::in | std::ios::binary);
        if (!file.is_open())
            return {};
        return read_textfile_utf16(file);
    }

    export bool write_textfile_utf8(std::ofstream &file, const std::u8string &text) {
        file.write(reinterpret_cast<const std::ostream::char_type *>(text.data()),
                   static_cast<std::streamsize>(text.size()));
        return !file.fail();
    }

    export bool write_textfile_utf8(const std::filesystem::path &filepath, const std::u8string &text) {
        auto file = std::ofstream(filepath, std::ios::out | std::ios::trunc | std::ios::binary);
        if (!file.is_open())
            return false;
        return write_textfile_utf8(file, text);
    }

    export bool write_textfile_utf16(std::ofstream &file, const std::u16string &text) {
        const auto size = static_cast<std::streamsize>(text.length() * sizeof(std::u16string::value_type));
        const auto data_ptr = reinterpret_cast<const std::ofstream::char_type *>(text.data());
        file.write(data_ptr, size);
        return !file.fail();
    }

    export bool write_textfile_utf16(const std::filesystem::path &filepath, const std::u16string &text) {
        auto file = std::ofstream(filepath, std::ios::out | std::ios::trunc | std::ios::binary);
        if (!file.is_open())
            return false;
        return write_textfile_utf16(file, text);
    }
}
