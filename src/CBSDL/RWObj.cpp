#include "stdafx.h"
#include <CBSDL/RWObj.h>
#include <CBCore/StringConvert.h>

inline SDL_RWops* get(cb::sdl::RWObj& obj) {
  return reinterpret_cast<SDL_RWops*>(obj.get());
}

inline SDL_RWops* get(cb::sdl::RWObj const& obj) {
  return reinterpret_cast<SDL_RWops*>(obj.get());
}

namespace cb {
  namespace sdl {
    RWObj::RWObj(RWObj && other)
      : mObj(nullptr) {
      std::swap(mObj, other.mObj);
    }

    RWObj::~RWObj() {
      close();
    }

    void RWObj::setPos(s64 const pos, SeekPos const whence) {
      SDL_RWseek(::get(*this), pos, static_cast<int>(whence));
      CB_SDL_CHECKERRORS();
    }

    Sint64 RWObj::getPos() const {
      auto res = SDL_RWtell(::get(*this));
      CB_SDL_CHECKERRORS();
      return res;
    }

    Sint64 RWObj::getSize() const {
      auto res = SDL_RWsize(::get(*this));
      CB_SDL_CHECKERRORS();
      return res;
    }

    void RWObj::close() {
      if(mObj) {
        SDL_RWclose(::get(*this));
        mObj = nullptr;
      }
    }

    void RWObj::readPriv(cb::byte * pData, size_t const size) {
      SDL_RWread(::get(*this), pData, size, 1);
      CB_SDL_CHECKERRORS();
    }

    void RWObj::writePriv(const cb::byte * pData, size_t const size) {
      SDL_RWwrite(::get(*this), pData, size, 1);
      CB_SDL_CHECKERRORS();
    }

    RWObj RWObj::fromFile(cb::string const & filepath, FileMode const mode) {
      auto szFilePath = toUtf8(filepath);
      auto szMode = "";
      switch(mode) {
      case FileMode::read:  szMode = "rb";  break;
      case FileMode::write: szMode = "wb";  break;
      case FileMode::Append: szMode = "ab"; break;
      case FileMode::ReadWrite: szMode = "r+b"; break;
      case FileMode::ReadWriteForce: szMode = "w+b"; break;
      default:
        throw std::exception("Unknown file mode for SDL RWops.");
      }
      auto obj = SDL_RWFromFile(szFilePath.data(), szMode);
      CB_SDL_CHECKERRORS();
      return RWObj(obj);
    }

    RWObj RWObj::fromMemory(std::vector<cb::byte>& data) {
      auto obj = SDL_RWFromMem(data.data(), static_cast<int>(data.size()));
      CB_SDL_CHECKERRORS();
      return RWObj(obj);
    }

    RWObj RWObj::fromConstMemory(std::vector<cb::byte> const & data) {
      auto obj = SDL_RWFromConstMem(data.data(), static_cast<int>(data.size()));
      CB_SDL_CHECKERRORS();
      return RWObj(obj);
    }
  }
}
