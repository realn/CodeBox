#pragma once

#include <glm/fwd.hpp>

#include <CBCore/Defines.h>

namespace cb {
  namespace gl {
    using OGLObjId = unsigned;
    using AttributeId = unsigned;
    using UniformId = unsigned;

    template<typename _Type, typename _BindFunc, typename _UnBindFunc>
    class CBindGuard {
    private:
      _Type const* mObj;
      _BindFunc mBind;
      _UnBindFunc mUnBind;

    public:
      CBindGuard(_Type const& obj, _BindFunc bindFunc, _UnBindFunc unBindFunc)
        : mObj(&obj), mBind(bindFunc), mUnBind(unBindFunc) {
        mBind(mObj);
      }
      CBindGuard(CBindGuard<_Type, _BindFunc, _UnBindFunc> const&) = delete;
      CBindGuard(CBindGuard<_Type, _BindFunc, _UnBindFunc>&& other)
        : mObj(other.mObj), mBind(other.mBind), mUnBind(other.mUnBind) {
        other.mObj = nullptr;
      }
      ~CBindGuard() {
        if(mObj) mUnBind(mObj);
      }
    };

    template<typename _Type, typename ... _Args>
    auto bind(_Type const& obj, _Args ... args) {
      auto bindFunc = [args...](_Type const* obj)->void{ obj->Bind(args...); };
      auto unBindFunc = [args...](_Type const* obj)->void{ obj->UnBind(args...); };
      return CBindGuard<_Type, decltype(bindFunc), decltype(unBindFunc)>(obj, bindFunc, unBindFunc);
    }
  }
}
