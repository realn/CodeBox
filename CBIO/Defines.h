#ifndef __CB_IO_DEFINES_H__
#define __CB_IO_DEFINES_H__

#include <string>
#include <fstream>
#include <vector>
#include <iostream>

namespace cb {
  typedef unsigned char byte;
  typedef std::vector<byte> bytevector;
  typedef std::vector<char> charvector;

  typedef std::wstring string;

  typedef std::wostream ostream;
  typedef std::wistream istream;

  typedef std::fstream fstream;
  typedef std::ifstream ifstream;
  typedef std::ofstream ofstream;

  template<typename _Elem, typename _Alloc>
  const _Elem* vectorptr(const std::vector<_Elem, _Alloc>& data) {
    if(data.empty())
      return nullptr;
    return &data[0];
  }
  
  template<typename _Elem, typename _Alloc>
  _Elem* vectorptr(std::vector<_Elem, _Alloc>& data) {
    if(data.empty())
      return nullptr;
    return &data[0];
  }

  template<typename _Type, typename _Elem, typename _Alloc>
  const _Type* vectorcastptr(const std::vector<_Elem, _Alloc>& data) {
    return reinterpret_cast<const _Type*>(vectorptr(data));
  }

  template<typename _Type, typename _Elem, typename _Alloc>
  _Type* vectorcastptr(std::vector<_Elem, _Alloc>& data) {
    return reinterpret_cast<_Type*>(vectorptr(data));
  }
}

#endif // !__CB_IO_DEFINES_H__

