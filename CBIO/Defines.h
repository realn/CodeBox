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

  //typedef std::fstream fstream;
  //typedef std::ifstream ifstream;
  //typedef std::ofstream ofstream;

  typedef std::basic_fstream<byte> fstream;
  typedef std::basic_ifstream<byte> ifstream;
  typedef std::basic_ofstream<byte> ofstream;

  template<typename _Type>
  byte* byteptr(_Type& data) {
    return reinterpret_cast<byte*>(&data);
  }

  template<typename _Type>
  const byte* byteptr(const _Type& data) {
    return reinterpret_cast<const byte*>(&data);
  }

  template<typename _Type>
  byte* byteptr(_Type* data) {
    return reinterpret_cast<byte*>(data);
  }

  template<typename _Type>
  const byte* byteptr(const _Type* data) {
    return reinterpret_cast<const byte*>(data);
  }

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

  template<typename _TypeL, typename _TypeR>
  const bool all(const _TypeL& lvalue, const std::vector<_TypeR>& rvalues) {
    for(typename std::vector<_TypeR>::const_iterator it = rvalues.begin();
        it != rvalues.end(); it++) {
      if(lvalue != *it) {
        return false;
      }
    }
    return true;
  }

  template<typename _TypeL, typename _TypeR>
  const bool any(const _TypeL& lvalue, const std::initializer_list<_TypeR>& rvalues) {
    for(typename std::initializer_list<_TypeR>::const_iterator it = rvalues.begin();
        it != rvalues.end(); it++) {
      if(lvalue == *it) {
        return true;
      }
    }
    return false;
  }
}

#endif // !__CB_IO_DEFINES_H__

