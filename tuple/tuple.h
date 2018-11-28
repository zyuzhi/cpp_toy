#pragma once
#include <cstdint>

namespace tuple {

template<typename ...Ts>
struct tuple;

template<typename T, typename ...Ts>
struct tuple<T, Ts...> : tuple<Ts...> {
  explicit tuple(const T& v, const Ts&... args)
    : value(v), tuple<Ts...>(args...) {}
  T value;
};

template<>
struct tuple<> {
};

using null_tuple = tuple<>;

template<typename T>
struct tuple<T> : null_tuple {
  explicit tuple(const T& v)
    : value(v) {}
  T value;
};

template<std::size_t Index, typename ...Ts>
struct tuple_traits;

template<std::size_t Index, typename T, typename ...Ts>
struct tuple_traits<Index, tuple<T, Ts...> > {
  using ClassType = typename tuple_traits<Index - 1, tuple<Ts...> >::ClassType;
  using ValueType = typename tuple_traits<Index - 1, tuple<Ts...> >::ValueType;
};

template<typename T, typename ...Ts>
struct tuple_traits<0, tuple<T, Ts...> > {
  using ClassType = tuple<T, Ts...>;
  using ValueType = T;
};

template<std::size_t Index>
struct tuple_traits<Index, null_tuple> {
  using ClassType = null_tuple;
  using ValueType = void;
};

template<std::size_t Index, typename ...Ts>
typename tuple_traits<Index, tuple<Ts...> >::ValueType &
get(tuple<Ts...> &t) {
    using ClassType = typename tuple_traits<Index, tuple<Ts...> >::ClassType;
    return ((ClassType *)&t)->value;
};

template<typename ...Ts>
tuple<Ts...> make_tuple(const Ts &... args) {
    return tuple<Ts...>{args...};
}

}
