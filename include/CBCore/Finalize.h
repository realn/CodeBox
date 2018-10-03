#pragma once

namespace cb {
  template<typename _LambdaT>
  class OnScopeExit {
  private:
    _LambdaT mLambda;
  public:
    OnScopeExit(_LambdaT onScope) : mLambda(onScope) {}
    ~OnScopeExit() { mLambda(); }
  };

  template<typename _LambdaT>
  auto finalize(_LambdaT onScopeExit) {
    return OnScopeExit<_LambdaT>(onScopeExit);
  }
}