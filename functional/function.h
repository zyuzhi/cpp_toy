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
struct function_traits<R (C::*)(Args...) const> {
  using RawType = R(C::*)(Args...) const;
  using Return = R;
  using Class = C;
};

template<typename R, typename ...Args>
struct function_traits<R (Args...)> {
  using RawType = R(*)(Args...);
  using Return = R;
};

template<typename R, typename ...Args>
struct function_traits<R (Args...) const> : function_traits<R (Args...)> {};

template<typename F>
struct function {
  using Function = typename function_traits<F>::RawType;
  using Return = typename function_traits<F>::Return;
  function() = delete;
  explicit function(const Function& f) : f_(f) {}
  explicit function(Function&& f) : f_(std::forward<Function>(f)) {}
  function(const function &func) : f_(func.f_) {}
  function(function &&func) : f_(std::move(func.f_)) {}

  template<typename ...Args>
  Return operator()(Args&&... args) {
    return f_(std::forward<Args>(args)...);
  }

  template<typename Class, typename ...Args>
  Return operator()(Class* c, Args&&... args) {
    return (c->*f_)(std::forward<Args>(args)...);
  }
 private:
  Function f_;
};

}
