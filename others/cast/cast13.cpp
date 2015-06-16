// this example shows when make constructor explicit 
// implicit conversion is not allowed any more 
#include <iostream>
using namespace std;

class Foo
{
public:
  // explicit constructor 
  explicit Foo (int foo) : m_foo (foo) 
  {
     cout << "Foo ctor called." << endl;
  }

  int getFoo () const { return m_foo; }

private:
  int m_foo;
};

void doBar(Foo foo) {
  int i = foo.getFoo();
  cout << "doBar: " << i << endl;
}
int main() {
  //doBar(42); // error: implicit conversion from int to Foo not allowed
  
  //Foo foo = 42; // error
 
  Foo foo(1);
  //foo = 42; // error: assignment prevent when explicit ctor used 
 
  doBar(Foo(42)); // ok
}
