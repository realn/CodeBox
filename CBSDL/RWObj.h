#pragma once

#include "Defines.h"

#include <SDL_rwops.h>

namespace cb {
  namespace sdl {
    class CRWObj {
    private:
      SDL_RWops* mObj;

    public:
      CRWObj(SDL_RWops* obj = nullptr) : mObj(obj) {}
      CRWObj(CRWObj const&) = delete;
      CRWObj(CRWObj&& other);
      ~CRWObj();

      template<typename _Type>
      void Read(_Type& obj) {
        ReadPriv(reinterpret_cast<cb::byte*>(&obj), sizeof(_Type));
      }
      template<typename _Type>
      void Read(std::vector<_Type>& data) {
        ReadPriv(reinterpret_cast<cb::byte*>(data.data()), sizeof(_Type) * data.size());
      }
      template<typename _Type, size_t _Size>
      void Read(std::array<_Type, _Size>& data) {
        ReadPriv(reinterpret_cast<cb::byte*>(data.data()), sizeof(_Type) * data.size());
      }

      void Close();

    private:
      void ReadPriv(cb::byte* pData, size_t const size);
      void WritePriv(const cb::byte* pData, size_t const size);
    };
  }
}