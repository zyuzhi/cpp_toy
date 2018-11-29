#include <iostream>
#include "tuple/tuple.h"

int main() {
  auto t = tuple::make_tuple(1, 'c', 2.03);
  auto t1 = t;
  auto t2 = std::move(t1);
  std::cout << tuple::get<0>(t) << std::endl;
  tuple::get<1>(t) = 'a';
  std::cout << tuple::get<1>(t) << std::endl;
  return 0;
}
