#pragma once

#include <glm/fwd.hpp>

#include <CBCore/Defines.h>

namespace cb {
  namespace gl {
    using OGLObjId = unsigned;
    using AttributeId = unsigned;
    using UniformId = unsigned;

    template<typename _Type, typename _BindFunc, typename _UnBindFunc>
    class BindGuard {
    private:
      _Type const* mObj;
      _BindFunc mBind;
      _UnBindFunc mUnBind;

    public:
      BindGuard(_Type const& obj, _BindFunc bindFunc, _UnBindFunc unBindFunc)
        : mObj(&obj), mBind(bindFunc), mUnBind(unBindFunc) {
        mBind(mObj);
      }
      BindGuard(BindGuard<_Type, _BindFunc, _UnBindFunc> const&) = delete;
      BindGuard(BindGuard<_Type, _BindFunc, _UnBindFunc>&&) = default;
      ~BindGuard() {
        if(mObj) mUnBind(mObj);
      }

      BindGuard<_Type, _BindFunc, _UnBindFunc>& operator=(BindGuard<_Type, _BindFunc, _UnBindFunc> const&) = delete;
      BindGuard<_Type, _BindFunc, _UnBindFunc>& operator=(BindGuard<_Type, _BindFunc, _UnBindFunc>&&) = default;
    };

    template<typename _Type, typename ... _Args>
    auto bind(_Type const& obj, _Args ... args) {
      auto bindFunc = [args...](_Type const* obj)->void{ obj->bind(args...); };
      auto unBindFunc = [args...](_Type const* obj)->void{ obj->unBind(args...); };
      return BindGuard<_Type, decltype(bindFunc), decltype(unBindFunc)>(obj, bindFunc, unBindFunc);
    }
  }
}
