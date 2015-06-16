#include <cassert>

struct Base {
  // ...
};

struct Derived: Base {
   bool foo(long) {return true;}
};

int main() {
  Derived d;
  assert(d.foo(1));
}
