#include <cassert>
// if name hiding not working, it may cause surprised behavior
// Since the Base author may not know the Derived code
// if the author of Base add a new method to Base
// then Derived may not be working as expected
struct Base {
  // ...
  bool foo(int) {return false;}
};

struct Derived: Base {
   using Base::foo; // simulate if name hiding not working
   bool foo(long) {return true;}
};

int main() {
  Derived d;
  assert(d.foo(1)); // will failed then print error info
}
