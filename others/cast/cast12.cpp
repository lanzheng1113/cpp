// this example shows implicit conversion by compiler when resolving function parameter
#include <iostream>
using namespace std;

class Foo
{
public:
  // single parameter constructor, can be used as an implicit conversion
  Foo (int foo) : m_foo (foo) 
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
  doBar(42); // implicit conversion from int to Foo
  Foo foo = 42;
  foo = 43;
}
