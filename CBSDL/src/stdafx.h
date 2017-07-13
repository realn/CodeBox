#pragma once

#include <string>
#include <vector>
#include <map>
#include <algorithm>

#include <glm/glm.hpp>

#include <SDL.h>

#include <CBStr/Defines.h>
#include <CBStr/StringEx.h>

namespace cb {
  namespace detail {
    template<typename _FlagT>
    std::vector<_FlagT> fromflags(Uint32 const flags, std::vector<_FlagT>& result) {
      return result;
    }

    template<typename _FlagT, typename ... _ArgsT>
    std::vector<_FlagT> fromflags(Uint32 const flags, std::vector<_FlagT>& result, _FlagT flag, _ArgsT ... args) {
      if((flags & static_cast<Uint32>(flag)) > 0) {
        result.push_back(flag);
      }
      return detail::fromflags(flags, result, args...);
    }
  }

  template<typename _FlagsT>
  Uint32 genflags(const _FlagsT& flags) {
    auto result = 0u;
    for(auto& item : flags) {
      result |= static_cast<Uint32>(item);
    }
    return result;
  }

  template<typename _FlagT, typename ... _ArgsT>
  std::vector<_FlagT> fromflags(Uint32 const flags, _FlagT const& flag, _ArgsT ... args) {
    return detail::fromflags(flags, std::vector<_FlagT>(), flag, args...);
  }
}