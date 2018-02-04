#pragma once

#include "Defines.h"

namespace cb {
  // string checking

  extern size_t count(string const & text, string const & what);

  extern bool subcmp(string const& text, string const& what, size_t const pos = 0);

  extern bool subcmp(string const& text, const strvector& list, size_t const pos = 0);

  extern bool rsubcmp(string const& text, string const& what, size_t const roffset = 0);

  extern bool subrcmp(string const& text, string const& what, size_t const offset = 0);

  extern strvector::const_iterator subfind(string const& text, strvector const& list, size_t const pos);

  extern size_t strposrev(string const& text, size_t const roffset = 0);

  extern bool ends_with(string const& text, string const& with);

  extern size_t strfind_of(string const& text, strvector const& list, size_t const offset = 0, strvector::const_iterator outIt = strvector::const_iterator());

  // string manipulation

  extern string substrpos(string const& text, size_t const pos = 0, size_t const endpos = string::npos);

  extern string replace(string const& text, string const& what, string const& with);

  extern string replace(string const& text, strmap const& list);

  extern string replace_by_char(string const& text, string const& what, string const& with);

  extern string replace_by_char(string const& text, strmap const& list);

  extern string join(const strvector& list, string const& glue = string());

  extern strvector split(string const& text, string const& knife = string(), bool const skipEmpty = false);

  extern strvector split(string const& text, strvector const& knifes = strvector(), bool const skipEmpty = false);

  extern string varReplace(string const& format, const strvector& list);

  extern string repeat(string const& text, size_t const times);
}