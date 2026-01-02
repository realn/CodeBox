//
// Created by noname on 30.12.2025.
//

module;

#include <algorithm>
#include <map>
#include <vector>

export module realn.codebox.core:util.functions;

namespace realn::cb {
    template<class key_type, class value_type, class container_type>
    concept has_value_pair_type = std::is_same_v<typename container_type::value_type, std::pair<key_type, value_type> >;

    template<class value_type, class container_type>
    concept has_value_type = std::is_same_v<typename container_type::value_type, value_type>;

    export template<class key_type, class value_type, class container_type = std::map<key_type, value_type> >
        requires has_value_pair_type<key_type, value_type, container_type>
    std::vector<value_type> map_vector_values(const container_type &obj) {
        auto result = std::vector<value_type>();
        std::ranges::transform(obj, std::back_inserter(result), [](const auto &item) {
            return item.second;
        });
        return result;
    }

    export template<typename key_type, typename value_type, class container_type>
        requires has_value_pair_type<key_type, value_type, container_type>
    std::vector<key_type> map_vector_keys(const container_type &obj) {
        auto result = std::vector<key_type>();
        std::ranges::transform(obj, std::back_inserter(result), [](const auto &item) {
            return item.first;
        });
        return result;
    }

    export template<typename key_type, typename value_type>
    std::map<value_type, key_type> map_flip(const std::map<key_type, value_type> &obj) {
        auto result = std::map<value_type, key_type>();
        std::ranges::transform(obj, std::inserter(result), [](const auto &item) {
            return {item.second, item.first};
        });
        return result;
    }

    export template<class value_type>
    [[maybe_unused]] bool set_if_valid(value_type *pvalue, const value_type &value) {
        if (pvalue) {
            *pvalue = value;
            return true;
        }
        return false;
    }

    export template<class size_type, class unary_function_type>
    void do_times(const size_type times, unary_function_type func) {
        for (auto i = size_type{0}; i < times; ++i) {
            func();
        }
    }

    template<class iterator_type>
    struct reverse_adapter {
        iterator_type &iterable;
        auto begin() { return std::rbegin(iterable); }
        auto begin() const { return std::rbegin(iterable); }
        auto end() { return std::rend(iterable); }
        auto end() const { return std::rend(iterable); }
    };

    export template<class iterator_type>
    reverse_adapter<iterator_type> reverse(iterator_type &&iterable) {
        return {iterable};
    }

    namespace detail {
        template<class func_type>
        class on_scope_exit_caller {
            func_type m_func;

        public:
            explicit on_scope_exit_caller(func_type func) : m_func(std::move(func)) {
            }

            on_scope_exit_caller(const on_scope_exit_caller &) = delete;

            on_scope_exit_caller(on_scope_exit_caller &&) = default;

            ~on_scope_exit_caller() {
                m_func();
            }
        };
    }

    export template<class func_type>
    detail::on_scope_exit_caller<func_type> on_scope_exit(func_type func) {
        return detail::on_scope_exit_caller<func_type>{func};
    }
}
