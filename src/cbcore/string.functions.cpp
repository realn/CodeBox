module;

#include <algorithm>
#include <functional>
#include <ranges>
#include <set>
#include <string>

export module realn.codebox.core:string.functions;

import :string.convert;
import :util.functions;

namespace realn::cb {
    // string checking

    export template<class string_type = std::u8string>
    std::size_t count(string_type const &text, string_type const &what) {
        auto result = std::size_t{0};
        for (auto pos = text.find(what, 0);
             pos != string_type::npos;
             pos = text.find(what, pos + what.length())) {
            result++;
        }
        return result;
    }

    export template<class string_type = std::u8string>
        requires is_a_string_type<string_type>
    bool sub_compare(string_type const &text, string_type const &what, std::size_t const pos) {
        return text.compare(pos, what.length(), what) == 0;
    }

    export template<class string_type, class string_container_type>
        requires is_a_string_type<string_type> && has_value_type<string_type, string_container_type>
    bool sub_compare(string_type const &text, string_container_type const &list, size_t const pos) {
        return std::ranges::any_of(list, [&](const auto &item) {
            return sub_compare(text, item, pos);
        });
    }

    export template<class string_type>
        requires is_a_string_type<string_type>
    bool sub_compare_from_back(string_type const &text, string_type const &what, size_t const reverse_offset) {
        if (reverse_offset > text.length()) {
            return false;
        }
        return sub_compare(text, what, text.length() - reverse_offset);
    }

    export template<class string_type>
        requires is_a_string_type<string_type>
    bool sub_compare_from_word_back(string_type const &text, string_type const &what, size_t const offset) {
        if (offset < what.length()) {
            return false;
        }
        return text.compare(offset - what.length(), what.length(), what) == 0;
    }

    export template<class string_type = std::u8string, class string_container_type = std::set<string_type> >
        requires is_a_string_type<string_type> && has_value_type<string_type, string_container_type>
    auto sub_find(string_type const &text, string_container_type const &list,
                  const typename string_type::size_type from_pos = 0) {
        for (auto pos = from_pos; pos < text.length(); ++pos) {
            if (sub_compare(text, list, pos)) {
                return pos;
            }
        }
        return string_type::npos;
    }

    // string manipulation

    export template<class string_type = std::u8string>
        requires is_a_string_type<string_type>
    string_type sub_string_by_pos(string_type const &text, size_t const pos, size_t const end_pos = string_type::npos) {
        if (pos == string_type::npos || pos >= text.length()) {
            return {};
        }
        if (end_pos == string_type::npos) {
            return text.substr(pos);
        }
        return text.substr(pos, end_pos - pos);
    }

    export template<class string_type = std::u8string>
        requires is_a_string_type<string_type>
    string_type replace(string_type const &text, string_type const &what, string_type const &with) {
        if (what.empty() || text.empty()) {
            return text;
        }
        auto result = string_type{};
        result.reserve(text.length());
        auto pos = size_t{0};
        while (pos != string_type::npos) {
            auto next_pos = text.find(what, pos);
            result += substrpos(text, pos, next_pos);

            if (next_pos != string_type::npos) {
                result += with;
                next_pos += what.length();
            }
            pos = next_pos;
        }
        return result;
    }

    export template<class string_type = std::u8string, class string_container_type =
        std::unordered_map<string_type, string_type> >
        requires is_a_string_type<string_type> && has_value_pair_type<string_type, string_type,
                     string_container_type>
    string_type replace(string_type const &text, const string_container_type &list) {
        auto result = text;
        for (auto &item: list) {
            result = replace(result, item.first, item.second);
        }
        return result;
    }

    export template<class string_type = std::u8string>
        requires is_a_string_type<string_type>
    string_type replace_by_char(string_type const &text, string_type const &what, string_type const &with) {
        auto result = string_type{};
        for (auto i = size_t{0}; i < text.length();) {
            if (sub_compare(text, what, i)) {
                result += with;
                i += what.length();
            } else {
                result += text[i];
                i++;
            }
        }
        return result;
    }

    export template<class string_type = std::u8string, class string_container_type =
        std::unordered_map<string_type, string_type> >
        requires is_a_string_type<string_type> && has_value_pair_type<string_type, string_type,
                     string_container_type>
    string_type replace_by_char(string_type const &text, string_container_type const &list) {
        auto result = string_type{};
        auto keys = map_vector_keys(list);
        for (auto i = size_t{0}; i < text.length();) {
            auto it = sub_find(text, keys, i);
            if (it != keys.end()) {
                auto mapit = list.find(*it);

                result += mapit->second;
                i += mapit->first.length();
            } else {
                result += text[i];
                i++;
            }
        }
        return result;
    }

    export template<class string_type = std::u8string, class string_container_type =
        std::vector<string_type> >
        requires is_a_string_type<string_type> && has_value_type<string_type, string_container_type>
    string_type join(string_container_type const &list, string_type const &glue) {
        auto result = string_type{};
        for (auto it = list.begin(); it != list.end();) {
            result += *it;
            ++it;
            if (it != list.end()) {
                result += glue;
            }
        }
        return result;
    }

    export template<class string_type = std::u8string, class string_container_type =
        std::vector<string_type> >
        requires is_a_string_type<string_type> && has_value_type<string_type, string_container_type>
    string_container_type split(string_type const &text, string_type const &knife, bool const skipEmpty = false) {
        auto result = string_container_type{};
        if (knife.empty()) {
            for (auto &item: text) {
                result.emplace_back(1, item);
            }
            return result;
        }

        auto pos = size_t{0};
        while (pos != string_type::npos) {
            auto next_pos = text.find(knife, pos);
            if (auto item = sub_string_by_pos(text, pos, next_pos); !(item.empty() && skipEmpty)) {
                result.push_back(item);
            }
            if (next_pos != string_type::npos) {
                next_pos += knife.length();
            }
            pos = next_pos;
        }
        return result;
    }

    export template<class string_type = std::u8string, class string_container_type =
        std::vector<string_type> >
        requires is_a_string_type<string_type> && has_value_type<string_type, string_container_type>
    string_container_type split(string_type const &text, string_container_type const &knifes, bool const skipEmpty) {
        auto result = string_container_type{};
        if (knifes.empty()) {
            for (auto &item: text) {
                result.emplace_back(1, item);
            }
            return result;
        }

        auto pos = size_t{0};
        auto it = knifes.end();
        while (pos != string_type::npos) {
            auto next_pos = strfind_of(text, knifes, pos, it);
            if (auto item = sub_string_by_pos<>(text, pos, next_pos); !(item.empty() && skipEmpty)) {
                result.push_back(item);
            }
            if (next_pos != string_type::npos) {
                next_pos += it->length();
            }
            pos = next_pos;
        }
        return result;
    }

    export template<class string_type = std::u8string>
        requires is_a_string_type<string_type>
    size_t string_pos_reverse(string_type const &text, size_t const reverse_offset) {
        if (text.empty() || reverse_offset + 1 > text.length()) {
            return string_type::npos;
        }
        return text.length() - (1 + reverse_offset);
    }

    export template<class string_type = std::u8string>
        requires is_a_string_type<string_type>
    bool ends_with(string_type const &text, string_type const &with) {
        if (with.length() > text.length()) {
            return false;
        }
        return text.compare(text.length() - with.length(), with.length(), with) == 0;
    }

    export template<class string_type = std::u8string, class string_container_type =
        std::vector<string_type> >
        requires is_a_string_type<string_type> && has_value_type<string_type, string_container_type>
    size_t string_find_first_of(string_type const &text, string_container_type const &list, size_t const offset,
                                typename string_container_type::iterator &outIt) {
        size_t result = string_type::npos;
        outIt = list.end();
        for (auto it = list.begin(); it < list.end(); ++it) {
            if (it->empty())
                continue;

            auto pos = text.find(*it, offset);
            if (pos == string_type::npos)
                continue;

            if (result == string_type::npos || pos < result) {
                result = pos;
                outIt = it;
            }
        }
        return result;
    }

    export template<class string_type = std::u8string>
        requires is_a_string_type<string_type>
    string_type repeat(string_type const &text, size_t const times) {
        if (times == 0)
            return {};
        if (times == 1)
            return text;

        auto result = string_type{};
        do_times(times, [&]() {
            result += text;
        });
        return result;
    }

    void to_variable_string(const size_t i, std::string &output) {
        output = std::string{str_format_brace_left} + std::to_string(i) + std::string{str_format_brace_right};
    }

    void to_variable_string(const size_t i, std::u8string &output) {
        output = std::u8string{utf8_format_brace_left} + cast_string_to_u8(std::to_string(i)) + std::u8string{
                     utf8_format_brace_right
                 };
    }

    void to_variable_string(const size_t i, std::u16string &output) {
        output = std::u16string{utf16_format_brace_left} + utf_convert_to_u16(cast_string_to_u8(std::to_string(i))) +
                 std::u16string{utf16_format_brace_right};
    }

    void to_variable_string(const size_t i, std::u32string &output) {
        output = std::u32string{utf32_format_brace_left} + utf_convert_to_u32(cast_string_to_u8(std::to_string(i))) +
                 std::u32string{utf32_format_brace_right};
    }

    export template<class string_type = std::u8string, class string_container_type =
        std::vector<string_type> >
        requires is_a_string_type<string_type> && has_value_type<string_type, string_container_type>
    auto variable_replace(string_type const &format, string_container_type const &list) {
        if (format.empty()) {
            return {};
        }
        if (list.empty()) {
            return format;
        }

        auto result = format;
        string_type var{};
        for (auto i = size_t{0}; i < list.size(); i++) {
            to_variable_string(i, var);
            result = replace(result, var, list[i]);
        }

        return result;
    }
}
