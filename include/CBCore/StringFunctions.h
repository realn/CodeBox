#pragma once

#include "Defines.h"

namespace cb {
  // string checking

  size_t count(string const& text, string const& what);

  bool subcmp(string const& text, string const& what, size_t const pos = 0);

  bool subcmp(string const& text, const strvector& list, size_t const pos = 0);

  bool rsubcmp(string const& text, string const& what, size_t const roffset = 0);

  bool subrcmp(string const& text, string const& what, size_t const offset = 0);

  strvector::const_iterator subfind(string const& text, strvector const& list, size_t const pos);

  size_t strposrev(string const& text, size_t const roffset = 0);

  bool ends_with(string const& text, string const& with);

  size_t strfind_of(string const& text, strvector const& list, size_t const offset = 0, strvector::const_iterator outIt = strvector::const_iterator());

  // string manipulation

  string substrpos(string const& text, size_t const pos = 0, size_t const endpos = string::npos);

  string replace(string const& text, string const& what, string const& with);

  string replace(string const& text, strmap const& list);

  string replace_by_char(string const& text, string const& what, string const& with);

  string replace_by_char(string const& text, strmap const& list);

  string join(const strvector& list, string const& glue = string());

  strvector split(string const& text, string const& knife = string(), bool const skipEmpty = false);

  strvector split(string const& text, strvector const& knifes = strvector(), bool const skipEmpty = false);

  string repeat(string const& text, size_t const times);
}