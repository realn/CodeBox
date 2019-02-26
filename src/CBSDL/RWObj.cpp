#include "stdafx.h"
#include <CBSDL/RWObj.h>
#include <CBCore/StringConvert.h>

inline SDL_RWops* Get(cb::sdl::CRWObj& obj) {
  return reinterpret_cast<SDL_RWops*>(obj.Get());
}

inline SDL_RWops* Get(cb::sdl::CRWObj const& obj) {
  return reinterpret_cast<SDL_RWops*>(obj.Get());
}

namespace cb {
  namespace sdl {
    CRWObj::CRWObj(CRWObj && other)
      : mObj(nullptr) {
      std::swap(mObj, other.mObj);
    }

    CRWObj::~CRWObj() {
      Close();
    }

    void CRWObj::SetPos(Sint64 const pos, SeekPos const whence) {
      SDL_RWseek(::Get(*this), pos, static_cast<int>(whence));
      CB_SDL_CHECKERRORS();
    }

    Sint64 CRWObj::GetPos() const {
      auto res = SDL_RWtell(::Get(*this));
      CB_SDL_CHECKERRORS();
      return res;
    }

    Sint64 CRWObj::GetSize() const {
      auto res = SDL_RWsize(::Get(*this));
      CB_SDL_CHECKERRORS();
      return res;
    }

    void CRWObj::Close() {
      if(mObj) {
        SDL_RWclose(::Get(*this));
        mObj = nullptr;
      }
    }

    void CRWObj::ReadPriv(cb::byte * pData, size_t const size) {
      SDL_RWread(::Get(*this), pData, size, 1);
      CB_SDL_CHECKERRORS();
    }

    void CRWObj::WritePriv(const cb::byte * pData, size_t const size) {
      SDL_RWwrite(::Get(*this), pData, size, 1);
      CB_SDL_CHECKERRORS();
    }

    CRWObj CRWObj::FromFile(cb::string const & filepath, FileMode const mode) {
      auto szFilePath = toUtf8(filepath);
      auto szMode = "";
      switch(mode) {
      case FileMode::Read:  szMode = "rb";  break;
      case FileMode::Write: szMode = "wb";  break;
      case FileMode::Append: szMode = "ab"; break;
      case FileMode::ReadWrite: szMode = "r+b"; break;
      case FileMode::ReadWriteForce: szMode = "w+b"; break;
      default:
        throw std::exception("Unknown file mode for SDL RWops.");
      }
      auto obj = SDL_RWFromFile(szFilePath.data(), szMode);
      CB_SDL_CHECKERRORS();
      return CRWObj(obj);
    }

    CRWObj CRWObj::FromMemory(std::vector<cb::byte>& data) {
      auto obj = SDL_RWFromMem(data.data(), static_cast<int>(data.size()));
      CB_SDL_CHECKERRORS();
      return CRWObj(obj);
    }

    CRWObj CRWObj::FromConstMemory(std::vector<cb::byte> const & data) {
      auto obj = SDL_RWFromConstMem(data.data(), static_cast<int>(data.size()));
      CB_SDL_CHECKERRORS();
      return CRWObj(obj);
    }
  }
}
