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
      CBindGuard(CBindGuard<_Type, _BindFunc, _UnBindFunc>&&) = default;
      ~CBindGuard() {
        if(mObj) mUnBind(mObj);
      }

      CBindGuard<_Type, _BindFunc, _UnBindFunc>& operator=(CBindGuard<_Type, _BindFunc, _UnBindFunc> const&) = delete;
      CBindGuard<_Type, _BindFunc, _UnBindFunc>& operator=(CBindGuard<_Type, _BindFunc, _UnBindFunc>&&) = default;
    };

    template<typename _Type, typename ... _Args>
    auto bind(_Type const& obj, _Args ... args) {
      auto bindFunc = [args...](_Type const* obj)->void{ obj->bind(args...); };
      auto unBindFunc = [args...](_Type const* obj)->void{ obj->unBind(args...); };
      return CBindGuard<_Type, decltype(bindFunc), decltype(unBindFunc)>(obj, bindFunc, unBindFunc);
    }
  }
}
