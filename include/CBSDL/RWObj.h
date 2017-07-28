#pragma once

#include "Defines.h"

#include <SDL_rwops.h>

namespace cb {
  namespace sdl {
    enum class SeekPos {
      SET = RW_SEEK_SET,
      CUR = RW_SEEK_CUR,
      END = RW_SEEK_END,
    };

    enum class FileMode {
      Read, // file must exist
      Write,
      Append,
      ReadWrite, // file must exist
      ReadWriteForce,
    };

    class CRWObj {
    private:
      SDL_RWops* mObj;

    public:
      CRWObj(SDL_RWops* obj = nullptr) : mObj(obj) {}
      CRWObj(CRWObj const&) = delete;
      CRWObj(CRWObj&& other);
      ~CRWObj();

      SDL_RWops* Get() const { return mObj; }

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

      template<typename _Type>
      void Write(_Type const& obj) {
        WritePriv(reinterpret_cast<const cb::byte*>(&obj), sizeof(_Type));
      }
      template<typename _Type>
      void Write(std::vector<_Type> const& data) {
        WritePriv(reinterpret_cast<const cb::byte*>(data.data()), sizeof(_Type) * data.size());
      }
      template<typename _Type, size_t _Size>
      void Write(std::array<_Type, _Size> const& data) {
        WritePriv(reinterpret_cast<const cb::byte*>(data.data()), sizeof(_Type) * data.size());
      }

      void SetPos(Sint64 const pos, SeekPos const whence = SeekPos::SET);
      Sint64 GetPos() const;
      Sint64 GetSize() const;

      void Close();

      static CRWObj FromFile(cb::string const& filepath, FileMode const mode);
      static CRWObj FromMemory(std::vector<cb::byte>& data);
      static CRWObj FromConstMemory(std::vector<cb::byte> const& data);

    private:
      void ReadPriv(cb::byte* pData, size_t const size);
      void WritePriv(const cb::byte* pData, size_t const size);
    };
  }
}