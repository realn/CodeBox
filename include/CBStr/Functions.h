#pragma once

#include "Defines.h"

namespace cb {
  // string checking

  extern size_t count(string const & text, string const & what);

  extern bool subcmp(string const& text, string const& what, size_t const pos = 0);

  extern bool subcmp(string const& text, const strvector& list, size_t const pos = 0);

  extern bool rsubcmp(string const& text, string const& what, size_t const roffset = 0);

  extern bool subrcmp(string const& text, string const& what, size_t const offset = 0);

  extern size_t strposrev(string const& text, size_t const roffset = 0);


  // string manipulation

  extern string substrpos(string const& text, size_t const pos = 0, size_t const endpos = string::npos);

  extern string replace(string const& text, string const& what, string const& with);

  extern string replace(string const& text, const strmap& list, bool const flip = false);

  extern string join(const strvector& list, string const& glue = string());

  extern strvector split(string const& text, string const& knife = string(), bool const skipEmpty = false);

  extern string varReplace(string const& format, const strvector& list);

  extern string repeat(string const& text, size_t const times);
}