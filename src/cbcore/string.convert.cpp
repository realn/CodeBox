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

    enum class to_string_conv_type {
        LOWER = 0,
        CAPITALIZED = 1,
        HIGHER = 2,
    };

    template<class string_t, class char_t>
    concept is_a_string = std::is_base_of_v<std::basic_string<char_t>, string_t>;

    template<class string_view_t, class char_t>
    concept is_a_string_view = std::is_base_of_v<std::basic_string_view<char_t>, string_view_t>;

    template<class string_type_t, class char_t>
    concept is_a_string_type = is_a_string<string_type_t, char_t> || is_a_string_view<string_type_t, char_t>;

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
                                                     const to_string_conv_type type = to_string_conv_type::LOWER) {
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
                                                       const to_string_conv_type type = to_string_conv_type::LOWER) {
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
                                                       const to_string_conv_type type = to_string_conv_type::LOWER) {
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

    template<class char_t, class string_t = std::basic_string<char_t> >
        requires is_a_string_type<string_t, char_t>
    constexpr auto bool_to_multi_string(const bool value, const to_string_conv_type type = to_string_conv_type::LOWER)
    = delete;

    template<>
    constexpr auto bool_to_multi_string<char, std::string>(const bool value, const to_string_conv_type type) {
        return bool_to_string(value, type);
    }

    template<>
    constexpr auto bool_to_multi_string<char, std::string_view>(const bool value, const to_string_conv_type type) {
        return bool_to_string(value, type);
    }

    template<>
    constexpr auto bool_to_multi_string<char8_t, std::u8string>(const bool value, const to_string_conv_type type) {
        return bool_to_utf8(value, type);
    }

    template<>
    constexpr auto bool_to_multi_string<char8_t, std::u8string_view>(const bool value, const to_string_conv_type type) {
        return bool_to_utf8(value, type);
    }

    template<>
    constexpr auto bool_to_multi_string<char16_t, std::u16string>(const bool value, const to_string_conv_type type) {
        return bool_to_utf16(value, type);
    }

    template<>
    constexpr auto bool_to_multi_string<char16_t,
        std::u16string_view>(const bool value, const to_string_conv_type type) {
        return bool_to_utf16(value, type);
    }

    template<>
    constexpr auto bool_to_multi_string<char32_t, std::u32string>(const bool value, const to_string_conv_type type) {
        return bool_to_utf32(value, type);
    }

    template<>
    constexpr auto bool_to_multi_string<char32_t,
        std::u32string_view>(const bool value, const to_string_conv_type type) {
        return bool_to_utf32(value, type);
    }

    export template<class char_t, class string_t = std::basic_string<char_t> >
        requires std::is_base_of_v<string_t, std::basic_string<char_t> >
    bool string_to_bool(const string_t &text, bool *result = nullptr) {
        if (text == bool_to_multi_string<char_t, string_t>(true, to_string_conv_type::LOWER) ||
            text == bool_to_multi_string<char_t, string_t>(true, to_string_conv_type::CAPITALIZED) ||
            text == bool_to_multi_string<char_t, string_t>(true, to_string_conv_type::HIGHER)) {
            set_if_valid(result, true);
            return true;
        }
        if (text == bool_to_multi_string<char_t, string_t>(false, to_string_conv_type::LOWER) ||
            text == bool_to_multi_string<char_t, string_t>(false, to_string_conv_type::CAPITALIZED) ||
            text == bool_to_multi_string<char_t, string_t>(false, to_string_conv_type::HIGHER)) {
            set_if_valid(result, false);
            return true;
        }
        return false;
    }

    export template<class char_type, class string_type = std::basic_string<char_type> >
    string_type::size_type utf_length(const string_type &text) {
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

    bool starts_with_bom(const std::string &s) {
        return starts_with_bom(s.begin(), s.end());
    }

    export template<class char_type, class string_type = std::basic_string<char_type> >
    bool starts_with_utf_bom(const string_type &text) {
        return starts_with_bom(text);
    }

    export template<class char_type, class string_type = std::basic_string<char_type> >
    bool is_valid_utf_string(const string_type &text) {
        return utf8::is_valid(text);
    }

    export template<class char_type, class string_type = std::basic_string<char_type> >
    auto replace_invalid_utf(const string_type &text, const char_type value) {
        return utf8::replace_invalid(text, value);
    }

    export template<class char_type, class string_type = std::basic_string<char_type> >
    auto replace_invalid_utf(const string_type &text) {
        return utf8::replace_invalid(text);
    }
}
