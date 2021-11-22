#pragma once

#include "Defines.h"
#include "Consts.h"

namespace cb {
  namespace gl {
    enum class BlendFactor {
      ZERO = 0,
      ONE = 1,
      SRC_COLOR = 0x0300,
      ONE_MINUS_SRC_COLOR = 0x0301,
      SRC_ALPHA = 0x0302,
      ONE_MINUS_SRC_ALPHA = 0x0303,
      DST_ALPHA = 0x0304,
      ONE_MINUS_DST_ALPHA = 0x0305,
      DST_COLOR = 0x0306,
      ONE_MINUS_DST_COLOR = 0x0307,
      SRC_ALPHA_SATURATE = 0x0308,
      CONSTANT_COLOR = 0x8001,
      ONE_MINUS_CONSTANT_COLOR = 0x8002,
      CONSTANT_ALPHA = 0x8003,
      ONE_MINUS_CONSTANT_ALPHA = 0x8004,
    };

    enum class BlendFunc {
      ADD = 0x8006,
      SUBTRACT = 0x800A,
      REVERSE_SUBTRACT = 0x800B,
      MIN = 0x8007,
      MAX = 0x8008,
    };

    enum class CullFace {
      FRONT = 0x0404,
      BACK = 0x0405,
      FRONT_AND_BACK = 0x0408,
    };

    enum class FrontFace {
      CW = 0x0900,
      CCW = 0x0901,
    };

    enum class DepthFunc {
      NEVER = 0x0200,
      LESS = 0x0201,
      EQUAL = 0x0202,
      LEQUAL = 0x0203,
      GREATER = 0x0204,
      NOTEQUAL = 0x0205,
      GEQUAL = 0x0206,
      ALWAYS = 0x0207,
    };

    enum class State {
      NONE = 0,
      BLEND = 0x0BE2,
      DEPTH_TEST = 0x0B71,
      CULL_FACE = 0x0B44,
    };

    struct BlendState {
      BlendFactor SrcFactor = BlendFactor::ONE;
      BlendFactor DstFactor = BlendFactor::ZERO;
      BlendFunc ColorFunc = BlendFunc::ADD;
      BlendFunc AlphaFunc = BlendFunc::ADD;
      glm::vec4 ConstColor = glm::vec4(1.0f);
      glm::bvec4 ColorMask = glm::bvec4(true);
    };

    struct CullState {
      CullFace Face = CullFace::BACK;
      FrontFace Front = FrontFace::CCW;
    };

    struct DepthState {
      DepthFunc Func = DepthFunc::LESS;
      bool Mask = true;
      float RangeNear = 0.0f;
      float RangeFar = 1.0f;
    };

    using statemap = std::map<State, bool>;

    void setStateEnabled(State const state, bool enabled);
    void setStateEnabled(statemap const& states) { for (auto& item : states) { setStateEnabled(item.first, item.second); } }
    void setState(BlendState const& state);
    void setState(CullState const& state);
    void setState(DepthState const& state);

    bool isStateEnabled(State const state);
    BlendState getBlendState();
    CullState getCullState();
    DepthState getDepthState();

    class StateGuard {
    private:
      statemap mStates;
    public:
      StateGuard(statemap const& states) : mStates(states) {}
      StateGuard(StateGuard&& other) = default;
      StateGuard(StateGuard const& other) = delete;
      ~StateGuard() { setStateEnabled(mStates); }

      void operator=(StateGuard&& other) { std::swap(mStates, other.mStates); }
      void operator=(StateGuard const& other) = delete;
    };

    inline StateGuard bindStateEnabled(State const state, bool const enabled) {
      setStateEnabled(state, enabled);
      return StateGuard({ {state, !enabled} });
    }
    inline StateGuard bindStateEnabled(statemap const& states) {
      setStateEnabled(states);
      auto nstates = states;
      for (auto& item : nstates) { item.second = !item.second; }
      return StateGuard(nstates);
    }
  }
}