#include "stdafx.h"
#include "../RWObj.h"

namespace cb {
  namespace sdl {
    CRWObj::CRWObj(CRWObj && other)
      : mObj(nullptr) {
      std::swap(mObj, other.mObj);
    }

    CRWObj::~CRWObj() {
      Close();
    }

    void CRWObj::Close() {
      if(mObj) {
        SDL_RWclose(mObj);
        mObj = nullptr;
      }
    }

    void CRWObj::ReadPriv(cb::byte * pData, size_t const size) {
      SDL_RWread(mObj, pData, size, 1);
      CB_SDL_CHECKERRORS();
    }

    void CRWObj::WritePriv(const cb::byte * pData, size_t const size) {
      SDL_RWwrite(mObj, pData, size, 1);
      CB_SDL_CHECKERRORS();
    }
  }
}
