#pragma once

#include "Defines.h"

namespace cb {
  size_t filenameextpos(string const& filename);
  string filenameext(string const& filename);
  string filenamebase(string const& filename);
  string makefilename(string const& name, string const& ext);

  string clearpath(string const& path);

  size_t pathnamepos(string const& path);
  string pathname(string const& path);
  string pathbase(string const& path);
  string makepath(string const& path1, string const& path2);
}

