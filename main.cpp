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
  struct Foo {
    Foo(int i) : i_(i) {}
    void echo() {
      std::cout << i_ << std::endl;
    }
   private:
    int i_;
  };
  using namespace functional;
  std::cout << std::is_same<typename functional::function_traits<decltype(test_tuple)>::Return, void>::value << std::endl;
  const auto lambda_f = [](){return 1;};
  function<int()> f1(lambda_f);
  function<void()> f2(test_tuple);
  function<void (Foo::*)()> f3(&Foo::echo);
  std::cout << f1() << std::endl;
  f2();
  Foo o(4);
  f3(&o);
}

int main() {
  test_functional();
  return 0;
}
