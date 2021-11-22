#pragma once

#include "Defines.h"

namespace cb {
  namespace sdl {
    enum class SeekPos {
      SET = RW_SEEK_SET,
      CUR = RW_SEEK_CUR,
      END = RW_SEEK_END,
    };

    enum class FileMode {
      read, // file must exist
      write,
      Append,
      ReadWrite, // file must exist
      ReadWriteForce,
    };

    class RWObj {
    private:
      void* mObj = nullptr;

    public:
      RWObj(RWObj const&) = delete;
      RWObj(RWObj&& other);
      ~RWObj();

      void* get() const { return mObj; }

      template<typename _Type>
      void read(_Type& obj) {
        readPriv(reinterpret_cast<cb::byte*>(&obj), sizeof(_Type));
      }
      template<typename _Type>
      void read(std::vector<_Type>& data) {
        readPriv(reinterpret_cast<cb::byte*>(data.data()), sizeof(_Type) * data.size());
      }
      template<typename _Type, size_t _Size>
      void read(std::array<_Type, _Size>& data) {
        readPriv(reinterpret_cast<cb::byte*>(data.data()), sizeof(_Type) * data.size());
      }

      template<typename _Type>
      void write(_Type const& obj) {
        writePriv(reinterpret_cast<const cb::byte*>(&obj), sizeof(_Type));
      }
      template<typename _Type>
      void write(std::vector<_Type> const& data) {
        writePriv(reinterpret_cast<const cb::byte*>(data.data()), sizeof(_Type) * data.size());
      }
      template<typename _Type, size_t _Size>
      void write(std::array<_Type, _Size> const& data) {
        writePriv(reinterpret_cast<const cb::byte*>(data.data()), sizeof(_Type) * data.size());
      }

      void setPos(s64 const pos, SeekPos const whence = SeekPos::SET);
      s64 getPos() const;
      s64 getSize() const;

      void close();

      static RWObj fromFile(cb::string const& filepath, FileMode const mode);
      static RWObj fromMemory(std::vector<cb::byte>& data);
      static RWObj fromConstMemory(std::vector<cb::byte> const& data);

    private:
      explicit RWObj(void* obj) : mObj(obj) {}

      void readPriv(cb::byte* pData, size_t const size);
      void writePriv(const cb::byte* pData, size_t const size);
    };
  }
}