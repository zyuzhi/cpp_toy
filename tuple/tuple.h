#pragma once
#include <cstdint>
#include <memory>

namespace tuple {

template<typename ...Ts>
struct tuple;

template<typename T, typename ...Ts>
struct tuple<T, Ts...> : tuple<Ts...> {
  tuple() : value(T()), tuple<Ts...>() {}
  explicit tuple(const T& v, const Ts&... args) : value(v), tuple<Ts...>(args...) {}
  explicit tuple(T&& v, Ts&&... args) : value(std::forward<T>(v)), tuple<Ts...>(std::forward<Ts>(args)...) {}
  tuple(const tuple<T, Ts...>& t) : value(t.value), tuple<Ts...>(static_cast<const tuple<Ts...>&>(t)) {}
  tuple(tuple<T, Ts...>&& t) : value(std::move(t.value)), tuple<Ts...>(static_cast<const tuple<Ts...>&>(t)) {}

  tuple<T, Ts...>& operator=(const tuple<T, Ts...>& t) {
    value = t.value;
    static_cast<tuple<Ts...> *>(this)->operator=(t);
    return *this;
  }
  tuple<T, Ts...>& operator=(tuple<T, Ts...>&& t) {
    value = std::move(t.value);
    static_cast<tuple<Ts...> *>(this)->operator=(t);
    return *this;
  }
  T value;
};

template<>
struct tuple<> {
};

using null_tuple = tuple<>;

template<typename T>
struct tuple<T> : null_tuple {
  tuple() : value(T()) {}
  explicit tuple(const T& v) : value(v) {}
  explicit tuple(T&& v) : value(std::forward<T>(v)) {}
  tuple(const tuple<T>& t) : value(t.value) {}
  tuple(tuple<T>&& t) : value(std::move(t.value)) {}
  tuple<T>& operator=(const tuple<T> &t) {
    value = t.value;
    return *this;
  }
  tuple<T>& operator=(tuple<T>&& t) {
    value = std::move(t.value);
    return *this;
  }
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
