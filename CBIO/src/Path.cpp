#include "stdafx.h"
#include "../Path.h"

using namespace std::string_literals;

namespace cb {
  const auto PATH_EXT_SEP = L"."s;
  const auto PATH_DIR_SEP = L"/"s;
  const auto PATH_DIR_BACKSEP = L"\\"s;
  const auto PATH_DIR_DBL_SEP = PATH_DIR_SEP + PATH_DIR_SEP;

  size_t filenameextpos(string const & filename) {
    auto pos = filename.find_last_of(PATH_EXT_SEP);
    if(pos != string::npos)
      pos++;
    return pos;
  }

  string filenameext(string const & filename) {
    auto pos = filenameextpos(filename);
    if(pos == string::npos) {
      return string();
    }

    return filename.substr(pos);
  }

  string makefilename(string const & name, string const & ext) {
    return name + PATH_EXT_SEP + ext;
  }

  string clearpath(string const & path) {
    if(path.empty())
      return path;

    auto pos = path.find(PATH_DIR_BACKSEP);
    auto result = path;
    while(pos != string::npos) {
      result = result.replace(pos, PATH_DIR_BACKSEP.length(), PATH_DIR_SEP);

      pos = result.find(PATH_DIR_BACKSEP);
    }

    pos = result.find(PATH_DIR_DBL_SEP);
    while(pos != string::npos) {
      result = result.replace(pos, PATH_DIR_DBL_SEP.length(), PATH_DIR_SEP);

      pos = result.find(PATH_DIR_DBL_SEP);
    }

    pos = result.find_last_of(PATH_DIR_SEP);
    if(pos != string::npos && pos + 1 == result.length()) {
      return result.substr(0, result.length() - 1);
    }
    return result;
  }

  size_t pathnamepos(string const & path) {
    auto pos = path.find_last_of(PATH_DIR_SEP);
    if(pos != string::npos)
      pos++;
    return pos;
  }

  string pathname(string const & path) {
    auto pos = pathnamepos(path);
    if(pos == string::npos)
      return string();

    return path.substr(pos);
  }

  string pathbase(string const & path) {
    auto pos = pathnamepos(path);
    if(pos == string::npos)
      return string();

    return path.substr(0, pos - 1);
  }

  string makepath(string const & path1, string const & path2) {
    return clearpath(path1 + PATH_DIR_SEP + path2);
  }
}