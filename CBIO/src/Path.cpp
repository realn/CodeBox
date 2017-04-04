#include "stdafx.h"
#include "../Path.h"

namespace cb {
  static const string g_extsep = L".";
  static const string g_dirsep = L"/";
  static const string g_backsep = L"\\";

  const size_t filenameextpos(const string & filename) {
    size_t pos = filename.find_last_of(g_extsep);
    if(pos != string::npos)
      pos++;
    return pos;
  }

  const string filenameext(const string & filename) {
    size_t pos = filenameextpos(filename);
    if(pos == string::npos) {
      return string();
    }

    return filename.substr(pos);
  }

  const string makefilename(const string & name, const string & ext) {
    return name + g_extsep + ext;
  }
  const string clearpath(const string & path) {
    if(path.empty())
      return path;

    size_t pos = path.find(g_backsep);
    string result = path;
    while(pos != string::npos) {
      result = result.replace(pos, g_backsep.length(), g_dirsep);

      pos = result.find(g_backsep);
    }
    string dbsep = g_dirsep + g_dirsep;
    pos = result.find(dbsep);
    while(pos != string::npos) {
      result = result.replace(pos, dbsep.length(), g_dirsep);

      pos = result.find(dbsep);
    }

    if(result.find_last_of(g_dirsep) == result.length() - 1) {
      return result.substr(0, result.length() - 1);
    }
    return result;
  }
  const size_t pathnamepos(const string & path) {
    size_t pos = path.find_last_of(g_dirsep);
    if(pos != string::npos)
      pos++;
    return pos;
  }

  const string pathname(const string & path) {
    size_t pos = pathnamepos(path);
    if(pos == string::npos)
      return string();

    return path.substr(pos);
  }

  const string pathbase(const string & path) {
    size_t pos = pathnamepos(path);
    if(pos == string::npos)
      return string();

    return path.substr(0, pos - 1);
  }

  const string makepath(const string & path1, const string & path2) {
    return clearpath(path1 + g_dirsep + path2);
  }
}