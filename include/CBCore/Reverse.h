#pragma once

namespace cb {
  template<class _T>
  struct reverse_adapter {
    _T& iterable;
  public:
    auto begin() { return std::rbegin(iterable); }
    auto begin() const { return std::rbegin(iterable); }
    auto end() { return std::rend(iterable); }
    auto end() const { return std::rend(iterable); }
  };

  template<class _T>
  reverse_adapter<_T> reverse(_T&& iterable) { return { iterable }; }
}