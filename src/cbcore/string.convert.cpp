module;

#include <string>

#include "utf-cpp/source/utf8.h"

export module realn.codebox.core:string.convert;

import :util.functions;

namespace realn::cb {
    using namespace std::string_literals;
    using namespace std::string_view_literals;

    constexpr auto str_bool_true{"true"sv};
    constexpr auto str_bool_false{"false"sv};

    constexpr auto str_bool_true_cap{"True"sv};
    constexpr auto str_bool_false_cap{"False"sv};

    constexpr auto str_bool_true_high{"TRUE"sv};
    constexpr auto str_bool_false_high{"FALSE"sv};

    constexpr auto utf8_bool_true{u8"true"sv};
    constexpr auto utf8_bool_false{u8"false"sv};

    constexpr auto utf8_bool_true_cap{u8"True"sv};
    constexpr auto utf8_bool_false_cap{u8"False"sv};

    constexpr auto utf8_bool_true_high{u8"TRUE"sv};
    constexpr auto utf8_bool_false_high{u8"FALSE"sv};

    constexpr auto utf16_bool_true{u"true"sv};
    constexpr auto utf16_bool_false{u"false"sv};

    constexpr auto utf16_bool_true_cap{u"True"sv};
    constexpr auto utf16_bool_false_cap{u"False"sv};

    constexpr auto utf16_bool_true_high{u"TRUE"sv};
    constexpr auto utf16_bool_false_high{u"FALSE"sv};

    constexpr auto utf32_bool_true{U"true"sv};
    constexpr auto utf32_bool_false{U"false"sv};

    constexpr auto utf32_bool_true_cap{U"True"sv};
    constexpr auto utf32_bool_false_cap{U"False"sv};

    constexpr auto utf32_bool_true_high{U"TRUE"sv};
    constexpr auto utf32_bool_false_high{U"FALSE"sv};

    constexpr auto str_format_brace_left = "{"sv;
    constexpr auto str_format_brace_right = "}"sv;

    constexpr auto utf8_format_brace_left = u8"{"sv;
    constexpr auto utf8_format_brace_right = u8"}"sv;

    constexpr auto utf16_format_brace_left = u"{"sv;
    constexpr auto utf16_format_brace_right = u"}"sv;

    constexpr auto utf32_format_brace_left = U"{"sv;
    constexpr auto utf32_format_brace_right = U"}"sv;

    export enum class to_string_conv_type {
        LOWER = 0,
        CAPITALIZED = 1,
        HIGHER = 2,
    };

    template<class string_type>
    concept is_a_string =
            std::is_base_of_v<std::string, string_type> ||
            std::is_base_of_v<std::u8string, string_type> ||
            std::is_base_of_v<std::u16string, string_type> ||
            std::is_base_of_v<std::u32string, string_type>;

    template<class string_view_type>
    concept is_a_string_view =
            std::is_base_of_v<std::string_view, string_view_type> ||
            std::is_base_of_v<std::u8string_view, string_view_type> ||
            std::is_base_of_v<std::u16string_view, string_view_type> ||
            std::is_base_of_v<std::u32string_view, string_view_type>;

    template<class string_type>
    concept is_a_string_type = is_a_string<string_type> || is_a_string_view<string_type>;

    export std::u8string utf_convert_to_u8(const std::u16string &text) {
        return utf8::utf16tou8(text);
    }

    export std::u8string utf_convert_to_u8(const std::u32string &text) {
        return utf8::utf32tou8(text);
    }

    export std::u16string utf_convert_to_u16(std::u16string text) {
        return std::move(text);
    }

    export std::u16string utf_convert_to_u16(const std::u32string &text) {
        const auto temp = utf8::utf32tou8(text);
        return utf8::utf8to16(temp);
    }

    export std::u16string utf_convert_to_u16(const std::u8string &text) {
        return utf8::utf8to16(text);
    }

    export std::u32string utf_convert_to_u32(const std::u8string &text) {
        return utf8::utf8to32(text);
    }

    export std::u32string utf_convert_to_u32(const std::u16string &text) {
        const auto temp = utf8::utf16tou8(text);
        return utf8::utf8to32(temp);
    }

    export std::u32string utf_convert_to_u32(std::u32string text) {
        return std::move(text);
    }

    export std::u8string cast_string_to_u8(const std::string &text) {
        return {text.begin(), text.end()};
    }

    export constexpr std::string_view bool_to_string(const bool value,
                                                     const to_string_conv_type type = to_string_conv_type::LOWER) {
        switch (type) {
            case to_string_conv_type::CAPITALIZED:
                return value ? str_bool_true_cap : str_bool_false_cap;
            case to_string_conv_type::HIGHER:
                return value ? str_bool_true_high : str_bool_false_high;
            case to_string_conv_type::LOWER:
            default:
                return value ? str_bool_true : str_bool_false;
        }
    }

    export constexpr std::u8string_view bool_to_utf8(const bool value,
                                                     const to_string_conv_type type = to_string_conv_type::LOWER)
        noexcept {
        switch (type) {
            case to_string_conv_type::CAPITALIZED:
                return value ? utf8_bool_true_cap : utf8_bool_false_cap;
            case to_string_conv_type::HIGHER:
                return value ? utf8_bool_true_high : utf8_bool_false_high;
            case to_string_conv_type::LOWER:
            default:
                return value ? utf8_bool_true : utf8_bool_false;
        }
    }

    export constexpr std::u16string_view bool_to_utf16(const bool value,
                                                       const to_string_conv_type type = to_string_conv_type::LOWER)
        noexcept {
        switch (type) {
            case to_string_conv_type::CAPITALIZED:
                return value ? utf16_bool_true_cap : utf16_bool_false_cap;
            case to_string_conv_type::HIGHER:
                return value ? utf16_bool_true_high : utf16_bool_false_high;
            case to_string_conv_type::LOWER:
            default:
                return value ? utf16_bool_true : utf16_bool_false;
        }
    }

    export constexpr std::u32string_view bool_to_utf32(const bool value,
                                                       const to_string_conv_type type = to_string_conv_type::LOWER)
        noexcept {
        switch (type) {
            case to_string_conv_type::CAPITALIZED:
                return value ? utf32_bool_true_cap : utf32_bool_false_cap;
            case to_string_conv_type::HIGHER:
                return value ? utf32_bool_true_high : utf32_bool_false_high;
            case to_string_conv_type::LOWER:
            default:
                return value ? utf32_bool_true : utf32_bool_false;
        }
    }

    template<class string_type = std::u8string>
        requires is_a_string_type<string_type>
    constexpr auto bool_to_multi_string(const bool value, const to_string_conv_type type = to_string_conv_type::LOWER)
    = delete;

    template<>
    constexpr auto bool_to_multi_string<std::string>(const bool value, const to_string_conv_type type) {
        return bool_to_string(value, type);
    }

    template<>
    constexpr auto bool_to_multi_string<std::string_view>(const bool value, const to_string_conv_type type) {
        return bool_to_string(value, type);
    }

    template<>
    constexpr auto bool_to_multi_string<std::u8string>(const bool value, const to_string_conv_type type) {
        return bool_to_utf8(value, type);
    }

    template<>
    constexpr auto bool_to_multi_string<std::u8string_view>(const bool value, const to_string_conv_type type) {
        return bool_to_utf8(value, type);
    }

    template<>
    constexpr auto bool_to_multi_string<std::u16string>(const bool value, const to_string_conv_type type) {
        return bool_to_utf16(value, type);
    }

    template<>
    constexpr auto bool_to_multi_string<std::u16string_view>(const bool value, const to_string_conv_type type) {
        return bool_to_utf16(value, type);
    }

    template<>
    constexpr auto bool_to_multi_string<std::u32string>(const bool value, const to_string_conv_type type) {
        return bool_to_utf32(value, type);
    }

    template<>
    constexpr auto bool_to_multi_string<std::u32string_view>(const bool value, const to_string_conv_type type) {
        return bool_to_utf32(value, type);
    }

    export template<class string_type = std::u8string>
        requires is_a_string<string_type>
    bool string_to_bool(const string_type &text, bool *result) noexcept {
        if (text == bool_to_multi_string<string_type>(true, to_string_conv_type::LOWER) ||
            text == bool_to_multi_string<string_type>(true, to_string_conv_type::CAPITALIZED) ||
            text == bool_to_multi_string<string_type>(true, to_string_conv_type::HIGHER)) {
            set_if_valid(result, true);
            return true;
        }
        if (text == bool_to_multi_string<string_type>(false, to_string_conv_type::LOWER) ||
            text == bool_to_multi_string<string_type>(false, to_string_conv_type::CAPITALIZED) ||
            text == bool_to_multi_string<string_type>(false, to_string_conv_type::HIGHER)) {
            set_if_valid(result, false);
            return true;
        }
        return false;
    }

    export template<class string_type = std::u8string>
    bool string_to_bool(const string_type &text) noexcept(false) {
        bool value = false;
        if (!string_to_bool<string_type>(text, &value)) {
            throw std::runtime_error("bad string to bool conversion");
        }
        return value;
    }

    export std::string::size_type utf_length(const std::string &text) {
        return utf8::distance(text.begin(), text.end());
    }

    export std::u8string::size_type utf_length(const std::u8string &text) {
        return utf8::distance(text.begin(), text.end());
    }

    constexpr char8_t bom[] = {0xef, 0xbb, 0xbf};

    template<typename octet_iterator>
    bool starts_with_bom(octet_iterator it, octet_iterator end) {
        return (
            ((it != end) && (utf8::internal::mask8(*it++)) == bom[0]) &&
            ((it != end) && (utf8::internal::mask8(*it++)) == bom[1]) &&
            ((it != end) && (utf8::internal::mask8(*it)) == bom[2])
        );
    }

    export bool starts_with_utf8_bom(const std::string &text) {
        return starts_with_bom(text.begin(), text.end());
    }

    export bool starts_with_utf8_bom(const std::u8string &text) {
        return starts_with_bom(text.begin(), text.end());
    }

    export bool is_valid_utf8_string(const std::string &text) {
        return utf8::is_valid(text);
    }

    export bool is_valid_utf8_string(const std::u8string &text) {
        return utf8::is_valid(text);
    }

    export std::string replace_invalid_utf8(const std::string &text, const std::string::value_type value) {
        return utf8::replace_invalid(text, value);
    }

    export std::u8string replace_invalid_utf8(const std::u8string &text, const std::u8string::value_type value) {
        return utf8::replace_invalid(text, value);
    }

    export std::string replace_invalid_utf8(const std::string &text) {
        return utf8::replace_invalid(text);
    }

    export std::u8string replace_invalid_utf8(const std::u8string &text) {
        return utf8::replace_invalid(text);
    }
}
