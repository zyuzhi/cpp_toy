#include <iostream>
#include "tuple/tuple.h"
#include "functional/function.h"

void test_tuple() {
  auto t = tuple::make_tuple(1, 'c', 2.03);
  auto t1 = t;
  auto t2 = std::move(t1);
  std::cout << tuple::get<0>(t) << std::endl;
  tuple::get<1>(t) = 'a';
  std::cout << tuple::get<1>(t) << std::endl;
}

void test_functional() {
  std::cout << std::is_same<typename functional::function_traits<decltype(test_tuple)>::Return, void>::value << std::endl;
}

int main() {
  test_functional();
  return 0;
}
