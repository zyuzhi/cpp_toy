#pragma once
#include <cstdint>
#include <tuple>

namespace functional {
template<typename F>
struct function_traits : function_traits<decltype(&F::operator())> {};

template<typename R, typename ...Args, typename C>
struct function_traits<R (C::*)(Args...)> {
  using RawType = R(C::*)(Args...);
  using Return = R;
  using Class = C;
};

template<typename R, typename ...Args, typename C>
struct function_traits<R (C::*)(Args...) const> : function_traits<R (C::*)(Args...)> {};

template<typename R, typename ...Args>
struct function_traits<R (Args...)> {
  using RawType = R(Args...);
  using Return = R;
};

template<typename R, typename ...Args>
struct function_traits<R (Args...) const> : function_traits<R (Args...)> {};
}
