// using namespace to show overload hide
#include <iostream>

namespace outer
{
  void foo(char c) { std::cout << "outer\n"; }

  namespace inner
  {
    void foo(int i) { std::cout << "inner\n"; }

    void bar() { foo('c'); }
  }
}

int main()
{
  outer::inner::bar(); // hide the outer::foo 
}
